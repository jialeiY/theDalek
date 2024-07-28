import { ExtensionContext } from "@foxglove/extension";
import { initExamplePanel } from "./ExamplePanel";
import { LinePrimitive } from "@foxglove/schemas";
import { LineType } from "@foxglove/schemas/schemas/typescript/LineType"


type Position2D = {
  x: number;
  y: number;
}

type Vector2D = {
  orientation: number;
  value: number;
}
type PlanningRequestTopic = {
  fromPosition: Position2D;
  targetPosition: Position2D;
  targetVelocity: Vector2D;
};

export function activate(extensionContext: ExtensionContext): void {
  extensionContext.registerPanel({ name: "example-panel", initPanel: initExamplePanel });

  extensionContext.registerMessageConverter({
    fromSchemaName: "cooboc.proto.PlanningRequestTopic",
    toSchemaName: "foxglove.SceneUpdate",
    converter: (inputMessage: PlanningRequestTopic) => {
      // https://docs.foxglove.dev/docs/visualization/message-schemas/line-primitive
      console.log(inputMessage);
      // logic to turn sensors.MyGps messages into foxglove.LocationFix messages
      const lines: LinePrimitive[] = [{
        type: LineType.LINE_LIST,
        pose: {
          position: { x: 0, y: 0, z: 0 },
          orientation: { x: 0, y: 0, z: 0, w: 1 }
        },
        thickness: 1,
        scale_invariant: true,

        points: [
          { x: inputMessage.fromPosition.x, y: inputMessage.fromPosition.y, z: 0 },
          { x: inputMessage.targetPosition.x, y: inputMessage.targetPosition.y, z: 0 }
        ],
        // color 0 - 1
        color: { r: 0.0, g: 0.0, b: 0.0, a: 1.0 },
        colors: [],
        indices: [0, 1]
      }];


      const sceneUpdateMessage = {
        deletions: [],
        entities: [
          {
            id: "PlanningRequest",
            timestamp: 0,
            frame_id: "WORLD",
            lifetime: { sec: 10, nsec: 0 },
            frame_locked: false,
            metadata: [],
            arrows: [],
            cubes: [],
            spheres: [],
            cylinders: [],
            lines: lines,
            triangles: [],
            texts: [],
            models: [],
          },
        ],
      };

      return sceneUpdateMessage;

    },
  });


}
