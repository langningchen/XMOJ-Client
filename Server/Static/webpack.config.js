const Path = require("path");

module.exports = {
    mode: "production",
    entry: Path.resolve(__dirname, "index.tsx"),
    output: {
        filename: "index.js",
        path: Path.resolve(__dirname, "..", "..", "build", "HTML"),
    },
    devtool: "source-map",
    resolve: {
        extensions: [".ts", ".tsx", ".js"],
    },
    module: {
        rules: [
            {
                test: /\.tsx?$/,
                use: "ts-loader",
                exclude: /node_modules/,
            },
        ],
    },
};
