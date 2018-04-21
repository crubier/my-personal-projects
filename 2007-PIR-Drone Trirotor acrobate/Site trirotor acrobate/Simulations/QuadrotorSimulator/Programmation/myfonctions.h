/*************************************************************************************************
 Fichier myfonctions.h
 Ce fichier comprend toutes les fonctions créées pour la simulation
 - reset
 - exit
 - masse_cm_inertie
 - init
 - regulateur
 - display_matrix
 - display_position_vitesse
 - display_regulateur_output
 - display_limite
 - display_gyro
 - display_frottement
 - display_force
**************************************************************************************************



/*************************************************************************************************
 Fonction reset() :
 - Lecture et écriture du nom du robot
 - Initialisation du gps
*************************************************************************************************/
void reset(void)
	{
		const char *robot_name = robot_get_name();
		printf("Hello, my name is %s\n\n", robot_name);
		gps1 = robot_get_device("gps1");
	}



/*************************************************************************************************
 Fonction exit() :
 - Sortie du programme de simulation : écrit Bye bye
*************************************************************************************************/
/*void exit(void)
	{
		printf("Bye bye!\n");
	}
*/




/*************************************************************************************************
 Fonction masse_cm_inertie() : 
 - Calcul de la masse totale => m
 - Initialisation de quelques variables
 - Calcul de la position des centres de masse de chaque élément relatif à l'intersection des
   barres => z_
 - Calcul de la position du centre de masse de l'hélicoptère relatif à l'intersection des
   barres => zcm
 - Calcul de la poistion des centres de masse de chaque élément relatifs au centre de masse de
   l'hélicoptère => dz_
 - Calcul des moments d'inertie de chaque élément => Ixx_,Iyy_,Izz_
 - Calcul des moments d'inertie de l'hélicoptère => Ixx,Iyy,Izz
 - Calcul du moment d'inertie rotorique => Ipr
 - Affichage des résultats pour l'utilisateur
*************************************************************************************************/

