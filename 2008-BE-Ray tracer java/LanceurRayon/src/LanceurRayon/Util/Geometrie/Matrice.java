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
public class Matrice extends Tenseur implements JDomIO{
	
	public final static Liste<Integer> dimensions =	new Liste<Integer>().Explicite(3,3);
	
	public final static Liste<Integer> i00 =new Liste<Integer>().Explicite(0,0);
	public final static Liste<Integer> i01 =new Liste<Integer>().Explicite(0,1);
	public final static Liste<Integer> i02 =new Liste<Integer>().Explicite(0,2);
	public final static Liste<Integer> i10 =new Liste<Integer>().Explicite(1,0);
	public final static Liste<Integer> i11 =new Liste<Integer>().Explicite(1,1);
	public final static Liste<Integer> i12 =new Liste<Integer>().Explicite(1,2);
	public final static Liste<Integer> i20 =new Liste<Integer>().Explicite(2,0);
	public final static Liste<Integer> i21 =new Liste<Integer>().Explicite(2,1);
	public final static Liste<Integer> i22 =new Liste<Integer>().Explicite(2,2);
	
	public final static Matrice identite =	new Matrice(1.,0.,0.,0.,1.,0.,0.,0.,1.) ;
	public final static Matrice zero =		new Matrice(0.,0.,0.,0.,0.,0.,0.,0.,0.) ;
	
	public final static Matrice eij =		new Matrice(1.,1.,1.,1.,1.,1.,1.,1.,1.) ;
	public final static Matrice neij =		new Matrice(-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.) ;
	
	public final static Matrice ei0 =		new Matrice(1.,0.,0.,1.,0.,0.,1.,0.,0.) ;
	public final static Matrice ei1 =		new Matrice(0.,1.,0.,0.,1.,0.,0.,1.,0.) ;
	public final static Matrice ei2 =		new Matrice(0.,0.,1.,0.,0.,1.,0.,0.,1.) ;
	public final static Matrice nei0 =		new Matrice(-1.,0.,0.,-1.,0.,0.,-1.,0.,0.) ;
	public final static Matrice nei1 =		new Matrice(0.,-1.,0.,0.,-1.,0.,0.,-1.,0.) ;
	public final static Matrice nei2 =		new Matrice(0.,0.,-1.,0.,0.,-1.,0.,0.,-1.) ;
	
	public final static Matrice e0j =		new Matrice(1.,1.,1.,0.,0.,0.,0.,0.,0.) ;
	public final static Matrice e1j =		new Matrice(0.,0.,0.,1.,1.,1.,0.,0.,0.) ;
	public final static Matrice e2j =		new Matrice(0.,0.,0.,0.,0.,0.,1.,1.,1.) ;
	public final static Matrice ne0j =		new Matrice(-1.,-1.,-1.,0.,0.,0.,0.,0.,0.) ;
	public final static Matrice ne1j =		new Matrice(0.,0.,0.,-1.,-1.,-1.,0.,0.,0.) ;
	public final static Matrice ne2j =		new Matrice(0.,0.,0.,0.,0.,0.,-1.,-1.,-1.) ;
	
