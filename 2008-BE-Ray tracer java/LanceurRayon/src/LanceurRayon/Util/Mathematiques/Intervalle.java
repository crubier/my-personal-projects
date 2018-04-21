/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util.Mathematiques;

import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Nombre;
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
 */
public class Intervalle< E extends Number & Comparable<E>> implements JDomIO {
	
	private E borneInf;

	private E borneSup;


	public Intervalle() {
	}

	public Intervalle(E borneInf, E borneSup) {
		this.borneInf =  borneInf;
		this.borneSup =  borneSup;
	}

	public Intervalle(Intervalle<E> a) {
		this.borneInf =  a.borneInf;
		this.borneSup =  a.borneSup;
	}

	public E getBorneInf() {
		return borneInf;
	}

	public void setBorneInf(E borneInf) {
		this.borneInf =  borneInf;
	}

	public E getBorneSup() {
		return borneSup;
	}


	public void setBorneSup(E borneSup) {
		this.borneSup =  borneSup;
	}


	public void set(E borneInf, E borneSup) {
		this.borneInf =  borneInf;
		this.borneSup =  borneSup;
	}



	@Override
	public String toString() {
		return "["+borneInf+", "+borneSup+"]";
	}

	public void set(Intervalle<E> p) {
		this.set(p.getBorneInf(), p.getBorneSup());
	}

	public Boolean contient(E x) {
		return (this.borneInf.compareTo(x) <= 0  ) &&
				(this.borneSup.compareTo(x) >= 0  );

	}

	@Override
	public boolean equals(Object obj) {
		return super.equals(obj);
	}

	@Override
	public int hashCode() {
		int hash = 7;
		return hash;
	}

	public Number longueur() {
		if (borneInf.getClass().getName().compareTo(Double.class.getName()) == 0) {
			return new Double(borneSup.doubleValue() - borneInf.doubleValue());
		} else if (borneInf.getClass().getName().compareTo(Integer.class.getName()) == 0) {
			return new Integer(borneSup.intValue() - borneInf.intValue());
		} else {
			return 0;
		}
	}

	@SuppressWarnings("unchecked")
	public Intervalle<E> fromJdom(Element element) {
			if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Intervalle"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				Intervalle<E> res = new Intervalle<E>();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("bornesup")) {
						res.setBorneSup((E)Nombre.convertir(res.borneSup,fils.getText()));
					}
					else if (role.contains("borneinf")) {
						res.setBorneInf((E)Nombre.convertir(res.borneInf,fils.getText()));
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
		Element c = new Element("Intervalle") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		if(this.borneInf== null ||this.borneSup==null) {
			return c;
		}
		else {
				c.addContent(new Nombre(this.borneSup).toJdom("","BorneSup"));
				c.addContent(new Nombre(this.borneInf).toJdom("","BorneInf"));
			return c;
		}
	}
		
}