void masse_cm_inertie (void)
{
	/***** Masse totale *****/
	m = me + mh + ms + 4 * mm + 2 * mb + 4 * mg + 4 * mp;	// [kg]

	/***** Variables nécessaire pour le calcul du centre de masse et des moments d'inertie *****/
	alphar = (alpha * PI) / 180;
	L = Lb/2;
	dp = dm + ea;
	dp = dp - zcm * sin(alphar);
	c[4] = 0;
	for (i = 0; i < 4; i++)
	{
		c[i] = d[i]/b[i];
		c[4] = c[4] + c[i];
	}

	/***** Centre de masse de chaque élément relatif à l'intersection des barres *****/
	if (alpha != 0)
	{
		ze = ze;
		zh = zh;
		zs = zs;
		zm = (dm * sin(alphar) + zm * cos(alphar));
		zb = (L * sin(alphar)) / 2;
		zg = (dp * sin(alphar) + zg * cos(alphar));
		zp = (dp * sin(alphar) + zp * cos(alphar));
		zcm = (me*ze + mh*zh + ms*zs + 4*mm*zm + 2*mb*zb + 4*mg*zg + 4*mp*zp) / m;	// [m]
	}

	/***** Centre de masse de l'hélicoptère relatif à l'intersection des barres *****/
	zcm = (me*ze + mh*zh + ms*zs + 4*mm*zm + 2*mb*zb + 4*mg*zg + 4*mp*zp) / m;	// [m]

	/***** Centre de masse de chaque élément relatif au centre de masse de l'hélicoptère *****/
	dze = ze - zcm;		// [m]
	dzh = zh - zcm;		// [m]
	dzs = zs - zcm;		// [m]
	dzm = zm - zcm;		// [m]
	dzb = zb - zcm;		// [m]
	dzg = zg - zcm;		// [m]
	dzp = zp - zcm;		// [m]

	/***** Calcul des moments d'inertie de chaque élément (réducteur est négligé) *****/
	// Ixx
	Ixxe = me/12 * (Le*Le + he*he)		+ me * dze*dze;				// electronics inertia
	Ixxh = mh/12 * (Lh*Lh + hh*hh)		+ mh * dzh*dzh;				// electronics holder inertia
	Ixxs = ms/12 * (Ls*Ls + hs*hs)		+ ms * dzs*dzs;				// supply inertia
	Ixxm1 = mm * (rm*rm/4 + Lm*Lm/12)	+ mm * dzm*dzm;				// motor inertia 1,3 
	Ixxm2 = mm * (rm*rm/4 + Lm*Lm/12)	+ mm * (dm*dm + dzm*dzm);	// motor inertia 2,4
	Ixxb1 =								  mb * dzb*dzb;				// bar inertia 1,3
	Ixxb2 = mb * Lb*Lb/12				+ mb * dzb*dzb;				// bar inertia 2,4
	Ixxp1 = mp/4 * rp*rp				+ mp * dzp*dzp;				// propeller as a disc 1,3
	Ixxp2 = mp/4 * rp*rp				+ mp * (dzp*dzp + dp*dp);	// propeller as a disc 2,4         

	// Iyy
	Iyye = me/12 * (le*le + he*he)		+ me * dze*dze;				// electronics inertia
	Iyyh = mh/12 * (lh*lh + hh*hh)		+ mh * dzh*dzh;				// electronics holder inertia
	Iyys = ms/12 * (ls*ls + hs*hs)		+ ms * dzs*dzs;				// supply inertia
	Iyym1 = mm * (rm*rm/4 + Lm*Lm/12)	+ mm * (dm*dm + dzm*dzm);	// motor inertia 1,3 
	Iyym2 = mm * (rm*rm/4 + Lm*Lm/12)	+ mm * dzm*dzm;				// motor inertia 2,4
	Iyyb1 = mb * Lb*Lb/12				+ mb * dzb*dzb;				// bar inertia 1,3
	Iyyb2 =								  mb * dzb*dzb;				// bar inertia 2,4
	Iyyp1 = mp/4 * rp*rp				+ mp * (dzp*dzp + dp*dp);	// propeller as a disc 1,3
	Iyyp2 = mp/4 * rp*rp				+ mp * dzp*dzp;				// propeller as a disc 2,4

	// Izz
	Izze = me/12 * (Le*Le + le*le);									// electronics inertia
	Izzh = mh/12 * (Lh*Lh + lh*lh);									// electronics holder inertia
	Izzs = ms/12 * (Ls*Ls + ls*ls);									// supply inertia
	Izzm1 = mm/2 * rm*rm				+ mm * dm*dm;				// motor inertia 1,3 
	Izzm2 = mm/2 * rm*rm				+ mm * dm*dm;				// motor inertia 2,4 
	Izzb1 = mb * Lb*Lb/12;											// bar inertia 1,3
	Izzb2 = mb * Lb*Lb/12;											// bar inertia 2,4
	Izzp1 = mp/2 * rp*rp				+ mp * dp*dp;				// propeller as a disc 1,3
	Izzp2 = mp/2 * rp*rp				+ mp * dp*dp;				// propeller as a disc 2,4

	/***** Calcul des moments d'inertie de l'hélicoptère *****/
	Ixx = Ixxe + Ixxh + Ixxs + 2*(Ixxm1+Ixxp1) + 2*(Ixxm2+Ixxp2) + Ixxb1 + Ixxb2;	// [kg.m2]    
	Iyy = Iyye + Iyyh + Iyys + 2*(Iyym1+Iyyp1) + 2*(Iyym2+Iyyp2) + Iyyb1 + Iyyb2;	// [kg.m2]
	Izz = Izze + Izzh + Izzs + 2*(Izzm1+Izzp1) + 2*(Izzm2+Izzp2) + Izzb1 + Izzb2;	// [kg.m2]

	/***** Moment d'inertie rotorique (hélice + moteur rapporté) *****/
	Ipr = mp/12 * (Lp*Lp + lp*lp) + Im * r*r;	// [kg.m2];

	/***** Affichage des résultats *****/
	printf("Masse totale : %f [kg]\n\n", m);
	printf("Position du centre de masse de chaque element \npar rapport a l'intersection des barres : \n");
	printf("Electro :	%f [m]\n",ze);
	printf("Holder :	%f [m]\n",zh);
	printf("Alim :		%f [m]\n",zs);
	printf("Moteur :	%f [m]\n",zm);
	printf("Barre :		%f [m]\n",zb);
	printf("Reducteur :	%f [m]\n",zg);
	printf("Helice :	%f [m]\n\n",zp);
	printf("Position du centre de masse par rapport a l'intersection \ndes barres :	%f [m]\n\n",zcm);
	printf("Moments d'inertie\n");
	printf("Ixx = %f [kgm2] => Izz de Webots\n",Ixx);
	printf("Iyy = %f [kgm2] => Ixx de Webots\n",Iyy);
	printf("Izz = %f [kgm2] => Iyy de Webots\n",Izz);
	printf("Ipr = %f [kgm2]\n",Ipr);
	printf("\n");
}



