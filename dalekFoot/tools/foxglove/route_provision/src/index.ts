import { ExtensionContext } from "@foxglove/extension";
import { SceneUpdate, LinePrimitive, LineType, SpherePrimitive } from "@foxglove/schemas";

type Position2D = {
    x: number;
    y: number;
};

type RouteTopic = {
    hasValue: boolean;
    routeId: number;
    polylineLength: number;
    polyline: Position2D[];
};

export function activate(extensionContext: ExtensionContext): void {
    extensionContext.registerMessageConverter({
        fromSchemaName: "cooboc.proto.RouteTopic",
        toSchemaName: "foxglove.SceneUpdate",
        converter: (inputMessage: RouteTopic) => {
            let spheres: SpherePrimitive[] = [];
            let lines: LinePrimitive[] = [];
            if ((inputMessage.hasValue) && (inputMessage.polylineLength > 0)) {
                spheres.push({
                    pose: {
                        position: {
                            x: inputMessage.polyline[0]?.x || 0,
                            y: inputMessage.polyline[0]?.y || 0,
                            z: 0
                        },
                        orientation: { x: 0, y: 0, z: 0, w: 1 }
                    },
                    size: {x: 0.030, y:0.030, z:0.030},
                    color:{ r: 1.0, g: 1.0, b: 1.0, a: 0.7 }
                });
                spheres.push({
                    pose: {
                        position: {
                            x: inputMessage.polyline[inputMessage.polylineLength-1]?.x || 0,
                            y: inputMessage.polyline[inputMessage.polylineLength-1]?.y || 0,
                            z: 0
                        },
                        orientation: { x: 0, y: 0, z: 0, w: 1 }
                    },
                    size: {x: 0.030, y:0.030, z:0.030},
                    color:{ r: 1.0, g: 1.0, b: 1.0, a: 0.7 }
                });
                lines.push({
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
                });

                for (let i = 0; i < inputMessage.polylineLength; ++i) {
                    lines[0]?.points.push({
                        x: inputMessage.polyline[i]?.x || 0,
                        y: inputMessage.polyline[i]?.y || 0,
                        z: 0
                    });
                }
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
