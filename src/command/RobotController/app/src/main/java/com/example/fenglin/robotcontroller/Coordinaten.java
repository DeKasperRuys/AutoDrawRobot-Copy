package com.example.fenglin.robotcontroller;

import java.util.ArrayList;
import java.util.List;

public class Coordinaten {
    private List<Integer> x;
    private List<Integer> y;
    private List<Integer> penStrength;

    Coordinaten()
    {
        x = new ArrayList<Integer>();
        y = new ArrayList<Integer>();
        penStrength = new ArrayList<Integer>();
    }

    public void setCoordinaten()
    {

    }


    public void setPenStrength(List<Integer> penStrength) {
        this.penStrength = penStrength;
    }

    public void setX(List<Integer> x) {
        this.x = x;
    }

    public void setY(List<Integer> y) {
        this.y = y;
    }

    public List<Integer> getX() {
        return x;
    }

    public List<Integer> getY() {
        return y;
    }

    public List<Integer> getPenStrength() {
        return penStrength;
    }

    public void addToX(int x)
    {
        this.x.add(x);
    }

    public void addToY(int y)
    {
        this.y.add(y);
    }

    public void addToPenStrength(int strength)
    {
        this.penStrength.add(strength);
    }


}