/*************************************************************************************************
 Fonction init() : 
 - Initialisation des paramètres du régulateur par l'utilisateur
*************************************************************************************************/
void init (void)
{
	// Initialisation de la position desiree
	printf("Initialisation de la position desiree\n");
	printf("zd : %f, phid : %f, thetad : %f, psid : %f\n", zd,phid,thetad,psid);
	printf("Position desiree par default ? ");
	answer = getchar();
	if (answer != 'y')
	{
		printf("Altitude z : ");
		scanf("%lf", &zd);
		printf("Orientation phi : ");
		scanf("%lf", &phid);
		printf("Orientation theta : ");
		scanf("%lf", &thetad);
		printf("Orientation psi : ");
		scanf("%lf", &psid);
	}
	printf("Confirmation :\n%f %f %f %f\n\n\n", zd, phid, thetad, psid);

	getchar();		// Lire le dernier return
	
	// Initialisation des paramètres Kp,Td et Ti des 4 régulateur
	printf("Initialisation des regulateurs\n");
	for (i = 0; i < 4; i++)
	{
		printf("Kp%d : %f, Td%d : %f, Ti%d : %f, U0%d : %f\n", i+1,Kp[i],i+1,Td[i],i+1,Ti[i],i+1,U0[i]);
		printf("Regulateur %d par default ? ", i+1);
		answer = getchar();
		if (answer != 'y')
		{
			printf("Parametres du regulateur %d : Kp Td Ti U0 : ", i+1);
			scanf("%lf %lf %lf %lf", &Kp[i], &Td[i], &Ti[i], &U0[i]);
		}
		printf("Confirmation :\nKp%d = %f, Td%d = %f, Ti%d = %f, U0%d = %f\n\n\n",i+1,Kp[i],i+1,Td[i],i+1,Ti[i],i+1,U0[i]);
		getchar();
	}

	// Description de l'helicoptère
	printf("Caracterisation des helices :\n coefficient de portance b et de trainee d\n");
	for (i = 0; i < 4; i++)
	{
		printf("b%d : %.8lf, d%d : %.8f\n", i+1,b[i],i+1,d[i]);
		printf("Coefficients par default ? ");
		answer = getchar();
		if (answer != 'y')
		{
			printf("b%d d%d : ",i+1,i+1);
			scanf("%lf %lf", &b[i], &d[i]);
		}
		printf("Confirmation :\nb%d : %.8f, d%d : %.8f\n\n\n", i+1,b[i],i+1,d[i]);
		getchar();
	}

	printf("Caracterisation des moteur\n");
	printf("Vitesse max : %f\n", vmax);
	printf("OK ? ");
	answer = getchar();
	if (answer != 'y')
	{
		printf("Vmax : ");
		scanf("%lf", &vmax);
	}
	printf("Confirmation :\nvmax : %f\n\n\n", vmax);
	
	getchar();

	printf("Acceleration max : %f\n", amax);
	printf("OK ? ");
	answer = getchar();
	if (answer != 'y')
	{
		printf("Amax : ");
		scanf("%lf", &amax);
	}
	printf("Confirmation :\namax : %f\n\n\n", amax);
	
	getchar();

	printf("Rapport de reduction : %f\n", r);
	printf("OK ? ");
	answer = getchar();
	if (answer != 'y')
	{
		printf("r : ");
		scanf("%lf", &r);
	}
	printf("Confirmation :\nr : %f\n\n\n", r);
	
	getchar();
	
	printf("Caracterisation des frottements\nCoefficients de frottement\n");
	printf("kx : %f, ky : %f, kz : %f\n", kx,ky,kz);
	printf("Coefficients par default ? ");
	answer = getchar();
	if (answer != 'y')
	{
		printf("kx ky kz : ");
		scanf("%lf %fl", &kx, &ky, &kz);
	}
	printf("Confirmation :\nkx : %f, ky : %f, kz : %f\n\n\n", kx,ky,kz);
	
	getchar();
}



