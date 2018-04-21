/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util;

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
public class Angle extends Number implements JDomIO, Comparable<Angle>{
	
	public final static Angle a0 = new Angle(0.);
	public final static Angle a90 = new Angle(Math.PI/2.);
	public final static Angle a180 = new Angle(Math.PI);
	public final static Angle a270 = new Angle(-1*Math.PI/2.);
	
	Double Valeur; //en radians

	public Angle(Double Valeur) {
		this.Valeur = Valeur;
	}
	
	public Angle(Double y,Double x) {
		this.Valeur = Math.atan2(y, x);
	}
	
	public Angle( ) {
		this.Valeur = 0.;
	}
		
	public Double getRad() {
		return Valeur;
	}

	public void setRad(Double Valeur) {
		this.Valeur = Valeur;
	}
		
	public Double getDeg() {
		return Valeur * 180 / Math.PI;
	}

	public void setDeg(Double Valeur) {
		this.Valeur = Valeur * Math.PI / 180;
	}
	
	public Angle multiplication(Double k) {
		Angle res = new Angle(this.Valeur);
		res.Valeur *= k;
		return res;
	}
	
	public static Angle Deg(Double val) {
		Angle res = new Angle();
		res.setDeg(val);
		return res;
	}
		
	public static Angle Rad(Double val) {
		Angle res = new Angle();
		res.setRad(val);
		return res;
	}

	public Element toJdom(String Nom, String Role) {
		Element c = new Element("Angle") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		c.setAttribute("Unite", "rad");
		c.addContent(new Nombre(this.Valeur).toJdom("", "Valeur"));
		return c;
	}

	public Angle fromJdom(Element element) {
	
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Angle"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				Angle res = new Angle();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					String unite = element.getAttributeValue("Unite", "Inconnu").toLowerCase(Locale.ENGLISH);
					
					if (role.contains("valeur")) {
						System.out.println(role + " " + unite);
						if (unite.compareTo("rad") == 0) {
							res.setRad(new Double(fils.getText()));
						} else if (unite.compareTo("deg") == 0) {
							System.out.println("degrés");
							res.setDeg(new Double(fils.getText()));
						} else {
							res.setRad(new Double(fils.getText()));
						}
					}
				}
				return res;
			} catch (Exception ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				return null;
			}
		} else {
			return null;
		}
	}
	
	@Override
	public int intValue() {
		return this.Valeur.intValue();
	}

	@Override
	public long longValue() {
		return this.Valeur.longValue();
	}

	@Override
	public float floatValue() {
		return this.Valeur.floatValue();
	}

	@Override
	public double doubleValue() {
		return this.Valeur.doubleValue();
	}

	public int compareTo(Angle o) {
		return this.Valeur.compareTo(o.Valeur);
	}
	
	public Double cos() {
		return Math.cos(Valeur);
	}
	
	public Double sin() {
		return Math.sin(Valeur);
	}
	
	public Double tan() {
		return Math.tan(Valeur);
	}

}
