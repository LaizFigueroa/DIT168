package com.example.rema.controller;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;

import com.nasable.smoothnetworking.TcpClient;


public class MainActivity extends AppCompatActivity implements JoystickClass.JoystickListener {

   // Decelerations for variable used for the server-client connection
   String SERVERIP ="192.168.1.249";
    int    SERVERPORT=8081;
    TcpClient tcpClient;

    // Decelerations for variable used for the displayed screen
    int height;
    int width;
    int centerWidth;
    int centerHeight;

  /*
   * THE layout, handling the displayed joystick placement according to the different screen's
   * (pixels)
   **/
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        DisplayMetrics displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        height = displayMetrics.heightPixels;
        width = displayMetrics.widthPixels;

        centerWidth =(int)((float)width/2);
        centerHeight =(int)((float)height/2);
        Log.d("Main Method", " width "  + width  + " height " + height );
        findViewById(R.id.joystick).setVisibility(View.VISIBLE);



    /*
     * Library used for the TCP connection
     **/
         tcpClient=new TcpClient(SERVERIP, SERVERPORT, new TcpClient.OnActionListener() {
            @Override
            public void onMessage(String s) {
            }

            @Override
            public void onError(String s) {
                Log.d("Main Method", "error "  +s);
                finish();
            }

            @Override
            public void onClose() {
                Log.d("Main Method", "closed "  );
              finish();
            }

            @Override
            public void onConnect() {
            }
        });
        tcpClient.run();
    }

    /*
     * Method for getting the coordinates according to the joystick movement
     * then sends it to the server
     **/
    @Override
    public void onJoystickMoved( float coordinateX, float coordinateY) {
        Log.d("Main Method", " X "  + coordinateX  + " Y " + coordinateY );
        // sending the coordinates to the (car server),
        // after changing them to commands by the coordinateToCommand method
        tcpClient.sendMessage(coordinateToCommand(coordinateX,coordinateY)+"");
    }

    /*
     * Method for estimating the coordinates (divide the joystick space into 4 directions)
     * @return int:  the Car's movement commands as integers
     **/
    public int coordinateToCommand(float x,float y){
        if(x>width/3 && x<(width*2)/3 && y<centerHeight)
            return 1; // up

        if(x<width/3)
            return 2;//left

        if(x>(width*2)/3)
            return 3;//right

        return 0; //  (backwards) stop

    }

    /*
    * Stoping the connection in case of leaving the joystick page
    **/
    @Override
    protected void onDestroy() {
        tcpClient.stopClient();
        super.onDestroy();
    }
}
