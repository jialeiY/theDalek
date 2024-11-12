import { ExtensionContext } from "@foxglove/extension";
import { SceneUpdate, LinePrimitive, LineType, SpherePrimitive } from "@foxglove/schemas";

type Position2D = {
    x: number;
    y: number;
};

enum CurvatureDistribution {
    CONSIDER_PREVIOUS = 0,
    CONSIDER_NEXT = 1,
    CONSIDER_BOTH = 2,
    CONSTANT_NEXT = 3,    // the circle
    DONT_CARE = 4,
};

const kPolylineCapacity: number = 100;
const kInvalidRouteId: number = 0;

type StaticPolylinePod = {
    capacity: number;
    size: number;
    points: Position2D[];
};

type RouteTopic = {
    id: number;
    behaviorId: number;
    polyline: StaticPolylinePod;
    connectivityProperties: CurvatureDistribution[];
};




export function activate(extensionContext: ExtensionContext): void {
    extensionContext.registerMessageConverter({
        fromSchemaName: "cooboc.proto.RouteTopic",
        toSchemaName: "foxglove.SceneUpdate",
        converter: (routeTopic: RouteTopic) => {
            let spheres: SpherePrimitive[] = [];
            let lines: LinePrimitive[] = [];

            const isTopicValid: boolean = routeTopic.id != kInvalidRouteId;
            const hasRouteInTopic: boolean = routeTopic.polyline.size > 0;

            if (isTopicValid && hasRouteInTopic) {
                // Draw route on 3D
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

                const validatedPointsNumber: number = Math.min(kPolylineCapacity, routeTopic.polyline.size);
                for (let i = 0; i < validatedPointsNumber; ++i) {
                    polyline.points.push({
                        x: routeTopic.polyline.points[i]?.x as number,
                        y: routeTopic.polyline.points[i]?.y as number,
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
