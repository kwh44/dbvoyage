module.exports = function(query) {
    let fetch = require("node-fetch");
    const endpoint = "http://localhost:8890/sparql";
    const graph = "http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com";
    const url = endpoint +
        '?query=' + encodeURIComponent(query) +
        '&format=json' +
        '&default-graph-uri=' + encodeURIComponent(graph) +
        '&format=text/html' +
        '&timeout=0';
    return fetch(url);
};