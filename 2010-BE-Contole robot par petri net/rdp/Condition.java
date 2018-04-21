/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package rdp;

/**
 *
 * @author Jean-Baptiste
 */
public class Condition {

    /* ATTRIBUTES */

    private int sensor;
    private int threshold;
    private int operator;
    
    public enum OPERATOR{
    EGAL,
    INF_EGAL,
    SUP_EGAL,
    INF_STRICT,
    SUP_STRICT;
    }

    /* CONSTRUCTORS */

    public Condition(){


    }

    public Condition(int sen, int thr, int ope){

    this.sensor=sen;
    this.threshold=thr;
    this.operator=ope;
    
    }

    /* METHODS */

    public boolean isValid(int[] sensors){

        if(this.operator==1){
            if(sensors[this.sensor]==this.threshold){
                return true;
            }
        }

        if(this.operator==2){
            if(sensors[this.sensor]<=this.threshold){
                return true;
            }
        }

        if(this.operator==3){
            if(sensors[this.sensor]>=this.threshold){
                return true;
            }
        }

        if(this.operator==4){
            if(sensors[this.sensor]<this.threshold){
                return true;
            }
        }

        if(this.operator==5){
            if(sensors[this.sensor]>this.threshold){
                return true;
            }
        }

        return false;
    }

    /* GETTERS */
    
    public int getSensor(){
        return this.sensor;
    }
    
    public int getOperator(){
        return this.operator;
    }
    
    public int getThreshold(){
        return this.threshold;
    }

    /* SETTERS */

    public void setSensor(int sen){
        this.sensor=sen;
    }

    public void setOperator(int ope){
        this.operator=ope;
    }

    public void setThreshold(int thr){
        this.threshold=thr;
    }


}
