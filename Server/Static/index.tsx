import React from "react";
import { createRoot } from "react-dom/client";
import { Load } from "./Interface/Load";
import { Popup } from "./Interface/Popup";

createRoot(document.getElementById("Content")!).render(<Load />);
createRoot(document.getElementById("Popup")!).render(<Popup />);
