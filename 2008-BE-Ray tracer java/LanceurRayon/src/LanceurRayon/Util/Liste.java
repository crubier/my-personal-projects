/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Attribute;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @param E 
 * @author Lecrubier
 */
public class Liste<E> extends Vector<E> implements JDomIO, Cloneable{

	/*
    * JDK 1.1 serialVersionUID 
    */
    private static final long serialVersionUID = 1111111;
	 
	public Liste(Collection<? extends E> c) {
		super();
		super.addAll(c);
	}

	public Liste() {
		super();
	}
	
	/**
	 * Cree une liste de longueur donnee remplie d'elements identiques
	 * @param longueur
	 * @param element
	 */
	public Liste(Integer longueur, E element) {
		super();
		for(Integer i=0; i<longueur;i++) {
			super.add(element);
		}
	}
	
	public Liste<E> Explicite() {
		this.clear();
		return this;
	}
	
	public Liste<E> Explicite(E element1) {
		this.clear();
		super.add(element1);
		return this;
	}
	
	public Liste<E> Explicite(E element1, E element2) {
		this.clear();
		super.add(element1);
		super.add(element2);
		return this;
	}

	
	public Liste<E> Explicite(E element1, E element2,  E element3) {
		this.clear();
		super.add(element1);
		super.add(element2);
		super.add(element3);
		return this;
	}

	
	public Liste<E> Explicite(E element1, E element2,  E element3, E element4) {
		this.clear();
		super.add(element1);
		super.add(element2);
		super.add(element3);
		super.add(element4);
		return this;
	}

	
	public Liste<E> Explicite(E element1, E element2,  E element3, E element4, E element5) {
		this.clear();
		super.add(element1);
		super.add(element2);
		super.add(element3);
		super.add(element4);
		super.add(element5);
		return this;
	}

	
	public Liste<E> Explicite(E element1, E element2,  E element3, E element4, E element5, E element6) {
		this.clear();
		super.add(element1);
		super.add(element2);
		super.add(element3);
		super.add(element4);
		super.add(element5);
		super.add(element6);
		return this;
	}

	
	public Liste<E> Explicite(E element1, E element2,  E element3, E element4, E element5, E element6,  E element7) {
		this.clear();
		super.add(element1);
		super.add(element2);
		super.add(element3);
		super.add(element4);
		super.add(element5);
		super.add(element6);
		super.add(element7);
		return this;
	}

	
	public Liste<E> Explicite(E element1, E element2,  E element3, E element4, E element5, E element6,  E element7, E element8) {
		this.clear();
		super.add(element1);
		super.add(element2);
		super.add(element3);
		super.add(element4);
		super.add(element5);
		super.add(element6);
		super.add(element7);
		super.add(element8);
		return this;
	}

	
	public Liste<E> Explicite(E element1, E element2,  E element3, E element4, E element5, E element6,  E element7, E element8, E element9) {
		this.clear();
		super.add(element1);
		super.add(element2);
		super.add(element3);
		super.add(element4);
		super.add(element5);
		super.add(element6);
		super.add(element7);
		super.add(element8);
		super.add(element9);
		return this;
	}

	@Override
	public synchronized void insertElementAt( E e, int i) {
		super.insertElementAt(e, i % this.size());
	}
	
	public void ajouter(Integer i, E e) {
		this.add(i % this.size(), e);
	}
	
	public void ajouter( E e) {
		
		this.add( e);
	}
	
	public E lire(Integer i) {
		return this.get(((i+this.size()) % this.size())); //Un peu pourri mias sinon ça marche pas ?? ggrr
	}
	
	public void regler(Integer i, E e) {
		this.set(i % this.size(), e);
	}
	
	public Liste<E> getPart(Integer from, Integer to) {
		Liste<E> res = new Liste<E>();
		if(from==to){
			return res;
		}
		else {
			if(from<to) {
				for(Integer i = from  ; i < to ; i++) {
					res.add(this.lire(i));
				}
			}
			else {
				for(Integer i = to  ; i < from ; i++) {
					res.add(this.lire(i));
				}
			}
			return res;
		}
		
	}
	
	public Liste<E> getFrom(Integer from) {
		return this.getPart(from, this.size());
	}
	
	public Liste<E> getTo(Integer to) {
		return this.getPart(0, to);
	}
	
