package LanceurRayon.Objets.Figures;

import LanceurRayon.Physique.Materiau;
import LanceurRayon.Util.Mathematiques.*;
import LanceurRayon.Util.Geometrie.*;
import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Liste;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;

/**
 * Facette est une classe heritiere de Plan
 * par rapport à Plan, on se place uniquement à l'intérieur 
 * du triangle défini par les 3 plan définissant le plan
 * @author Solenne
 */
public class Facette extends Plan3Points implements JDomIO{

	private Liste<Vecteur> sommets;
	/**
	 * Contrairement au plan qui peut etre construit par 3 points non colinéaires lui appartenant
	 * une Facette est construite à partir des 3 sommets la définissant
	 * @param p1 sommet 1
	 * @param p2 sommet 2
	 * @param p3 sommet 3
	 */	
	public Facette(Vecteur p1, Vecteur p2, Vecteur p3){
		super( p1,  p2,  p3 ) ;
		this.sommets = new Liste<Vecteur>().Explicite(p1, p2, p3) ;
	}
	
	public Facette(Vecteur p1, Vecteur p2, Vecteur p3,Materiau mat){
		super( p1,  p2,  p3 ,mat) ;
		this.sommets = new Liste<Vecteur>().Explicite(p1, p2, p3) ;
	}

	public Facette() {
		super();
	}
	
	/**
	 * On redéfinit la classe intersection: le principe est le meme que Plan
	 * On rajoute une condition: l'intersection doit se situer à l'interieur du triangle définnissant la facette
	 * 
	 * @throws java.lang.Exception 
	 */
   	public Vecteur entree(Vecteur s, Vecteur d) throws Exception{
            Vecteur A,B,C ;
            A = super.getP1().difference(super.getP0()).vecteurValue();
            B = super.getP2().difference(super.getP0()).vecteurValue();
            C = s.difference(super.getP0()).vecteurValue();
            
            Matrice M ;
            M = new Matrice(A, B,  d.oppose().vecteurValue());
            
            if (M.determinant() <= Constante.Epsilon){
                return null ;
            }
            else {
                Matrice Ma ;
                Double a;
                Ma = new Matrice(C, B, d.oppose().vecteurValue());
                a = Ma.determinant() / M.determinant();
                
                Matrice Mb ;
                Double b;
                Mb = new Matrice(A, C, d.oppose().vecteurValue());
                b = Mb.determinant() / M.determinant();
                
                if ( (0 <= a) & (a <= 1) & (0 < b) &(b < (1-a)) ){
                    Matrice Mg ;
                    Mg = new Matrice(A, B, C);
                    Double g;
                    g = Mg.determinant() / M.determinant();
//                    return (Vecteur) s.somme(d.multiscalaire(g));
					return s.somme(d.multiplication(g)).vecteurValue();
                }
                else {
					return null ;
				}
            }   
		}
	
@Override
	public Figure fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
				if( ! type.contains("facette") ) {
					return super.fromJdom(element);
				}
				Facette res = new Facette();
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
		c.setAttribute("Type", "facette");
				
		c.addContent(super.getMateriau().toJdom("","Materiau"));
		c.addContent(this.getP0().toJdom("","P0"));
		c.addContent(this.getP1().toJdom("","P1"));
		c.addContent(this.getP2().toJdom("","P2"));
		
		return c;
	}
	
}
