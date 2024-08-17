import { ExtensionContext } from '@foxglove/extension';
import { LinePrimitive, LineType, SceneUpdate, SpherePrimitive } from '@foxglove/schemas';

type Position2D = {
    x: number; y: number;
};

type PassingPoint = {
    position: Position2D;
};

type TrajectoryTopic = {
    hasValue: boolean; trajectoryId: number; passingPointSize: number;
    passingPoint: PassingPoint[];
    routeId: number;
};

export function activate(extensionContext: ExtensionContext): void {
    extensionContext.registerMessageConverter({
        fromSchemaName: 'cooboc.proto.TrajectoryTopic',
        toSchemaName: 'foxglove.SceneUpdate',
        converter: (inputMessage: TrajectoryTopic) => {
            let spheres: SpherePrimitive[] = [];
            let lines: LinePrimitive[] = [];
            if ((inputMessage.hasValue) && (inputMessage.passingPointSize > 0)) {

                // Construct the lines for trajectory
                const polyline: LinePrimitive = {
                    type: LineType.LINE_STRIP,
                    pose: {
                        position: { x: 0, y: 0, z: 0 },
                        orientation: { x: 0, y: 0, z: 0, w: 1 }
                    },
                    thickness: 0.002,
                    scale_invariant: false,
                    points: [],
                    color: { r: 0.0, g: 0.0, b: 1.0, a: 1.0 },
                    colors: [],
                    indices: []
                };

                // Put the trajectory into polyline
                for (let i = 0; i < inputMessage.passingPointSize; ++i) {
                    polyline.points.push({
                        x: inputMessage.passingPoint[i]?.position.x || 0,
                        y: inputMessage.passingPoint[i]?.position.y || 0,
                        z: 0
                    });
                }

                lines.push(polyline);
            }


            const sceneUpdateMessage: SceneUpdate = {
                deletions: [],
                entities: [
                    {
                        id: 'trajectory',
                        timestamp: { sec: 0, nsec: 0 },
                        frame_id: 'WORLD',
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
