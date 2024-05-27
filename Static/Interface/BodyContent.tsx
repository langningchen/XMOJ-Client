import React from "react";
import { Logger } from "../Logger";

export class BodyContent extends React.Component {
    render(): React.ReactNode {
        Logger.Output("Rendered: BodyContent", Logger.LEVEL.DEBUG);
        return <div>123</div>
    }
}