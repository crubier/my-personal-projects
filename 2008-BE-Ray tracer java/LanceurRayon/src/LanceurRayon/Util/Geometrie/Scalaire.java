/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util.Geometrie;

import LanceurRayon.Util.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @author Lecrubier
 */
public class Scalaire extends Tenseur implements JDomIO {
    
	public final static Liste<Integer> dimensions =	new Liste<Integer>().Explicite();
	public final static Liste<Integer> i =			new Liste<Integer>().Explicite();

	/**
	 * Scalaires de base
	 */
	public final static Scalaire zero = new Scalaire(0.) ;
	public final static Scalaire identite = new Scalaire(1.) ;
	public final static Scalaire e = new Scalaire(1.) ;
	public final static Scalaire ne = new Scalaire(-1.) ;
	
	/**
	 * 
	 */
	public Scalaire() {
        super();
    }
    
    public Scalaire(Double a) {
        super();
		try {
			Liste<Double> c = new Liste<Double>();
			c.add(a);
			super.setCoefficients(c);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
    }
	
	
	public Scalaire(Tenseur a) {
		super();
		try {
			if(a.getDimensions().equals(Scalaire.dimensions)) {
				super.setDimensions(Scalaire.dimensions);
				super.setCoefficients(new Liste<Double>(a.getCoefficients()));
			}


		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
	
	public Double getDouble(Integer i) {
		try {
			Liste<Integer> pos = new Liste<Integer>();
			pos.add(i);
			return this.getDouble(pos);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	public void setDouble(Integer i, Double element) {
		try {
			Liste<Integer> pos = new Liste<Integer>();
			pos.add(i);
			this.setDouble(pos, element);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}		
	}
	
	public Double getVal() throws Exception {
		return this.getDouble(Scalaire.i);
	}
	
	public void setVal(Double a) throws Exception {
		this.setDouble(Scalaire.i, a);
	}
		
	@Override
	public Scalaire fromJdom(Element element) {
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Scalaire"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				Scalaire res = new Scalaire();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("valeur")) {
						res.setVal(new Double(fils.getText()));
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

	public Element toJdom(String Nom, String Role) {
		try {
			Element c = new Element("Scalaire");
			c.setAttribute("Role", Role);
			c.setAttribute("Nom", Nom);
			c.addContent(new Nombre(this.getVal()).toJdom("", "Valeur"));
		

			return c;
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	
}
