/*************************************************************************************************
 Fichier variables.h
 Ce fichier contient toutes les variables globales associées aux calculs de la simulation
 (résultats de calculs intermédiaires pour une meilleure lecture)
 - simulation :				- temps et communication
 - description mécanique :	- quelques dimensions
 - description physique :	- vitesses,accélération,masses,centre de masse, moments d'inertie
 - régulateur :				- entrées et sorties
 - position et orientation de l'hélicoptère
 - forces généralisées appliquées à l'hélicoptère
**************************************************************************************************



/*************************************************************************************************
 Variables associées à la simulation
 - gps1			: déclaration du GPS de l'hélicoptère
 - Dt			: pas de temps de la simulation [s]
 - time			: variable temps [s]
 - answer		: caractère pour la communication avec l'utilisateur
 - i			: compteur de boucle
*************************************************************************************************/	// Divers
DeviceTag gps1;
double Dt = 0.032;	// [s]
double time = 0;	// [s]
char answer;
int i;


/*************************************************************************************************
 Variables associées à la description mécanique de l'hélicoptère :
 - L		: demi longeur d'une barre
 - rp		: rayon d'une hélice
 - dp		: position des hélices (selon x et y) par rapport à l'intersection des barres
 - alphar	: angle alpha exprimé en radians
*************************************************************************************************/
double L;			// [m]
double rp;			// [m] rayon d'une hélice
double dp;			// [m] position d'une hélice (position du moteur + entraxe)
double alphar;		// [rad]



/*************************************************************************************************
 Variables associées à la description physique de l'hélicoptère
 - vp[i]	: vitesse angulaire des hélices [rad/s]
 - vpu[i]	: vitesse angulaire des hélices demandée par le régulateur
 - a		: accélération angulaire demandée par le régulateur
 - limit	: une limite physique a-t-elle été atteint ? (oui => limit = 1)
 - c[i]		: d[i]/b[i] = rapport entre les coefficients des hélices
			  c[4] = c[0] + ... + c[3]
 - m		: masse totale [kg]
 - zcm		: position du centre de masse (selon axe z) par rapport à l'intersection des barres
 - dz_		: position relative de chaque élément par rapport au centre de masse
 - Ixx_		: moment d'inertie de chaque élément par rapport à l'axe x (hélicoptère)
 - Iyy_		: moment d'inertie de chaque élément par rapport à l'axe y (hélicoptère)
 - Izz_		: moment d'inertie de chaque élément par rapport à l'axe z (hélicoptère)
 - Ixx,Iyy,Izz : moments d'inertie de l'hélicoptère
 - Ipr		: moment d'inertie rotorique de l'hélice + moment d'inertie du rotor rapporté
			  à l'hélice
 *************************************************************************************************/
double vp[4];	// [rad/s]
double vpu[4];	// [rad/s]
double a;		// [rad/s2]
int limit = 0;	// [boolean]
double c[5];	// [m]
double m;		// [kg]		
double zcm;		// [m]
double dze;		// [m]
double dzh;		// [m]
double dzs;		// [m]
double dzm;		// [m]
double dzb;		// [m]
double dzp;		// [m]
double dzg;		// [m]
double Ixxe;	// [kgm2]
double Ixxh;	// [kgm2]
double Ixxs;	// [kgm2]
double Ixxm1;	// [kgm2]
double Ixxm2;	// [kgm2]
double Ixxb1;	// [kgm2]
double Ixxb2;	// [kgm2]
double Ixxp1;	// [kgm2]
double Ixxp2;	// [kgm2]
double Iyye;	// [kgm2]
double Iyyh;	// [kgm2]
double Iyys;	// [kgm2]
double Iyym1;	// [kgm2]
double Iyym2;	// [kgm2]
double Iyyb1;	// [kgm2]
double Iyyb2;	// [kgm2]
double Iyyp1;	// [kgm2]
double Iyyp2;	// [kgm2]
double Izze;	// [kgm2]
double Izzh;	// [kgm2]
double Izzs;	// [kgm2]
double Izzm1;	// [kgm2]
double Izzm2;	// [kgm2]
double Izzb1;	// [kgm2]
double Izzb2;	// [kgm2]
double Izzp1;	// [kgm2]
double Izzp2;	// [kgm2]
double Ixx;		// [kgm2]
double Iyy;		// [kgm2]
double Izz;		// [kgm2]
double Ipr;		// [kgm2]



/*************************************************************************************************
 Variables associées aux calculs des régulateurs PID
 - ei[i]	: variable intégration des écarts
 - U[i]		: variable de sortie (force généralisée [N ou Nm])
*************************************************************************************************/
double ei[4];
double ei2[4];
double U[4];		// U[0] : [N], U[1]-U[3] : [Nm]



/*************************************************************************************************
 Variables associées à la position et à l'orientation de l'hélicoptère
 - x,y,z	: [1] = position actuelle du CM de l'hélicoptère (référentiel terrestre)
			: [0] = position précédente du CM de l'hélicoptère (référentiel terrestre)
 - dx,dy,dz	: vitesse actuelle du CM de l'hélicoptère (référentielle terrestre)
 - phi,theta,psi : [1] = orientation actuelle de l'hélicoptère (angle d'Euler)
				 : [0] = orientation actuelle de l'hélicoptère (angle d'Euler)
 - dphi,dtheta,dpsi : vitesse angulaire de l'hélicoptère (angle d'Euler)
 - PosMatrix : matrice de position fournie par le GPS de Webots
 - MW11,...,MW33 : variables pour l'extraction des éléments de la matrice de rotation
   (référentiel terrestre -> référentiel du robot)
*************************************************************************************************/
double x[2],y[2],z[2];
double dx,dy,dz;
double phi[2],theta[2],psi[2];
double dphi,dtheta,dpsi;
const float *PosMatrix;
float MW11, MW12, MW13,            // Rotation Matrix: tranform vector 
	  MW21, MW22, MW23,            // expressed in WEBOTS earth ref 
	  MW31, MW32, MW33;            // in a vector expressed W. body ref. 



/*************************************************************************************************
 Variables associées à l'expression des forces généralisées appliquées à l'hélicoptère 
 exprimées par rapport au référentiel de l'hélicoptère
 - tgphi,tgtheta			: moment gyroscopiques
 - v1,v2,v3					: vitesses associées au calcul des moments gyroscopiques
 - ffrotx, ffroty, ffrotz	: forces de frottement avec l'air
 - fx,fy,fz,tx,ty,tz		: forces résultantes totales
 - beta						: pour créer perturbation harmonique
*************************************************************************************************/
double tgphi, tgtheta;			// [Nm]
double v1,v2,v3;				// [rad/s]
double ffrotx,ffroty,ffrotz;	// [N]
double fx,fy,fz,tx,ty,tz;		// f : [N], t [Nm]
double beta = 0;