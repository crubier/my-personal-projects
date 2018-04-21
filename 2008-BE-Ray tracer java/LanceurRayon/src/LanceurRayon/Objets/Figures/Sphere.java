package LanceurRayon.Objets.Figures;

import LanceurRayon.Physique.Materiau;
import LanceurRayon.Util.Angle;
import LanceurRayon.Util.Geometrie.*;
import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Nombre;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;
/**
 * Permet de modéliser une sphère par la donnée de son centre et de son rayon
 * @author Solenne
 */

public class Sphere extends Figure  implements JDomIO{

	private Vecteur centre ;
	private Double rayon ;
/**
 * @ensure r > 0 
 * @param c centre de la sphère
 * @param r rayon de la sphère
 */	
	public Sphere(Vecteur c, Double r){
		super();
		this.centre = c ;
		this.rayon = r ;
	}
	
	public Sphere(Vecteur c, Double r,Materiau mat){
		super(mat);
		this.centre = c ;
		this.rayon = r ;
	}

	public Sphere() {
		this.centre = Vecteur.zero ;
		this.rayon = 0. ;
	}
	
	

    public Vecteur getCentre() {
        return centre;
    }

    public Double getRayon() {
        return rayon;
    }

    public void setCentre(Vecteur c) {
        this.centre = c;
    }

    public void setRayon(Double r) {
        this.rayon = r;
    }
 /**
 * Clacul l'intersection de la sphère avec un rayon issu de du point s, dans la direction d
 * @param s origine du rayon
 * @param d direction du rayon
 * @return Vecteur nul si l'intersection n'existe pas.
  *         Le point d'intersection s'il existe.
  * @throws java.lang.Exception 
 */               
	
	public Vecteur entree(Vecteur s , Vecteur d) throws Exception {
	
		Double r = this.rayon;
		Double x0=this.getCentre().getX();
		Double y0=this.getCentre().getY();
		Double z0=this.getCentre().getZ();
		Double x1=s.getX();
		Double y1=s.getY();
		Double z1=s.getZ();
		Double x2=d.getX();
		Double y2=d.getY();
		Double z2=d.getZ();

		
		Double delta =	4*Math.pow (x0*x2 - x1*x2 + y0*y2 - y1*y2 + z0*z2 - z1*z2, 2) - 
						4*(-Math.pow (r, 2) + Math.pow (x0, 2) - 2*x0*x1 + Math.pow (x1, 2) +
						Math.pow (y0, 2) - 2*y0*y1 + Math.pow (y1, 2) + 
						Math.pow (z0, 2) - 2*z0*z1 + Math.pow (z1, 2))*(Math.pow (x2, 2) +
						Math.pow (y2, 2) + Math.pow (z2, 2));
		
		
		if(delta>=0 ) {
			
			Double t = (x0*x2 - x1*x2 + y0*y2 - y1*y2 + z0*z2 - z1*z2)/(Math.pow(x2,2) + Math.pow(y2,2) + Math.pow(z2,2)) - 1/2.*Math.sqrt(delta);
			Double x = x1 + x2 *t;
			Double y = y1 + y2 *t;
			Double z = z1 + z2 *t;
				
			return new Vecteur(x,y,z);
		}
		else {
			return null;
		}
		                
	}
	
	public Vecteur sortie(Vecteur s , Vecteur d) throws Exception {
	
		Double r = this.rayon;
		Double x0=this.getCentre().getX();
		Double y0=this.getCentre().getY();
		Double z0=this.getCentre().getZ();
		Double x1=s.getX();
		Double y1=s.getY();
		Double z1=s.getZ();
		Double x2=d.getX();
		Double y2=d.getY();
		Double z2=d.getZ();

		
		Double delta =	4*Math.pow (x0*x2 - x1*x2 + y0*y2 - y1*y2 + z0*z2 - z1*z2, 2) - 
						4*(-Math.pow (r, 2) + Math.pow (x0, 2) - 2*x0*x1 + Math.pow (x1, 2) +
						Math.pow (y0, 2) - 2*y0*y1 + Math.pow (y1, 2) + 
						Math.pow (z0, 2) - 2*z0*z1 + Math.pow (z1, 2))*(Math.pow (x2, 2) +
						Math.pow (y2, 2) + Math.pow (z2, 2));
		
		
		if(delta>=0 ) {
			
			Double t = (x0*x2 - x1*x2 + y0*y2 - y1*y2 + z0*z2 - z1*z2)/(Math.pow(x2,2) + Math.pow(y2,2) + Math.pow(z2,2)) + 1/2.*Math.sqrt(delta);
			Double x = x1 + x2 *t;
			Double y = y1 + y2 *t;
			Double z = z1 + z2 *t;
				
			return new Vecteur(x,y,z);
		}
		else {
			return null;
		}
		                
	}
	
/**
 * Normale à la sphère  
 * @param p 
 * @return le vecteur normal à la sphère
 * @throws java.lang.Exception 
 */		
	public Vecteur normale(Vecteur p) throws Exception {
//		System.out.println("d="+((this.centre.distance(p))-rayon));
//		return new Vecteur(Vecteur.e0);
		return  p.difference(this.getCentre()).vecteurValue() ;
	}
	
	@Override
	public Vecteur projection(Vecteur a) throws Exception {
		Vecteur res = null;
		res =	a
			.difference
				(normale(a).multiplication(this.distance(a)))
			.vecteurValue();
		return res;
	}

	@Override
	public Double distance(Vecteur a) throws Exception {
		
		return (this.centre.distance(a))-rayon;
	}

	/**
	 * translate la sphère
	 * 
	 * @param direction 
	 */
	public void translation(Vecteur direction) {
        try {
            this.centre = this.centre.somme(direction).vecteurValue();
        } catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
        }
	}

	
	public void rotation(Vecteur origine, Angle a, Vecteur axe) {
		this.setCentre(this.getCentre().rotation(origine, a, axe));
	}

	@Override
	public Figure fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
				if( ! type.contains("sphere") ) {
					return super.fromJdom(element);
				}
				Sphere res = new Sphere();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("materiau")) {
						res.setMateriau(res.getMateriau().fromJdom(fils));
					} 
					else if (role.contains("position")) {
						res.setCentre(res.getCentre().fromJdom(fils));
					}
					else if (role.contains("rayon")) {
						res.setRayon(new Double(fils.getText()));
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
		c.setAttribute("Type", "sphere");
				
		c.addContent(super.getMateriau().toJdom("","Materiau"));
		c.addContent(this.getCentre().toJdom("","Position"));
		c.addContent(new Nombre(this.getRayon()).toJdom("","Rayon"));
		
		return c;
	}

	@Override
	public Figure clone() {
		Sphere res = new Sphere();
		res.centre = new Vecteur(this.centre);
		res.rayon = new Double(this.rayon);
		return res;
	}
	
}
