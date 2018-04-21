/*************************************************************************************************
 Fichier description_helico.h
 Ce fichier contient l'initialisation de toutes les variables globales caractérisant
 l'hélicoptère, c'est-à-dire :
 - les caractéristiques mécaniques :	- dimensions des éléments et positions relatives
										entre les éléments
 - les caractéristiques physiques :	- masses des éléments
									- caractérisation des hélices
									- caractérisation des moteurs
									- caractérisation des forces de frottement
 - les paramètres des régulateurs PID
*************************************************************************************************/

#define PI	3.141592654

/*************************************************************************************************
 Caractéristiques mécaniques et masses des éléments de l'hélicoptère
 Notations :
 - inclinaison des barres par rapport à l'horizontal : alpha
 - masse des éléments : m_
 - dimensions mécaniques des éléments:
			- parallélépipède :	- L_ (longueur = dimension selon l'axe y)
								- l_ (largeur = dimension selon axe x)
								- h_ (hauteur = dimension selon axe z)
			- cylindre :		- L_ (hauteur du cylindre)
								- r_ (rayon)
 - position du centre de masse selon l'axe z d'un élément : z_
 Remarque1 :- cette distance est mesurée par à la position verticale (axe z) de l'intersection
			  des barres (si celles-ci sont à l'horizontal : alpha = 0), avec z > 0 si le CM
			  de l'élément considéré est au-dessus de l'intersection des barres
 Remarque2 :- si l'angle alpha != 0, les nouvelles positions des centres de masse sont déduites
			  des positions z, il est donc important de bien définir les valeur des z_
*************************************************************************************************/

//***** Inclinaison des barres
int alpha = 0;			// [°]

//***** Electronics (e)
double me = 0.040;		// [kg]
double Le = 0.054;		// [m]
double le = 0.039;		// [m]
double he = 0.028;		// [m]
double ze = 0.020;		// [m]

//***** Electronics holder (h)
double mh = 0.010;		// [kg]
double Lh = 0.054;		// [m]
double lh = 0.039;		// [m]
double hh = 0.002;		// [m]
double zh = 0.005;		// [m]

//***** Supply (s)
double ms = 0.064;		// [kg]
double Ls = 0.095;		// [m]
double ls = 0.065;		// [m]
double hs = 0.005;		// [m]
double zs = -0.0065;	// [m]

//***** Motor (m)
double mm = 0.017;		// [kg]
double Lm = 0.024;		// [m]
double rm = 0.0085;		// [m]
double zm = -0.012;		// [m]
double dm = 0.200;		// [m]		position des moteurs (selon x et y) par rapport à
						//			l'intersection des barres
double Im = 0;			// [kgm2]	inertie du moteur

//***** Bar (b)
double mb = 0.030;		// [kg]
double Lb = 0.450;		// [m]
double zb = 0.000;		// [m]

//***** Gear box (g)
double mg = 0.005;		// [kg]
double zg = 0.005;		// [m]

//***** Propeller (p)
double mp = 0.007;		// [kg]
// Propeller as a cylinder (or disc)
double Lp = 0.285;		// [m]		diamètre
double hp = 0.002;		// [m]		hauteur
// Propeller as a parallelepiped
double lp = 0.030;		// [m]		Lp = longeur, lp = largeur d'une pale
double zp = 0.010;		// [m]
double ea = 0.0126;		// [m]		entraxe moteur-hélice


						
/*************************************************************************************************
 Caractéristiques physiques de l'hélicoptère
 - Caractérisation des hélices :	- b[i] : coefficients de portance [N s2]
									- d[i] : coefficients de trainée [Nm s2]
 - Caractérisation des moteurs :	- vmax : vitesse max [rad/s]
									- amax : accélération max (positive et négative) [rad/s2]
									- r    : rapport de réduction
 - Caractérisation des forces de frottement : - coefficients de frottements : kx,ky,kz
   (les forces de frottement linéaires sont modélisées comme étant proportionnelles aux
    vitesses linéraires au carré : Ffrot = k * v * v avec v = vitesse linéaire)
 - Rapport de réduction : r
 *************************************************************************************************/
double b[4] = {0.000009 ,	0.0000087 ,	0.0000085,	0.0000093	};	// [N s2]
double d[4] = {0.0000002,	0.00000018,	0.0000002,	0.00000023	};	// [Nm s2]
double vmax = 1800;		// [rad/s]
double amax = 25000;	// [rad/s2]
double kx = 0.8;
double ky = 0.8;
double kz = 0.2;
double r = 5;



/*************************************************************************************************
 Paramètres des 4 régulateurs PID : - PID1 [0] : contrôle de l'altitude
									- PID2 [1] : contrôle du roulis (phi) (ou tangage)
									- PID3 [2] : contrôle du tangage (theta) (ou roulis)
									- PID4 [3] : contrôle du lacet (psi)
 - Kp[i] : paramètre multipliant l'ecart e (consigne-mesure)
 - Td[i] : paramètre multipliant la vitesse
 - Ti[i] : paramètre multipliant le terme d'intégration des écarts
 - U0[i] : commande a priori (force généralisée [N ou Nm])
 - zd    : altitude désirée (consigne)
 - phid,thetad,psid : orientation désirée (consigne)
*************************************************************************************************/
double Kp[4] = {5.0,	1.0		, 0.5	,0.01	};
double Td[4] = {0.2,	0.2		, 0.2	,5.0	};
double Ti[4] = {0.002,	0.01	, 0.02	,0.1	};
double U0[4] = {2.8449,	0.0		, 0.0	,0.0	};
double zd = 0.5;		// [m]
double phid = 0;		// [rad]
double thetad = 0;		// [rad]
double psid = 0;		// [rad]