	public final static Matrice e00 =		new Matrice(1.,0.,0.,0.,0.,0.,0.,0.,0.) ;
	public final static Matrice e01 =		new Matrice(0.,1.,0.,0.,0.,0.,0.,0.,0.) ;
	public final static Matrice e02 =		new Matrice(0.,0.,1.,0.,0.,0.,0.,0.,0.) ;
	public final static Matrice e10 =		new Matrice(0.,0.,0.,1.,0.,0.,0.,0.,0.) ;
	public final static Matrice e11 =		new Matrice(0.,0.,0.,0.,1.,0.,0.,0.,0.) ;
	public final static Matrice e12 =		new Matrice(0.,0.,0.,0.,0.,1.,0.,0.,0.) ;	
	public final static Matrice e20 =		new Matrice(0.,0.,0.,0.,0.,0.,1.,0.,0.) ;
	public final static Matrice e21 =		new Matrice(0.,0.,0.,0.,0.,0.,0.,1.,0.) ;
	public final static Matrice e22 =		new Matrice(0.,0.,0.,0.,0.,0.,0.,0.,1.) ;
	public final static Matrice ne00 =		new Matrice(-1.,0.,0.,0.,0.,0.,0.,0.,0.) ;
	public final static Matrice ne01 =		new Matrice(0.,-1.,0.,0.,0.,0.,0.,0.,0.) ;
	public final static Matrice ne02 =		new Matrice(0.,0.,-1.,0.,0.,0.,0.,0.,0.) ;
	public final static Matrice ne10 =		new Matrice(0.,0.,0.,-1.,0.,0.,0.,0.,0.) ;
	public final static Matrice ne11 =		new Matrice(0.,0.,0.,0.,-1.,0.,0.,0.,0.) ;
	public final static Matrice ne12 =		new Matrice(0.,0.,0.,0.,0.,-1.,0.,0.,0.) ;	
	public final static Matrice ne20 =		new Matrice(0.,0.,0.,0.,0.,0.,-1.,0.,0.) ;
	public final static Matrice ne21 =		new Matrice(0.,0.,0.,0.,0.,0.,0.,-1.,0.) ;
	public final static Matrice ne22 =		new Matrice(0.,0.,0.,0.,0.,0.,0.,0.,-1.) ;

	
	public Matrice(Double a, Double b, Double c, Double d, Double e, Double f, Double g, Double h, Double i)  {
		super();
		try {
			super.setDimensions(Matrice.dimensions);
			super.setCoefficients(new Liste<Double>().Explicite(a,b,c,d,e,f,g,h,i));
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
	public Matrice(Vecteur a, Vecteur b, Vecteur c) {
		super();
		try {
			super.setDimensions(Matrice.dimensions);
			Liste<Double> coeffs = new Liste<Double>();
			coeffs.addAll(a.getCoefficients());
			coeffs.addAll(b.getCoefficients());
			coeffs.addAll(c.getCoefficients());
			super.setCoefficients(coeffs);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
	public Matrice(Tenseur a) {
		super();
		try {
			if(a.getDimensions().equals(Matrice.dimensions)) {
				super.setDimensions(Matrice.dimensions);
				super.setCoefficients(new Liste<Double>(a.getCoefficients()));
			}


		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
	public Matrice() {
		super();	
		super.setDimensions(Matrice.dimensions);
	}
	
	
	public Double determinant() throws Exception {
		return			  this.getDouble(0,0)*this.getDouble(1,1)*this.getDouble(2,2)
                        + this.getDouble(0,1)*this.getDouble(1,2)*this.getDouble(2,0)
                        + this.getDouble(0,2)*this.getDouble(1,0)*this.getDouble(2,1)
                        - this.getDouble(0,0)*this.getDouble(1,2)*this.getDouble(2,1)
                        - this.getDouble(0,1)*this.getDouble(1,0)*this.getDouble(2,2)
                        - this.getDouble(0,2)*this.getDouble(1,1)*this.getDouble(2,0);
	}
	
	public Double trace() throws Exception {
		return			this.getDouble(0,0)+
						this.getDouble(1,1)+
						this.getDouble(2,2);
	}
	
	
	public Double getDouble(Integer i, Integer j) {
		try {
			Liste<Integer> pos = new Liste<Integer>();
			pos.add(i);
			pos.add(j);
			return this.getDouble(pos);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	public void setDouble(Integer i, Integer j, Double element) {
		try {
			Liste<Integer> pos = new Liste<Integer>();
			pos.add(i);
			pos.add(j);
			this.setDouble(pos, element);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}		
	}
	
	public Matrice transposee() {
		try {
			
			return (Matrice) this.transposition(0,1);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}

	@Override
	public Tenseur getTenseur(Integer element) throws Exception {
		return super.getTenseur(element);
	}
	
	
	public static Matrice rotationOlinde(Angle angle, Vecteur axe) {
		try {
		Double a = axe.getDouble(Vecteur.i0);
		Double b = axe.getDouble(Vecteur.i1);
		Double c = axe.getDouble(Vecteur.i2);
		Double t=angle.getRad();
		return new Matrice(
			Math.pow(a,2)*(1 - Math.cos(t)) + Math.cos(t),
			a*b*(1 - Math.cos(t)) - c*Math.sin(t),
			a*c*(1 - Math.cos(t)) + b*Math.sin(t),
			a*b*(1 - Math.cos(t)) + c*Math.sin(t),
			Math.pow(b,2)*(1 - Math.cos(t)) + Math.cos(t),
			b*c*(1 - Math.cos(t)) - a*Math.sin(t),
			a*c*(1 - Math.cos(t)) - b*Math.sin(t),
			b*c*(1 - Math.cos(t)) + a*Math.sin(t),
			Math.pow(c,2)*(1 - Math.cos(t)) + Math.cos(t)
			);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
//		List(List(Power(a,2)*(1 - Cos(t)) + Cos(t),a*b*(1 - Cos(t)) - c*Sin(t),a*c*(1 - Cos(t)) + b*Sin(t)),
//   List(a*b*(1 - Cos(t)) + c*Sin(t),Power(b,2)*(1 - Cos(t)) + Cos(t),b*c*(1 - Cos(t)) - a*Sin(t)),
//   List(a*c*(1 - Cos(t)) - b*Sin(t),b*c*(1 - Cos(t)) + a*Sin(t),Power(c,2)*(1 - Cos(t)) + Cos(t)))
	}
	
	public Matrice rotation(Angle angle, Vecteur axe) {
		try {
			Matrice matrot = Matrice.rotationOlinde(angle, axe);
			Tenseur res = matrot.produitcontracte(this, 1);
			return (Matrice) res;
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}

	/**
	 * 
	 * @param other
	 * @return
	 * @throws java.lang.Exception
	 */
	/*public Matrice multiplication(Matrice other) throws Exception {
		return (Matrice) super.multiplication(other);
	}

	public Matrice produit(Matrice other) throws Exception {
		return (Matrice) super.produit(other);
	}

	public Matrice somme(Matrice other) throws Exception {
		return (Matrice) super.somme(other);
	}

	public Matrice transposition() throws Exception {
		return (Matrice) super.transposition(0, 1);
	}*/
	
	public Vecteur getV1() throws Exception {
		
		Vecteur res = new Vecteur();
		res.setDouble(Vecteur.i0, this.getDouble(Matrice.i00));
		res.setDouble(Vecteur.i1, this.getDouble(Matrice.i10));
		res.setDouble(Vecteur.i2, this.getDouble(Matrice.i20));
		return res;
	}
	
	public void setV1(Vecteur a) throws Exception {
		this.setDouble(Matrice.i00, a.getDouble(Vecteur.i0));
		this.setDouble(Matrice.i10, a.getDouble(Vecteur.i1));
		this.setDouble(Matrice.i20, a.getDouble(Vecteur.i2));
	}
	
	public Vecteur getV2() throws Exception {
		
		Vecteur res = new Vecteur();
		res.setDouble(Vecteur.i0, this.getDouble(Matrice.i01));
		res.setDouble(Vecteur.i1, this.getDouble(Matrice.i11));
		res.setDouble(Vecteur.i2, this.getDouble(Matrice.i21));
		return res;
	}
	
	public void setV2(Vecteur a) throws Exception {
		this.setDouble(Matrice.i01, a.getDouble(Vecteur.i0));
		this.setDouble(Matrice.i11, a.getDouble(Vecteur.i1));
		this.setDouble(Matrice.i21, a.getDouble(Vecteur.i2));
	}
	
	public Vecteur getV3() throws Exception {
		
		Vecteur res = new Vecteur();
		res.setDouble(Vecteur.i0, this.getDouble(Matrice.i02));
		res.setDouble(Vecteur.i1, this.getDouble(Matrice.i12));
		res.setDouble(Vecteur.i2, this.getDouble(Matrice.i22));
		return res;
	}
	
	public void setV3(Vecteur a) throws Exception {
		this.setDouble(Matrice.i02, a.getDouble(Vecteur.i0));
		this.setDouble(Matrice.i12, a.getDouble(Vecteur.i1));
		this.setDouble(Matrice.i22, a.getDouble(Vecteur.i2));
	}
	
	
	@Override
	public Element toJdom(String Nom, String Role) {
		try {
			Element c = new Element("Matrice");
			c.setAttribute("Role", Role);
			c.setAttribute("Nom", Nom);
			c.addContent(this.getV1().toJdom("", "V1"));
			c.addContent(this.getV2().toJdom("", "V2"));
			c.addContent(this.getV3().toJdom("", "V3"));

			return c;
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}

	@Override
	public Matrice fromJdom(Element element) {
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Matrice"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				Matrice res = new Matrice();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("v1")) {
						res.setV1(res.getV1().fromJdom(fils));
					}
					else if (role.contains("v2")) {
						res.setV2(res.getV2().fromJdom(fils));
					}
					else if (role.contains("v3")) {
						res.setV3(res.getV3().fromJdom(fils));
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
	
	
	
}
