package LanceurRayon.Util;

import LanceurRayon.IHM.AffichageImage;
import LanceurRayon.Physique.Couleur;
import LanceurRayon.Util.Mathematiques.Intervalle;
import com.sun.imageio.plugins.png.*;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;


public class Image implements JDomIO{

	private Liste<Couleur> Tableau;
	
	private Rectangle<Integer> Dimensions;
	
	public static final Couleur defaut = Couleur.blanc;
		
	
	public Image(Intervalle<Integer> X, Intervalle<Integer> Y,Couleur fond) {
		this.Dimensions = new Rectangle<Integer>(X,Y);
		
		this.Tableau = new Liste<Couleur>((this.Dimensions.getX().longueur().intValue()+1) * (this.Dimensions.getY().longueur().intValue()+1),fond);
		
	}
	
	public Image(Intervalle<Integer> X, Intervalle<Integer> Y) {
		this(X,Y, defaut);
	}
	
	public Image(Integer X, Integer Y) {
		this(new Intervalle<Integer>(0, X),new Intervalle<Integer>(0, Y), defaut);
	}
	
	public Image(Integer X, Integer Y,Couleur fond) {
		this(new Intervalle<Integer>(0, X),new Intervalle<Integer>(0, Y), fond);
	}

	private Image() {
		this.Dimensions = new Rectangle<Integer>();
		this.Dimensions.setX(new Intervalle<Integer>(0,0));
		this.Dimensions.setY(new Intervalle<Integer>(0,0));
		this.Tableau = new Liste<Couleur>((this.Dimensions.getX().longueur().intValue()+1) * (this.Dimensions.getY().longueur().intValue()+1),defaut);
		
		
	}

	private Image(Image a) {
		this.Dimensions = new Rectangle<Integer>(a.Dimensions);
		this.Tableau = new Liste<Couleur>(a.Tableau);
	}

	public Liste<Couleur> getTableau() {
		return Tableau;
	}

	public void setTableau(Liste<Couleur> Tableau) {
		this.Tableau = Tableau;
	}

	public Rectangle<Integer> getDimensions() {
		return Dimensions;
	}

	public void setDimensions(Rectangle<Integer> Dimensions) {
		this.Dimensions = Dimensions;
	}
	
	public void setPixel(Integer X, Integer Y, Couleur val) {
		this.Tableau.set(X+Y*this.Dimensions.getX().longueur().intValue(), val);
	}
	
	public Couleur getPixel(Integer X, Integer Y) {
		return this.Tableau.get(X+Y*this.Dimensions.getX().longueur().intValue());
	}
	
	public void multiplicationPixel(Integer X, Integer Y, Couleur val) {
		this.Tableau.get(X+Y*this.Dimensions.getX().longueur().intValue()).multiplicationObjet(val);
	}
	
	public void multiplicationPixel(Integer X, Integer Y, Double val) {
		this.Tableau.get(X+Y*this.Dimensions.getX().longueur().intValue()).multiplicationObjet(val);
	}
	
	public Image multiplication(Double other) {
		Image res = new Image(this);
		Integer x0 = this.Dimensions.getX().getBorneInf();
		Integer x1 = this.Dimensions.getX().getBorneSup();
		Integer y0 = this.Dimensions.getY().getBorneInf();
		Integer y1 = this.Dimensions.getY().getBorneSup();
		for(Integer j = y0; j < y1; j++) {
			for(Integer i = x0; i < x1; i++) {
				res.multiplicationPixel(i,j,other);
			}
		}
		return res;
	}
	
	public void multiplicationObjet(Double other) {
		Integer x0 = this.Dimensions.getX().getBorneInf();
		Integer x1 = this.Dimensions.getX().getBorneSup();
		Integer y0 = this.Dimensions.getY().getBorneInf();
		Integer y1 = this.Dimensions.getY().getBorneSup();
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setEtat("Multiplication Image");
		for(Integer j = y0; j < y1; j++) {
			for(Integer i = x0; i < x1; i++) {
				this.multiplicationPixel(i,j,other);
			}
			LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setProgression((j-y0)/(y1-y0));
		}
	}
	
