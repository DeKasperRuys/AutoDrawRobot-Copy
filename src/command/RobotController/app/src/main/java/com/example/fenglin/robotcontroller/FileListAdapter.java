package com.example.fenglin.robotcontroller;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class FileListAdapter extends RecyclerView.Adapter<FileListAdapter.FileViewHolder> {

    private JSONArray files;
    private LayoutInflater layoutInflater;
    private Context context;
    private RecyclerView recyclerView;
    public FileListAdapter(Context _context, JSONArray _files, RecyclerView _recyclerView)
    {
        this.files = _files;
        this.context = _context;
        this.layoutInflater = LayoutInflater.from(_context);
        this.recyclerView = _recyclerView;
    }

    @NonNull
    @Override
    public FileListAdapter.FileViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {

        View view = layoutInflater.inflate(R.layout.coordinaten_file,viewGroup,false);

        return new FileViewHolder(view, this);
    }

    @Override
    public void onBindViewHolder(@NonNull FileListAdapter.FileViewHolder fileViewHolder, int i) {
        try {

            JSONObject file  = this.files.getJSONObject(i);
            fileViewHolder.txtFileName.setText(file.getString("name"));

            if (file != null)
            {
                Log.d("jsonobjectFile", "is NIET leeg");
                Log.d("jsonobjectFile", file.getString("name"));

            }
            else
            {
                Log.d("jsonobjectFile", "isLeeg");
            }

        } catch (JSONException e) {
            e.printStackTrace();
        }

    }

    @Override
    public int getItemCount() {
        return files.length();
    }

    class FileViewHolder extends RecyclerView.ViewHolder implements RecyclerView.OnClickListener {
        TextView txtFileName;
        FileListAdapter mAdapter;

        public FileViewHolder(@NonNull View itemView, FileListAdapter adapter) {
            super(itemView);

            this.txtFileName = (TextView) itemView.findViewById(R.id.txtFileName);
            this.mAdapter = adapter ;
            itemView.setOnClickListener(this);
        }

        @Override
        public void onClick(View v) {

            int itemPosition = recyclerView.getChildLayoutPosition(v);
            String path = null;
            Log.d("coordinatenHandler", "file is geklikt ");

           // get path van geselecteerde file
            try {
                JSONObject file = files.getJSONObject(itemPosition);
                path = (String) file.get("path");

                int state = 0;
                BluetoothThread bluetoothThread = new BluetoothThread(ConnectieActivity.mBTSocket,state,"bluetoothThread");
                final CoordinatenHandler coordinatenHandler = new CoordinatenHandler(path,context,state,bluetoothThread,"handler");

                UploadActivity.btnSend.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        coordinatenHandler.run();
                    }
                });
            } catch (JSONException e) {
                e.printStackTrace();
                Log.e("FileListAdapter", "onClick: files.getJSONObject(itemPosition)");
            }

        }


    }
}
