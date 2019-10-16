package com.example.heartrateapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;
public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    Button START;
    Button STOP;
    TextView txtView;
    ProgressBar progressBar;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        START = findViewById(R.id.button);
        STOP = findViewById(R.id.button2);
        txtView = findViewById(R.id.textView);
        progressBar = findViewById(R.id.progressBar);

        START.setOnClickListener(this);
        STOP.setOnClickListener(this);
    }

    @Override
    public void onClick(View v)
    {
        if(View.getId()==START){
            txtView.setText("Started");
    }
        if(View.getId()==STOP){
            txtView.setText('Stopped');
    }
    }
}
