import React from "react";
import { Logger } from "../Logger";

export class BodyList extends React.Component {
    constructor(props: any) {
        super(props);
        this.state = {
            Items: [<span>An item</span>]
        };
    }
    render(): React.ReactNode {
        Logger.Output("Rendered: BodyList", Logger.LEVEL.DEBUG);
        return <ul className="list-group list-group-flush">
            {
                (this.state["Items" as keyof typeof this.state] as React.ReactNode[]).map((Data, Index) => {
                    return <li className="list-group-item" key={Index}>{Data}</li>;
                })
            }
        </ul>;
    }
}