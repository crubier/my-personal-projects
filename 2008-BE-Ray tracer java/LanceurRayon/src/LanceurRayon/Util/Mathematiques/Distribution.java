/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util.Mathematiques;

/**
 * Résultats mathématiques obtenus avec Wolfram Mathematica 5.1
 * <p>
 * Resultats traduits automatiquement en language java, j'ai essayer de rendre ça lisible, mais c'est parfois trop compliqué.
 * </p>
 * @author Lecrubier
 */
public class Distribution {
	
	 /**
     * Impossible d'instancier cette classe
     */
    private Distribution() {}
	
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
	 * @param x
	 * @param m
	 * @param e
	 * @return distribution gaussienne centree en m, variance e, calculee en x
	 */

	public static double gauss(double x,double m,double e) {
		if(e < Constante.Epsilon) {
			return dirac(x,m);
		}
		return Math.exp(	-0.5*Math.pow((x-m)/e,2)		)   /    (e*Math.sqrt(2*Math.PI));
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
	 * @param x0
	 * @param x1
	 * @param m
	 * @param e
	 * @return integrale de la distribution gaussienne centree en m, variance e, calculee entre x0 et x1
	 */
	
	public static double gauss(double x0, double x1,double m,double e) {
		double res;
		if( x1 < x0) {
			res =  -1*gauss( x1,  x0, m, e);
		}
		else {
			if(e < Constante.Epsilon) {
				return dirac(x0,x1,m);
			}
			res =  (-erf( (x0-m) /(Math.sqrt(2)*e)) + erf( (x1-m) /(Math.sqrt(2)*e)))/2.;
		}
		return res;
	}
	

	private static double erf(double z) {
		
        double t = 1.0 / (1.0 + 0.5 * Math.abs(z));

        double ans = 1 - t * Math.exp( -z*z   -   1.26551223 +
                                            t * ( 1.00002368 +
                                            t * ( 0.37409196 + 
                                            t * ( 0.09678418 + 
                                            t * (-0.18628806 + 
                                            t * ( 0.27886807 + 
                                            t * (-1.13520398 + 
                                            t * ( 1.48851587 + 
                                            t * (-0.82215223 + 
                                            t * ( 0.17087277))))))))));
        if (z >= 0) {
			return ans;
		}
        else {
			return -ans;
		}
    		
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
	 * @param x
	 * @param m
	 * @param a
	 * @return sinus cardinal centre en m, de largeur 2* pi /a , calcule en x
	 */
	public static double sinc(double x,double m, double a) {
		if(a < Constante.Epsilon) {
			return dirac(x,m);
		}
		return Math.sin(	a * (x-m)	) / ( (x-m) * Math.PI);
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
	 * @param x0 
	 * @param x1 
	 * @param m 
	 * @param a
	 * @return integrale du sinus cardinal centre en m, de largeur 2* pi /a , calcule entre x0 et x1
	 */
	public static double sinc(double x0, double x1,double m, double a) {
		double res;
		if( x1 < x0) {
			res = -1*sinc(x1, x0, m, a);
		}
		else {
			if(a < Constante.Epsilon) {
				return dirac(x0,x1,m);
			}
			res= -1*((sinint(a*(-m + x0)) + sinint(a*(m - x1)))/Math.PI);
		}
		return res;
	}
	
	/**
	 * approximation de la fonction sinIntegral a l ordre 20 avec raccord en 8, pour calcul integral de distribution sinc
	 * @param x
	 * @return Sinint(x) a peu près partout a 0.8% pres (erreur max vers +-10)
	 */
	private static double sinint(double x) {
		if(x<-8) {
			return -Math.PI/2.-Math.cos(x)/x;
		}
		if(x>8) {
			return Math.PI/2.-Math.cos(x)/x;
		}
		return	x -
				Math.pow(x,3)/18. +
				Math.pow(x,5)/600. - 
				Math.pow(x,7)/35280. + 
				Math.pow(x,9)/3.26592e6 - 
				Math.pow(x,11)/4.390848e8 + 
				Math.pow(x,13)/8.09512704e10 - 
				Math.pow(x,15)/1.961511552e13 + 
				Math.pow(x,17)/6.046686277632e15 - 
				Math.pow(x,19)/2.311256907767808e18;
		
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
	 * @param x
	 * @param m
	 * @param a
	 * @return sinus cardinal au carré centre en m, de largeur 2* pi /a , calcule en x, convolution de sinc avec elle meme
	 */
	public static double sinc2(double x,double m, double a) {
		if(a < Constante.Epsilon) {
			return dirac(x,m);
		}
		return Math.pow(Math.sin(	a * (x-m)	),2) / ( Math.pow((x-m),2) * Math.PI * a);
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1 
	 * <p>
	 * On remarquera les calculs *un peu lourds*
	 * </p>
	 * @param x0
	 * @param x1
	 * @param m
	 * @param a
	 * @return integrale du sinus cardinal au carre centre en m, de largeur 2* pi /a , calcule entre x0 et x1
	 */
	public static double sinc2(double x0, double x1,double m, double a) {
		double res;
		if( x1 < x0) {
			res = -1*sinc2(x1, x0, m, a);
		}
		else {
			if(a < Constante.Epsilon) {
				return dirac(x0,x1,m);
			}
			if(x0 < m && m < x1){
				res =  ((-1 + Math.cos(2*a*(m - x0)) + 2*a*m*sinint(2*a*(m - x0)) + 2*a*x0*sinint(2*a*(-m + x0)))/(m - x0) + 
						(2*(Math.pow(Math.sin(a*(m - x1)),2) + a*(-m + x1)*sinint(2*a*(m - x1))))/(m - x1))/(2.*a*Math.PI);
			}
			else {
				res = (-x0 + x1 + m*Math.cos(2*a*(m - x0)) - x1*Math.cos(2*a*(m - x0)) - m*Math.cos(2*a*(m - x1)) + x0*Math.cos(2*a*(m - x1)) + 
					 2*a*(Math.pow(m,2) + x0*x1)*sinint(2*a*(m - x0)) + 2*a*m*(x0 + x1)*sinint(2*a*(-m + x0)) - 
					2*a*Math.pow(m,2)*sinint(2*a*(m - x1)) + 2*a*m*x0*sinint(2*a*(m - x1)) + 
					2*a*m*x1*sinint(2*a*(m - x1)) - 2*a*x0*x1*sinint(2*a*(m - x1)))/(2.*a*Math.PI*(m - x0)*(m - x1));
			}
		}
		return res;
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1 
	 * @param x
	 * @param m
	 * @param a
	 * @return fonction fenetre de largeur 2a centree en m, calcule en x
	 */	
	public static double fenetre(double x, double m, double a) {
		if(a < Constante.Epsilon) {
			return dirac(x,m);
		}
		return ((x-m) >= -a && (x-m) <= a ) ? 1 /(2*a) : 0.;
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1 
	 * @param x0
	 * @param x1
	 * @param m
	 * @param a
	 * @return integrale de la fonction fenetre de largeur 2a centree en m, calcule entre x0 et x1
	 */	
	public static double fenetre(double x0, double x1, double m, double a) {
		double res = 0.;
		if( x1 < x0) { // bornes inversees
			res = -1*fenetre(x1, x0, m, a);  
		}
		else {
			if(a < Constante.Epsilon) {
				return dirac(x0,x1,m);
			}
			if ( (x1-m) <= -a || (x0-m) >= a ) { // exterieur de la fenetre
				res = 0.; 
			}	
			else {   // on est donc pas a l'exterieur ie (x1-m) > -a  &&  (x0-m) < a
				if ((x0-m) >= -a && (x1-m) <= a ) { // interieur de la fenetre
					res = (x1-x0) /(2*a); 
				}	
				else {
					if ((x0-m) <= -a && (x1-m) <= a ) { // chevauchement du bord gauche
						res = ((x1-m)+a) /(2*a);
					}
					if((x0-m) >= -a && (x1-m) >= a ) { // chevauchement du bord droit
						res = (a-(x0-m)) /(2*a);
					}
					if ((x0-m) <= -a && (x1-m) >= a ) { // chevauchement de la fenetre entiere
						res = 1.;
					}
				}
			}
		}
		return res;
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
	 * @param x
	 * @param m
	 * @param a
	 * @return fonction triangle de largeur 4a centree en m, calcule en x, convolution de fentre avec elle meme
	 */	
	public static double triangle(double x, double m,double a) {
		if(a < Constante.Epsilon) {
			return dirac(x,m);
		}
		return ((x-m) >= -2*a && (x-m) <= 2*a ) ? 1 /(2*a) - Math.abs((x-m)/(2*a) /(2*a)) : 0.;
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
	 * @param x0 
	 * @param x1 
	 * @param m 
	 * @param a
	 * @return integrale de la fonction triangle de largeur 4a centree en m, calcule entre x0 et x1
	 */	
	public static double triangle(double x0, double x1, double m, double a) {
		double res = 0.;
		if( x1 < x0) { // bornes inversees
			res = -1*triangle(x1, x0, m, a);  
		}
		else {
			if(a < Constante.Epsilon) {
				return dirac(x0,x1,m);
			}
			if(x0<=(m-2*a) &&  x1>=(m-2*a)) {
				res= 1.;
			}
			else {
				//A ameliorer c'est horrible !
				res = (triangle(x1,m,a)+ triangle(x0,m,a))/2;  //trop long, la flemme, on passe en integration par methode des trapezes
			}
		}
		return res;
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
	 * @param x
	 * @param m
	 * @return dirac en m
	 */	
	public static double dirac(double x, double m) {
		return ((x-m) >= -Constante.Epsilon && (x-m) <= Constante.Epsilon ) ? 1/Constante.Epsilon : 0.;
	}
	
	/**
	 * Integrale sur ] -inf , + inf [ = 1
		 * @param x0 
		 * @param x1 
		 * @param m 
		 * @return integrale de dirac en m entre x0 et x1
	 */	
	public static double dirac(double x0, double x1, double m) {
		double res = 0.;
		if( x1 < x0) { // bornes inversees
			res = -1*dirac(x1, x0, m);  
		}
		else {
			if ((x0-m)<=0. && (x1-m) >= 0.) {
				if ((x0-m)==0. || (x1-m) == 0.) {
					res = 0.5;
				}
				else {
					res = 1.;
				}
			}
			else {
				res = 0.;
			}
		}
		return res;
	}
	
}
