/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Objets.Figures;

import LanceurRayon.Physique.Materiau;
import LanceurRayon.Util.Angle;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Liste;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @author Lecrubier
 */
public class Negation extends Figure implements JDomIO{
	
	private static final Double eps = 1.e-6;

	Figure figure;

	public Negation(Figure figure,Materiau mat) {
		super(mat);
		this.figure = figure;
	}
	
	public Negation() {
		super();
		this.figure =new Sphere();
	}
	
		
	public Negation(Figure figure) {
		super();
		this.figure =figure;
	}

	public Figure getFigure() {
		return figure;
	}

	public void setFigure(Figure figure) {
		this.figure = figure;
	}
	
	@Override
	public Vecteur entree(Vecteur s, Vecteur d) throws Exception {
		return figure.sortie(s, d);
	}

	@Override
	public Vecteur sortie(Vecteur s, Vecteur d) throws Exception {
		return figure.entree(s, d);
	}

	@Override
	public Vecteur normale(Vecteur a) throws Exception {
		return figure.normale(a).multiplication(-1.).vecteurValue();
	}
	
	@Override
	public Vecteur projection(Vecteur a) throws Exception {
		return figure.projection(a);
	}

	@Override
	public Double distance(Vecteur a) throws Exception {
		return -1. * figure.distance(a);
	}
	
		
	public void translation(Vecteur direction) {
		figure.translation(direction);
	}

	public void rotation(Vecteur origine, Angle a, Vecteur axe) {
		figure.rotation(origine, a, axe);
	}

	@Override
	public Figure fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Intersection"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
				if( ! type.contains("negation") ) {
					return super.fromJdom(element);
				}
				Negation res = new Negation();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("materiau")) {
						res.setMateriau(res.getMateriau().fromJdom(fils));
					} 
					else if (role.contains("figure")) {
						res.setFigure(res.getFigure().fromJdom(fils));
					} 
				}
				return res;

			} catch (Exception ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				return null;
			}
		}
	}

	public Element toJdom(String Nom, String Role) {
		Element c = new Element("Figure") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		c.setAttribute("Type", "negation");
				
		c.addContent(super.getMateriau().toJdom("","Materiau"));
		c.addContent(this.getFigure().toJdom("","Figure"));
		
		return c;
	}
	
	@Override
	public Figure clone() {
		Negation res = new Negation(figure.clone());
		return res;
	}
	

}
