package rdp;

import java.util.ArrayList;
import java.util.List;

/**
 * Prend en charge la vérification des conditiosn associées aux transitions.
 * 
 * @author Yannick BISIAUX
 *
 */
public class GestionnaireAbonnement {

	private Tribot tribot;
	private List<Transition> abonnements;
	
	public GestionnaireAbonnement(Tribot tribot){
		this.tribot = tribot;
		this.abonnements = new ArrayList<Transition>();
	}
	
	public void abonnerTransitions(List<Transition> transitions){
		this.abonnements = transitions;
	}
	
	/**Attention, ne gère pas la gestion de priorité.
	 * 
	 * @return
	 */
	public Transition verifierAbonnements(){
		int indexTrans = -1;
		for (int i=0; i<abonnements.size(); i++){
			Transition transition = abonnements.get(i);
			boolean ok = true;
			for(Condition condition : transition.getConditions()){
				if(!condition.isValid(tribot.getValeurs())){
					ok = false;
				}
			}
			if(ok){
				indexTrans = i;
				break;
			}
		}
		
		if(indexTrans == -1){
			return null;
		} else {
			return abonnements.get(indexTrans);
		}
		
	}
}
