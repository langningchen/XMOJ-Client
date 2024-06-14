import React from "react";
import { Logger } from "../../Logger";
import { MessagePipeInstance } from "../../MessagePipe";
import { Welcome } from "./Welcome";
import { Problems } from "./Problems";
import { LoadingSpinner } from "../LoadingSpinner";
import { API } from "../../API";

type PropsType = {
    ProblemID: number;
}

export interface ProblemDataStructure {
    Name: string;
    InputFilename: string;
    OutputFilename: string;
    TimeLimit: number;
    MemoryLimit: number;
    SpecialJudge: boolean;
    EnableO2: boolean;
    SubmitCount: number;
    SolvedCount: number;
    Description: string;
    InputFormat: string;
    OutputFormat: string;
    Samples: Array<{
        Input: string;
        Output: string;
        Description: string;
    }>;
    DataRange: string;
    Hint: string;
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
                "Title": this.props.ProblemID,
                "Component": <Problem ProblemID={this.props.ProblemID} />
            },
        ]);
        MessagePipeInstance.Send("SetBodyList", []);
        API.Request("GetProblem", { ProblemID: this.props.ProblemID }, () => { }, (Data: ProblemDataStructure) => {

        }, () => {
            setTimeout(() => {
                MessagePipeInstance.Send("SetBodyContent", <Problems />);
            }, 1000);
        }, () => { });
    }
    render(): React.ReactNode {
        Logger.Output("Rendered: Problem, ProblemID: " + this.props.ProblemID, Logger.LEVEL.DEBUG);
        return <LoadingSpinner />;
    }
}