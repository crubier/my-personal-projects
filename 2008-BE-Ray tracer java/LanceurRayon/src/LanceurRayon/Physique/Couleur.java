/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Physique;

import LanceurRayon.Util.*;
import LanceurRayon.Util.Mathematiques.*;

/*
import java.awt.Paint;
import java.awt.PaintContext;
import java.awt.Rectangle;
import java.awt.Transparency;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.geom.Rectangle2D;
import java.awt.image.ColorModel; 
 */
import afficheur.Ecran;
import java.awt.Color;
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
public class Couleur implements Comparable, JDomIO/*, Paint*/{
	
    private Liste<Double> spectre;
    private Double alpha;
	
    public static Integer PRECISION = 12; //La precision du spectre de toutes les couleurs est identique
	public static Double SATURATION = 1.; // sinon on peut mettre LanceurRayon.Util.Math.Constante.Infini pour une raie
	public static Intervalle<Double> INTERVALLE_SPECTRAL = new Intervalle<Double>(400.,800.); //L'intervalle contenant le spectre de toutes les couleurs, ici le spectre visible
	
	/**
	 * Couleurs de base definies  en TSL
	 */
	public final static Couleur blanc =		new Couleur().CouleurTSL(0., 0., 1.).normaliserInf();
	public final static Couleur noir =		new Couleur().CouleurTSL(0., 0., 0.);
	
	public final static Couleur rouge =		new Couleur().CouleurTSL(001., Couleur.SATURATION, 1.);
	public final static Couleur jaune =		new Couleur().CouleurTSL(060., Couleur.SATURATION, 1.);
	public final static Couleur vert =		new Couleur().CouleurTSL(121., Couleur.SATURATION, 1.);
	public final static Couleur cyan =		new Couleur().CouleurTSL(180., Couleur.SATURATION, 1.);
	public final static Couleur bleu =		new Couleur().CouleurTSL(241., Couleur.SATURATION, 1.);
	public final static Couleur magenta =	new Couleur().CouleurTSL(300., Couleur.SATURATION, 1.);

    public Couleur() {
	    this.spectre = new Liste<Double>(PRECISION, 0.);
	    this.alpha = 0.;
    }

    public Couleur(Liste<Double> spectre, Double alpha) throws Exception {
		this.spectre = spectre;
	    this.alpha = alpha;
		if(this.spectre.size()!=PRECISION) {
		    throw new Exception("Couleur incompatible");
	    }
    }
	
	public Couleur(Couleur a) throws Exception {
		
	    this.spectre = new Liste<Double>(a.spectre);
		
	    this.alpha = a.alpha;
		if(this.spectre.size()!=PRECISION) {
		    throw new Exception("Couleur incompatible");
	    }
    }
	
