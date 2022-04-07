package com.example.fenglin.robotcontroller;

import android.bluetooth.BluetoothSocket;
import android.os.SystemClock;
import android.util.Base64;
import android.util.Log;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Array;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.List;
import java.nio.ByteBuffer;

public class BluetoothThread extends Thread {
    private BluetoothSocket bluetoothSocket;
    private InputStream inputStream;
    private OutputStream outputStream;
    private Integer status;
    private readThread readThread;
    private boolean magWakkerMaken;
    public int getStatus() {
        return status;
    }

    public void setStatus(int state) {
        this.status = state;
    }


    public BluetoothThread(BluetoothSocket socket, int status, String name) {
        super(name);
        this.status = status;
        bluetoothSocket = socket;
        try {
            inputStream = socket.getInputStream();
            outputStream = socket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
        readThread = new readThread(socket);
        magWakkerMaken = false;
    }

    public void ReadStart() {
        readThread.start();
    }

    public void ReadStop() {
    }

    public void ReadSuspend()
    {

    }
    public void ReadResume()
    {

    }

    @Override
    public void run() {
        readThread.start();
        while (true) {
            Log.d("coordinatenHandler", "binnen run van bluetoothThread");
            synchronized (status) {
                Log.d("coordinatenHandler", "binnen synchronized van bluetoothThread");
                while (!magWakkerMaken) // Als geen request, of OK, dan stop met sturen en wachten op ok en ACCEPTED
                {
                    Log.d("coordinatenHandler", "in de while loop van btThread");
                    try {
                        Log.d("coordinatenHandler", "readThread.GetData() = " +readThread.GetData());
                        if (readThread.GetData() != "") {
                            String temp = readThread.GetData();
                            if (temp.endsWith("200"))
                            {
                                status = 200;
                            }
                            if (status != 0)
                            {
                                magWakkerMaken = true;
                            }
                            Log.d("coordinatenHandler", "status = " + status);
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                while (magWakkerMaken) // Als er een REQUEST of OK is, maak andere thread wakker
                {
                    readThread.ResetData();
                    magWakkerMaken = false;
                    Log.d("coordinatenHandler", "maak handler wakker");
                    try {
                        status.wait();
                        status.notifyAll(); // maak andere threat wakker
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }


    }

    public void Write(String input) {
        byte[] bytes = input.getBytes();
        try {
            outputStream.write(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void Cancel() {
        try {
            bluetoothSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private class readThread extends Thread {

        private BluetoothSocket bluetoothSocket;
        private InputStream inputStream;
        private String data;

        public readThread(BluetoothSocket socket) {
            bluetoothSocket = socket;
            data = "";
            try {
                inputStream = socket.getInputStream();
                outputStream = socket.getOutputStream();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        public String GetData() {
            return data;
        }

        public void ResetData() {
            data = "";
        }

        @Override
        public void run() {
            while (true) {
                byte[] buffer = new byte[1024];
                int bytes;
                int availble = 0;
                try {
                    availble = inputStream.available();
                    if (availble != 0)
                    {
                        Log.d("coordinatenHandler", "availble = "+availble);
                        bytes = inputStream.read(buffer);

                        Log.d("coordinatenHandler", "bytes = "+ bytes);
                        if (bytes != 0)
                            processBuffer(buffer,1024);

                    }
                    } catch (IOException e) {
                    e.printStackTrace();
                }

            }

        }
        private void processBuffer(byte[] buffer, int size)
        {
            int length=0;
            for(int i=0;i<size;i++)
            {
                if(buffer[i]>'\0')
                {
                    length++;
                }
                else
                {
                    break;
                }
            }

            byte[] newbuff=new byte[length];

            for(int j=0;j<length;j++)
            {
                newbuff[j]=buffer[j];
            }

            if (data == "")
            {
                data = new String(newbuff);
            }
            else
            {
                data = data+new String(newbuff);
            }
            Log.d("coordinatenHandler", "data = "+ data);


        }
    }
}
