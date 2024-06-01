import React from "react";
import { Button, Container, FloatingLabel, Form } from "react-bootstrap";
import { ContentRoot } from ".";
import { Load } from "./Load";
import { API } from "../API";
import * as Formik from "formik";
import * as yup from "yup";

type StateType = {
    Step: number;
};
type StepType = {
    HTML: JSX.Element;
    Callback?: () => boolean;
};
type SettingsType = {
    XMOJUsername: string;
    XMOJPassword: string;
};

export class Initiate extends React.Component<{}, StateType> {
    state = {
        Step: 0,
    };
    Settings: SettingsType | null = null;
    Steps: StepType[] = [
        {
            HTML: <div>
                <h1 className="mb-3">欢迎使用 XMOJ-Client</h1>
                <p>我们检测到您的配置不存在或有误，请您跟随我们的引导进行配置。</p>
                <Button variant="primary" onClick={() => { this.setState({ Step: this.state.Step + 1 }); }}>开始</Button>
            </div>,
        },
        {
            HTML: <div>
                <h1 className="mb-3">XMOJ账户</h1>
                <p>请填写您的XMOJ账户信息，以便我们验证您的身份并获取相关数据。</p>
                <Formik.Formik
                    onSubmit={() => {
                        const UsernameInput = document.getElementById("XMOJUsername") as HTMLInputElement;
                        const PasswordInput = document.getElementById("XMOJPassword") as HTMLInputElement;
                        if (UsernameInput.value && PasswordInput.value) {
                            this.Settings!.XMOJUsername = UsernameInput.value;
                            this.Settings!.XMOJPassword = PasswordInput.value;
                            this.setState({ Step: this.state.Step + 1 });
                        }
                    }}
                    initialValues={{ XMOJUsername: this.Settings?.XMOJUsername, XMOJPassword: this.Settings?.XMOJPassword }}
                    validationSchema={yup.object().shape({
                        XMOJUsername: yup.string().required("请填写用户名"),
                        XMOJPassword: yup.string().required("请填写密码"),
                    })}
                    children={(FormikProps: any) => (
                        <Formik.Form noValidate onSubmit={FormikProps.handleSubmit}>
                            <FloatingLabel controlId="XMOJUsername" label="用户名" className="mb-3">
                                <Form.Control type="text" placeholder="用户名" isInvalid={!!FormikProps.errors.XMOJUsername} {...FormikProps.getFieldProps("XMOJUsername")} />
                                <Form.Control.Feedback type="invalid">{FormikProps.errors.XMOJUsername}</Form.Control.Feedback>
                            </FloatingLabel>
                            <FloatingLabel controlId="XMOJPassword" label="密码" className="mb-3">
                                <Form.Control type="password" placeholder="密码" isInvalid={!!FormikProps.errors.XMOJPassword} {...FormikProps.getFieldProps("XMOJPassword")} />
                                <Form.Control.Feedback type="invalid">{FormikProps.errors.XMOJPassword}</Form.Control.Feedback>
                            </FloatingLabel>
                            <Button variant="primary" type="submit">下一步</Button>
                        </Formik.Form>
                    )}
                />
            </div>,
        },
        {
            HTML: <div>
                <h1 className="mb-3">大功告成</h1>
                <p>您已完成配置，现在您可以点击下方按钮开始使用XMOJ-Client。</p>
                <Button variant="primary" onClick={async () => {
                    await API.Request("SetSettings", {
                        Settings: this.Settings
                    }, () => { }, () => { }, () => { }, () => { });
                    ContentRoot.render(<Load />);
                }}>完成</Button>
            </div>,
        }
    ];

    constructor(props: {}) {
        super(props);
        API.Request("GetSettings", {}, () => { }, (Data: { Settings: SettingsType }) => {
            this.Settings = Data.Settings;
        }, () => { }, () => { });
    }

    render() {
        return (
            <Container className="d-flex justify-content-center flex-column" style={{ height: "100vh" }}>
                {this.Steps[this.state.Step].HTML}
            </Container>
        );
    }
}
