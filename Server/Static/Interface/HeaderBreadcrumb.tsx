import React from "react";
import { Breadcrumb } from "react-bootstrap";
import { Logger } from "../Logger";

export interface HeaderBreadcrumbDataStructure {
    Title: string,
    Callback: () => void,
}
export class HeaderBreadcrumb extends React.Component {
    constructor(props: any) {
        super(props);
        this.state = {
            HeaderBreadcrumbData: [{
                Title: "XMOJ-Client",
                Callback: () => { },
            }],
        };
    }
    render(): React.ReactNode {
        Logger.Output("Rendered: HeaderBreadcrumb", Logger.LEVEL.DEBUG);
        return <Breadcrumb className="ms-1 me-1">
            {
                (() => {
                    const RealData = this.state["HeaderBreadcrumbData" as keyof typeof this.state] as HeaderBreadcrumbDataStructure[];
                    return RealData.map((Data, Index) => {
                        return <Breadcrumb.Item onClick={() => {
                            RealData.splice(Index + 1, RealData.length - Index - 1);
                            this.setState({ "HeaderBreadcrumbData": RealData });
                            Data.Callback();
                        }}>{Data.Title}</Breadcrumb.Item>
                    })
                })()
            }
        </Breadcrumb>
    }
}