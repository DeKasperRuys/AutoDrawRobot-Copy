package com.example.fenglin.robotcontroller;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    ImageButton btnBluetooth;
    public static  ImageButton up;
    public static  ImageButton down;
    public static  ImageButton left;
    public static  ImageButton right;
    public static  ImageButton pen;
    public static  ImageButton right90;
    public static  ImageButton left45;
    public static  ImageButton right180;
    public static  ImageButton left135;
    public static ImageButton btnCalibratiob,btnStart;


    public static boolean penBoolean = false;
    public static boolean startBoolean = false;
    public static TextView txtTest;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        up = findViewById(R.id.btnUp);
        down = findViewById(R.id.btnDown);
        left = findViewById(R.id.btnLeft);
        right = findViewById(R.id.btnRight);
        pen = findViewById(R.id.btnPen);
        left45 = findViewById(R.id.btn45);
        left135= findViewById(R.id.btn135);
        right90 = findViewById(R.id.btn90);
        right180= findViewById(R.id.btn180);
        btnCalibratiob = findViewById(R.id.btnCallibrate);
        btnStart = findViewById(R.id.btnStart);

        btnBluetooth = findViewById(R.id.btnBluetooth);
        final Intent intent = new Intent(this, ConnectieActivity.class);

        btnBluetooth.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
               startActivity(intent);
            }
    });

        this.getFilesDir();
        //Upload intent
        final Intent intentUpload = new Intent(this,UploadActivity.class);
        ImageButton btnUpload = (ImageButton) findViewById(R.id.btnUpload);
        btnUpload.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(intentUpload);
            }
        });

        ImageButton btnTest = (ImageButton) findViewById(R.id.btnDraw);
        btnTest.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BluetoothThread bt = new BluetoothThread(ConnectieActivity.mBTSocket,0,"test");
                Log.d("coordinatenHandler", "clickt");
                bt.ReadStart();

            }
        });
    }

}
