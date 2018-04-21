/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Objets.Lumieres;

import LanceurRayon.Physique.Couleur;
import LanceurRayon.Physique.Materiau;
import LanceurRayon.Physique.Rayon;
import LanceurRayon.Util.Angle;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Liste;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;

/**
 *
 * @author Lecrubier
 */
public class LumiereSimple extends Lumiere implements JDomIO{

	private Vecteur position;

	public LumiereSimple(Vecteur point) {
		super();
		this.position = point;
	}
	
	public LumiereSimple(Vecteur point, Couleur couleur) {
		super(couleur);
		this.position = point;
	}

	public LumiereSimple() {
		super();
		this.position = new Vecteur(Vecteur.e0);
	}

	public Vecteur getPosition() {
		return position;
	}

	public void setPosition(Vecteur position) {
		this.position = position;
	}
		
	public void translation(Vecteur direction) {
		try {
			position = (Vecteur) position.somme(direction);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}

	public void rotation(Vecteur origine, Angle a, Vecteur axe) {
		
	}

	public Rayon rayonConvergent(Vecteur position, Liste<Materiau> materiau) {
		try {
			Vecteur dir = this.position.difference(position).vecteurValue();
			Double longueur = this.position.distance(position);
			return new Rayon(position, dir, longueur, 0, this.getCouleur(), materiau);
						
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}

	public Element toJdom(String Nom, String Role) {
		Element c = new Element("Lumiere") ;
		c.setAttribute("type", "ponctuelle");
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		
		c.addContent(this.getPosition().toJdom("","Position"));
		c.addContent(this.getCouleur().toJdom("","Couleur"));

		return c;
	}

	/**
	 * 
	 * @param element
	 * @return
	 */
	@Override
	public LumiereSimple fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				LumiereSimple res = new LumiereSimple();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("couleur")) {
						res.setCouleur(res.getCouleur().fromJdom(fils));
					}
					else if (role.contains("position")) {
						res.setPosition(res.getPosition().fromJdom(fils));
					}
				}
				return res;

			} catch (Exception ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				return null;
			}
		}
			
	}


}
