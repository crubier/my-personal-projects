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
public class Intersection extends Figure implements JDomIO{
	
	private static final Double eps = 1.e-6;

	Liste<Figure> figures;

	public Intersection(Liste<Figure> figures,Materiau mat) {
		super(mat);
		this.figures = figures;
	}
	
	public Intersection() {
		super();
		this.figures = new Liste<Figure>();
		this.figures.add(new Sphere());
	}

	public Liste<Figure> getFigures() {
		return figures;
	}

	public void setFigures(Liste<Figure> figures) {
		this.figures = figures;
	}
	
	@Override
	public Vecteur entree(Vecteur s, Vecteur d) throws Exception {
		Vecteur res = null;
		for(Figure f:figures) {
			Vecteur inter = f.entree(s, d);
			if(inter!= null) {
				if(res==null) {
					if(this.contient(inter,f)) {
						res=new Vecteur(inter);
					}
				}
				else if(s.distance(inter)<=s.distance(res)) {
					if(this.contient(inter,f)) {
						res=new Vecteur(inter);
					}
				}
			}
		}
		return res;
	}
	
	
	@Override
	public Vecteur sortie(Vecteur s, Vecteur d) throws Exception {
		Vecteur res = null;
		for(Figure f:figures) {
			Vecteur inter = f.sortie(s, d);
			if(inter!= null) {
				if(res==null) {
					if(this.contient(inter,f)) {
						res=new Vecteur(inter);
					}
				}
				else if(s.distance(inter)<=s.distance(res)) {
					if(this.contient(inter,f)) {
						res=new Vecteur(inter);
					}
				}
			}
		}
		return res;
	}

	@Override
	public Vecteur normale(Vecteur a) throws Exception {
//		if(this.plusProche(a).getClass()==Plan.class) {
//				System.out.println("bobar " +this + " > " +this.plusProche(a));
//				return new Vecteur(1.,0.,0.);
//			}
		if(this.contient(a)) {
//			System.out.println("bobie " +this + " > " +this.plusProcheInt(a));
			return this.plusProcheInt(a).normale(a);
		}
		else {
//			if(this.plusProche(a).getClass()==Plan.class) {
//				System.out.println("bobar " +this + " > " +this.plusProche(a));
//				return new Vecteur(1.,0.,0.);
//			}
			return this.plusProcheExt(a).normale(a);
		}
	}
	
	@Override
	public Vecteur projection(Vecteur a) throws Exception {
		if(this.contient(a)) {
			return this.plusProcheExt(a).projection(a);
		}
		else {
			return this.plusProcheInt(a).projection(a);
		}
	}

	@Override
	public Double distance(Vecteur a) throws Exception {
		if(this.contient(a)) {
			return this.plusProcheExt(a).distance(a);
		}
		else {
			return this.plusProcheInt(a).distance(a);
		}
	}
	
	/**
	 * 
	 * @param a
	 * @return la figure de l'ensemble dont le point a est le plus proche
	 * @throws java.lang.Exception
	 */
	public Figure plusProche(Vecteur a) throws Exception {
		Double dist = LanceurRayon.Util.Mathematiques.Constante.Infini;
		Figure res = null;
		for(Figure f: figures) {
//			System.out.println("dist : " + f.getClass().getName() + " >  " +  f.distance(a));
			if(Math.abs(f.distance(a))<dist) {
				res = f;
				dist = Math.abs(f.distance(a));
			}
		}
		if(this.figures.size()>0 && res == null) {
			throw new Exception("Objet le plus proche non trouvé");
		}
//		System.out.println("resultatpluroche " + res.getClass().getName());
		return res;
	}
	
	/**
	 * 
	 * @param a
	 * @return la figure de l'ensemble dont le point a est le plus proche, tout en restant a l'exterieur
	 * @throws java.lang.Exception
	 */
	public Figure plusProcheExt(Vecteur a) throws Exception {
		Double dist = LanceurRayon.Util.Mathematiques.Constante.Infini;
		Figure res = null;
		for(Figure f: figures) {
			if(Math.abs(f.distance(a))<dist && f.distance(a)>=-eps) {
				res = f;
				dist = Math.abs(f.distance(a));
			}
		}
		if(this.figures.size()>0 && res == null) {
			throw new Exception("Objet le plus proche non trouvé");
		}
		return res;
	}
	
	/**
	 * 
	 * @param a
	 * @return la figure de l'ensemble dont le point a est le plus proche, tout en restant a l'exterieur
	 * @throws java.lang.Exception
	 */
	public Figure plusProcheInt(Vecteur a) throws Exception {
		Double dist = LanceurRayon.Util.Mathematiques.Constante.Infini;
//		System.out.println("nomclassfigure " + (this.figures.get(0)).getClass().getSimpleName());
		Figure res = null;
		for(Figure f: this.figures) {
//			System.out.println("nomclassfigure " + f.getClass().getSimpleName());
//			System.out.println("toc " + f.distance(a));
//			System.out.println(f.distance(a));
			if(Math.abs(f.distance(a))<dist && f.distance(a)<=eps) {
				res = f;
				dist = Math.abs(f.distance(a));
			}
		}
		if(this.figures.size()>0 && res == null) {
			throw new Exception("Objet le plus proche non trouvé");
		}
		return res;
	}
	
	public boolean contient(Vecteur a) throws Exception {
		for(Figure f: figures) {
			if(f.distance(a)>=eps) {
				return false;
			}
		}
		return true;
	}
	
	public boolean contient(Vecteur a, Figure ex) throws Exception {
		for(Figure f: figures) {
			if(f.distance(a)>=eps && !f.equals(ex)) {
				return false;
			}
			
		}
		return true;
	}

	public void translation(Vecteur direction) {
		for(Figure f:figures) {
			f.translation(direction);
		}
	}

	public void rotation(Vecteur origine, Angle a, Vecteur axe) {
		for(Figure f:figures) {
			f.rotation(origine, a, axe);
		}
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
					System.out.println("reference");
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
				if( ! type.contains("intersection") ) {
					return super.fromJdom(element);
				}
				Intersection res = new Intersection();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("materiau")) {
						res.setMateriau(res.getMateriau().fromJdom(fils));
					} 
					else if (role.contains("ensemble")) {
						res.setFigures(res.getFigures().fromJdom(fils));
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
		c.setAttribute("Type", "intersection");
				
		c.addContent(super.getMateriau().toJdom("","Materiau"));
		c.addContent(this.getFigures().toJdom("","Ensemble"));
		
		return c;
	}
	
	@Override
	public Figure clone() {
		Intersection res = new Intersection();
		res.figures = new Liste<Figure>(this.figures);
		return res;
	}
	

}
