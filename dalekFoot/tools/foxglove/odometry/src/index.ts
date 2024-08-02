import { ExtensionContext } from "@foxglove/extension";
import {ModelPrimitive, SceneUpdate} from "@foxglove/schemas";
type OdometryTopic = {};

export function activate(extensionContext: ExtensionContext): void {
  // extensionContext.registerPanel({ name: "example-panel", initPanel: initExamplePanel });
  extensionContext.registerMessageConverter({
    fromSchemaName: "cooboc.proto.OdometryTopic",
    toSchemaName: "foxglove.SceneUpdate",
    converter: (inputMessage: OdometryTopic) => {
      console.log(inputMessage);
      const robotModel:ModelPrimitive[]  = [{
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
            w: 1.0
          }
        },
        scale: {
          x: 1.0,
          y: 1.0,
          z: 1.0
        },
        color: { r: 1.0, g: 1.0, b: 0.0, a: 1.0 },
        override_color: false,
        url: "package://asset/robot.glb",
        media_type: "glTF",
        data: Uint8Array.from([])
      }];
      const sceneUpdateMessage:SceneUpdate = {
        deletions: [],
        entities: [
          {
            id: "Odometry",
            timestamp: {sec: 0, nsec: 0},
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
