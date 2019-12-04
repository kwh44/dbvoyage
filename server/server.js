let http = require("http");
let fs = require("fs");

let server = new http.Server();
const port_number = 8080;
server.listen(port_number, "127.0.0.1");

server.on("request", function (req, res) {
        if (req.url === "/") {
            res.writeHead(200, {'Content-Type': 'text/html'});
            let file = new fs.ReadStream('static/index.html');
            sendFile(file, res);
        } else {
            if (req.url == "/sparql") {
                res.writeHead(200, {'Content-Type': 'text/html'});
                let file = new fs.ReadStream('static/sparql.html');
                sendFile(file, res);
            } else {
                // make database query
                // if query referenced valid record return db response
                // else 404 not found page
            }
        }
    }
);

function sendFile(file, res) {
    file.pipe(res);

    file.on('error', function (err) {
        console.err(err);
        file.destroy();
    });

    res.on('close', function () {
        file.destroy();
    });
}

process.stdout.write("Server is running.\nGo to http://localhost:" + port_number + ".\n");