/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Scene;

import LanceurRayon.Objets.Cameras.Camera;
import LanceurRayon.Objets.Cameras.CameraSimple;
import LanceurRayon.Objets.Figures.Figure;
import LanceurRayon.Objets.Figures.Sphere;
import LanceurRayon.Objets.Lumieres.Lumiere;
import LanceurRayon.Objets.Lumieres.LumiereSimple;
import LanceurRayon.Physique.Couleur;
import LanceurRayon.Physique.Rayon;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.Image;
import LanceurRayon.IHM.Arbre.ArbreXMLModel;
import LanceurRayon.Physique.Materiau;
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
public class Scene implements JDomIO{
	
	public static final Materiau fondDefaut = new Materiau();
	
	private Materiau fond ;
	
	private Liste<Camera> cameras ;
	private Liste<Lumiere> lumieres ;
	private Liste<Figure> figures ;

	public Scene() {
		this.fond = fondDefaut;
			
		this.cameras = new Liste<Camera>();
		this.cameras.add(new CameraSimple());


		this.lumieres = new Liste<Lumiere>();
		this.lumieres.add(new LumiereSimple());


		this.figures = new Liste<Figure>();
		this.figures.add(new Sphere());
	}
	
	public Scene(Materiau fond) {
		this();
		this.fond=fond;
	}

	public Scene(Materiau fond, Liste<Camera> cameras, Liste<Lumiere> lumieres, Liste<Figure> figures) {
		this.fond = fond;
		this.cameras = cameras;
		this.lumieres = lumieres;
		this.figures = figures;
	}

	public Materiau getFond() {
		return fond;
	}

	public void setFond(Materiau fond) {
		this.fond = fond;
	}

	public void ajouter(Camera e) {
		cameras.ajouter(e);
	}

	public void ajouter(Figure e) {
		figures.ajouter(e);
	}

	public void ajouter(Lumiere e) {
		lumieres.ajouter(e);
	}
	

	public Liste<Camera> getCameras() {
		return cameras;
	}

	public void setCameras(Liste<Camera> cameras) {
		this.cameras = cameras;
	}

	public Liste<Figure> getFigures() {
		return figures;
	}

	public void setFigures(Liste<Figure> figures) {
		this.figures = figures;
	}

	public Liste<Lumiere> getLumieres() {
		return lumieres;
	}

	public void setLumieres(Liste<Lumiere> lumieres) {
		this.lumieres = lumieres;
	}

