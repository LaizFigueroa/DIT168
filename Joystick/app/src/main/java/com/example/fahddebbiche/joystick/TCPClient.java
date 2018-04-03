package com.example.fahddebbiche.joystick;


import android.text.format.Formatter;
import android.util.Log;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Enumeration;

public class TCPClient   {


    public static void main () throws UnknownHostException {


       // String serverC = "10.132.27.127";

        String serverC =getLocalIpAddress();
        System.out.println("server" + serverC);
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

    public static String getLocalIpAddress() {
        try {
            for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress()) {
                        String ip = Formatter.formatIpAddress(inetAddress.hashCode());
                        Log.i("found ip", "***** IP="+ ip);
                        return ip;
                    }
                }
            }
        } catch (SocketException ex) {
            Log.e("no ip found", ex.toString());
        }
        return null;
    }


}

