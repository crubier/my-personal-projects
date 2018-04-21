/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Scene;

import LanceurRayon.Objets.Figures.Figure;
import LanceurRayon.Physique.Materiau;
import LanceurRayon.Physique.Rayon;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.Mathematiques.Constante;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Lecrubier
 */
public class IntersectionRayon {
	
	public static final Integer entree = 1;
	public static final Integer tangence = 0;
	public static final Integer sortie = -1;
	
	private Figure figureIntersection;
	private Vecteur pointIntersection ;
	private Vecteur normaleIntersection ;
	private Vecteur tangenteIntersection ;
	private Materiau materiauInterieur ;
	private Materiau materiauExterieur ;
	private Integer type;
	private Double longueurRayon;

	public IntersectionRayon(Figure figureIntersection, Vecteur pointIntersection, Vecteur normaleIntersection, Vecteur tangenteIntersection, Materiau materiauInterieur, Materiau materiauExterieur, Integer type, Double longueurRayon) {
		this.figureIntersection = figureIntersection;
		this.pointIntersection = pointIntersection;
		this.normaleIntersection = normaleIntersection;
		this.tangenteIntersection = tangenteIntersection;
		this.materiauInterieur = materiauInterieur;
		this.materiauExterieur = materiauExterieur;
		this.type = type;
		this.longueurRayon = longueurRayon;
	}
	
	public static IntersectionRayon calculer(Scene scene, Rayon rayon) throws Exception {
		Figure figureIn = null;
		Vecteur pointIn = null;
		Figure figureOut = null;
		Vecteur pointOut = null;
		
		
		for(Figure f : scene.getFigures()) {
			Vecteur pointInTemp = IntersectionRayon.entree(f, rayon);
			Vecteur pointOutTemp = IntersectionRayon.sortie(f, rayon);
			if(pointInTemp != null) {
				try {
					pointIn = pointInTemp;
					figureIn = f;
					rayon.setLongueur(Math.min(rayon.getLongueur(),rayon.getOrigine().distance(pointIn)));
				} catch (Exception ex) {
					Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				}
			}					
		
			if(pointOutTemp != null) {
				try {
					pointOut = pointOutTemp;
					figureOut = f;
					rayon.setLongueur(Math.min(rayon.getLongueur(),rayon.getOrigine().distance(pointOut)));
				} catch (Exception ex) {
					Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				}
			}					
		}
		
		if(!((pointIn == null || figureIn == null) && (pointOut == null || figureOut == null))) {
			if(pointIn == null || figureIn == null) {
				return new IntersectionRayon(
							figureOut,
							pointOut,
							figureOut.normale(pointOut),
							figureOut.tangente(pointOut,rayon.getDirection()),
							figureOut.materiau(pointOut),
							rayon.getMateriauTraverse(),
							IntersectionRayon.sortie,
							rayon.getOrigine().distance(pointOut)
						);
			}
			else if (pointOut == null || figureOut == null) {
				return new IntersectionRayon(
							figureIn,
							pointIn,
							figureIn.normale(pointIn),
							figureIn.tangente(pointIn,rayon.getDirection()),
							figureIn.materiau(pointIn),
							rayon.getMateriauTraverse(),
							IntersectionRayon.entree,
							rayon.getOrigine().distance(pointIn)
						);
			}
			else {
				if(rayon.getOrigine().distance(pointOut) <= rayon.getOrigine().distance(pointIn)) {
					return new IntersectionRayon(
							figureOut,
							pointOut,
							figureOut.normale(pointOut),
							figureOut.tangente(pointOut,rayon.getDirection()),
							figureOut.materiau(pointOut),
							rayon.getMateriauTraverse(),
							IntersectionRayon.sortie,
							rayon.getOrigine().distance(pointOut)
						);
				}
				else {
					return new IntersectionRayon(
							figureIn,
							pointIn,
							figureIn.normale(pointIn),
							figureIn.tangente(pointIn,rayon.getDirection()),
							figureIn.materiau(pointIn),
							rayon.getMateriauTraverse(),
							IntersectionRayon.entree,
							rayon.getOrigine().distance(pointIn)
						);
				}
			}
		}
		else {
			return null;
		}
		
		
		
	}
	
	public static Vecteur entree (Figure figure, Rayon rayon){
		try {
			Vecteur pointIntersection = figure.entree(rayon.getOrigine(), rayon.getDirection());
			if(pointIntersection != null) {
				Double distanceParcourue;
				distanceParcourue = pointIntersection.difference(rayon.getOrigine()).vecteurValue().produitScalaire(rayon.getDirection().normaliser().vecteurValue());
				if(distanceParcourue < rayon.getLongueur() && distanceParcourue > Math.sqrt(Constante.Epsilon)) {
					return pointIntersection;
				}
				else {
					return null;
				}
			}
			else {
				return null;
			}
			
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	public static Vecteur sortie (Figure figure, Rayon rayon){
		try {
			Vecteur pointIntersection = figure.sortie(rayon.getOrigine(), rayon.getDirection());
			if(pointIntersection != null) {
				Double distanceParcourue;
				distanceParcourue = pointIntersection.difference(rayon.getOrigine()).vecteurValue().produitScalaire(rayon.getDirection().normaliser().vecteurValue());
				if(distanceParcourue < rayon.getLongueur() && distanceParcourue > Math.sqrt(Constante.Epsilon)) {
					return pointIntersection;
				}
				else {
					return null;
				}
			}
			else {
				return null;
			}
			
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}

	public Figure getFigureIntersection() {
		return figureIntersection;
	}

	public Materiau getMateriauExterieur() {
		return materiauExterieur;
	}

	public Materiau getMateriauInterieur() {
		return materiauInterieur;
	}
	
	public Materiau getMateriauDirect() {
		return (getType() == IntersectionRayon.entree) ?  materiauExterieur : materiauInterieur;
	}

	public Materiau getMateriauIndirect() {
		return (getType() == IntersectionRayon.sortie) ?  materiauExterieur : materiauInterieur;
	}

	public Double getLongueurRayon() {
		return longueurRayon;
	}
	
	public Vecteur getNormaleIntersection() {
		return normaleIntersection;
	}
	public Vecteur getTangenteIntersection() {
		return tangenteIntersection;
	}

	public Vecteur getPointIntersection() {
		return pointIntersection;
	}

	public Integer getType() {
		return type;
	}
	
	
	
	
}
