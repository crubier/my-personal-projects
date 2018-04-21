/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package rdp;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Jean-Baptiste
 */
public class Transition {

    /* ATTRIBUTES */

    private int[] input;
    private int[] output;
    private List<Condition> conditions;
    private List<Action> actions;
    private int priority;

    /* CONSTRUCTORS */

    public Transition(){
        priority = 0;
        actions = new ArrayList<Action>();
        conditions = new ArrayList<Condition>();
    }


    public Transition(int[] inp, int[] out, List<Action> act, List<Condition> cond, int pri){
        input=inp;
        output=out;
        actions = new ArrayList<Action>();
        actions=act;
        priority=pri;
        conditions = new ArrayList<Condition>();
        conditions=cond;
    }

    /* METHODS */

    public int[] Cross(int[] marking){

        int aux[] = new int[marking.length];

        for(int i=0 ; i<marking.length ; i++){
            aux[i]=marking[i]+this.output[i]-this.input[i];
        }

        return aux;
    }

    public int isCrossable(int[] marking, int[] sensors){

    	if(this.isSensitive(marking)==1){
    		int c=1;
    		for(int j=0; j<this.conditions.size(); j++){
    			if(!this.conditions.get(j).isValid(sensors)){
    				c=0;
    			}
    		}
    		return c;
    	}
    	else
    		return 1;
    }

    public int isSensitive(int[] marking){
        int c=0;
        for(int j=0; j<marking.length; j++){
        	if(this.input[j]<=marking[j]){
        		c=c+1;
        	}
        }

        if (c==marking.length){
        	return 1;
        }
        else
        	return 0;
    }

    /* GETTERS */

    public int[] getInput(){
        return this.input;
    }

    public int[] getOutput(){
        return this.output;
    }

    public List<Condition> getConditions(){
        return this.conditions;
    }

    public List<Action> getActions(){
        return this.actions;
    }

    public int getPriority(){
        return this.priority;
    }

    /* SETTERS */

    public void setInput(int[] inp){
        this.input=inp;
    }

    public void setOutput(int[] out){
        this.output=out;
    }

    public void setConditions(List<Condition> cond){
        this.conditions=cond;
    }

    public void setAction(List<Action> act){
        this.actions=act;
    }

    public void setPriority(int pri){
        this.priority=pri;
    }
}