	public Rayon calculerRayon(Rayon a) throws Exception {

/////////////////////////////////////////////////////////////////
// On initialise les variables
		Rayon res = new Rayon(a);
		Couleur couleurRayon = res.getCouleur();
		Liste<Materiau> materiauRayon = res.getMateriauxTraverses();
		Integer recursiviteRayon  = res.getRecursivite();
		Couleur couleurResultat = new Couleur(Couleur.noir);
		Vecteur directionRayon = res.getDirection();

		if(materiauRayon.isEmpty()) {
			throw new Exception("Pas de materiau !");
		}
/////////////////////////////////////////////////////////////////
// On calcule l'intersection du rayon avec les objets de la scene
		IntersectionRayon intersection = null;
		if( recursiviteRayon >0 ) {
			intersection = IntersectionRayon.calculer(this,a);
		}
		if(intersection != null) {
			
			res.setLongueur(intersection.getLongueurRayon());
			Figure figureIntersection = intersection.getFigureIntersection();
			Vecteur pointIntersection = intersection.getPointIntersection();
			Vecteur normaleIntersection = intersection.getNormaleIntersection();
			Vecteur tangenteIntersection = intersection.getTangenteIntersection();
			Materiau materiauIntersectionDirect = intersection.getMateriauDirect();
			Materiau materiauIntersectionIndirect = intersection.getMateriauIndirect();
			
	
		

//////////////////////////////////////////////////////////////
// On calcule la couleur du rayon reflechi
			Couleur couleurReflechi = null;
			if(Math.abs(materiauIntersectionIndirect.getReflexion().norme(1))>=LanceurRayon.Util.Mathematiques.Constante.Epsilon) {
				Double projectionNormaleReflexion = -1*directionRayon.cosAngle(normaleIntersection);
				Double projectionTangentielleReflexion = 1.*directionRayon.sinAngle(normaleIntersection);

				Vecteur directionReflexion = 
						(normaleIntersection.multiplication(projectionNormaleReflexion))
					.somme
						(tangenteIntersection.multiplication(projectionTangentielleReflexion))
					.vecteurValue();

				Liste<Materiau> matReflexion = materiauRayon;

				Rayon rayonReflechi = new Rayon(
					pointIntersection,
					directionReflexion,
					LanceurRayon.Util.Mathematiques.Constante.Infini,
					recursiviteRayon - 1,
					couleurRayon,
					matReflexion
					) ;

				rayonReflechi = this.calculerRayon(rayonReflechi);

				couleurReflechi = rayonReflechi.getCouleur().multiplication(materiauIntersectionIndirect.getReflexion());
			}
			else {
				couleurReflechi = Couleur.noir;
			}
		
//////////////////////////////////////////////////////////////
// On calcule la couleur du rayon refracté
			Couleur couleurRefracte = null;
			if(Math.abs(materiauIntersectionIndirect.getRefraction().norme(1))>=LanceurRayon.Util.Mathematiques.Constante.Epsilon) {
				Double i2 = Math.asin(-1. * directionRayon.sinAngle(normaleIntersection) * materiauIntersectionDirect.getIndiceRefraction().norme(1) / materiauIntersectionIndirect.getIndiceRefraction().norme(1));
				
				if(! i2.isNaN()) {
					Double projectionNormaleRefraction = 1.*Math.cos(i2);
					Double projectionTangentielleRefraction = -1. * Math.sin(i2);

					
					Vecteur directionRefraction = null;

					Liste<Materiau> matRefraction = new Liste<Materiau>(materiauRayon);

					if(intersection.getType()==IntersectionRayon.entree) {
						matRefraction.addElement(materiauIntersectionIndirect);
						directionRefraction = 
							(normaleIntersection.multiplication(-1.*projectionNormaleRefraction))
						.somme
							(tangenteIntersection.multiplication(1. * projectionTangentielleRefraction))
						.vecteurValue();
					}
					else if(intersection.getType()==IntersectionRayon.sortie) {
						matRefraction.removeElement(materiauIntersectionDirect);
						directionRefraction = 
							(normaleIntersection.multiplication(1.*projectionNormaleRefraction))
						.somme
							(tangenteIntersection.multiplication(1. * projectionTangentielleRefraction))
						.vecteurValue();
					}

					Rayon rayonRefracte = new Rayon(
						pointIntersection,
						directionRefraction,
						LanceurRayon.Util.Mathematiques.Constante.Infini,
						recursiviteRayon - 1,
						couleurRayon,
						matRefraction
						) ;

					rayonRefracte = this.calculerRayon(rayonRefracte);
					couleurRefracte = rayonRefracte.getCouleur().multiplication(materiauIntersectionIndirect.getRefraction());
				}
				else {
					couleurRefracte = couleurReflechi.multiplication(materiauIntersectionIndirect.getRefraction());
				}
				
//				if(intersection.getType()==IntersectionRayon.entree) {
//					couleurRefracte.sommeObjet(Couleur.noir);
//				}
//				else if(intersection.getType()==IntersectionRayon.sortie) {
//					couleurRefracte.sommeObjet(Couleur.vert);
//				}
			}
			else {
					couleurRefracte = Couleur.noir;
			}

		
//////////////////////////////////////////////////////////////
// On calcule la couleur de la surface
			Couleur couleurSurface = new Couleur(Couleur.noir);
		
			for (Lumiere l : this.lumieres) {
				
				//Initialisation des proprietes du rayon convergeant vers la lumiere l	
				Rayon rayonConv = l.rayonConvergent(pointIntersection, materiauRayon);
								
				Double indiceDiffuse = materiauIntersectionIndirect.getIndiceDiffuse().norme(1);
				
				if(IntersectionRayon.calculer(this,rayonConv) == null) {
					
					Couleur filtre = 
							(materiauRayon.lastElement().getAttenuation().exponentielle(rayonConv.getLongueur()));
					
					
					couleurSurface.sommeObjet(
								(l.getCouleur())
							.multiplication
								(filtre)
							.multiplication
								(materiauIntersectionIndirect.getDiffuse())
							.multiplication
								(Math.pow( Math.max(0., rayonConv.getDirection().cosAngle(normaleIntersection)),indiceDiffuse))

						);
					
					couleurSurface.sommeObjet(
								(l.getCouleur())
							.multiplication
								(filtre)
							.multiplication
								(materiauIntersectionIndirect.getAntiDiffuse())
							.multiplication
								(Math.pow( Math.max(0., rayonConv.getDirection().sinAngle(normaleIntersection)),1./indiceDiffuse))

						);
				}
			}
			
			//AJOUT
			couleurSurface.sommeObjet(
					(materiauRayon.lastElement().getAmbiante())
				.multiplication
					(materiauIntersectionIndirect.getDiffuse())
				);
			
			Double indiceNormale = materiauIntersectionIndirect.getIndiceNormale().norme(1);
			Double sinangle = 	Math.abs(directionRayon.sinAngle(normaleIntersection));
			Double cosangle = 	Math.abs(directionRayon.cosAngle(normaleIntersection));
			

			
			
//////////////////////////////////////////////////////////////
// On en deduit la couleur du rayon au niveau de son intersection avec la figure
			couleurReflechi.multiplicationObjet(
					(materiauIntersectionIndirect.getNormale().multiplication(Math.pow(cosangle,indiceNormale)))
				.somme
					(materiauIntersectionIndirect.getAntiNormale().multiplication(Math.pow(sinangle,1./indiceNormale))));
			
			couleurSurface.multiplicationObjet(
					(materiauIntersectionIndirect.getNormale().multiplication(Math.pow(cosangle,indiceNormale)))
				.somme
					(materiauIntersectionIndirect.getAntiNormale().multiplication(Math.pow(sinangle,1./indiceNormale))));
			
			
			couleurResultat.sommeObjet(couleurReflechi);
			couleurResultat.sommeObjet(couleurRefracte);
			couleurResultat.sommeObjet(couleurSurface);
			
		}
	
		
//////////////////////////////////////////////////////////////
// On calcule la couleur du milieu
	Couleur couleurMilieu = new Couleur(Couleur.noir);

		for (Lumiere l : this.lumieres) {

			//Initialisation des proprietes du rayon convergeant vers la lumiere l	
			Rayon rayonConv = l.rayonConvergent(res.getOrigine(), materiauRayon);
	
			Double indiceSpeculaire = materiauRayon.lastElement().getIndiceSpeculaire().norme(1);

			if(IntersectionRayon.calculer(this,rayonConv) == null) {
				Couleur filtre = 
							(materiauRayon.lastElement().getAttenuation().exponentielle(rayonConv.getLongueur()));
					
				
				couleurMilieu.sommeObjet(
							(l.getCouleur())
						.multiplication
							(filtre)
						.multiplication
							(materiauRayon.lastElement().getSpeculaire())
						.multiplication
							(Math.pow( Math.max(0.,  rayonConv.getDirection().cosAngle(directionRayon)),indiceSpeculaire))

					);


				couleurMilieu.sommeObjet(
							(l.getCouleur())
						.multiplication
							(filtre)
						.multiplication
							(materiauRayon.lastElement().getAntiSpeculaire())
						.multiplication
							(Math.pow( Math.max(0., rayonConv.getDirection().sinAngle(directionRayon)),1./indiceSpeculaire))
					);
			}
// Pour verifier les ombres : surlignage en rouge des ombres
//			else {
//				res.setCouleur(Couleur.rouge.multiplication(20.));
//				return res;
//			}
		}
		
		

		
		
		
//////////////////////////////////////////////////////////////
// On multiplie par l'attenuation pour avoir la couleur du rayon au niveau de son origine
		Couleur filtre = 
				(materiauRayon.lastElement().getAttenuation().exponentielle(res.getLongueur()));
		Couleur antiFiltre = 
					(Couleur.blanc)	.somme(	filtre.multiplication(-1.));
//		System.out.println(filtre.norme(1) + " " + antiFiltre.norme(1));
		couleurResultat.multiplicationObjet(filtre);
		//AJOUT
		couleurResultat.sommeObjet(
				(materiauRayon.lastElement().getAmbiante())
			.multiplication(antiFiltre)
			);
		
		couleurResultat.sommeObjet(couleurMilieu);
		
//////////////////////////////////////////////////////////////
// On retourne le resultat
		res.setCouleur(couleurResultat);
		return res;
	}
	
	
	public Image calculer(Integer camera) throws Exception {
		Logger.getLogger("Journal").log(Level.INFO, "Calcul Scene");
////		LanceurRayonApp.getApplication().getFenetre().setEtat("Calcul Scene");
//
//		System.out.println("il y a "  + cameras.size() + " cameras");
//		System.out.println("il y a "  + lumieres.size() + " lumieres");
//		System.out.println("il y a "  + figures.size() + " figures");
//		System.out.println("Exportation de la scène pour verification... ");
//		(new ArbreXMLModel(this.toJdom("","test"))).enregistrer("c:/test.xml");
//		System.out.println("Scène exportée !");
		Camera cam = cameras.lire(camera);
		Integer X = (Integer)cam.getDimensions().getX().longueur().intValue();
		Integer Y = (Integer)cam.getDimensions().getY().longueur().intValue();
		Integer recursivite = cam.getRecursivite();
		Image res = new Image(X,Y);
		for(Integer i = 0; i < X; i++) {
			for(Integer j = 0; j < Y; j++) {
				Rayon rayonLance = cam.rayonLance( (2.*i/X) - 1.,  (2.*j/Y) - 1.);
				rayonLance.setRecursivite(recursivite);
				rayonLance.setMateriauTraverse(this.getFond());
				rayonLance.setLongueur(LanceurRayon.Util.Mathematiques.Constante.Infini);
				rayonLance.setCouleur(new Couleur(Couleur.blanc));
				rayonLance = this.calculerRayon(rayonLance);
				res.setPixel(i, j, rayonLance.getCouleur());
			}
			LanceurRayon.LanceurRayonApp.getApplication().getFenetre().setProgression((100*i/X) );
		}
		LanceurRayon.LanceurRayonApp.getApplication().getFenetre().resetEtat();
		Logger.getLogger("Journal").log(Level.INFO, "Scene calculée");
		return res;
	}
	
