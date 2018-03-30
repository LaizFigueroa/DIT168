package com.example.rema.controller;

import java.io.IOException;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.Socket;
import java.io.OutputStreamWriter;
import java.net.UnknownHostException;

public class TCPClient   {


    public static void main () throws UnknownHostException {

        String serverC = "10.132.27.127";
        InetAddress address = Inet4Address.getLocalHost(); //localhost
        int portNumber = 8080;

        try {
            Socket client = new Socket(serverC, portNumber);
            System.out.println(client);

            client.close();
        } catch (IOException e) {
            e.printStackTrace();
        }


    }



    public static void sendCommands(Integer angle, Integer speed) throws IOException {

        String command = "" + angle.byteValue() + "//" + speed.byteValue();
        Socket client = new Socket("localhost" ,  8080);
        OutputStreamWriter TOserver = new OutputStreamWriter(client.getOutputStream());
        TOserver.write(command);
        TOserver.flush();
        client.close();

    }


}