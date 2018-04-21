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

public class Plan extends Figure  implements JDomIO{

	private Vecteur centre ;
	private Vecteur normale ;

	public Plan(Vecteur centre, Vecteur normale) {
		this.centre = centre;
		this.normale = normale.normaliser().vecteurValue();
	}
	
	public Plan(Vecteur centre, Vecteur normale,Materiau mat) {
		super(mat);
		this.centre = centre;
		this.normale = normale.normaliser().vecteurValue();
	}

	public Plan() {
		this.centre = Vecteur.zero ;
		this.normale = Vecteur.e2.normaliser().vecteurValue();
	}

	public Vecteur getCentre() {
		return centre;
	}

	public void setCentre(Vecteur centre) {
		this.centre = centre;
	}

	public Vecteur getNormale() {
		return normale.normaliser().vecteurValue();
	}

	public void setNormale(Vecteur normale) {
		this.normale = normale.normaliser().vecteurValue();
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
	
		Double x0=this.getCentre().getX();
		Double y0=this.getCentre().getY();
		Double z0=this.getCentre().getZ();
		Double a=this.getNormale().getX();
		Double b=this.getNormale().getY();
		Double c=this.getNormale().getZ();
		Double x1=s.getX();
		Double y1=s.getY();
		Double z1=s.getZ();
		Double x2=d.getX();
		Double y2=d.getY();
		Double z2=d.getZ();

		if((a*x2 + b*y2 + c*z2)<0) {
			Double t = (a*x0 - a*x1 + b*y0 - b*y1 + c*z0 - c*z1)/(a*x2 + b*y2 + c*z2);
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
	
		Double x0=this.getCentre().getX();
		Double y0=this.getCentre().getY();
		Double z0=this.getCentre().getZ();
		Double a=this.getNormale().getX();
		Double b=this.getNormale().getY();
		Double c=this.getNormale().getZ();
		Double x1=s.getX();
		Double y1=s.getY();
		Double z1=s.getZ();
		Double x2=d.getX();
		Double y2=d.getY();
		Double z2=d.getZ();

		if((a*x2 + b*y2 + c*z2)>0) {
			Double t = (a*x0 - a*x1 + b*y0 - b*y1 + c*z0 - c*z1)/(a*x2 + b*y2 + c*z2);
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
		return  this.getNormale();
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
		return this.getNormale().produitScalaire(a.difference(this.getCentre()).vecteurValue());
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
		this.setNormale(this.getNormale().rotation(Vecteur.zero, a, axe));
	}

	@Override
	public Figure fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
				if( ! type.contains("plan") ) {
					return super.fromJdom(element);
				}
				Plan res = new Plan();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("materiau")) {
						res.setMateriau(res.getMateriau().fromJdom(fils));
					} 
					else if (role.contains("position")) {
						res.setCentre(res.getCentre().fromJdom(fils));
					}
					else if (role.contains("normale")) {
						res.setNormale(res.getNormale().fromJdom(fils));
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
		c.setAttribute("Type", "plan");
				
		c.addContent(super.getMateriau().toJdom("","Materiau"));
		c.addContent(this.getCentre().toJdom("","Position"));
		c.addContent(this.getNormale().toJdom("","Normale"));
		
		return c;
	}

	@Override
	public Figure clone() {
		Plan res = new Plan();
		res.centre = new Vecteur(this.centre);
		res.normale = new Vecteur(this.normale);
		return res;
	}
	
}
