import React from "react";
import { Logger } from "../Logger";

type StateType = {
    Items: React.ReactNode[];
};

export class BodyList extends React.Component<{}, StateType> {
    state = {
        Items: [
            <span>An item</span>,
        ],
    }
    // constructor(props: any) {
    //     super(props);
    //     this.state.Items.push(<span>An item</span>);
    // }
    render(): React.ReactNode {
        Logger.Output("Rendered: BodyList", Logger.LEVEL.DEBUG);
        return <ul className="list-group list-group-flush">
            {
                this.state.Items.map((Data, Index) => {
                    return <li className="list-group-item" key={Index}>{Data}</li>;
                })
            }
        </ul>;
    }
}