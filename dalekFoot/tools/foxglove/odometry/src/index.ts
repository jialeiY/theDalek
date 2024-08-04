import { ExtensionContext } from "@foxglove/extension";
import { ModelPrimitive, SceneUpdate, FrameTransform } from "@foxglove/schemas";
import { robot } from "./asset/robot_model";

type Position2D = {
    x: number;
    y: number;
};

type Pose2D = {
    position: Position2D;
    orientation: number;
};

type OdometryTopic = {
    timestamp: number;
    pose: Pose2D;
};

const PI = 3.141592653589793238462643383279502884197;

export function activate(extensionContext: ExtensionContext): void {
    // extensionContext.registerPanel({ name: "example-panel", initPanel: initExamplePanel });
    extensionContext.registerMessageConverter({
        fromSchemaName: "cooboc.proto.OdometryTopic",
        toSchemaName: "foxglove.FrameTransform",
        converter: (inputMessage: OdometryTopic):FrameTransform => {
            let transAngle = (inputMessage.pose.orientation / 2.0) % PI;
            if (transAngle < 0) {
                transAngle += PI;
            }
            const w = Math.cos(transAngle);
            const z = Math.sqrt(1 - (w * w));
            const frameTransform:FrameTransform = {
                timestamp: { sec: 0, nsec: 0 },
                parent_frame_id: "WORLD",
                child_frame_id: "EGO",
                translation: {
                    x: inputMessage.pose.position.x,
                    y: inputMessage.pose.position.y,
                    z: 0
                },
                rotation: {
                    x: 0,
                    y: 0,
                    z: z,
                    w: w
                }
            };
            return frameTransform
        }
    });

    extensionContext.registerMessageConverter({
        fromSchemaName: "cooboc.proto.OdometryTopic",
        toSchemaName: "foxglove.SceneUpdate",
        converter: (_: OdometryTopic) => {
            // let angle = (inputMessage.pose.orientation / 3.141592653589793238462643383279502884197) % 1;
            const robotModel: ModelPrimitive[] = [{
                pose: {
                    position: {
                        x: 0,
                        y: 0,
                        z: 0
                    },
                    orientation: {
                        x: 0,
                        y: 0,
                        z: 0,
                        w: 1
                    }
                },
                scale: {
                    x: 1.0,
                    y: 1.0,
                    z: 1.0
                },
                color: { r: 1.0, g: 1.0, b: 0.0, a: 1.0 },
                override_color: false,
                url: "",
                media_type: "model/gltf-binary",
                data: robot
            }];
            const sceneUpdateMessage: SceneUpdate = {
                deletions: [],
                entities: [
                    {
                        id: "Odometry",
                        timestamp: { sec: 0, nsec: 0 },
                        frame_id: "EGO",
                        lifetime: { sec: 10, nsec: 0 },
                        frame_locked: false,
                        metadata: [],
                        arrows: [],
                        cubes: [],
                        spheres: [],
                        cylinders: [],
                        lines: [],
                        triangles: [],
                        texts: [],
                        models: robotModel,
                    },
                ],
            };

            return sceneUpdateMessage;
        }
    });
}
