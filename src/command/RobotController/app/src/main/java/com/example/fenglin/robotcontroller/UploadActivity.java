package com.example.fenglin.robotcontroller;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;

public class UploadActivity extends AppCompatActivity {
    RecyclerView recyclerView;
    FileListAdapter mAdapter;
    private static final int REQUEST_WRITE_STORAGE_REQUEST_CODE = 1;
    public static FloatingActionButton btnSend;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_upload);

        requestAppPermissions();

        String path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).toString();
        Log.d("test2","path = "+ path );
        JSONArray files =  getFiles(path,".txt");

        this.recyclerView = findViewById(R.id.recyclerView);
        mAdapter = new FileListAdapter(this,files,recyclerView);

        recyclerView.setAdapter(mAdapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        btnSend = findViewById(R.id.fab);
    }

    public static JSONArray getFiles (String path, String type)
    {
        File file = new File(path);
        if (!file.exists())
        {
            Log.d("test2","not exists");
            return null;
        }

        File[] files = file.listFiles();
        if (files == null)
        {
            Log.d("test2","geen files");
            return null;
        }

        JSONArray fileList = new JSONArray();
        for (File _file :files){
            if (_file.isFile()&&_file.getName().endsWith(type))
            {
                String name = _file.getName();
                String filePath = _file.getAbsolutePath();
                String fileName = _file.getName().substring(0,name.length()-4);
                try {
                    JSONObject info = new JSONObject();
                    info.put("name",fileName);
                    info.put("path",filePath);
                    fileList.put(info);

                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }
        return  fileList;
    }

    private void requestAppPermissions() {
        if (android.os.Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
            return;
        }

        if (hasReadPermissions() && hasWritePermissions()) {
            return;
        }

        ActivityCompat.requestPermissions(this,
                new String[] {
                        Manifest.permission.READ_EXTERNAL_STORAGE,
                        Manifest.permission.WRITE_EXTERNAL_STORAGE
                }, REQUEST_WRITE_STORAGE_REQUEST_CODE);
    }

    private boolean hasReadPermissions() {
        return (ContextCompat.checkSelfPermission(getBaseContext(), Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED);
    }

    private boolean hasWritePermissions() {
        return (ContextCompat.checkSelfPermission(getBaseContext(), Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED);
    }
}
