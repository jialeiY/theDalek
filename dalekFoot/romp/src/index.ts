import * as net from'net';

const server : net.Server = net.createServer();
server.on("connection", (conn: net.Socket):void => {
    const remoteAddress:string = conn.remoteAddress +':' + conn.remotePort;
    console.log("client come", remoteAddress);
    conn.on("data", (data:Buffer):void => {
        console.log("data", data);
    })
});
server.listen(8113, () => {
    console.log('server listening to %j', server.address());
});
