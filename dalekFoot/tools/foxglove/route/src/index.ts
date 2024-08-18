import { ExtensionContext } from "@foxglove/extension";
import { SceneUpdate, LinePrimitive, LineType, SpherePrimitive } from "@foxglove/schemas";

type Position2D = {
    x: number;
    y: number;
};

enum CurvatureDistribution {
    CONSIDER_CURRENT = 0,
    CONSIDER_NEXT = 1,
    CONSIDER_BOTH = 2,
    CONSTANT = 3,    // the circle
    DONT_CARE = 4,
};

type RouteSegment = {
    endPoint: Position2D;
    curvatureDistribution: CurvatureDistribution;
};

type RouteTopic = {
    hasValue: boolean;
    routeId: number;
    routeSegmentSize: number;
    startPoint: Position2D;
    routeSegment: RouteSegment[];
};



export function activate(extensionContext: ExtensionContext): void {
    extensionContext.registerMessageConverter({
        fromSchemaName: "cooboc.proto.RouteTopic",
        toSchemaName: "foxglove.SceneUpdate",
        converter: (inputMessage: RouteTopic) => {
            //console.log(inputMessage);
            let spheres: SpherePrimitive[] = [];
            let lines: LinePrimitive[] = [];
            if ((inputMessage.hasValue) && (inputMessage.routeSegmentSize > 0)) {
                // spheres.push({
                //     pose: {
                //         position: {
                //             x: inputMessage.polyline[0]?.x || 0,
                //             y: inputMessage.polyline[0]?.y || 0,
                //             z: 0
                //         },
                //         orientation: { x: 0, y: 0, z: 0, w: 1 }
                //     },
                //     size: { x: 0.030, y: 0.030, z: 0.030 },
                //     color: { r: 1.0, g: 1.0, b: 1.0, a: 0.7 }
                // });
                // spheres.push({
                //     pose: {
                //         position: {
                //             x: inputMessage.polyline[inputMessage.polylineLength - 1]?.x || 0,
                //             y: inputMessage.polyline[inputMessage.polylineLength - 1]?.y || 0,
                //             z: 0
                //         },
                //         orientation: { x: 0, y: 0, z: 0, w: 1 }
                //     },
                //     size: { x: 0.030, y: 0.030, z: 0.030 },
                //     color: { r: 1.0, g: 1.0, b: 1.0, a: 0.7 }
                // });

                // Construct the lines for route segments
                const polyline: LinePrimitive = {
                    type: LineType.LINE_STRIP,
                    pose: {
                        position: { x: 0, y: 0, z: 0 },
                        orientation: { x: 0, y: 0, z: 0, w: 1 }
                    },
                    thickness: 0.050,
                    scale_invariant: false,
                    points: [],
                    color: { r: 0.2, g: 0.2, b: 0.2, a: 0.7 },
                    colors: [],
                    indices: []
                };

                // Put the start point
                polyline.points.push({
                    x: inputMessage.startPoint.x,
                    y: inputMessage.startPoint.y,
                    z: 0
                });

                // Put the route segments into polyline
                for (let i = 0; i < inputMessage.routeSegmentSize; ++i) {
                    polyline.points.push({
                        x: inputMessage.routeSegment[i]?.endPoint.x || 0,
                        y: inputMessage.routeSegment[i]?.endPoint.y || 0,
                        z: 0
                    });
                }

                lines.push(polyline);
            }


            const sceneUpdateMessage: SceneUpdate = {
                deletions: [],
                entities: [
                    {
                        id: "Route",
                        timestamp: { sec: 0, nsec: 0 },
                        frame_id: "WORLD",
                        lifetime: { sec: 10, nsec: 10000 },
                        frame_locked: false,
                        metadata: [],
                        arrows: [],
                        cubes: [],
                        spheres: spheres,
                        cylinders: [],
                        lines: lines,
                        triangles: [],
                        texts: [],
                        models: [],
                    },
                ],
            };

            return sceneUpdateMessage;
        }
    });
}
