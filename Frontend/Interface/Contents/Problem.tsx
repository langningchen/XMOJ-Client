import React from "react";
import { Logger } from "../../Logger";
import { MessagePipeInstance } from "../../MessagePipe";
import { Welcome } from "./Welcome";
import { Problems } from "./Problems";
import { LoadingSpinner } from "../LoadingSpinner";

type PropsType = {
    ProblemID: number;
}

export class Problem extends React.Component<PropsType> {
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
            {
                "Title": "题目1",
                "Component": <Problem ProblemID={1} />,
            }
        ]);
        MessagePipeInstance.Send("SetBodyList", [
            {
                "Title": "题目1",
                "Component": <Problem ProblemID={1} />,
            },
        ]);
    }
    render(): React.ReactNode {
        Logger.Output("Rendered: Problem, ProblemID: " + this.props.ProblemID, Logger.LEVEL.DEBUG);
        return <LoadingSpinner />;
    }
}