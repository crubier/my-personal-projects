/*************************************************************************************************
 Fichier Helico.c
 Programme principal du contrôleur de la simulation du quadrator VTOL
*************************************************************************************************/

// Include Visual C++
#include <stdio.h>
#include <math.h>
#include <string.h>
// Include Webots
#include <device/robot.h>
#include <device/custom_robot.h>
#include <device/gps.h>
// My include
#include <description_helico.h>
#include <variables.h>
#include <myfonctions.h>


int main()
{
	robot_live(reset);
	masse_cm_inertie();

	// Entrée des parametres par l'utilisateur
	//init();

	// Activation du GPS
	gps_enable(gps1,(short unsigned int)(Dt*1000));
	robot_step((int)(Dt*1000));
	time = time + Dt;
	
	// Initialisation des positions et orientations du robot
	PosMatrix = gps_get_matrix(gps1);
		        
	// Compute Rotation Matrix MW
	MW11 = PosMatrix[0]; MW12 = PosMatrix[1]; MW13 = PosMatrix[2];
	MW21 = PosMatrix[4]; MW22 = PosMatrix[5]; MW23 = PosMatrix[6];
	MW31 = PosMatrix[8]; MW32 = PosMatrix[9]; MW33 = PosMatrix[10];

	// Calcul des angles d'Euler correspondants
	psi[0] = asin(-MW13);				// [rad]
	phi[0] = asin(MW12/cos(psi[0]));	// [rad]
	theta[0] = asin(MW23/cos(psi[0]));	// [rad]
	
	// Position du robot par rapport au référentiel terrestre
	y[0] = PosMatrix[12];				// [m]
	z[0] = PosMatrix[13];				// [m]
	x[0] = PosMatrix[14];				// [m]
		
	
	for (i = 0; i < 4; i++)
		ei[i] = 0;
	for (i = 0; i < 4; i++)
		ei2[i] = 0;

	printf("Fin initialisation\n\n");
	
	robot_step((int)(Dt*1000));
	time = time + Dt;

/*************************************************************************************************
 Boucle de contrôle infinie : the robot never dies !
*************************************************************************************************/
	for(;;)
	{
/*************************************************************************************************
 Lecture de la position du robot dans l'espace par le GPS
*************************************************************************************************/
		// GPS
		PosMatrix = gps_get_matrix(gps1);
		        
		// Compute Rotation Matrix MW
		MW11 = PosMatrix[0]; MW12 = PosMatrix[1]; MW13 = PosMatrix[2];
		MW21 = PosMatrix[4]; MW22 = PosMatrix[5]; MW23 = PosMatrix[6];
		MW31 = PosMatrix[8]; MW32 = PosMatrix[9]; MW33 = PosMatrix[10];

		display_matrix();

		// Calcul des angles d'Euler correspondants
		psi[1] = asin(-MW13);					// [rad]
		phi[1] = asin(MW12/cos(psi[1]));		// [rad]
		theta[1] = asin(MW23/cos(psi[1]));		// [rad]

		// Calcul des vitesses angulaires correspondantes (approximation linéaire)
		dphi = (phi[1] - phi[0]) / Dt;			// [rad/s]
		dpsi = (psi[1] - psi[0]) / Dt;			// [rad/s]
		dtheta = (theta[1] - theta[0]) / Dt;	// [rad/s]
		
		// Position du robot par rapport au référentiel terrestre
		y[1] = PosMatrix[12];					// [m]
		z[1] = PosMatrix[13];					// [m]
		x[1] = PosMatrix[14];					// [m]

		// Calcul des vitesses par rapport au référentiel terrestre (approximation linéaire)
		dx = (x[1] - x[0])  / Dt;				// [m/s]
		dy = (y[1] - y[0])  / Dt;				// [m/s]
		dz = (z[1] - z[0])  / Dt;				// [m/s]
		
		display_position_vitesse();
		
/*************************************************************************************************
 Régulateur PID : contrôle de l'altitude
 - entrée : consigne de position zd, position actuelle z[1] et vitesse actuelle dz
 - sortie : somme des forces de portance U1
 - paramètres : Kp1,Td1,Ti1,U01

 Régulateur PID2 : contrôle de l'orientation phi (roulis ou tangage)
 - entrée : consigne d'orientation phid, orientation actuelle phi[1] et vitesse angulaire 
   actuelle dphi
 - sortie : moment de force U2
 - paramètres : Kp2,Td2,Ti2,U02

 Régulateur PID3 : contrôle de l'orientation theta (roulis ou tangage)
 - entrée : consigne d'orientation thetad, orientation actuelle theta[1] et vitesse angulaire 
   actuelle dtheta
 - sortie : moment de force U3
 - paramètres : Kp3,Td3,Ti3,U03

 Régulateur PID4 : contrôle de l'orientation psi (lacet)
 - entrée : consigne d'orientation psid, orientation actuelle psi[1] et vitesse angulaire 
   actuelle dpsi
 - sortie : moment de force U4
 - paramètres : Kp4,Td4,Ti4,U04
*************************************************************************************************/
		U[0] = regulateur(0, zd, z[1], dz);
		U[1] = regulateur(1, phid, phi[1], dphi);
		U[2] = regulateur(2, thetad, theta[1], dtheta);
		U[3] = regulateur(3, psid, psi[1], dpsi);

		// Calcul des vitesses correspondant aux 4 consignes U1,U2,U3 et U4
		vpu[0] = sqrt((0.5*(U[0]+U[1]-U[2])*(c[1]+c[3])-c[3]*U[1]-c[2]*U[2]-U[3]) / (b[0]*c[4]));
		vpu[1] = sqrt((0.5 * (U[0]+U[1]-U[2]) -  b[0]*vpu[0]*vpu[0]) / b[1]);
		vpu[2] = sqrt((U[2] + b[0]*vpu[0]*vpu[0]) / b[2]);
		vpu[3] = sqrt((b[1]*vpu[1]*vpu[1]) / b[3]);
		
		display_regulateur_output();

/*************************************************************************************************
 Limitation des commandes au niveau de la vitesse des moteurs : c'est plus facile à estimer au
 niveau de vp1,vp2,vp3 et vp4 qu'au niveau de U1,U2,U3 et U4
 Entrées :	- vpu = vitesse désirée par le régulateur
			- vp = vitesse actuelle des hélices
*************************************************************************************************/		
		// Pas de limitation
		/*
		for (i = 0; i< 4; i++)
			vp[i] = vpu[i];
		*/

		/****** Limitation 1 : accélération max du moteur *****/
		// Approximation (linéaire) de l'accélération commandée par la sortie du régulateur
		// Accélération mot = (vmotu - vmot)/Dt = ((vpu - vp)*r)/Dt
		for (i = 0; i < 4; i++)
		{
			a = ((vpu[i] - vp[i]) * r) / Dt;
			printf("a = %f [rad/s2]\n",a);
			if ((a > amax) || (a < -amax))
			{
				limit = 1;
				printf("Limitation acceleration moteur %d\n", i+1);
				if (a > 0)
					vpu[i] = vp[i] + (amax * Dt) / r;
				else
					vpu[i] = vp[i] - (amax * Dt) / r;
			}
		}
		printf("\n");

		/****** Limitation 2 : vitesse max du moteur *****/
		printf("Vitesses apres limitation due a l'accélération des moteurs\n");
		display_limite();

		// Limitation 2 : vitesse max du moteur
		for (i = 0; i < 4; i++)
		{
			if (vpu[i] > vmax/r)
			{
				limit = 1;
				printf("Limitation vitesse moteur %d\n", i+1);
				vpu[i] = vmax/r;
			}
		}
		printf("\n");

		printf("Vitesses apres limitation due a la vitesse max des moteurs\n");
		display_limite();
		
		// Vitesse à appliquer aux moteurs : vpu --> vp
		for (i = 0; i < 4; i++)
			vp[i] = vpu[i];

		/***** Une limite a-t-elle été atteinte ? Si oui, il faut recalculer les forces
		       à appliquer au robot, car U1...U4 ne sont plus valables *****/
		if (limit == 1)
		{
			// U1 = b1*vp1*vp1 + b2*vp2*vp2 + b3*vp3*vp3 + b4*vp4*vp4
			U[0] = 0;
			for (i = 0; i < 4; i++)
				U[0] = U[0] + b[i]*vp[i]*vp[i];
			// U2 = b2*vp2*vp2 - b4*vp4*vp4
			U[1] = b[1]*vp[1]*vp[1] - b[3]*vp[3]*vp[3];
			// U3 = b3*vp3*vp3 - b1*vp1*vp1
			U[2] = b[2]*vp[2]*vp[2] - b[0]*vp[0]*vp[0];
			// U4 = d2*vp2*vp2 + d4*vp4*vp4 - d1*vp1*vp1 - d3*vp3*vp3
			U[3] = d[1]*vp[1]*vp[1] + d[3]*vp[3]*vp[3] - d[0]*vp[0]*vp[0] - d[2]*vp[2]*vp[2];
		}

		printf("Sorties du regulateur Ui corrigees apres limitations dues aux moteurs\n");
		display_regulateur_output();

		limit = 0;
		
/*************************************************************************************************
 Mise à jour et application des forces généralisées par rapport au référentiel du robot
 Les indices x,y et z correspondent au référentiel défini dans le modèle de Samir
 La correction entre les deux référentiels (Samir et Webots) s'effectuent lors de l'application
 des forces par la fonction custom_robot_set_rel_force_and_torque
*************************************************************************************************/
		/***** Moments gyroscopiques *****/
		// Vitesses pour le calcul des moments gyroscopiques
		if (alpha == 0)
		{
			v1 = vp[1] + vp[3] - vp[0] - vp[2];
			v2 = -v1;
			v3 = 0;
		}
		else
		{
			v1 = vp[1] + vp[3] - (vp[0] + vp[2]) * cos(alphar);
			v2 = vp[0] + vp[2] - (vp[1] + vp[3]) * cos(alphar);
			v3 = ((vp[2]-vp[0])*dtheta + (vp[3]-vp[1])*dphi) * sin(alphar);
		}
		tgtheta = Ipr * dtheta * v1;
		tgphi = Ipr * dphi * v2;

		display_gyro();

		/***** Forces de frottements : Frot = k * v * ¦v¦ *****/
		ffrotx = kx * dx * dx;
		ffroty = ky * dy * dy;
		ffrotz = kz * dz * dz;
		if (dx > 0)
			ffrotx = - ffrotx;
		if (dy > 0)
			ffroty = - ffroty;
		if (dz > 0)
			ffrotz = - ffrotz;

		display_frottement();
		
		/***** Forces résultantes totales *****/
		fx = U[2] * sin(alphar) + ffrotx;
		fy = U[1] * sin(alphar) + ffroty;
		fz = U[0] * cos(alphar) + ffrotz;
		tx = U[1] * dp - c[0] * U[2] * sin(alphar) + tgtheta;
		ty = U[2] * dp - c[0] * U[1] * sin(alphar) + tgphi;
		tz = U[3] * cos(alphar) + Ipr * v3;
		
/*************************************************************************************************
 Ajout de perturbations sur l'hélicoptère, sinon c'est pas drôle
 - Couple parasite			: impulsion
 - Couple parasite			: constant pendant x step
 - Force parasite			: impulsion
 - Force parasite			: constant pendant x step
 - Perturbation harmonique	: continue
*************************************************************************************************/
		/***** Couples parasites : impulsion (1 step) *****/
		if (time  > Dt*100 - 0.01  &&  time < Dt*100 + 0.01)
		{
			tx = tx + 0.08;
			ty = ty + 0.04;
			tz = tz + 0.02;
			printf("Couple perturbateur : impulsion\n\n");
		}

		/***** Couples parasites : cst pendant x step *****/
		if (time  > Dt*200 - 0.01  &&  time < Dt*(200+5) + 0.01)
		{
			tx = tx + 0.02;
			ty = ty + 0.04;
			tz = tz + 0.03;
			printf("Couple perturbateur : cst\n\n");
		}

		/***** Forces parasites : impulsion (1 step) *****/
		if (time > Dt*300 - 0.01 && time < Dt*300 + 0.01)
		{
			fx = fx - 1;
			fy = fy - 1;
			fz = fz - 5;
			printf("Force perturbatrice : impulsion\n\n");
		}
		
		/***** Forces parasites : cst pendant x step *****/
		if (time > Dt*400 - 0.01 && time < Dt*(400+3) + 0.01)
		{
			fx = fx - 1;
			fy = fy + 1;
			fz = fz - 1;
			printf("Force perturbatrice : cst\n\n");
		}

		/***** Perturbation de type harmonique *****/
		if (time > Dt*500)
		{
			tx = tx + 0.02 * sin(beta);
			ty = ty + 0.03 * sin(beta);
			fz = fz + 0.01 * sin(beta);
			beta = beta + 0.05;
			printf("Perturbation harmonique\n\n");
		}
		
		display_force();
				
		/***** Application des forces sur le robot *****/
		custom_robot_set_rel_force_and_torque(fy,fz,fx,ty,tz,tx);
				
		/***** Mise à jour des positions et angles d'Euler *****/
		phi[0] = phi[1];
		psi[0] = psi[1];
		theta[0] = theta[1];
		x[0] = x[1];
		y[0] = y[1];
		z[0] = z[1];

		printf("Time = %f\n", time);

		robot_step((int)(Dt*1000)); /* run one step */
		time = time + Dt;
  	}
  	return 0;
}