	@Override
	public synchronized String toString() {
		String res = "<Liste>\n";
		for(int i = 0; i<this.size(); i++) {
			res = res + "	<Element>"+this.get(i)+"</Element>\n";
		}
		res = res + "\n</Liste>\n";
		return res;
	}


	
	public Boolean jdom() {
		boolean JDOMIO = false;
		if(this.isEmpty()) {
			return false;
		}
		else {
			Class<?>[] interfacesRealisees = this.firstElement().getClass().getInterfaces();
			for(Integer i = 0 ; i < interfacesRealisees.length ; i++) {
				if(interfacesRealisees[i].getName().compareTo(JDomIO.class.getName()) == 0) {
					JDOMIO = true;
				}
			}
			return JDOMIO;
		}
	}

		
//	@SuppressWarnings("unchecked")
//	public Liste fromJdom(Element element) {
//		if(element == null) {
//			return null;
//		}
//		else {
//			
////			Iterator<Attribute> i = element.getAttributes().iterator();
////			System.out.println("nattr : " + element.getName());
////			while(i.hasNext()) {
////				System.out.println(">>>>>>>>"+i.next().getName());
////			}
//			
//			String type = element.getAttribute("type").getValue();
//						
//
//			Iterator<Element> iterateur = (Iterator<Element>) element.getChildren().iterator();
//					
//			//Selon le resultat, on agit.
//			
//			if(!this.jdom() )  {
//				if(type.contains("Double")) {
//					Liste<Double> res = new Liste<Double>();
//					while(iterateur.hasNext()) {
//						String temp = iterateur.next().getValue();
//						res.add(new Double(temp));
//					}
//					return res;
//				}
//				else {
//					Liste<Integer> res = new Liste<Integer>();
//					while(iterateur.hasNext()) {
//						String temp = iterateur.next().getValue();
//						res.add(new Integer(temp));
//					}
//					return res;
//				}	
//					
//
//			}
//			else {
//				Liste<E> res = new Liste<E>();
//				while(iterateur.hasNext()) {
//					E te = (E) ((JDomIO)this.firstElement()).fromJdom(iterateur.next());
//					res.add(te );
//				}
//
//				return res;
//			}
//
//
//		}
//	
//	}
//
//	public Element toJdom(String Nom, String Role) {
//
//
//		Element c = new Element("Liste");
//		c.setAttribute("Role", Role);
//		c.setAttribute("Nom", Nom);
//
//		if (this.isEmpty()) {
//			return c;
//		} else {
//
////On verifie si les elements de la liste sont JDomisables
//
//			if (this.firstElement().getClass().getSuperclass().getName().compareTo(Number.class.getName()) == 0) {
//				c.setAttribute("type", this.firstElement().getClass().getSimpleName());
//			} else {
//				c.setAttribute("type", this.firstElement().getClass().getSuperclass().getSimpleName());
//			}
//
////Selon le resultat, on agit.
//			if (!this.jdom()) {
//				String type = this.firstElement().getClass().getSimpleName();
//				for (Integer i = 0; i < this.size(); i++) {
//					Element temp = new Element(type);
//					temp.setText(this.get(i).toString());
//					c.addContent(temp);
//				}
//			} else {
//				for (Integer i = 0; i < this.size(); i++) {
//					c.addContent(((JDomIO) this.get(i)).toJdom("", "Element " + i));
//				}
//			}
//
//			return c;
//
//		}
//	}
	
	public Liste fromJdom(Element element) {
		if (element == null) {
			return null;
		} 
		else {
			String ref = element.getAttributeValue("Reference","Inconnu");
			if(ref.compareTo("Inconnu")!=0) {
				System.out.println("reference");
				Iterator el = element.getDocument().getDescendants(new ElementFilter("Liste"));
				while(el.hasNext()) {
					Element actuel = (Element)el.next();
					String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
					if(nomEl.compareTo(ref)==0) {
						return this.fromJdom(actuel);
					}
				}
			}
			

			Iterator<Attribute> i = element.getAttributes().iterator();
			
			String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
			Iterator<Element> iterateur = (Iterator<Element>) element.getChildren().iterator();
			if (!this.jdom()) {
				if(type.contains("double")) {
					Liste<Double> res = new Liste<Double>();
					while(iterateur.hasNext()) {
						String temp = iterateur.next().getValue();
						res.add(new Double(temp));
					}
					return res;
				}
				else {
					Liste<Integer> res = new Liste<Integer>();
					while(iterateur.hasNext()) {
						String temp = iterateur.next().getValue();
						res.add(new Integer(temp));
					}
					return res;
				}	

			} else {
				Liste<E> res = new Liste<E>();
				while (iterateur.hasNext()) {
//					System.out.println("LISTE de "+this.firstElement().getClass().getSimpleName());
					E te = (E) ((JDomIO) this.firstElement()).fromJdom(iterateur.next());
					res.add(te);
				}

				return res;
			}
		}
	}
	

	public Element toJdom(String Nom, String Role) {
		Element c = new Element("Liste") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		if (this.isEmpty()) {
			return c;
		} else {
			
			if (this.firstElement().getClass().getSuperclass().getName().compareTo(Number.class.getName()) == 0) {
				c.setAttribute("Type", this.firstElement().getClass().getSimpleName());
			} else {
				c.setAttribute("Type", this.firstElement().getClass().getSuperclass().getSimpleName());
			}
			
			if (this.firstElement().getClass().getSuperclass().getName().compareTo(Number.class.getName()) == 0) {
				for(Integer i = 0; i< this.size();i++) {
					c.addContent(new Nombre((Number)this.get(i)).toJdom("",i.toString()));
				}
			}
			else {
				for(Integer i = 0; i< this.size();i++) {
					c.addContent(((JDomIO)this.get(i)).toJdom("",i.toString()));
				}
			}

			return c;
		}
	}

	public Object clone() {
		return super.clone();
	}
	

}


