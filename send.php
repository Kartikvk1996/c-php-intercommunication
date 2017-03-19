<!DOCTYPE HTML>
<html>
  <head>
    <title>C-PHP intercommunication</title>
  </head>
  <body>
    <div>
      <h2>Send your message </h2><p style="color:red;">send 'exit' to terminate</p>
      <p>
        Enter your name : <input type="text" id="value"/><input type="button" id="send" value="send" onclick="send()"/>
      </p>
    </div>
        <p id="status">

        </p>
    <script src="jQuery/jquery-3.1.1.min.js"></script>
    <script>

      function send()
      {
          var send_data=document.getElementById("value").value;
          $.ajax({
            url:"socket.php",
            type:"POST",
            data:{
              val:send_data
            },
            success:function(data){
              $("#status").html(data);
            }
          });
      }

    </script>
  </body>
</html>
