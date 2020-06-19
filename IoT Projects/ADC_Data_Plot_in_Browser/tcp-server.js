
var net = require('net');
var string = " is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";

var server = net.createServer(function(socket)
{
    //console.log('Turn ON LED')

    //socket.write('\nTurn ON LED\r\n');
    socket.write(string);
    //socket.pipe(socket);
  //When client sent data this is called
    socket.on('data',function(data)
      {
        console.log(String(data));
      });
      console.log("No of Connected Device : "+ server.connections);//
});

server.listen(8000, '192.168.0.110', function()
{
  console.log('Server is listening to the port 8000');
});
