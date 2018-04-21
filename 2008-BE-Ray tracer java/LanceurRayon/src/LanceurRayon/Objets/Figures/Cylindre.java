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

public class Cylindre extends Figure  implements JDomIO{

	private Vecteur centre ;
	private Vecteur direction ;
	private Double rayon ;
/**
 * @ensure r > 0 
 * @param c centre de la sphère
 * @param r rayon de la sphère
 * @param d 
 */	
	public Cylindre(Vecteur c, Double r, Vecteur d){
		super();
		this.centre = c ;
		this.rayon = r ;
		this.direction = d.normaliser().vecteurValue() ;
	}
	
	public Cylindre(Vecteur c, Double r, Vecteur d, Materiau mat){
		super(mat);
		this.centre = c ;
		this.rayon = r ;
		this.direction = d.normaliser().vecteurValue() ;
	}

	public Cylindre() {
		this.centre = Vecteur.zero ;
		this.direction = Vecteur.e0 ;
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

	public Vecteur getDirection() {
		return direction.normaliser().vecteurValue();
	}

	public void setDirection(Vecteur direction) {
		this.direction = direction.normaliser().vecteurValue();
	}
	
	public Vecteur entree(Vecteur s , Vecteur d) throws Exception {
	
		Double r = this.rayon;
		Double x0=this.centre.getX();
		Double y0=this.centre.getY();
		Double z0=this.centre.getZ();
		Double a=this.direction.getX();
		Double b=this.direction.getY();
		Double c=this.direction.getZ();
		Double x1=s.getX();
		Double y1=s.getY();
		Double z1=s.getZ();
		Double x2=d.getX();
		Double y2=d.getY();
		Double z2=d.getZ();
		
		Double delta = 4 * Math.pow(Math.pow(c, 2) * (x0 * x2 - x1 * x2 + y0 * y2 - y1 * y2) + a * c * (-(x2 * z0) + x2 * z1 - x0 * z2 + x1 * z2) +
			Math.pow(b, 2) * (x0 * x2 - x1 * x2 + z0 * z2 - z1 * z2) + Math.pow(a, 2) * (y0 * y2 - y1 * y2 + z0 * z2 - z1 * z2) +
			b * (a * (-(x2 * y0) + x2 * y1 - x0 * y2 + x1 * y2) + c * (-(y2 * z0) + y2 * z1 - y0 * z2 + y1 * z2)), 2) -
			4 * (Math.pow(c, 2) * (Math.pow(x2, 2) + Math.pow(y2, 2)) - 2 * a * c * x2 * z2 - 2 * b * y2 * (a * x2 + c * z2) +
			Math.pow(b, 2) * (Math.pow(x2, 2) + Math.pow(z2, 2)) + Math.pow(a, 2) * (Math.pow(y2, 2) + Math.pow(z2, 2))) *
			(Math.pow(a, 2) * Math.pow(y0, 2) + Math.pow(c, 2) * (Math.pow(x0, 2) - 2 * x0 * x1 + Math.pow(x1, 2) + Math.pow(y0 - y1, 2)) -
			2 * Math.pow(a, 2) * y0 * y1 + Math.pow(a, 2) * Math.pow(y1, 2) + Math.pow(a, 2) * Math.pow(z0, 2) -
			2 * b * (y0 - y1) * (a * (x0 - x1) + c * (z0 - z1)) +
			Math.pow(b, 2) * (Math.pow(x0, 2) - 2 * x0 * x1 + Math.pow(x1, 2) + Math.pow(z0 - z1, 2)) - 2 * a * c * (x0 - x1) * (z0 - z1) -
			2 * Math.pow(a, 2) * z0 * z1 + Math.pow(a, 2) * Math.pow(z1, 2) -
			Math.pow(r, 2) * Math.sqrt(Math.pow(Math.abs(a), 2) + Math.pow(Math.abs(b), 2) + Math.pow(Math.abs(c), 2)));
			
		if(delta>=0) {
		
			Double gamma = Math.sqrt(delta) /
				(Math.pow(c, 2) * (Math.pow(x2, 2) + Math.pow(y2, 2)) - 2 * a * c * x2 * z2 - 2 * b * y2 * (a * x2 + c * z2) +
				Math.pow(b, 2) * (Math.pow(x2, 2) + Math.pow(z2, 2)) + Math.pow(a, 2) * (Math.pow(y2, 2) + Math.pow(z2, 2)));

			Double t = (Math.pow(c, 2) * (x0 * x2 - x1 * x2 + y0 * y2 - y1 * y2) + a * c * (-(x2 * z0) + x2 * z1 - x0 * z2 + x1 * z2) +
				Math.pow(b, 2) * (x0 * x2 - x1 * x2 + z0 * z2 - z1 * z2) + Math.pow(a, 2) * (y0 * y2 - y1 * y2 + z0 * z2 - z1 * z2) +
				b * (a * (-(x2 * y0) + x2 * y1 - x0 * y2 + x1 * y2) + c * (-(y2 * z0) + y2 * z1 - y0 * z2 + y1 * z2))) /
				(Math.pow(c, 2) * (Math.pow(x2, 2) + Math.pow(y2, 2)) - 2 * a * c * x2 * z2 - 2 * b * y2 * (a * x2 + c * z2) +
				Math.pow(b, 2) * (Math.pow(x2, 2) + Math.pow(z2, 2)) + Math.pow(a, 2) * (Math.pow(y2, 2) + Math.pow(z2, 2))) - gamma / 2;

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
		Double x0=this.centre.getX();
		Double y0=this.centre.getY();
		Double z0=this.centre.getZ();
		Double a=this.direction.getX();
		Double b=this.direction.getY();
		Double c=this.direction.getZ();
		Double x1=s.getX();
		Double y1=s.getY();
		Double z1=s.getZ();
		Double x2=d.getX();
		Double y2=d.getY();
		Double z2=d.getZ();
		
		Double delta = 4 * Math.pow(Math.pow(c, 2) * (x0 * x2 - x1 * x2 + y0 * y2 - y1 * y2) + a * c * (-(x2 * z0) + x2 * z1 - x0 * z2 + x1 * z2) +
			Math.pow(b, 2) * (x0 * x2 - x1 * x2 + z0 * z2 - z1 * z2) + Math.pow(a, 2) * (y0 * y2 - y1 * y2 + z0 * z2 - z1 * z2) +
			b * (a * (-(x2 * y0) + x2 * y1 - x0 * y2 + x1 * y2) + c * (-(y2 * z0) + y2 * z1 - y0 * z2 + y1 * z2)), 2) -
			4 * (Math.pow(c, 2) * (Math.pow(x2, 2) + Math.pow(y2, 2)) - 2 * a * c * x2 * z2 - 2 * b * y2 * (a * x2 + c * z2) +
			Math.pow(b, 2) * (Math.pow(x2, 2) + Math.pow(z2, 2)) + Math.pow(a, 2) * (Math.pow(y2, 2) + Math.pow(z2, 2))) *
			(Math.pow(a, 2) * Math.pow(y0, 2) + Math.pow(c, 2) * (Math.pow(x0, 2) - 2 * x0 * x1 + Math.pow(x1, 2) + Math.pow(y0 - y1, 2)) -
			2 * Math.pow(a, 2) * y0 * y1 + Math.pow(a, 2) * Math.pow(y1, 2) + Math.pow(a, 2) * Math.pow(z0, 2) -
			2 * b * (y0 - y1) * (a * (x0 - x1) + c * (z0 - z1)) +
			Math.pow(b, 2) * (Math.pow(x0, 2) - 2 * x0 * x1 + Math.pow(x1, 2) + Math.pow(z0 - z1, 2)) - 2 * a * c * (x0 - x1) * (z0 - z1) -
			2 * Math.pow(a, 2) * z0 * z1 + Math.pow(a, 2) * Math.pow(z1, 2) -
			Math.pow(r, 2) * Math.sqrt(Math.pow(Math.abs(a), 2) + Math.pow(Math.abs(b), 2) + Math.pow(Math.abs(c), 2)));
			
		if(delta>=0) {
		
			Double gamma = Math.sqrt(delta) /
				(Math.pow(c, 2) * (Math.pow(x2, 2) + Math.pow(y2, 2)) - 2 * a * c * x2 * z2 - 2 * b * y2 * (a * x2 + c * z2) +
				Math.pow(b, 2) * (Math.pow(x2, 2) + Math.pow(z2, 2)) + Math.pow(a, 2) * (Math.pow(y2, 2) + Math.pow(z2, 2)));

			Double t = (Math.pow(c, 2) * (x0 * x2 - x1 * x2 + y0 * y2 - y1 * y2) + a * c * (-(x2 * z0) + x2 * z1 - x0 * z2 + x1 * z2) +
				Math.pow(b, 2) * (x0 * x2 - x1 * x2 + z0 * z2 - z1 * z2) + Math.pow(a, 2) * (y0 * y2 - y1 * y2 + z0 * z2 - z1 * z2) +
				b * (a * (-(x2 * y0) + x2 * y1 - x0 * y2 + x1 * y2) + c * (-(y2 * z0) + y2 * z1 - y0 * z2 + y1 * z2))) /
				(Math.pow(c, 2) * (Math.pow(x2, 2) + Math.pow(y2, 2)) - 2 * a * c * x2 * z2 - 2 * b * y2 * (a * x2 + c * z2) +
				Math.pow(b, 2) * (Math.pow(x2, 2) + Math.pow(z2, 2)) + Math.pow(a, 2) * (Math.pow(y2, 2) + Math.pow(z2, 2))) + gamma / 2;

			Double x = x1 + x2 *t;
			Double y = y1 + y2 *t;
			Double z = z1 + z2 *t;
				
			
			return new Vecteur(x,y,z);
		}
		else {
			return null;
		}
		                
	}
	
	public Vecteur normale(Vecteur p) throws Exception {
//		Vecteur res = null;
//		Vecteur OM = p.difference(this.centre).vecteurValue();
//		res = (OM).difference((this.getDirection()).multiplication(1. * this.getDirection().produitScalaire(OM))).normaliser().vecteurValue();
//		return res;
		
		Double x=p.getX();
		Double y=p.getY();
		Double z=p.getZ();
		Double x0=this.centre.getX();
		Double y0=this.centre.getY();
		Double z0=this.centre.getZ();
		Double a=this.direction.getX();
		Double b=this.direction.getY();
		Double c=this.direction.getZ();
		

		return new Vecteur(-2*b*(-(b*x) + b*x0 + a*y - a*y0) + 2*c*(c*x - c*x0 - a*z + a*z0),
   2*a*(-(b*x) + b*x0 + a*y - a*y0) - 2*c*(-(c*y) + c*y0 + b*z - b*z0),
   -2*a*(c*x - c*x0 - a*z + a*z0) + 2*b*(-(c*y) + c*y0 + b*z - b*z0));
		
		
//		return Vecteur.ne0;

	}

	@Override
	public Vecteur projection(Vecteur a) throws Exception {
		Vecteur res = null;
		res =	(a)
			.difference
				(normale(a).multiplication(this.distance(a)))
			.vecteurValue();
		return res;
	}

	@Override
	public Double distance(Vecteur a) throws Exception {
		return this.getDirection().produitVectoriel(a.difference(this.centre).vecteurValue()).norme() - this.rayon;
	}
	
	/**
	 * translate le cylindre
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
		this.setDirection(this.getDirection().rotation(Vecteur.zero, a, axe));
	}

	@Override
	public Figure fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
				if( ! type.contains("cylindre") ) {
					return super.fromJdom(element);
				}
				Cylindre res = new Cylindre();
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
					else if (role.contains("direction")) {
						res.setDirection(res.getDirection().fromJdom(fils));
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
		c.setAttribute("Type", "cylindre");
				
		c.addContent(super.getMateriau().toJdom("","Materiau"));
		c.addContent(this.getCentre().toJdom("","Position"));
		c.addContent(this.getDirection().toJdom("","Direction"));
		c.addContent(new Nombre(this.getRayon()).toJdom("","Rayon"));
		
		return c;
	}

	@Override
	public Figure clone() {
		Cylindre res = new Cylindre();
		res.centre = new Vecteur(this.centre);
		res.direction = new Vecteur(this.direction);
		res.rayon = new Double(this.rayon);
		return res;
	}

	
}
