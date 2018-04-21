package LanceurRayon.Objets.Cameras;

import LanceurRayon.Objets.*;
import LanceurRayon.Physique.Rayon;
import LanceurRayon.Util.Angle;
import LanceurRayon.Util.AngleSolide;
import LanceurRayon.Util.Geometrie.Matrice;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Nombre;
import LanceurRayon.Util.Rectangle;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;



public class CameraSimple extends Camera implements JDomIO{

	private Vecteur position ;
	private Matrice direction ;
	private AngleSolide angles ;

	public CameraSimple(Rectangle<Integer> dimensions, Integer recursivite, Vecteur position, Matrice direction, AngleSolide angles) {
		super(dimensions, recursivite);
		this.position = position;
		this.direction = direction;
		this.angles = angles;
	}

	public CameraSimple(Vecteur position, Matrice direction, AngleSolide angles) {
		this.position = position;
		this.direction = direction;
		this.angles = angles;
	}
	
	public CameraSimple() {
		super();
		this.position =  Vecteur.zero;
		this.direction = Matrice.identite ;
		this.angles= AngleSolide.zero;
	}
	
	public AngleSolide getAngles() {
		return angles;
	}

	public void setAngles(AngleSolide angles) {
		this.angles = angles;
	}

	public Matrice getDirection() {
		return direction;
	}

	public void setDirection(Matrice direction) {
		this.direction = direction;
	}

	public Vecteur getPosition() {
		return position;
	}

	public void setPosition(Vecteur position) {
		this.position = position;
	}

	public void translation(Vecteur direction) {
		try {
			this.position = (Vecteur) this.position.somme(direction);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}

	public void rotation(Vecteur origine, Angle a, Vecteur axe) {
		this.position = this.position.rotation(origine, a, axe);
		this.direction = this.direction.rotation(a, axe);
	}

	@Override
	public Rayon rayonLance(Double x, Double y) {
		try {
			Vecteur dir = new Vecteur(Vecteur.e0);
			
			dir = dir.rotation(Vecteur.zero, this.angles.getY().multiplication(1.*y), Vecteur.e1);
			dir = dir.rotation(Vecteur.zero, this.angles.getX().multiplication(-1.*x), Vecteur.e2);
			
			dir = direction.produitcontracte(dir,1).vecteurValue();
			
			return new Rayon(this.position, dir);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	public Element toJdom(String Nom, String Role) {
		Element c = new Element("Camera") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		c.setAttribute("Type", "ponctuelle");
		
		c.addContent(this.position.toJdom("","Position"));
		c.addContent(this.direction.toJdom("","Direction"));
		c.addContent(this.angles.toJdom("","Angles"));
		c.addContent(this.getDimensions().toJdom("","Dimensions"));
		c.addContent(new Nombre(this.getRecursivite()).toJdom("","Recursivite"));
		
		return c;
	}

	@Override
	public CameraSimple fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				
				CameraSimple res = new CameraSimple();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("position")) {
						res.setPosition(res.getPosition().fromJdom(fils));
					} 
					else if (role.contains("direction")) {
						res.setDirection(res.getDirection().fromJdom(fils));
					}
					else if (role.contains("angles")) {
						res.setAngles(res.getAngles().fromJdom(fils));
					}
					else if (role.contains("dimensions")) {
						res.setDimensions(res.getDimensions().fromJdom(fils));
					}
					else if (role.contains("recursivite")) {
						res.setRecursivite(new Integer(fils.getText()));
					}
				}
				return res;

			} catch (Exception ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				return null;
			}
		}
	}

	
	

}
