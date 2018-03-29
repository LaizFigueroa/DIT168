package com.example.fahddebbiche.joystick;


import android.widget.Button;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import com.example.fahddebbiche.joystick.TCPClient;

import java.net.Inet4Address;
import java.util.Optional;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import java.io.IOException;


public class MainActivity extends AppCompatActivity implements JoystickClass.JoystickListener {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.joystick).setVisibility(View.VISIBLE);
        /**
         Button button= (Button) findViewById(R.id.button);
         button.setOnClickListener(new View.OnClickListener() {
        @Override public void onClick(View v) {
        try {
        TCPClient.sendCommands(0,0);
        } catch (IOException e) {
        e.printStackTrace();
        }
        }
        });
         **/
    }

    ExecutorService concurrent = Executors.newCachedThreadPool(); // Executor to concurrently run the main flow of app AND listen to server

    Future<Void> server = concurrent.submit(new Callable<Void>() { // Listen to server in one thread
        public Void call() throws Exception {
            TCPClient.main();
            return null;
        }
    });

    {
        try {
            server.get();
        } catch (InterruptedException e1) {
            e1.printStackTrace();
        } catch (ExecutionException e1) {
            e1.printStackTrace();
        }
    }


    @Override
    public void onJoystickMoved( float coordinateX, float coordinateY) {
        Log.d("Main Method", " X "  + coordinateX  + " Y " + coordinateY );

    }





}

