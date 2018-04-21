package LanceurRayon.Objets.Figures;

import LanceurRayon.Physique.Materiau;
import LanceurRayon.Util.Angle;
import LanceurRayon.Util.Geometrie.*;
import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Mathematiques.*;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;

/**
 * La classe Plan permet de modeliser un plan infini,par la donnée de 3 points non colinaires
 * @author Solenne
 */
public class Plan3Points extends Figure implements JDomIO{

	private Vecteur P0 ;
	private Vecteur P1 ;
	private Vecteur P2 ;
	

    public Plan3Points(Vecteur p1, Vecteur p2, Vecteur p3 ){
		super();
		this.P0 = p1 ;
		this.P1 = p2 ;
		this.P2 = p3 ;
	}
	
	public Plan3Points(Vecteur p1, Vecteur p2, Vecteur p3,Materiau mat ){
		super(mat);
		this.P0 = p1 ;
		this.P1 = p2 ;
		this.P2 = p3 ;
	}

	public Plan3Points() {
		super();
		this.P0=new Vecteur();
		this.P1=new Vecteur();
		this.P2=new Vecteur();
	}

	
	
    public Vecteur getP0() {
        return P0;
    }

    public Vecteur getP1() {
        return P1;
    }

    public Vecteur getP2() {
        return P2;
    }

    public void setP0(Vecteur P0) {
        this.P0 = P0;
    }

    public void setP1(Vecteur P1) {
        this.P1 = P1;
    }

    public void setP2(Vecteur P2) {
        this.P2 = P2;
    }
	
	/**
	 * Clacul l'intersection du plan avec un rayon issu de du point s, dans la direction d
	 * @param s origine du rayon
	 * @param d direction du rayon
	 * @return Vecteur nul si l'intersection n'existe pas.
	 *         Le point d'intersection s'il existe.
	 */        
	public Vecteur entree(Vecteur s, Vecteur d) throws Exception{
            Vecteur A,B,C ;
            A = P1.difference(P0).vecteurValue();
            B = P2.difference(P0).vecteurValue();
            C = s.difference(P0).vecteurValue();
            
            Matrice M1 ;
            M1 = new Matrice(A, B, d.oppose().vecteurValue());
            
            if (M1.determinant() <= Constante.Epsilon){
                return null;
            }
            else {
				Matrice M2 ;
				M2 = new Matrice(A, B, C);
				Double g;
				g = M2.determinant() / M1.determinant();
//				System.out.println(d.multiplication(g));
	//            return (Vecteur) s.somme(d.multiscalaire(g)); 
				return s.somme(d.multiplication(g)).vecteurValue();
            }
            
	}
	
	public Vecteur sortie(Vecteur s, Vecteur d) throws Exception{
            Vecteur A,B,C ;
            A = P2.difference(P0).vecteurValue();
            B = P1.difference(P0).vecteurValue();
            C = s.difference(P0).vecteurValue();
            
            Matrice M1 ;
            M1 = new Matrice(A, B, d.oppose().vecteurValue());
            
            if (M1.determinant() <= Constante.Epsilon){
                return null;
            }
            else {
				Matrice M2 ;
				M2 = new Matrice(A, B, C);
				Double g;
				g = M2.determinant() / M1.determinant();
//				System.out.println(d.multiplication(g));
	//            return (Vecteur) s.somme(d.multiscalaire(g)); 
				return s.somme(d.multiplication(g)).vecteurValue();
            }
            
	}
	
/**
 * Normal au plan 
 * @param p 
 * @return le vecteur normal au plan, non normé
 * @throws java.lang.Exception 
 */	
	public Vecteur normale(Vecteur p) throws Exception {
		Vecteur A, B ;
        A = P1.difference(P0).vecteurValue();
        B = P2.difference(P0).vecteurValue();
        return A.produitVectoriel(B).normaliser().vecteurValue();
	}
	
	/**
	 * 
	 * @param a le point a projeter
	 * @return la projection de a sur le plan
	 * @throws java.lang.Exception
	 */
	@Override
	public Vecteur projection(Vecteur a) throws Exception {
		Vecteur res = null;
		res =	a
			.difference
				(normale(a).multiplication(this.distance(a)))
			.vecteurValue();
		return res;
	}

	/**
	 * 
	 * @param a le point ddont on doi calculer la distance au plan
	 * @return la distance au plan, positive si on est du coté de la normale, negative sinon
	 * @throws java.lang.Exception
	 */
	@Override
	public Double distance(Vecteur a) throws Exception {
		return a.difference(P0).vecteurValue().produitScalaire(normale(P0).vecteurValue());
	}
	
	/**
	 * translate le plan p
	 * @param d vecteur de translation
	 */	
	public void translation(Vecteur d)  {
        try {
            this.P0 =  this.P0.somme(d).vecteurValue();
            this.P1 =  this.P1.somme(d).vecteurValue();
            this.P2 =  this.P2.somme(d).vecteurValue();
        } catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
        }
	}
	
	/**
	 * rotation dans l'espace
	 * @param origine vecteur autour duquel on tourne
	 * @param a angle de rotation
	 * @param axe 
	 */
	public void rotation(Vecteur origine, Angle a, Vecteur axe) {
		this.P0=this.P0.rotation(origine, a, axe);
		this.P1=this.P1.rotation(origine, a, axe);
		this.P2=this.P2.rotation(origine, a, axe);
	}

	@Override
	public Figure fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
				if( ! type.contains("plan3Points") ) {
					return super.fromJdom(element);
				}
				Plan3Points res = new Plan3Points();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("materiau")) {
						res.setMateriau(res.getMateriau().fromJdom(fils));
					} 
					else if (role.contains("p0")) {
						res.setP0(res.getP0().fromJdom(fils));
					}
					else if (role.contains("p1")) {
						res.setP1(res.getP1().fromJdom(fils));
					}
					else if (role.contains("p2")) {
						res.setP2(res.getP2().fromJdom(fils));
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
		c.setAttribute("Type", "plan3Points");
				
		c.addContent(super.getMateriau().toJdom("","Materiau"));
		c.addContent(this.getP0().toJdom("","P0"));
		c.addContent(this.getP1().toJdom("","P1"));
		c.addContent(this.getP2().toJdom("","P2"));
		
		return c;
	}
	
	@Override
	public Figure clone() {
		Plan3Points res = new Plan3Points();
		res.P0 = new Vecteur(this.P0);
		res.P1 = new Vecteur(this.P1);
		res.P2 = new Vecteur(this.P2);
		return res;
	}

	
}
