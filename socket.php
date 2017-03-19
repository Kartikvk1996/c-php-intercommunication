<?php

if(!isset($_POST))
{
    echo "send data";
    exit();
}

//get the value
$msg=$_POST['val'];



//create the socket --> ipv4
if(!($sock = socket_create(AF_INET, SOCK_STREAM, 0)))
{
    die("Couldn't create socket\n");
}

echo "Socket created \n";

//Connect socket to local ip address
if(!socket_connect($sock , '127.0.0.1' , 5000))
{
    die("Could not connect:\n");
}

echo "Connection established \n";

//Send the message to the server
if( ! socket_send ( $sock , $msg , 100 , 0))
{
    die("Could not send data\n");
}

echo "Message send successfully \n";

//get response from server
if( ! socket_recv( $sock , $msg , strlen($msg) , 0))
{
    die("Could not send data\n");
}
echo "<br/>response : ".$msg;

// close the socket
socket_close($sock);


?>
