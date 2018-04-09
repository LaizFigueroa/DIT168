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
                    //String command = "test";
                    sendData = command.getBytes();
                    System.out.println("hereeeeee" + sendData);

                    InetAddress serverC = InetAddress.getByName("10.132.27.127");
                    System.out.println("server" + serverC + "first" +   serverC.getHostName() + "/// " + serverC.getAddress() + "//////" + serverC.toString());

                    //System.out.println("this is the angle " + angle.byteValue() + "this is the speed " + speed.byteValue());
                    DatagramSocket clientSocket = new DatagramSocket();
                    InetSocketAddress address = new InetSocketAddress(serverC.getHostName(), 8080);
                    clientSocket.connect(address);

                    try {
                        DatagramPacket ToServer = new DatagramPacket(sendData, sendData.length, serverC, 8080);
                        System.out.print("senntttttt: " + command + ", ");
                        
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

