import { ExtensionContext } from '@foxglove/extension';
import { ArrowPrimitive, SceneUpdate } from '@foxglove/schemas';

type PolarVector2D = {
    orientation: number; value: number;
};

type EgoMotionStateTopic = {
    velocity: PolarVector2D; acceleration: PolarVector2D; angularVelocity: number;
    angularAcceleration: number;
};

const PI = 3.141592653589793238462643383279502884197;

export function activate(extensionContext: ExtensionContext): void {
    extensionContext.registerMessageConverter({
        fromSchemaName: 'cooboc.proto.EgoMotionStateTopic',
        toSchemaName: 'foxglove.SceneUpdate',
        converter: (inputMessage: EgoMotionStateTopic) => {
            let arrows: ArrowPrimitive[] = [];
            // velocity
            let va = (inputMessage.velocity.orientation / 2.0) % PI;
            if (va < 0) {
                va += PI;
            }
            const vw = Math.cos(va);
            const vz = Math.sqrt(1 - (vw * vw));

            arrows.push({
                pose: {
                    position: { x: 0, y: 0, z: 0 },
                    orientation: { x: 0, y: 0, z: vz, w: vw }
                },
                shaft_length: inputMessage.velocity.value * 0.9,
                shaft_diameter: 0.02,
                head_length: inputMessage.velocity.value * 0.1,
                head_diameter: 0.03,
                color: { r: 0.0, g: 0.0, b: 1.0, a: 1.0 },
            });


            // acceleration
            let aa = (inputMessage.acceleration.orientation / 2.0) % PI;
            if (aa < 0) {
                aa += PI;
            }
            const aw = Math.cos(aa);
            const az = Math.sqrt(1 - (aw * aw));

            arrows.push({
                pose: {
                    position: {
                        x: inputMessage.velocity.value *
                            Math.cos(inputMessage.velocity.orientation),
                        y: inputMessage.velocity.value *
                            Math.sin(inputMessage.velocity.orientation),
                        z: 0
                    },
                    orientation: { x: 0, y: 0, z: az, w: aw }
                },
                shaft_length: inputMessage.acceleration.value * 0.7,
                shaft_diameter: 0.015,
                head_length: inputMessage.acceleration.value * 0.3,
                head_diameter: 0.03,
                color: { r: 1.0, g: 0.0, b: 0.0, a: 1.0 },
            });

            const sceneUpdateMessage: SceneUpdate = {
                deletions: [],
                entities: [
                    {
                        id: 'EGO_MOTION_STATE',
                        timestamp: { sec: 0, nsec: 0 },
                        frame_id: 'EGO',
                        lifetime: { sec: 10, nsec: 0 },
                        frame_locked: false,
                        metadata: [],
                        arrows: arrows,
                        cubes: [],
                        spheres: [],
                        cylinders: [],
                        lines: [],
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
