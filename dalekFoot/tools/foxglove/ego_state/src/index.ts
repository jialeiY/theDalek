import { ExtensionContext } from "@foxglove/extension";
import { ArrowPrimitive, SceneUpdate} from "@foxglove/schemas";

type PolarVector2D = {
    orientation: number;
    value: number;
};

type EgoStateTopic = {
    velocity: PolarVector2D;
    acceleration: PolarVector2D;
    angularVelocity: number;
    angularAcceleration: number;
};

const PI = 3.141592653589793238462643383279502884197;

export function activate(extensionContext: ExtensionContext): void {
    extensionContext.registerMessageConverter({
        fromSchemaName: "cooboc.proto.EgoStateTopic",
        toSchemaName: "foxglove.SceneUpdate",
        converter: (inputMessage: EgoStateTopic) => {
            let arrows:ArrowPrimitive[] = [];
            // velocity
            let transAngle = (inputMessage.velocity.orientation / 2.0) % PI;
            if (transAngle < 0) {
                transAngle += PI;
            }
            const vw = Math.cos(transAngle);
            const vz = Math.sqrt(1 - (vw * vw));
            const arrowLength = inputMessage.velocity.value;
            arrows.push({
                pose: {
                    position: {
                        x: 0,
                        y: 0,
                        z: 0
                    },
                    orientation: {
                        x: 0,
                        y: 0,
                        z: vz,
                        w: vw
                    }
                },
                shaft_length: arrowLength* 0.9,
                shaft_diameter: 0.02,
                head_length: arrowLength*0.2,
                head_diameter:0.03,
                color: { r: 0.0, g: 0.0, b: 1.0, a: 1.0 },
            });

            const sceneUpdateMessage: SceneUpdate = {
                deletions: [],
                entities: [
                    {
                        id: "EGO_STATE",
                        timestamp: { sec: 0, nsec: 0 },
                        frame_id: "EGO",
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
