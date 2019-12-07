let http = require("http");
let fs = require("fs");

const graph = "http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com";
const port_number = 8081;

let sendFile = (file, res) => {
    file.pipe(res);
    file.on('error', function (err) {
        console.err(err);
        file.destroy();
    });
    res.on('close', function () {
        file.destroy();
    });
};

let query_graph = (query) => {
    let fetch = require("node-fetch");
    const endpoint = "http://localhost:8890/sparql";
    const url = endpoint +
        '?query=' + encodeURIComponent(query) +
        '&format=json' +
        '&default-graph-uri=' + encodeURIComponent(graph) +
        '&format=text/html' +
        '&timeout=0';
    return fetch(url);
};

let process_query = (query, res) => {
    query_graph(query).then(res => res.text()).then(html => {
        if (html.substr(1, 5) === "table") {
            res.writeHead(200, {'Content-Type': 'text/html'});
            res.write("<html lang=\"en\"><body>" + html + "</body></html>");
            res.end();
        } else {
            res.writeHead(404, {'Content-Type': 'text/html'});
            let file = new fs.ReadStream('static/routes/invalid_query.html');
            sendFile(file, res);
        }
    });
};

let server = new http.Server();

server.listen(port_number, "127.0.0.1");

server.on("request", function (req, res) {
        if (req.url === "/") {
            res.writeHead(200, {'Content-Type': 'text/html'});
            let file = new fs.ReadStream('static/routes/index.html');
            sendFile(file, res);
        } else {
            if (req.url === "/sparql" && req.method === "GET") {
                res.writeHead(200, {'Content-Type': 'text/html'});
                let file = new fs.ReadStream('static/routes/sparql.html');
                sendFile(file, res);
            } else if ((req.url === "/sparql" && req.method === "POST")) {
                let query = '';
                req.on('data', data => {
                    query.concat(data);
                });
                req.on('end', function () {
                    query = decodeURIComponent(query.substr(6, query.length - 6));
                    query = query.replace(/\+/g, " ").replace(/ {2}/g, " ");
                    console.log(query);
                    process_query(query, res);
                });
            } else {
                let query = "select ?predicate ?object where { <" + graph + req.url + "> ?predicate ?object}";
                process_query(query, res);
            }
        }
    }
);

process.stdout.write("Server is running.\nGo to http://localhost:" + port_number + ".\n");
