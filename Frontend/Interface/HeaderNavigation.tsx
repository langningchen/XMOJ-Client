import React from "react";
import { Logger } from "../Logger";

export class HeaderNavigation extends React.Component {
    render(): React.ReactNode {
        Logger.Output("Rendered: HeaderNavigation", Logger.LEVEL.DEBUG);
        return <div className="border rounded p-2 m-1" style={{ flex: 1 }}>
            问题
            竞赛
            状态
        </div>;
    }
}