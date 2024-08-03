import { ExtensionContext } from "@foxglove/extension";
import { ModelPrimitive, SceneUpdate } from "@foxglove/schemas";
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
  pose: Pose2D;
};

export function activate(extensionContext: ExtensionContext): void {
  // extensionContext.registerPanel({ name: "example-panel", initPanel: initExamplePanel });
  extensionContext.registerMessageConverter({
    fromSchemaName: "cooboc.proto.OdometryTopic",
    toSchemaName: "foxglove.SceneUpdate",
    converter: (inputMessage: OdometryTopic) => {
      // let angle = (inputMessage.pose.orientation / 3.141592653589793238462643383279502884197) % 1;
      const w = Math.cos(inputMessage.pose.orientation / 2.0);
      const z = Math.sqrt(1 - (w * w));
      const robotModel: ModelPrimitive[] = [{
        pose: {
          position: {
            x: inputMessage.pose.position.x,
            y: inputMessage.pose.position.y,
            z: 0
          },
          orientation: {
            x: 0,
            y: 0,
            z: z,
            w: w
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
            frame_id: "WORLD",
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
  })
}
