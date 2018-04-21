package LanceurRayon.Util;





import LanceurRayon.Util.Mathematiques.Intervalle;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @param E 
 * @author Lecrubier
 */
public class Rectangle<E extends Number & Comparable<E>> implements JDomIO{
	private Intervalle<E> X;
	private Intervalle<E> Y;

	Rectangle(Rectangle<E> a) {
		this.X = new Intervalle<E>(a.X);
		this.Y = new Intervalle<E>(a.Y);
	}

	public Intervalle<E> getX() {
		return X;
	}

	public void setX(Intervalle<E> X) {
		this.X = X;
	}

	public Intervalle<E> getY() {
		return Y;
	}

	public void setY(Intervalle<E> Y) {
		this.Y = Y;
	}

	public Rectangle(Intervalle<E> X, Intervalle<E> Y) {
		this.X = X;
		this.Y = Y;
	}
	
	public Rectangle(E X0, E Y0,E X1, E Y1) {
		this.X = new Intervalle<E>(X0,X1);
		this.Y = new Intervalle<E>(Y0,Y1);
	}

	public Boolean contient(E x, E y) {
		return X.contient(x) && Y.contient(y);
	}

	
	
	public Rectangle() {
		this.X = new Intervalle<E>();
		this.Y = new Intervalle<E>();
	}
	
	public Rectangle<E> fromJdom(Element element) {
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Rectangle"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				Rectangle<E> res = new Rectangle<E>();
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
		Element c = new Element("Rectangle");
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		c.addContent(X.toJdom("","X"));
		c.addContent(Y.toJdom("","Y"));
		return c;
	}
}
