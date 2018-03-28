package com.example.fahddebbiche.joystick;


import android.annotation.SuppressLint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;




public class MainActivity extends AppCompatActivity implements JoystickClass.JoystickListener{


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.joystick).setVisibility(View.VISIBLE);
    }

    @Override
    public void onJoystickMoved( float coordinateX, float coordinateY) {
        Log.d("Main Method", "X"  + coordinateX  + "Y" + coordinateY );


    }
}

