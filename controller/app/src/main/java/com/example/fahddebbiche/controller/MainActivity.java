package com.example.fahddebbiche.controller;


import android.widget.Button;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.util.DisplayMetrics;



public class MainActivity extends AppCompatActivity implements JoystickClass.JoystickListener {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        DisplayMetrics displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);

         Button button=  findViewById(R.id.button);
         button.setOnClickListener(new View.OnClickListener() {
        @Override public void onClick(View v) {
            UDPCommand.sendCommands(0,0);
        }
        });
    }



    @Override
    public void onJoystickMoved( float coordinateX, float coordinateY) {
        Log.d("Main Method", " X " + coordinateX + " Y " + coordinateY);


    }





}

