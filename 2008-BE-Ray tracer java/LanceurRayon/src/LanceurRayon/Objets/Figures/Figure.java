/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Objets.Figures;

import LanceurRayon.Objets.*;
import LanceurRayon.Physique.Materiau;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.JDomIO;
import java.util.Iterator;
import java.util.Locale;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @author Lecrubier
 */
public abstract class Figure implements ObjetDeScene, JDomIO, Cloneable{
	
	private Materiau mat;
	
	@Override
	public abstract Figure clone();
	
	public abstract Vecteur entree(Vecteur s, Vecteur d) throws Exception;
	
	public abstract Vecteur sortie(Vecteur s, Vecteur d) throws Exception;
	
	public abstract Vecteur normale(Vecteur a) throws Exception;
	
	public Vecteur tangente(Vecteur a, Vecteur dir) throws Exception {
		return normale(a).produitVectoriel(dir).produitVectoriel(normale(a)).normaliser().vecteurValue();
	}
	
	public abstract Vecteur projection(Vecteur a ) throws Exception;
	
	public abstract Double distance(Vecteur a) throws Exception;
	
	public Materiau materiau(Vecteur a) {
		return this.getMateriau();
	}

	public Figure(Materiau mat) {
		this.mat = mat;
	}

	public Figure() {
		this.mat = Materiau.defaut;
	}
	
	public Materiau getMateriau() {
		return mat;
	}

	public void setMateriau(Materiau mat) {
		this.mat = mat;
	}
	

	@Override
	public Figure fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			String ref = element.getAttributeValue("Reference","Inconnu");
			
			if(ref.compareTo("Inconnu")!=0) {
				System.out.println("reference");
				Iterator el = element.getDocument().getDescendants(new ElementFilter("Figure"));
				while(el.hasNext()) {
					Element actuel = (Element)el.next();
					String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
					if(nomEl.compareTo(ref)==0) {
						return this.fromJdom(actuel);
					}
				}
			}
			
			String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
			if(type.contains("sphere") ) {
				return (Sphere) (new Sphere()).fromJdom(element);
			} 
			else if(type.contains("plan3Points")  ) {
				return (Plan3Points) (new Plan3Points()).fromJdom(element);
			} 
			else if(type.contains("plan")  ) {
				return (Plan) (new Plan()).fromJdom(element);
			} 
			if(type.contains("cylindre")  ) {
				return (Cylindre) (new Cylindre()).fromJdom(element);
			} 
			else if(type.contains("facette") ) {
				return (Facette) (new Facette()).fromJdom(element);
			} 
			else if(type.contains("union") ) {
				return (Union) (new Union()).fromJdom(element);
			} 
			else if(type.contains("intersection") ) {
				return (Intersection) (new Intersection()).fromJdom(element);
			} 
			else if(type.contains("negation") ) {
				return (Negation) (new Negation()).fromJdom(element);
			} 
			else{
				return null;
			}
			
		}
	}

	
}