	/**
	 * 
	 * @param lambda longueur d'onde en nm
	 * @param delta largeur de bande en nm
	 * @param k hauteur de la raie
	 * @return
	 * @throws java.lang.Exception 
	 */
    public Couleur CouleurGauss(Double lambda, Double delta, Double k) throws Exception {
	    Couleur res = new Couleur();
		if(delta<0) {
			throw new Exception("Couleur Gaussienne invalide : Lambda = " + lambda + "nm Delta = " + delta + "nm k = " + k + " delta doit etre positif" );
		}
		if(lambda<0) {
			throw new Exception("Couleur Gaussienne invalide : Lambda = " + lambda + "nm Delta = " + delta + "nm k = " + k + " lambda doit etre positif" );
		}
		Double LargeurFenetre = delta/(Couleur.INTERVALLE_SPECTRAL.longueur().doubleValue());
		Double HauteurFenetre = k*Couleur.PRECISION;
		Double CentreFenetre = (Couleur.INTERVALLE_SPECTRAL.getBorneSup().doubleValue() -lambda )/(Couleur.INTERVALLE_SPECTRAL.longueur().doubleValue());
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			Double theta0= (double) i / Couleur.PRECISION;
			Double theta1= (double) (i+1) / Couleur.PRECISION;
			res.spectre.regler(i, 
				HauteurFenetre*Distribution.gauss(theta0, theta1, CentreFenetre, LargeurFenetre) 
			);
		}
	    return res;
    }

	/**
	 * Couleur definie en TSL
	 * @param T Teinte entre 0 et 360°
	 * @param S Saturation > 0
	 * @param L Luminosité > 0 dans le monde physique, notez que ce n'est pas obligatoire ici
	 * @return La couleur associé, calculée avec un spectre en forme de fenetre
	 */
    public Couleur CouleurTSL(Double T, Double S, Double L) {
		Couleur res = new Couleur();
		/*if(S<0) {
			throw new Exception("Couleur TSL invalide : T = " + T + "° S = " + S + " L = " + L + " S doit etre positif !");
		}*/
		Double LargeurFenetre = 1/(2*(2*S+1));
		Double HauteurFenetre = L*Couleur.PRECISION;
		Double CentreFenetre = (T%360)/360;
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			Double theta0= (double) i / Couleur.PRECISION;
			Double theta1= (double) (i+1) / Couleur.PRECISION;
			res.spectre.regler(i, 
				HauteurFenetre*Distribution.fenetre(theta0, theta1, CentreFenetre, LargeurFenetre) +
				HauteurFenetre*Distribution.fenetre(theta0, theta1, CentreFenetre + 1., LargeurFenetre) +
				HauteurFenetre*Distribution.fenetre(theta0, theta1, CentreFenetre - 1., LargeurFenetre)  // les Deux distributions supll sont dues au fait que la teinte est cirulaire et non pas lineaire comme les longueurs d'onde. L'ultraviolet est relié a l'infrarouge.
			);
		}
	
		return res;
    }

	/**
	 * 
	 * Couleur definie en RVB
	 * @param R > 0 dans le monde physique, notez que ce n'est pas obligatoire ici
	 * @param V > 0 dans le monde physique, notez que ce n'est pas obligatoire ici
	 * @param B > 0 dans le monde physique, notez que ce n'est pas obligatoire ici
	 * @return la couleur au spectre associé
	 */
    public Couleur CouleurRVB(Double R, Double V, Double B) {
		Couleur res = new Couleur();

		Double LargeurFenetre = 1./6.;
		Double CentreFenetreR = 0./6.;
		Double CentreFenetreV = 2./6.;
		Double CentreFenetreB = 4./6.;
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			Double theta0= (double) i / Couleur.PRECISION;
			Double theta1= (double) (i+1) / Couleur.PRECISION;
			res.spectre.regler(i, 
				Couleur.PRECISION*(
				R * Distribution.fenetre(theta0, theta1, CentreFenetreR , LargeurFenetre) +
				R * Distribution.fenetre(theta0, theta1, CentreFenetreR +1. , LargeurFenetre) +
				V * Distribution.fenetre(theta0, theta1, CentreFenetreV , LargeurFenetre) +
				B * Distribution.fenetre(theta0, theta1, CentreFenetreB , LargeurFenetre)
				)
			);
		}
	
		return res;
    }
	
	public Couleur CouleurJMC(Double J, Double M, Double C) {
		Couleur res = new Couleur();

		Double LargeurFenetre = 1./6.;
		Double CentreFenetreJ = 1./6.;
		Double CentreFenetreM = 3./6.;
		Double CentreFenetreC = 5./6.;
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			Double theta0= (double) i / Couleur.PRECISION;
			Double theta1= (double) (i+1) / Couleur.PRECISION;
			res.spectre.regler(i, 
				Couleur.PRECISION*(
				J * Distribution.fenetre(theta0, theta1, CentreFenetreJ , LargeurFenetre) +
				M * Distribution.fenetre(theta0, theta1, CentreFenetreM , LargeurFenetre) +
				C * Distribution.fenetre(theta0, theta1, CentreFenetreC , LargeurFenetre)
				)
			);
		}
	
		return res;
    }
	
	public Couleur somme(Couleur other) throws Exception {
		Couleur res = new Couleur(this);
		res.sommeObjet(other);
		return res;
	}
	
	public void sommeObjet(Couleur other) {
		if(other != null) {
			for(Integer i = 0; i<Couleur.PRECISION; i++) {
				this.spectre.regler( i, this.spectre.lire(i) + other.spectre.lire(i));
			}
		}
	}
	
	public Couleur exponentielle(Double other) throws Exception {
		Couleur res = new Couleur(this);
		res.exponentielleObjet(other);
		return res;
	}
	
	public void exponentielleObjet(Double other) {
		if(other != null) {
			for(Integer i = 0; i<Couleur.PRECISION; i++) {
				this.spectre.regler( i, Math.pow(this.spectre.lire(i),other));
			}
		}
	}
	
	public Couleur multiplication(Couleur other) throws Exception {
		Couleur res = new Couleur(this);
		res.multiplicationObjet(other);
		return res;
	}
	
	public void multiplicationObjet(Couleur other) {
		if(other != null) {
			for(Integer i = 0; i<Couleur.PRECISION; i++) {
				this.spectre.regler( i, this.spectre.lire(i) * other.spectre.lire(i));
			}
		}
	}
	
	public Couleur multiplication(Double other) throws Exception {
		Couleur res = new Couleur(this);
		res.multiplicationObjet(other);
		return res;
	}
	
	public void multiplicationObjet(Double other) {
		if(other != null) {
			for(Integer i = 0; i<Couleur.PRECISION; i++) {
				this.spectre.regler( i, this.spectre.lire(i) * other);
			}
		}
	}
	
	
	
	public Couleur puissance(Integer n) {
		Couleur res = new Couleur();
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			res.spectre.regler( i, Math.pow(this.spectre.lire(i),n));
		}
		return res;
	}
	
	public Couleur DSP() {
		return this.puissance(2);
	}
	
	public Double puissanceTotale() {
		return this.norme(2); 
	}
	
	public Double normeInf() {
		if (this !=null){
			Double M=0.;
			for(Integer j = 0; j<Couleur.PRECISION; j++) {
				M=Math.max(M, this.spectre.lire(j));
			}
			return M;
		}
		else {
			return 0.;
		}
	}
	
	public Double norme(Integer n) {
		if (this !=null){
			Double res = 0.0;
			for(Integer i = 0; i<Couleur.PRECISION; i++) {
				res += Math.pow(this.spectre.lire(i)/Couleur.PRECISION,n);
			}
			return res;
		}
		else {
			return 0.;
		}
	}
	
	public Double moyenne() {
		Double res = 0.;
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			res =  res + this.spectre.lire(i) * i ;
		}
		res = res / (this.norme(1) * Couleur.PRECISION.doubleValue()*Couleur.PRECISION.doubleValue());
		return res;
	}
	
	public Double moyenneCirculaire() {
		Double res = 0.;
		Double x = 0.;
		Double y = 0.;
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			Double angle = 2 * Math.PI * i.doubleValue() /Couleur.PRECISION.doubleValue() - Math.PI;
			x = x + this.spectre.lire(i) * Math.cos(angle.doubleValue());
			y = y + this.spectre.lire(i) * Math.sin(angle.doubleValue());
		}
		res = 0.5*(Math.atan2(y, x) / Math.PI) + 0.5;
		return res;
	}
	
	public Double varianceCirculaire() {
		Double moy = this.moyenneCirculaire().doubleValue();
		Double res = 0.;
		Double k = 1. / Couleur.PRECISION.doubleValue();
		Double j = 0.;
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			j = i * k;
			res = res + this.spectre.lire(i) * Math.pow(Math.IEEEremainder((j -  moy),1.),2);
		}
		res = res/ this.norme(1);
		return res;
	}
	
	public Double variance() {
		Double moy = this.moyenne().doubleValue();
		Double res = 0.;
		Double k = 1. / Couleur.PRECISION.doubleValue();
		Double j = 0.;
		for(Integer i = 0; i<Couleur.PRECISION; i++) {
			j = i * k;
			res = res + this.spectre.lire(i) * Math.pow((j -  moy),2);
		}
		res = res/ this.norme(1);
		return res;
	}
	
	public Couleur normaliserInf() {
		try {
			Couleur res = new Couleur(this);
			Double M = this.normeInf();
			for(Integer j = 0; j<Couleur.PRECISION; j++) {
				res.spectre.regler(j, this.spectre.lire(j) / M);
			}
			return res;
					
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
		
	}
	
	public Couleur normaliser(Integer n) {
		try {
			Couleur res = new Couleur(this);
			Double M = this.norme(n);
			Double k = Math.pow(1./M,1./n);
			for(Integer j = 0; j<Couleur.PRECISION; j++) {
				res.spectre.regler(j, this.spectre.lire(j)* k);
			}
			return res;
					
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
		
	}
	
	public void afficherSpectre(Ecran a, Double echelle) throws Exception {

		Couleur col = this.multiplication(echelle);
//		Color couleurdessin = this.toRGB(1./this.normeInf());
		Color couleurdessin = this.toRGB( 1000.);
		for(Integer j = 0; j<Couleur.PRECISION-1; j++) {
			Double i=j.doubleValue();
			a.dessinerLigne(
				2*i/Couleur.PRECISION -0.5	,
				1.5 * col.spectre.lire(j) -0.5	,
				2*(i+1.)/Couleur.PRECISION -0.5,
				1.5 * col.spectre.lire(j+1 )	-0.5, 
				couleurdessin
				);
		}
		a.rafraichir();
	}
	
	public void afficherSpectre(Ecran a) throws Exception {
		afficherSpectre(a, 1./this.normeInf());
	}
	
	public void afficherSpectre() throws Exception {
		Ecran a = new Ecran("Couleurs - Echelle : "+this.normeInf(), 800,600,400);
		afficherSpectre(a);
	}
	
    @Override
    public boolean equals(Object obj) {
	    if (obj == null) {
		    return false;
	    }
	    if (getClass() != obj.getClass()) {
		    return false;
	    }
	    final Couleur other = (Couleur) obj;
	    if (this.spectre != other.spectre && (this.spectre == null || !this.spectre.equals(other.spectre))) {
		    return false;
	    }
	    if (this.alpha != other.alpha && (this.alpha == null || !this.alpha.equals(other.alpha))) {
		    return false;
	    }
	    
	    return true;
    }

    @Override
    public int hashCode() {
	    int hash = 3;
	    hash = 89 * hash + (this.spectre != null ? this.spectre.hashCode() : 0);
	    hash = 89 * hash + (this.alpha != null ? this.alpha.hashCode() : 0);
	    hash = 89 * hash + (Couleur.PRECISION != null ? Couleur.PRECISION.hashCode() : 0);
	    return hash;
    }


    /**
	 * The paint context used to generate a solid color pattern.
	 * @see createContext()
	 */
	//transient private PaintContext theContext;

	/**
	 * Creates and returns a {@link PaintContext} used to generate a solid
	 * color pattern.  This enables a <code>Color</code> object to be used
	 * as an argument to any method requiring an object implementing the
	 * {@link Paint} interface.
	 * The same <code>PaintContext</code> is returned, regardless of
	 * whether or not <code>r</code>, <code>r2d</code>,
	 * <code>xform</code>, or <code>hints</code> are <code>null</code>.
	 * @param cm the specified <code>ColorModel</code>
	 * @param r the specified {@link Rectangle}
	 * @param r2d the specified {@link Rectangle2D}
	 * @param xform the specified {@link AffineTransform}
	 * @param hints the specified {@link RenderingHints}
	 * @return a <code>PaintContext</code> that is used to generate a
	 *		solid color pattern.
	 * @see Paint
	 * @see PaintContext
	 * @see Graphics2D#setPaint
	 */
	/*public synchronized PaintContext createContext(ColorModel cm, Rectangle r,
		Rectangle2D r2d,
		AffineTransform xform,
		RenderingHints hints) {
		PaintContext pc = theContext;
		if (pc == null) {
			pc = new ColorPaintContext(getValeurInt(), cm);
			theContext = pc;
		}
		return pc;
	}*/

	/**
	 * Returns the transparency mode for this <code>Color</code>.  This is
	 * required to implement the <code>Paint</code> interface.
	 * @return this <code>Color</code> object's transparency mode.
	 * @see Paint
	 * @see Transparency
	 * @see #createContext
	 */
/*	public int getTransparency() {
		Double a = getAlpha();
		if (a == 0.) {
			return Transparency.BITMASK;
		} else {
			return Transparency.TRANSLUCENT;
		}
	}*/

    	
    public int getValeurInt() {
		throw new UnsupportedOperationException("Not yet implemented");
    }

	public Liste<Double> getSpectre() {
		return spectre;
	}

	public void setSpectre(Liste<Double> spectre) {
		this.spectre = spectre;
	}

	public Double getAlpha() {
		return alpha;
	}

	public void setAlpha(Double alpha) {
		this.alpha = alpha;
	}
	
	
	
	

	@Override
	public String toString() {
		return ("<Couleur>\n" + this.spectre.toString()+"</Couleur>\n");
	}

	/**
	 * 
	 * @param gain
	 * @return la valeurRGB de la couleur
	 */
	public Color toRGB(Double gain) {
//////////////Methode 1//////////////////////////////
//		Double R = this.multiplication(Couleur.rouge).puissanceTotale();
//		Double G = this.multiplication(Couleur.vert).puissanceTotale();
//		Double B = this.multiplication(Couleur.bleu).puissanceTotale();
//
//		Double N = Math.max(R,Math.max(G,B));
//		
//		R = (255*R/N);
//		G = (255*G/N);
//		B = (255*B/N);
//
//		return new Color( R.intValue(), G.intValue(), B.intValue());
/////////////////////////////////////////////////////////
		
//////////////Methode 2//////////////////////////////
//		Color res = 
//			new Color(Color.HSBtoRGB(
//				this.moyenne().floatValue(),
//				((Double)(		(Couleur.blanc.variance() - this.variance() )/Couleur.blanc.variance()	)).floatValue(),
//				((Double)(		Math.max(0.,1. - Math.exp(-1.*gain*this.norme(1)))		)).floatValue()
//			));
//
//		return res;
/////////////////////////////////////////////////////
		
		
///////////Methode 2//////////////////////////////
		Color res = 
			new Color(Color.HSBtoRGB(
				this.moyenneCirculaire().floatValue(),
				((Double)(		(Couleur.blanc.varianceCirculaire() - this.varianceCirculaire() )/Couleur.blanc.varianceCirculaire()	)).floatValue(),
				((Double)(		Math.max(0.,1. - Math.exp(-1.*gain*this.norme(1)))		)).floatValue()
			));

		return res;
/////////////////////////////////////////////////////
		
	}
	
	public static Couleur fromRGB(Color a) {
		try {
			Couleur res = new Couleur();
			res.sommeObjet(Couleur.rouge.multiplication(a.getRed() / 255.));
			res.sommeObjet(Couleur.vert.multiplication(a.getGreen() / 255.));
			res.sommeObjet(Couleur.bleu.multiplication(a.getBlue() / 255.));

			return res;
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}

	public int compareTo(Object o) {
		if(o instanceof Couleur) {
			Couleur other = (Couleur)o;
			if(Math.abs(this.norme(1)-other.norme(1))<LanceurRayon.Util.Mathematiques.Constante.Epsilon) {
				return 0;
			}
			else {
				if(this.norme(1)-other.norme(1)>0) {
					return 1;
				}
				else {
					return -1;
				}
				
			}
		}
		else {
			return -1;
		}
	}


	@SuppressWarnings("unchecked")
	public Couleur fromJdom(Element element) {
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
//				System.out.println(element.getName()+ " > " + element.getAttributeValue("Role","Inconnu")+" > " + element.getAttributeValue("Reference","Inconnu"));

				if(ref.compareTo("Inconnu")!=0) {
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Couleur"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
//							System.out.println("Reference trouvée : " + ref);
							Logger.getLogger("Journal").log(Level.INFO, "Reference trouvée : " + ref);
							return this.fromJdom(actuel);
						}
					}
//					System.out.println("Reference introuvable : " + ref);
					Logger.getLogger("Journal").log(Level.SEVERE, "Reference introuvable : " + ref);
				}
				
				Couleur res = new Couleur();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("spectre")) {
						res.setSpectre(res.getSpectre().fromJdom(fils));
					}
					else if (role.contains("alpha")) {
						res.setAlpha(new Double(fils.getText()));
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
		Element c = new Element("Couleur") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		c.setAttribute("Precision", Couleur.PRECISION.toString());
		c.addContent(this.spectre.toJdom("","Spectre"));
		c.addContent(new Nombre(alpha).toJdom("","Alpha"));
		return c;
	}

}
