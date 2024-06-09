import React from "react";
import { Logger } from "../../Logger";
import { MessagePipeInstance } from "../../MessagePipe";
import { Welcome } from "./Welcome";
import { Problem } from "./Problem";

export class Problems extends React.Component {
    componentDidMount(): void {
        MessagePipeInstance.Send("SetHeaderBreadcrumb", [
            {
                "Title": "欢迎",
                "Component": <Welcome />,
            },
            {
                "Title": "题目",
                "Component": <Problems />,
            },
        ]);
        MessagePipeInstance.Send("SetBodyList", [
            {
                "Title": "题目1",
                "Component": <Problem ProblemID={1} />,
            },
        ]);
    }
    render(): React.ReactNode {
        Logger.Output("Rendered: Problems", Logger.LEVEL.DEBUG);
        return <div>题目</div>
    }
}