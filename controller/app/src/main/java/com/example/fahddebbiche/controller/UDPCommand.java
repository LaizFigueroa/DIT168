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


public class UDPCommand extends Thread {


    public static void sendCommands(final Integer angle, final Integer speed) {

        Thread thread = new Thread(new Runnable() {
            public void run() {
                try {
                    byte[] sendData= new byte[1024];;

                    String command = "" + angle + "//" + speed;
                    sendData = command.getBytes();

                    InetAddress serverC = InetAddress.getByName("192.168.8.1");

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

