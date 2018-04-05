package com.example.fahddebbiche.controller;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.net.UnknownHostException;

public class ConnectActivity extends AppCompatActivity {
    Button connect_btn;

    /*
    * FIRST PAGE: contains a connection button, in the case of, successful connection with server
    * changes the page to joystick
    */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connect);
        connect_btn=findViewById(R.id.connect);
        connect_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i=new Intent(getApplicationContext(),MainActivity.class);
                startActivity(i);
               // try {
               //     TCPClient.main();
               // } catch (UnknownHostException e) {
               // e.printStackTrace();
               // }
            }
        });
    }
}