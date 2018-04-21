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
public class AngleSolide implements JDomIO{
	
	public static final AngleSolide zero = new AngleSolide(Angle.a0, Angle.a0);
	
	private Angle X;
	private Angle Y;

	public Angle getX() {
		return X;
	}

	public void setX(Angle X) {
		this.X = X;
	}

	public Angle getY() {
		return Y;
	}

	public void setY(Angle Y) {
		this.Y = Y;
	}

	public AngleSolide(Angle X, Angle Y) {
		this.X = X;
		this.Y = Y;
	}

	public static AngleSolide Deg(Double X, Double Y) {
		return new AngleSolide(Angle.Deg(X),Angle.Deg(Y));
	}
	
	public static AngleSolide Rad(Double X, Double Y) {
		return new AngleSolide(Angle.Rad(X),Angle.Rad(Y));
	}
	
	

	public AngleSolide() {
		this.X = new Angle();
		this.Y = new Angle();
	}
	
	
	public AngleSolide fromJdom(Element element) {
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("AngleSolide"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				AngleSolide res = new AngleSolide();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("x")) {
						res.setX(res.getX().fromJdom(fils));
					}
					else if (role.contains("y")) {
						res.setY(res.getY().fromJdom(fils));
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
		Element c = new Element("AngleSolide");
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);

		c.addContent(X.toJdom("","X"));
		c.addContent(Y.toJdom("","Y"));
		return c;
	}
}