	/**
	 * OK
	 * @param Nom 
	 * @param Role 
	 * @return
	 */
	public Element toJdom(String Nom, String Role) {
		Element c = new Element("Scene") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);

		c.addContent(this.cameras.toJdom("","Cameras"));
		c.addContent(this.lumieres.toJdom("","Lumieres"));
		c.addContent(this.figures.toJdom("","Figures"));
		c.addContent(this.fond.toJdom("","Fond"));
		
		return c;
	}
	
	public void importer(String URL ) throws Exception{
		ArbreXMLModel a = new ArbreXMLModel();
		a.ouvrir(URL);
	}

	@SuppressWarnings("unchecked")
	public Scene fromJdom(Element element) {	
	
		if(element == null) {
			return null;
		}
		else {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Scene"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
//				System.out.println("References : " + element.getChild("References").getChildren().size());
				
				Scene res = new Scene();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("cameras")) {
						res.setCameras(res.getCameras().fromJdom(fils));
					} 
					else if (role.contains("lumieres")) {
						res.setLumieres(res.getLumieres().fromJdom(fils));
					}
					else if (role.contains("figures")) {
						res.setFigures(res.getFigures().fromJdom(fils));
					}
					else if (role.contains("fond")) {
						res.setFond(res.getFond().fromJdom(fils));
					}
				}
				return res;
			}
			catch (Exception ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				return null;
			}
		}
	}
}
