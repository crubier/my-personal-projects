/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Objets.Lumieres;

import LanceurRayon.Objets.*;
import LanceurRayon.Physique.Couleur;
import LanceurRayon.Physique.Materiau;
import LanceurRayon.Physique.Rayon;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Liste;
import java.util.Iterator;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @author Lecrubier
 */
public abstract class Lumiere implements ObjetDeScene, JDomIO{
	private Couleur couleur;
	public static final Couleur defaut = Couleur.blanc;

	public Lumiere(Couleur couleur) {
		this.couleur = couleur;
	}

	public Lumiere() {
		try {
			this.couleur = new Couleur(defaut);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
	/**
	 * 
	 * @param position
	 * @param materiau 
	 * @return Vecteur normé de la direction du rayon se dirigeant vers la lumiere
	 */
	public abstract Rayon rayonConvergent(Vecteur position, Liste<Materiau> materiau);
	
	public Couleur getCouleur() {
		return couleur;
	}

	public void setCouleur(Couleur couleur) {
		this.couleur = couleur;
	}
	
	@Override
	public Lumiere fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			String ref = element.getAttributeValue("Reference","Inconnu");
			if(ref.compareTo("Inconnu")!=0) {
				System.out.println("reference");
				Iterator el = element.getDocument().getDescendants(new ElementFilter("Lumiere"));
				while(el.hasNext()) {
					Element actuel = (Element)el.next();
					String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
					if(nomEl.compareTo(ref)==0) {
						return this.fromJdom(actuel);
					}
				}
			}
			
			String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
			if(type.compareTo("ponctuelle") == 0 ) {
				return new LumiereSimple().fromJdom(element);
			} 
			else{
				return new LumiereSimple().fromJdom(element);
			}
			
		}
	}

	
	

}
