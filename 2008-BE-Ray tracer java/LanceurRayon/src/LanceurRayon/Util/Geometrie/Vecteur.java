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
public class Vecteur extends Tenseur implements JDomIO{
	
	public final static Liste<Integer> dimensions =	new Liste<Integer>().Explicite(3);
	
	public final static Liste<Integer> i0 =			new Liste<Integer>().Explicite(0);
	public final static Liste<Integer> i1 =			new Liste<Integer>().Explicite(1);
	public final static Liste<Integer> i2 =			new Liste<Integer>().Explicite(2);
	
	public final static Vecteur zero =		new Vecteur(0.,0.,0.) ;
	
	public final static Vecteur ei =		new Vecteur(1.,1.,1.) ;
	public final static Vecteur nei =		new Vecteur(-1.,-1.,-1.) ;
	
	public final static Vecteur e0 =		new Vecteur(1.,0.,0.) ;
	public final static Vecteur e1 =		new Vecteur(0.,1.,0.) ;
	public final static Vecteur e2 =		new Vecteur(0.,0.,1.) ;
	public final static Vecteur ne0 =		new Vecteur(-1.,0.,0.) ;
	public final static Vecteur ne1 =		new Vecteur(0.,-1.,0.) ;
	public final static Vecteur ne2 =		new Vecteur(0.,0.,-1.) ;
	
	
	public Vecteur() {
		super();
		super.setDimensions(Vecteur.dimensions);
	}
	
	public Vecteur(Double a, Double b, Double c) {
		super();
		try {
			super.setDimensions(Vecteur.dimensions);
			super.setCoefficients(new Liste<Double>().Explicite(a,b,c));
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
	public Vecteur(Tenseur a) {
		super();
		try {
			if(a.getDimensions().equals(Vecteur.dimensions)) {
				super.setDimensions(Vecteur.dimensions);
				super.setCoefficients(new Liste<Double>(a.getCoefficients()));
			}


		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
//	public produitScalaire(Vecteur other) {
//		
//	}
	
	public Vecteur produitVectoriel(Vecteur other) {
		return new 
			Vecteur(
				this.getCoefficients().lire(1)*other.getCoefficients().lire(2)-
				this.getCoefficients().lire(2)*other.getCoefficients().lire(1),
				this.getCoefficients().lire(2)*other.getCoefficients().lire(0)-
				this.getCoefficients().lire(0)*other.getCoefficients().lire(2),
				this.getCoefficients().lire(0)*other.getCoefficients().lire(1)-
				this.getCoefficients().lire(1)*other.getCoefficients().lire(0)
			);
	}
	
	public Double produitScalaire(Vecteur other) {
		return 
				this.getCoefficients().lire(0)*other.getCoefficients().lire(0)+
				this.getCoefficients().lire(1)*other.getCoefficients().lire(1)+
				this.getCoefficients().lire(2)*other.getCoefficients().lire(2);
	}
	
	public Vecteur rotation(Vecteur centre, Angle angle, Vecteur axe) {
		try {
			Matrice matrot = Matrice.rotationOlinde(angle, axe);
			return centre.somme(matrot.produitcontracte(this.difference(centre), 1)).vecteurValue();
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	public Double cosAngle(Vecteur other) {
		return (this.produitScalaire(other))/(this.norme()*other.norme());
	}
	
	public Double sinAngle(Vecteur other) {
		return (this.produitVectoriel(other).norme())/(this.norme()*other.norme());
	}
	
	public Angle Angle(Vecteur other) {
		return new Angle(this.sinAngle(other),this.cosAngle(other));
	}

	public Double getX() throws Exception {
		return this.getDouble(Vecteur.i0);
	}
	
	public void setX(Double a) throws Exception {
		this.setDouble(Vecteur.i0, a);
	}
	
	public Double getY() throws Exception {
		return this.getDouble(Vecteur.i1);
	}
	
	public void setY(Double a) throws Exception {
		this.setDouble(Vecteur.i1, a);
	}
		
	public Double getZ() throws Exception {
		return this.getDouble(Vecteur.i2);
	}
	
	public void setZ(Double a) throws Exception {
		this.setDouble(Vecteur.i2, a);
	}

	@Override
	public Vecteur fromJdom(Element element) {
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Vecteur"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				
				Vecteur res = new Vecteur();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("x")) {
						res.setX(new Double(fils.getText()));
					}
					else if (role.contains("y")) {
						res.setY(new Double(fils.getText()));
					}
					else if (role.contains("z")) {
						res.setZ(new Double(fils.getText()));
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
			Element c = new Element("Vecteur");
			c.setAttribute("Role", Role);
			c.setAttribute("Nom", Nom);
			c.addContent(new Nombre(this.getX()).toJdom("", "X"));
			c.addContent(new Nombre(this.getY()).toJdom("", "Y"));
			c.addContent(new Nombre(this.getZ()).toJdom("", "Z"));


			return c;
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
}
