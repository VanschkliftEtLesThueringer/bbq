var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var SerialPort = require("serialport").SerialPort;
var serialport = new SerialPort("/dev/tty.usbmodem411",   {baudrate: 115200
});

app.use(express.static(__dirname + '/static'));

/*
app.get('/', function(req, res){
  res.sendFile(__dirname + '/static/index.html');
});
*/


serialport.on('open', function(){
  console.log('Serial Port Opend');
  /*
  serialport.on('data', function(data){
      console.log(data[0]);
  });
*/
	var buf = new Buffer(2);

  serialport.on('data', function(data){
      console.log(data.toString());
  });


	io.on('connection', function(socket){
	  socket.on('down', function(msg){
	    //console.log('down '+ msg);
    	buf[0] = 0;
    	buf[1] = keycodetosausage(msg);
      console.log(buf);
	    serialport.write(buf, function(err, results) {

      //console.log('err ' + err);
      //console.log('results ' + results);
   		});
	  });

	  socket.on('up', function(msg){
	    console.log('up '+ msg);
      buf[0] = 1;
      buf[1] = keycodetosausage(msg);
      console.log(buf);
      serialport.write(buf, function(err, results) {

      //console.log('err ' + err);
      //console.log('results ' + results);
      });
	  });
	});

});

function keycodetosausage(code) {
	switch (code) {
	  case 87:
	  	return 0;
	    break;	
	  case 65:
	  	return 1;
	    break;
  	  case 83:
  	  	return 2;
    	break;
  	  case 68:
  	  	return 3;
    	break;	
  	  case 70:
  	  	return 4;
    	break;			
  	  case 71:
  	  	return 5;
    	break;
    }
}

http.listen(3000, function(){
  console.log('listening on *:3000');
});