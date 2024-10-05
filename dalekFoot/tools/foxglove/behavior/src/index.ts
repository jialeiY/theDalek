import { ExtensionContext } from "@foxglove/extension";
import { LinePrimitive, ArrowPrimitive, Color } from "@foxglove/schemas";
import { LineType } from "@foxglove/schemas/schemas/typescript/LineType"


type Position2D = {
    x: number;
    y: number;
}

type Vector2D = {
    orientation: number;
    value: number;
}

type BehaviorId = number;

enum BehaviorTask {
    STOP = 0,
    MOVE = 1,
}

type BehaviorMoveRequest = {

    from: Position2D;
    to: Position2D;
    targetVelocity: Vector2D;
};

type BehaviorTopic = {
    id: BehaviorId;
    task: BehaviorTask;
    moveRequest: BehaviorMoveRequest;
};

export function activate(extensionContext: ExtensionContext): void {
    // extensionContext.registerPanel({ name: "example-panel", initPanel: initExamplePanel });

    extensionContext.registerMessageConverter({
        fromSchemaName: "cooboc.proto.BehaviorTopic",
        toSchemaName: "foxglove.SceneUpdate",
        converter: (inputMessage: BehaviorTopic) => {

            // https://docs.foxglove.dev/docs/visualization/message-schemas/line-primitive
            // console.log(inputMessage);
            // logic to turn sensors.MyGps messages into foxglove.LocationFix messages


            const BEHAVIOR_COLOR: Color = { r: 0.8, g: 0.8, b: 0.8, a: 0.5 };
            const magic: number = Math.cos(Math.PI / 4.0);

            const targetArrow: ArrowPrimitive[] = [{
                pose: {
                    position: { x: inputMessage.moveRequest.to.x, y: inputMessage.moveRequest.to.y, z: 0.12 },
                    orientation: { x: 0, y: magic, z: 0, w: magic }
                },
                shaft_length: 0.05,
                shaft_diameter: 0.02,
                head_length: 0.07,
                head_diameter: 0.07,
                color: BEHAVIOR_COLOR,
            }];

            const lines: LinePrimitive[] = [{
                type: LineType.LINE_LIST,
                pose: {
                    position: { x: 0, y: 0, z: 0 },
                    orientation: { x: 0, y: 0, z: 0, w: 1 }
                },
                thickness: 0.050,
                scale_invariant: false,

                points: [
                    { x: inputMessage.moveRequest.from.x, y: inputMessage.moveRequest.from.y, z: 0 },
                    { x: inputMessage.moveRequest.to.x, y: inputMessage.moveRequest.to.y, z: 0 }
                ],
                // color 0 - 1
                color: BEHAVIOR_COLOR,
                colors: [],
                indices: [0, 1]
            }];


            const sceneUpdateMessage = {
                deletions: [],
                entities: [
                    {
                        id: "Behavior",
                        timestamp: 0,
                        frame_id: "WORLD",
                        lifetime: { sec: 10, nsec: 0 },
                        frame_locked: false,
                        metadata: [],
                        arrows: targetArrow,
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
