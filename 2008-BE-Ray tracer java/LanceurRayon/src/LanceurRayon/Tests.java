package LanceurRayon;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import LanceurRayon.IHM.Arbre.ArbreXMLModel;
import LanceurRayon.Objets.Cameras.*;
import LanceurRayon.Objets.Figures.*;
import LanceurRayon.Objets.Lumieres.*;
import LanceurRayon.Objets.Figures.Sphere;
import LanceurRayon.Physique.Couleur;
import LanceurRayon.Physique.Couleur;
import LanceurRayon.Physique.Materiau;
import LanceurRayon.Physique.Rayon;
import LanceurRayon.Scene.Scene;
import LanceurRayon.Util.*;
import LanceurRayon.Util.Geometrie.Matrice;
import LanceurRayon.Util.Geometrie.Vecteur;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * @author Lecrubier
 */
public class Tests {
	 public static void main(String[] args) {
		try {
			test();
		} catch (Exception ex) {
			Logger.getLogger(Tests.class.getName()).log(Level.SEVERE, null, ex);
		}
    }
	
	
	public static void test() throws Exception {
//////////////////Test vecteurs//////////////////////
//		Vecteur a = new Vecteur(10.,1230.,540.);
//		System.out.println("Vecteur a                  : " + a);
//		System.out.println("Vecteur a normalisé        : " + a.normaliser());
//		System.out.println("Norme du vecteur normalisé : " + a.normaliser().norme());
//		System.out.println("Vecteur a après rotation   : " +  a.rotation(Vecteur.zero, Angle.Deg(90.),Vecteur.e1));
////////////////////////////////////////
		
//////////////Test figures/////////////////
//		Sphere a = new Sphere(Vecteur.zero,1.);
//		System.out.println("Entrée : " + a.entree(new Vecteur(10.,0.,0.),Vecteur.ne0));
//		System.out.println("Sortie : " + a.sortie(new Vecteur(10.,0.,0.),Vecteur.ne0));
////////////////////////////////////
		
//////////////////////Test contenu de scene////////////
//		
//		Scene a = testScene();
//		System.out.println("Figures  : " + a.getFigures());
//		System.out.println("Lumieres : " + a.getLumieres());
//		System.out.println("Cameras  : " + a.getCameras());
//		
///////////////////////////////////////////////////////////////////	

//////////////////////Test Couleur Rayon//////////////////////		
//		Rayon a = new Rayon(Vecteur.zero,Vecteur.e0) ;
//		a.setCouleur(new Couleur(Couleur.bleu));
//				a.getCouleur().afficherSpectre();
//		a.sommeCouleur(Couleur.vert);
//		a.getCouleur().afficherSpectre();
/////////////////////////////////////////////////////		
		
/////////////////Test Couleur norme etc/////////
////		
////		Couleur test1 = new Couleur().CouleurRVB(1.,0. , 0.);
////		Couleur test2 = new Couleur().CouleurRVB(0.,0.6 , 0.);
////		Couleur test3 = new Couleur().CouleurRVB(0.,0. , 0.3);
////		
////		Couleur test1 = new Couleur().CouleurJMC(1.,0. , 0.);
////		Couleur test2 = new Couleur().CouleurJMC(0.,0.6 , 0.);
////		Couleur test3 = new Couleur().CouleurJMC(0.,0. , 0.3);	
//		Couleur test1 = Couleur.rouge;
//		Couleur test2 = Couleur.vert;
//		Couleur test3 = Couleur.bleu;
//		
//		Double k = .9/test1.normeInf();
//		Ecran a = new Ecran("Test", 800,600,400);
//		test1.afficherSpectre(a,k);
//		test2.afficherSpectre(a,k);
//		test3.afficherSpectre(a,k);
//		System.out.println(test1);
//		System.out.println(test1.norme(1));
//		System.out.println(test1.normeInf());
//		System.out.println(test1.toRGB(1.));
/////////////////////////////////////////////////////
		
/////////////Test Precision couleur : faire varier Couleur.precision et deltalambda////		
//		Couleur.PRECISION = 36;
//		Image a = new Image(80,60,Couleur.noir);
//		Double deltalambda = 5.;
//		
//		a.dessinerRectangle(19, 19, 62, 41, Couleur.bleu.multiplication(50.));
//		for( Integer k=0;k<=40;k++) {
//			a.dessinerRectangle(20+1*k,20 , 21 + 1*k, 30, new Couleur().CouleurGauss(400.+10.*k, deltalambda, 2.));
//			a.dessinerRectangle(20+1*k,30 , 21 + 1*k, 40, new Couleur().CouleurTSL(-9.*k, 100., 2.));
//		}
//		System.out.println("OK");
//		a.afficher(1.,10.);
/////////////////////////////////////////////////////	
		
///////////Test Couleurs////////////////////////////////////////
//		Couleur.PRECISION = 12;
//		Couleur test1 = new Couleur().CouleurGauss(500., 100., 1.);
//		Couleur test2 = new Couleur().CouleurGauss(700., 50., 1.);
//		Couleur test3 = test1.somme(test2);
//		Couleur test4 = test1.multiplication(test2);
//		Double k = .9/test3.normeInf();
//		Ecran a = new Ecran("Test", 800,600,400);
//		test1.afficherSpectre(a,k);
//		test2.afficherSpectre(a,k);
//		test3.afficherSpectre(a,k);
//		test4.afficherSpectre(a,k);
////		Couleur.vert.afficherSpectre(new Ecran("Test", 800,600,400));
/////////////////////////////////////////////////////
//		
		
///////////Test rendu de scene test/////		
		Scene a = testScene();
		new ArbreXMLModel(a.toJdom("", "")).enregistrer("c:/figure.xml");
//		Integer qualite = 4;
//		Image b = a.calculer(800/qualite, 600/qualite, 4);
//		b = b.normaliserMax();
//		b.afficher(1.0,qualite.doubleValue());
//		b.exporter("c:/essai.png");
////////////////////////////////////////
	}
	
	public static Scene testScene() {
		try {
			Scene a = new Scene();
			
			Intersection tuy = new Intersection(
				new Liste<Figure>().Explicite(
						new Cylindre(Vecteur.zero,2.,Vecteur.e2),
						new Negation(new Cylindre(Vecteur.zero,1.,Vecteur.e2)),
						new Plan(Vecteur.e2,Vecteur.e2),
						new Plan(Vecteur.ne2,Vecteur.ne2)
					),
				Materiau.defaut
				);
			
			a.ajouter(tuy);
			
			
			return a;
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
}
