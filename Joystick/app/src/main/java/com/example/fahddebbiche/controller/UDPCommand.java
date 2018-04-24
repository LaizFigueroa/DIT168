package com.example.fahddebbiche.controller;

import android.os.AsyncTask;
import android.view.GestureDetector;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.UnknownHostException;

/**
 * this class create a datagram socket for UDP communication between the android client and the server.
 * it sends the data of the car which  are speed and angle to the server in order to control the car remotely
 */

public class UDPCommand extends Thread {


    public static void sendCommands(final Integer angle, final Integer speed) {

        Thread thread = new Thread(new Runnable() {
            public void run() {
                try {
                    byte[] sendData= new byte[1024];;

                    String command = "" + angle + "//" + speed;
                    sendData = command.getBytes();

                    InetAddress serverC = InetAddress.getByName("172.20.10.2");

                    DatagramSocket clientSocket = new DatagramSocket();
                    InetSocketAddress address = new InetSocketAddress(serverC.getHostName(), 8080);
                    clientSocket.connect(address);

                    try {
                        DatagramPacket ToServer = new DatagramPacket(sendData, sendData.length, serverC, 8080);
                        
                        System.out.println();
                        clientSocket.send(ToServer);
                        System.out.print("Package been sent : " + command + ", ");


                    } catch (UnknownHostException e) {
                        e.printStackTrace();
                    }

                    clientSocket.close();



                } catch (Exception e) {
                    getDefaultUncaughtExceptionHandler();
                }
            }

        });
        thread.start();


    }
}

