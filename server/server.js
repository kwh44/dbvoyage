let http = require("http");
let fs = require("fs");
let query_graph = require("./static/js/sparql_query");

let server = new http.Server();
const port_number = 8080;
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
            } else if (req.url === "/sparql" && req.method === "POST") {
                let query = '';
                req.on('data', data => {
                    query.concat(data);
                });
                req.on('end', function () {
                    query = decodeURIComponent(query.substr(6, query.length - 6));
                    query = query.replace(/\+/g, " ").replace(/ {2}/g, " ");
                    console.log(query);
                    query_graph(query).then(res => res.text()).then(html => {
                        if (html.substr(1, 5) === "table") {
                            res.writeHead(200, {'Content-Type': 'text/html'});
                            res.write("<html><body>" + html + "</body></html>");
                            res.end();
                        } else {
                            res.writeHead(200, {'Content-Type': 'text/html'});
                            let file = new fs.ReadStream('static/routes/invalid_query.html');
                            sendFile(file, res);
                        }
                    });
                });
            } else {
                // try to do sparql query with url
                // select ?predicate ?object where {url ?predicate ?value}
                // return resulting query result
            }
        }
    }
);

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

process.stdout.write("Server is running.\nGo to http://localhost:" + port_number + ".\n");