	public void dessinerRectangle(Integer X0, Integer Y0, Integer X1, Integer Y1, Couleur col) {
		for(Integer x=X0;x<=X1;x++) {
			for(Integer y=Y0;y<=Y1;y++) {
				this.setPixel(x, y, col);
			}
		}
	}
	
	public BufferedImage toAwtImage(Double gain) {
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setEtat("Conversion Image");
		Integer x = (this.Dimensions.getX().getBorneSup()-this.Dimensions.getX().getBorneInf());
		Integer y = (this.Dimensions.getY().getBorneSup()-this.Dimensions.getY().getBorneInf());
		BufferedImage res = new BufferedImage(x,y,BufferedImage.TYPE_3BYTE_BGR	);

		for(Integer j = 0; j < y; j++) {
			for(Integer i = 0; i < x; i++) {
//				if( !this.getPixel(i, j).equals(Couleur.noir) ) {
//					System.out.println(i+","+j);
//					System.out.println("couleur " + this.getPixel(i, j));
//					System.out.println("couleur " + this.getPixel(i, j).toRGB(gain));
//				}
				res.setRGB(i, j, this.getPixel(i, j).toRGB(gain).getRGB());
			}
			LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setProgression(j/y);
		}
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().resetEtat();
		return res;
				
	}
	
	public BufferedImage toAwtImage(Double gain, Double echelle) {
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setEtat("Conversion Image");
		BufferedImage bi = toAwtImage(gain);
        AffineTransform tx = new AffineTransform();
        tx.scale(echelle, echelle);
        AffineTransformOp op = new AffineTransformOp(tx,
                AffineTransformOp.TYPE_BILINEAR);
        BufferedImage biNew = new BufferedImage( (int) (bi.getWidth() * echelle),
                (int) (bi.getHeight() * echelle),
                bi.getType());
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().resetEtat();
        return op.filter(bi, biNew);
                
} 

	
	public void exporter(String URL,Double gain) throws IOException {
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setEtat("Exportation Image");
		BufferedImage res = this.toAwtImage(gain);
		File fichierSortie = new File(URL);
		fichierSortie.createNewFile();
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setEtat("Exportation Image");
		ImageIO.write(res, "png", fichierSortie);
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().resetEtat();
	}
	
	public void exporter(String URL ) throws IOException {
		exporter(URL, this.normeMax(1));

	}
	
	public void afficher(Double gain) {
		new AffichageImage("Image gain : "+gain+"",this.toAwtImage(gain));
	}
	
	public void afficher() {
		new AffichageImage("Image ",this.toAwtImage(this.normeMax(1)));
	}
	
	public void afficher(Double gain,Double echelle) {
		new AffichageImage("Image gain : "+gain+" "+"echelle : "+echelle+"",this.toAwtImage(gain,echelle));
	}
	
	public void afficher(Double gain,Double echelle, String nom) {
		new AffichageImage(nom+" gain : "+gain+" "+"echelle : "+echelle+"",this.toAwtImage(gain,echelle));
	}
	
	public Double normeMax(Integer n) {
		Double res = 0.;
		for(Couleur c : this.Tableau) {
			if( c.norme(n) > res) {
				res = c.norme(n);
			}
		}
		return res;
	}
	
	public Image normaliserMax( ) {
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setEtat("Normalisation Image");
		Image res = new Image(this);
		res.multiplicationObjet(1./res.normeMax(1));
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().resetEtat();
		return res;
	}
	
	public Image fromJdom(Element element) {
		
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Image"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				Image res = new Image();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("valeurs")) {
						res.setTableau(res.getTableau().fromJdom(fils));
					}
					else if (role .contains("dimensions")) {
						res.setDimensions(res.getDimensions().fromJdom(fils));
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
		Element c = new Element("Scene") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		c.addContent(this.Tableau.toJdom("","Valeurs"));
		c.addContent(this.Dimensions.toJdom("","Dimensions"));
		return c;
	}
	
}
