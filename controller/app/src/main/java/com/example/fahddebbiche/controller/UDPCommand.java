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


    public static Void sendCommands(final Integer angle, final Integer speed) {

        Thread thread = new Thread(new Runnable() {
            public void run() {
                try {
                    byte[] sendData;
                    //String command = "" + angle + "//" + speed;
                    String command = "test";
                    sendData = command.getBytes();
                    System.out.println("hereeeeee" + sendData);

                    InetAddress serverC = InetAddress.getByName("10.132.27.127");
                    System.out.println("serverrrrrrr" + serverC.getHostName() + "/// " + serverC.getAddress() + "//////" + serverC.toString());

                    //System.out.println("this is the angle " + angle.byteValue() + "this is the speed " + speed.byteValue());
                    DatagramSocket clientSocket = null;

                    //clientSocket = new DatagramSocket(8888, serverC.);
                    InetSocketAddress address = new InetSocketAddress("localhost", 8080);
                    //clientSocket.connect(address);
                    // clientSocket.bind(address);


                    try {
                        DatagramPacket ToServer = new DatagramPacket(sendData, sendData.length, InetAddress.getLocalHost(), 8080);
                        System.out.print("senntttttt: " + command + ", ");
                        for (int i = 0; i < ToServer.getLength(); i++) {
                            System.out.print(ToServer.getData()[i] + " ");
                        }
                        System.out.println();
                        clientSocket.send(ToServer);

                    } catch (UnknownHostException e) {
                        e.printStackTrace();
                    }

                    //client.close();


                } catch (Exception e) {
                    getDefaultUncaughtExceptionHandler();
                }
            }

        });
        thread.start();


        return null;

    }
}

