package rdp.debug;

import java.util.ArrayList;
import java.util.List;

import rdp.Action;
import rdp.Capteur;
import rdp.Condition;
import rdp.NomAction;
import rdp.Player;
import rdp.Transition;

public class PlayerSimpleDebug extends Player {
	
	public static Player load(){
		
		int nbSites = 4;
        List<Transition> transitions = new ArrayList<Transition>();
        List<Condition> conditions = new ArrayList<Condition>();
        List<Condition> conditions2 = new ArrayList<Condition>();
        List<Condition> conditions3 = new ArrayList<Condition>();
        List<Condition> conditions4 = new ArrayList<Condition>();
        List<Action> actions = new ArrayList<Action>();
        List<Action> actions2 = new ArrayList<Action>();
        List<Action> actions3 = new ArrayList<Action>();
        List<Action> actions4 = new ArrayList<Action>();
        
        //#1

        int [] input_1 = new int [nbSites];
        int [] output_1 = new int [nbSites];

        for (int i=0; i<nbSites; i++){
                input_1[i] = 0;
                output_1[i] = 0;
            }

        input_1[0] = 1;
        output_1[1] = 1;
        
        actions.add(new Action(NomAction.BIPER.ordinal(),100));
        actions.add(new Action(NomAction.AVANCER.ordinal(),100));
        Condition cond = new Condition(Capteur.ULTRASON.ordinal(), 20,2);
        conditions.add(cond);

        transitions.add(new Transition(input_1, output_1, actions, conditions, 1));
        
        //#2

        int [] input_2 = new int [nbSites];
        int [] output_2 = new int [nbSites];

        for (int i=0; i<nbSites; i++){
                input_2[i] = 0;
                output_2[i] = 0;
            }

        input_2[1] = 1;
        output_2[2] = 1;
        
        actions2.add(new Action(NomAction.STOP.ordinal(),0));
        actions2.add(new Action(NomAction.JOUER_TON.ordinal(),800));
        Condition cond2 = new Condition(Capteur.SONORE.ordinal(), 50 , 3);
        conditions2.add(cond2);

        transitions.add(new Transition(input_2, output_2, actions2, conditions2, 1));
        
        
        
        int [] input_3 = new int [nbSites];
        int [] output_3 = new int [nbSites];

        for (int i=0; i<nbSites; i++){
                input_3[i] = 0;
                output_3[i] = 0;
            }

        input_3[2] = 1;
        output_3[3] = 1;
        
        actions3.add(new Action(NomAction.OUVRIR_PINCE.ordinal(),0));
        conditions3.add(new Condition(Capteur.SONORE.ordinal(), 50 , 3));
        conditions3.add(new Condition(Capteur.TACTILE.ordinal(), 1 , 1));
        
        transitions.add(new Transition(input_3, output_3, actions3, conditions3, 1));
        
        
        int [] input_4 = new int [nbSites];
        int [] output_4 = new int [nbSites];

        for (int i=0; i<nbSites; i++){
                input_4[i] = 0;
                output_4[i] = 0;
            }

        input_4[3] = 1;
        output_4[0] = 1;
        
        actions4.add(new Action(NomAction.FERMER_PINCE.ordinal(),0));
        conditions4.add(new Condition(Capteur.PHOTOSENSIBLE.ordinal(), 50 , 2));
        
        transitions.add(new Transition(input_4, output_4, actions4, conditions4, 1));
        
        
        int [] input_ini= new int [nbSites];
        
        input_ini[0] = 1;
        input_ini[1] = 0;

        //On peut maintenant créer le joueur

        Player joueur = new Player(nbSites);
        joueur.setTransitions(transitions);
        joueur.setMarking(input_ini);
        
        return joueur; 

        
		
	}

}
