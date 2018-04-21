/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Physique;

import LanceurRayon.Objets.Figures.*;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.Liste;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Lecrubier
 */
public class Rayon {
	private Vecteur origine;
	private Vecteur direction;
	private Double longueur;
	private Integer recursivite;
	private Couleur couleur;
	private Liste<Materiau> materiauxTraverses;

	public Rayon(Vecteur origine, Vecteur direction, Double longueur, Integer recursivite, Couleur couleur, Liste<Materiau> materiauTraverse) {
		this.origine = origine;
		this.direction = new Vecteur(direction.normaliser());
		this.longueur = longueur;
		this.recursivite = recursivite;
		this.couleur = couleur;
		this.materiauxTraverses = materiauTraverse;
	}
	
	
	
	public Rayon(Rayon a) {
		try {
			this.origine = new Vecteur(a.origine);
			this.direction = new Vecteur(a.direction.normaliser());
			this.longueur = a.longueur;
			this.recursivite = a.recursivite;
			this.couleur = new Couleur(a.couleur);
			this.materiauxTraverses = new Liste<Materiau>(a.materiauxTraverses);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}

	public Rayon() {
		try {
			this.origine = new Vecteur();
			this.direction = new Vecteur();
			this.longueur = LanceurRayon.Util.Mathematiques.Constante.Infini;
			this.recursivite = 0;
			this.couleur = new Couleur();
			this.materiauxTraverses = new Liste<Materiau>().Explicite(new Materiau());
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
	public Rayon(Vecteur origine, Vecteur direction) {
		this.origine = origine;
		this.direction = direction.normaliser().vecteurValue();
		this.longueur = LanceurRayon.Util.Mathematiques.Constante.Infini;
		this.recursivite = 0;
		this.couleur = Couleur.blanc;
		this.materiauxTraverses = new Liste<Materiau>().Explicite(new Materiau());
	}

	public Liste<Materiau> getMateriauxTraverses() {
		return materiauxTraverses;
	}
	
	public Materiau getMateriauTraverse() {
		return materiauxTraverses.lastElement();
	}

	public void setMateriauxTraverses(Liste<Materiau> materiauxTraverses) {
		this.materiauxTraverses = materiauxTraverses;
	}
	
	public Vecteur getDirection() {
		return direction;
	}

	public void setDirection(Vecteur direction) {
		this.direction = direction.normaliser().vecteurValue();
	}

	public Vecteur getOrigine() {
		return origine;
	}

	public void setMateriauTraverse(Materiau fond) {
		this.materiauxTraverses = new Liste<Materiau>().Explicite(fond);
	}

	public void setOrigine(Vecteur origine) {
		this.origine = origine;
	}

	public Couleur getCouleur() {
		return couleur;
	}

	public void setCouleur(Couleur couleur) {
		this.couleur = couleur;
	}
	
	public void sommeCouleur(Couleur other) throws Exception {
		this.couleur.sommeObjet(other);
	}
	
	public void multiplicationCouleur(Couleur other) throws Exception {
		this.couleur.multiplicationObjet(other);
	}
	
	public void multiplicationCouleur(Double other) throws Exception {
		this.couleur.multiplicationObjet(other);
	}

	public Integer getRecursivite() {
		return recursivite;
	}

	public void setRecursivite(Integer recursivite) {
		this.recursivite = recursivite;
	}
	
	public void decrementeRecursivite() {
		this.recursivite --;
	}

	public Double getLongueur() {
		return longueur;
	}

	public void setLongueur(Double longueur) {
		this.longueur = longueur;
	}
	
	
	
}