/*************************************************************************************************
 Fonction regulateur(i,posd,pos,speed) : 
 - Calcul la sortie d'un régulateur PID
 - Input :	- i		: numéro du régulateur
			- posd	: position désirée <=> consigne
			- pos	: position actuelle (mesuree)
			- speed	: vitesse actuelle (mesuree)
 - Output :	- U[i]	: force généralisée à appliquer [N ou Nm]
 - Variables locales internes pour la lisibilité :
			- e		: ecart consigne-position actuelle
*************************************************************************************************/
double regulateur (int i, double posd, double pos, double speed)
{
	double e;
	e = posd - pos;
	printf("Posd %f, e %f  speed %f\n", posd, e, speed);
	ei[i] = ei[i] + e;
	return U0[i] + Kp[i] * (e - Td[i] * speed + Ti[i] * ei[i]);
}




/*************************************************************************************************
 Fonction display_position_vitesse() : 
 - Affiche la position et les vitesse de rotation actuels de l'hélicoptère
*************************************************************************************************/
void display_position_vitesse (void)
{
	printf("x = %f\n", x[1]);
	printf("y = %f\n", y[1]);
	printf("z = %f\n", z[1]);
	printf("phi = %f\n",phi[1]*180/PI);
	printf("psi = %f\n",psi[1]*180/PI);
	printf("theta = %f\n",theta[1]*180/PI);
	printf("\n");
	printf("dx = %f\n",dx);
	printf("dy = %f\n",dy);
	printf("dz = %f\n",dz);
	printf("dphi = %f\n",dphi);
	printf("dtheta = %f\n",dtheta);
	printf("dpsi = %f\n",dpsi);
	printf("\n");
}



/*************************************************************************************************
 Fonction display_regulateur_output() : 
 - Affiche les sortie du régulateur : forces généralisées Ui et vitesse angulaire des moteurs vpi
*************************************************************************************************/
void display_regulateur_output (void)
{
	for(i = 0; i < 4; i++)
		printf("U%d = %.10f\n", i+1, U[i]);
	printf("\n");
	for(i = 0; i < 4; i++)
		printf("vpu%d = %f\n", i+1, vpu[i]);
	printf("\n");
}



/*************************************************************************************************
 Fonction display_matrix() : 
 - Affiche la matrice de rotation 3x3 (terre -> helico)
*************************************************************************************************/
void display_matrix (void)
{
	printf("Matrice de rotation:\n%f %f %f\n%f %f %f \n%f %f %f\n",MW11,MW12,MW13,MW21,MW22,MW23,MW31,MW32,MW33);
	printf("\n");
}



/*************************************************************************************************
 Fonction display_limite() : 
 - Affiche les vitesses de commande corrigées après limitations physiques des moteurs
*************************************************************************************************/
void display_limite (void)
{
	for(i = 0; i < 4; i++)
		printf("vpu%d = %f\n", i+1, vpu[i]);
	printf("\n");
}



/*************************************************************************************************
 Fonction display_gyro() : 
 - Affiche la valeur des moments gyroscopiques
*************************************************************************************************/
void display_gyro (void)
{
	printf("tgtheta = %f [Nm]\n",tgtheta);
	printf("tgphi = %f [Nm]\n", tgphi);
	printf("\n");
}



/*************************************************************************************************
 Fonction display_frottement() : 
 - Affiche la valeur des forces de frottement
*************************************************************************************************/
void display_frottement (void)
{
	printf("ffrotx = %f [N]\n",ffrotx);
	printf("ffroty = %f [N]\n",ffroty);
	printf("ffrotz = %f [N]\n",ffrotz);
	printf("\n");
}



/*************************************************************************************************
 Fonction display_force() : 
 - Affiche la valeur des forces généralisées appliquées à l'hélicoptère
*************************************************************************************************/
void display_force (void)
{
	printf("fx = %f[N]\n",fx);		
	printf("fy = %f[N]\n",fy);
	printf("fz = %f[N]\n",fz);
	printf("tx = %f[Nm]\n",tx);
	printf("ty = %f[Nm]\n",ty);
	printf("tz = %f[Nm]\n",tz);
	printf("\n");
}
