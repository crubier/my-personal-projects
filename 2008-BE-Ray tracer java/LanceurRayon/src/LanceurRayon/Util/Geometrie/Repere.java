/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util.Geometrie;

/**
 *	Inactif pour l'instant
 * @author Lecrubier
 */
public class Repere {
	private Repere repere;
    private Vecteur origine;
    private Matrice orientation;

	public final static Repere R0 =		new Repere(null,Vecteur.zero,Matrice.identite);
	
	
	/**
	 * 
	 * @param repere 
	 * @param origine
	 * @param orientation
	 */
	public Repere(Repere repere, Vecteur origine, Matrice orientation) {
		this.repere = repere;
		this.origine = origine;
		this.orientation = orientation;
	}
	
	/**
	 * 
	 * @param repere 
	 * @param origine
	 */
	public Repere(Repere repere, Vecteur origine) {
		this.repere = repere;
		this.origine = origine;
		this.orientation = Matrice.identite;
	}
	
	/**
	 * 
	 * @param origine
	 * @param orientation
	 */
	public Repere(Vecteur origine, Matrice orientation) {
		this.repere = null;
		this.origine = origine;
		this.orientation = orientation;
	}
	
	/**
	 * 
	 * @param repere
	 * @param orientation 
	 */
	public Repere(Repere repere, Matrice orientation) {
		this.repere = repere;
		this.origine = Vecteur.zero;
		this.orientation = orientation;
	}	

	/**
	 * 
	 * 
	 * @param orientation 
	 */
	public Repere(Matrice orientation) {
		this.repere = null;
		this.origine = Vecteur.zero;
		this.orientation = orientation;
	}
	
	/**
	 * 
	 * @param repere 
	 */
	public Repere(Repere repere) {
		this.repere = repere;
		this.origine = Vecteur.zero;
		this.orientation = Matrice.identite;
	}
	
	/**
	 * 
	 * 
	 * @param origine 
	 */
	public Repere(Vecteur origine) {
		this.repere = null;
		this.origine = origine;
		this.orientation = Matrice.identite;
	}
	
	/**
	 * 
	 */
	public Repere() {
		this.repere = null;
		this.origine = Vecteur.zero;
		this.orientation = Matrice.identite;
	}
	
}
