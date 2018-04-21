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
public class Player {

    /* ATTRIBUTES */

    private int marking [];
    private List<Transition> transitions ;
    private List<Transition> sensitive ;
    private Tribot robot;
    private int[] sensors;

    /* CONSTRUCTORS */

    public Player(){
    	this.transitions = new ArrayList<Transition>();
    	this.sensitive = new ArrayList<Transition>();
        this.sensors = new int [4]; 
    }

    public Player(int nbSites){
        this.marking = new int[nbSites];
        this.transitions = new ArrayList<Transition>();
        this.sensitive = new ArrayList<Transition>();
        this.sensors = new int [4];
    }
    
    public Player(int nbSites, List<Transition> trans, List<Transition> sens){
        this.marking = new int[nbSites];
        this.transitions = trans;
        this.sensitive = sens;
        this.sensors = new int[4];
    }

    /* METHODS */

    public List<Transition> play(){
    	Transition aux= new Transition();
    	this.sensitive.clear();
        this.sensors=refresh();

    	for(int i=0;i<transitions.size();i++){
    		if(this.transitions.get(i).isSensitive(marking)==1){
    			sensitive.add(transitions.get(i));
    			if(transitions.get(i).isCrossable(marking, sensors)==1){
    				if(transitions.get(i).getPriority()>aux.getPriority())
    					aux=transitions.get(i);
    			}
    		}
    	}

    	if(aux.getPriority()>0){
    		marking=aux.Cross(marking);
    		List<Action> actions = aux.getActions();
    		for(Action action : actions){
    			robot.executerAction(action.GetNumero(), action.GetParametre());
    		}
    		sensitive.clear();
    	}
    	
    	

    	return sensitive;
    }

    public boolean tryToCross(Transition transition){
    	/*for(int i=0; i<this.marking.length;i++){
            System.out.println("Le marquage de la place " + i + " est :" + this.getMarking()[i]);
       }*/
    	boolean reussi = false;
    	this.sensors=refresh();
    	if (transition.isSensitive(marking)==1){
    		if(transition.isCrossable(marking, sensors)==1){
                marking=transition.Cross(marking);
                List<Action> actions = transition.getActions();
        		for(Action action : actions){
        			robot.executerAction(action.GetNumero(), action.GetParametre());
        		}
        		reussi = true;
            }
    	}
    	
    	return reussi;
    }

    public int [] refresh(){

        for(int i=0; i<4; i++){
            sensors[i]=robot.getValeur(i);
        }
        return sensors;

    }

    /* GETTERS */

    public int[] getMarking(){
        return this.marking;
    }

    public List<Transition> getTransitions(){
        return this.transitions;
    }

    public List<Transition> getSensitive(){
        return this.sensitive;
    }

    public Tribot getRobot(){
        return this.robot;
    }

    /* SETTERS */

    public void setMarking(int[] mark){
        this.marking=mark;
    }

    public void setTransitions(List<Transition> trans){
        this.transitions=trans;
    }

    public void setSensitive(List<Transition> sens){
        this.sensitive=sens;
    }

    public void setRobot(Tribot rob){
        this.robot=rob;
    }

    public String markingToString(){
    	String str = "";
    	
    	for(int i=0; i<marking.length; i++){
    		str += " " + marking[i] + " |";
    	}
    	
    	return str;
    }
}
