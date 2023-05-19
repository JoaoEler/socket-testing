import java.net.*;
import java.io.*;

public class Server_1 {
  public static void main(String[] args) {
    boolean flag;
    try {
      ServerSocket server = new ServerSocket(8888);
      flag = true;
      while(flag) {
        System.out.println("I am the server");
        Socket client_socket = server.accept();
        System.out.println("Connection established: " + client_socket.getInetAddress().getHostAddress()
                           + ", " + client_socket.getPort());
        ObjectInputStream input = new ObjectInputStream(client_socket.getInputStream());
        String msg = (String)input.readObject();

        System.out.println(msg);
        input.close();
        client_socket.close();

        if (msg.equals("over")) {
          server.close();
          flag = false;
        }

      }
    }
    catch(Exception e) {
       System.out.println("Error: " + e.getMessage());
    }

  }
}
