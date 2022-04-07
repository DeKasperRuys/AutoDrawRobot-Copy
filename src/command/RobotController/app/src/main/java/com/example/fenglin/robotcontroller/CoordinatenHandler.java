package com.example.fenglin.robotcontroller;

import android.content.Context;
import android.os.AsyncTask;
import android.text.LoginFilter;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CoordinatenHandler extends Thread {


    public static final int CONTINUE = 100; // Er zijn nog coodinaten moeten sturen;
    public static final int OK = 200; //heeft ontvangen, == ROGER
    public static final int COUNT = 210; //eind met 210 betekent deze message is aantal
    public static final int REQUEST = 201; // Request for next part
    public static final int ACCEPTED = 202; // Ontvangen van coordinaten, en het aantal is juist i.v.m aantal
    public static final int DONE = 203; // Geen coordinaten meer
    public static final int RESET = 205; // Reset gestuurde coordinaten, zal opnieuw beginnen
    public static final int WRONG = 400; // het aantal van verzonden coordianten klopt niet met het aantal van ontvangen coordinaten
    public static final int[] CODES = {CONTINUE,OK,COUNT,REQUEST,ACCEPTED,DONE,RESET,WRONG};



    private Integer state;
    private boolean isFinished;
    private int eindPosition;
    private String deelCoordinaten;
    private StringBuilder coordinatenBuilder;
    private ArrayList<ArrayList<String>> coordinaten;
    private File file;
    private BluetoothThread bluetoothThread;
    private Context context;

    private int positionPointer,aantalDelen;
    Toast beginToast,finalToast;
    public CoordinatenHandler(String path, Context context, int state, BluetoothThread btThread,String name)
    {
        super(name);
        this.state = state;

        file = new File(path);

        this.context = context;

        coordinatenBuilder = new StringBuilder();
        coordinaten = new ArrayList<>();
        splitCoordinatenFile(); //split de file van coordinaten in lagen
        //test();
        isFinished = false;
        this.bluetoothThread = btThread;

        splitCoordinatenFile();
        aantalDelen = coordinaten.size();
        positionPointer = 0;
        beginToast = Toast.makeText(context,"Frame "+Integer.toString(positionPointer+1)+"/"+Integer.toString(aantalDelen) +" wordt doorgestuurd",Toast.LENGTH_SHORT);
        finalToast = Toast.makeText(context,"Alles gestuurd",Toast.LENGTH_SHORT);

    }

    private void splitCoordinatenFile() // split de txt in verschillende framen, daarna in 16coordinaten per list
    {

        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            String line;
            int index = 0;
            int aantalDelen = 0;
            int rest = 0;
            int inStukVan = 16;
            while ((line = bufferedReader.readLine()) != null)
            {
                ArrayList<String> temp = splitString(line);
                aantalDelen = temp.size()/inStukVan;
                if (temp.size()%inStukVan !=0 )
                    rest = temp.size()-aantalDelen*inStukVan;

                int p = 0;

                for (int i= 0; i<aantalDelen; i++)
                {
                    ArrayList<String> list = new ArrayList<>();
                    for (int j = 0; j < inStukVan; j++) //16
                    {
                        list.add(temp.get(p));
                        p++;
                    }
                    coordinaten.add(list);
                }

                if (rest != 0) {
                    ArrayList<String> list = new ArrayList<>();
                    for (int i = 0; i < rest; i++)
                    {
                        list.add(temp.get(p));
                        p++;
                    }
                    coordinaten.add(list);
                }

            }

        }
        catch (Exception e)
        {
            e.printStackTrace();
        }


    }
    //TODO:DELET
    private void test()
    {
        for (int i = 0; i < coordinaten.size();i++)
        {
            int size = 0;
            boolean isOneven = false;
            for (int j = 0; j< coordinaten.get(i).size(); j++)
            {
                Log.d("CoordinatenHandler", coordinaten.get(i).get(j));
            }
                Log.d("CoordinatenHandler", "Volgende Deel");
        }
    }
    private ArrayList<String> splitString(String input)
    {
        String[] arrRes = input.split(";");
        ArrayList<String> listRes = new ArrayList<String>();

        for (int i = 0; i < arrRes.length; i++)
        {
            listRes.add(arrRes[i]);
        }

        return listRes;
    }

    private int coordinatenCount(String str)
    {
        String[] puntkomma = str.split(";");
        return puntkomma.length;
    }

    public boolean isFinished(){ return isFinished;}

    @Override
    public void run() {
        super.run();
        Log.d("coordinatenHandler", "run: nu begint sturen ");

        if (positionPointer < aantalDelen) {
            beginToast.show();
            int aantalCoordinaten = coordinaten.get(positionPointer).size();

            //stuur aantal coordinaten door
            bluetoothThread.Write(Integer.toString(aantalCoordinaten) + Integer.toString(CoordinatenHandler.COUNT));
            Log.d("coordinatenHandler", "aantal is doorgestuurd, aantal = "+Integer.toString(aantalCoordinaten));
            try {
                sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            int size = coordinaten.get(positionPointer).size();
////            boolean isOneven = false;
//            if (coordinaten.get(positionPointer).size() % 2 == 0) // Controleer de size van coordinaten even getal is of oneven, oneven getal kan leiden tot index of a list bound
//            {
//                size = coordinaten.get(positionPointer).size() / 2;
//            } else {
////                isOneven = true;
//                size = coordinaten.get(positionPointer).size() / 2 + 1;
//            }
            for (int i = 0; i < size; i+=2)            //coordinaten per 2 doorsturen;
            {

                if (size - i != 1) {
                    bluetoothThread.Write(coordinaten.get(positionPointer).get(i) + ";" + coordinaten.get(positionPointer).get(i + 1) + ";");
                    Log.d("coordinatenHandler", coordinaten.get(positionPointer).get(i) + ";" + coordinaten.get(positionPointer).get(i + 1) + ";");
                    try {
                        sleep(3000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                } else {
                    bluetoothThread.Write(coordinaten.get(positionPointer).get(i) + ";");
                    Log.d("coordinatenHandler", coordinaten.get(positionPointer).get(i) + ";");
                    try {
                        sleep(3000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
            positionPointer++;
            bluetoothThread.Write(Integer.toString(DONE));
        }
        else
        {
            finalToast.show();
            Log.d("coordinatenHandler", "Alles doorgestuurd");
        }
    }

    //   @Override
//    public void run() {
//        Log.d("coordinatenHandler", "binnen functie run");
//        synchronized (state){
//            Log.d("coordinatenHandler", "binnen functie synchronized");
//            while (!isFinished)
//            {
//            Log.d("coordinatenHandler","binnen while");
//                        for (int i = 0; i < coordinaten.size();)
//                        {
//                            //Stuur aantaal coordinaten door
//                            int aantalCoordinaten = coordinaten.get(i).size();
//                            bluetoothThread.Write(Integer.toString(aantalCoordinaten)+Integer.toString(CoordinatenHandler.COUNT)); //Stuur aantal coordianten door
//                            state.notifyAll(); // maak bt wakker
//                            Log.d("coordinatenHandler", "aantal gestuurd");
//                            try{
//                                while (bluetoothThread.getStatus() != CoordinatenHandler.OK )
//                                {
//                                    Log.d("coordinatenHandler", "wait coordinatenhandler");
//                                    state.wait(); // Wacht op OK;
//                                }
//                            }catch (Exception e)
//                            {
//                                e.printStackTrace();
//                            }
//                            Log.d("coordinatenHandler", "coordinatenHandler is terug wakker");
//                            if (bluetoothThread.getStatus() == CoordinatenHandler.OK)
//                            {
//                                bluetoothThread.setStatus(0); // init de status
//                            }
//
//
//                            int size = 0;
//                            boolean isOneven = false;
//                            if (coordinaten.get(i).size()%2 == 0) // Controleer de size van coordinaten even getal is of oneven, oneven getal kan leiden tot index of a list bound
//                            {
//                                size = coordinaten.get(i).size()/2;
//                            }
//                            else
//                            {
//                                isOneven = true;
//                                size = coordinaten.get(i).size()/2+1;
//                            }
//
//                            for (int j = 0; j< size ;j+=2) //coordinaten per 2 doorsturen;
//                            {
//
//                                if (isOneven)
//                                {
//                                    if (size - j != 1)
//                                    {
//                                        bluetoothThread.Write(coordinaten.get(i).get(j)+";"+coordinaten.get(i).get(j+1)+";");
//                                        state.notifyAll(); // laat bt beginnen te lezen
//                                        try{
//                                            while (bluetoothThread.getStatus() != CoordinatenHandler.OK)
//                                            {
//                                                state.wait(); // Wacht op OK;
//                                            }
//                                            bluetoothThread.setStatus(0); // init de status
//                                        }catch (Exception e)
//                                        {
//                                            e.printStackTrace();
//                                        }
//
//                                    }
//                                    else
//                                    {
//                                        bluetoothThread.Write(coordinaten.get(i).get(j)+";");
//                                        state.notifyAll(); // laat bt beginnen te lezen
//                                        try{
//                                            while (bluetoothThread.getStatus() != CoordinatenHandler.OK )
//                                            {
//                                                state.wait(); // Wacht op OK;
//                                            }
//                                            bluetoothThread.setStatus(0); // init de status
//
//                                        }catch (Exception e)
//                                        {
//                                            e.printStackTrace();
//                                        }
//                                    }
//                                }
//                                else
//                                {
//                                    bluetoothThread.Write(coordinaten.get(i).get(j)+";"+coordinaten.get(i).get(j+1)+";");
//                                    state.notifyAll(); // laat bt beginnen te lezen
//                                    try{
//                                        while (bluetoothThread.getStatus() != CoordinatenHandler.OK )
//                                        {
//                                            state.wait(); // Wacht op OK;
//                                        }
//                                        bluetoothThread.setStatus(0); // init de status
//                                    }catch (Exception e)
//                                    {
//                                        e.printStackTrace();
//                                    }
//                                }
//                                    //Is er nog andere deel
//                                    if ((coordinaten.size()-i) <= 1)
//                                    {
//                                        bluetoothThread.Write(Integer.toString(CoordinatenHandler.DONE)); //Geen andere laag meer
//                                        state.notifyAll();
//                                        while (bluetoothThread.getStatus() != CoordinatenHandler.OK)
//                                        {
//                                            try {
//                                                state.wait();   //wacht op ok
//
//                                            }catch (Exception e)
//                                            {
//                                                e.printStackTrace();
//                                            }
//
//                                        }
//                                        bluetoothThread.setStatus(0); // init de status
//                                        Toast toast = Toast.makeText(context, "Upload gedaan", Toast.LENGTH_SHORT);
//                                        toast.show();
//                                        return;
//                                    }
//                                    else
//                                    {
//                                        bluetoothThread.Write(Integer.toString(CoordinatenHandler.CONTINUE)); // nog andere laag
//                                        state.notifyAll();
//                                        while (bluetoothThread.getStatus() != CoordinatenHandler.OK)
//                                        {
//                                            try {
//                                                state.wait();   //wacht op ok
//                                            }catch (Exception e)
//                                            {
//                                                e.printStackTrace();
//                                            }
//                                        }
//                                        bluetoothThread.setStatus(0); // init de status
//
//                                        i++; // naar andere laag
//                                        state.notifyAll();
//                                        while (bluetoothThread.getStatus() != CoordinatenHandler.REQUEST) // wacht op request van andere laag
//                                        {
//                                            try {
//                                                state.wait();
//                                            } catch (Exception e)
//                                            {
//                                                e.printStackTrace();
//                                            }
//                                        }
//                                        bluetoothThread.setStatus(0); // init de status
//
//                                    }
//
//                            }
//
//
//                        }
//
//            }
//
//        }
//
//
//    }
}
