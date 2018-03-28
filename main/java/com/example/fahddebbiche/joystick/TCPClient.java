package com.example.fahddebbiche.joystick;


import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.OutputStreamWriter;

public class TCPClient  implements  Runnable  {

    String serverC="host";
    int portNumber=8080;

    @Override
    public void run() {
        try {
            Socket client = new Socket(serverC ,  portNumber);
        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    public void sendCommands(Integer angle, Integer speed) throws IOException {

        String command = "" + angle.byteValue() + "//" + speed.byteValue();
        Socket client = new Socket(serverC ,  portNumber);
        OutputStreamWriter TOserver = new OutputStreamWriter(client.getOutputStream());
        TOserver.write(command);
        TOserver.flush();
        client.close();

    }


}

