import React from "react";
import { Badge } from "react-bootstrap";
import { MessagePipeInstance } from "../MessagePipe";
import { Logger } from "../Logger";

export interface PopupToastDataStructure {
    Success: boolean,
    Content: string,
}

export class PopupToast extends React.Component {
    constructor(props: any) {
        super(props);
        this.state = {
            "PopupToastData": [],
        };
        MessagePipeInstance.Register("PopupToast", (Data: PopupToastDataStructure) => {
            const RealData = this.state["PopupToastData" as keyof typeof this.state] as PopupToastDataStructure[];
            RealData.push(Data);
            this.setState({ "PopupToastData": RealData });
            setTimeout(() => {
                RealData.splice(0, 1);
                this.setState({ "PopupToastData": RealData });
            }, 5000);
        });
    }
    render(): React.ReactNode {
        Logger.Output("Rendered: PopupToast", Logger.LEVEL.DEBUG);
        return <div className="position-fixed top-0 w-100 p-3 z-3 text-center fs-4">
            {
                (() => {
                    const RealData = this.state["PopupToastData" as keyof typeof this.state] as PopupToastDataStructure[];
                    if (RealData.length == 0) {
                        return null;
                    }
                    return RealData.map((Data) => {
                        return <div className="mb-2">
                            {
                                Data.Success ?
                                    <Badge bg="success" className="px-3 py-2"><i className="bi bi-check-circle-fill me-2"></i>{Data.Content}</Badge> :
                                    <Badge bg="danger" className="px-3 py-2"><i className="bi bi-x-circle-fill me-2"></i>{Data.Content}</Badge>
                            }
                        </div>;
                    })
                })()
            }
        </div>;
    }
}