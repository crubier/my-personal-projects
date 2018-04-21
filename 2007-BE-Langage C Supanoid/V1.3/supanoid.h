#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <string.h>

#include "graphic.h"

#define LONGCHAINE (256)           				// La longueur max des chaines de caracteres
#define NBPARAM (32)							// Le nombre maximal de parametres pouvant etre passes lors d'une commande
#define EPSILON (0.001)							// Le reel infiniment petit permettant de definir l'egalite de 2 reels
#define COUCHES (8)								// Le nombre de couches d'objets dans le jeu
#define VIDE ""									// La chaine de caractere vide, utilisee a la place de NULL pour les char* afin d'eviter les plantages.

// Les differentes formes d'un objet sont dans le type FORME
typedef enum {INCONNUE, RECTANGLE, CERCLE, RAQUETTE} FORME;

// Les differentes couleurs d'un objet (en français) sont dans le type COULEUR
typedef enum { BLANC, NOIR, ROUGE, BLEU, VERT, JAUNE, CYANFR, GRIS, MAGENTAFR, ORANGEFR, ROSE } COULEUR;

// Les differents modes de fonctionnement sont dans le type MODE
typedef enum { NORMAL, DEBUG, SANSECHEC, PASAPAS } MODE;

// La structure CHAINELISTE pour creer des listes chainees de chaines de caracteres
typedef struct chainelistestruct
{
		char* nom;
 		char* chaine;							// la chaine dans la table
		struct coordstruct* suivant;			// la cellule suivante
} CHAINELISTE, *PTRCHAINELISTE;

// La structure COORD permet de representer les vecteurs en 2D : un doublet de reels
typedef struct coordstruct
{
 		float x;								// la composante selon x (horizontal)
		float y;								// la composante selon y (vertical)
} COORD, *PTRCOORD;

// La structure IDENTIFIANT permet d'identifier chaque cellule de maniere unique sans passer par un pointeur, afin de permettre a l'utilisateur d'acceder a chaque cellule individuellement
typedef struct identifiantstruct
{
      	char* type;								// type represente le 'nom de famille' de l'objet
        char* nom;								// nom represente son nom plus precis
  		int numero;								// numero represente un numero permettant d'indexer les objets similaires
} IDENTIFIANT, *PTRIDENTIFIANT;

// La strucure OBJET permet de définir les caracteristiques visibles des objets associes aux cellules
typedef struct objetstruct
{

        COORD position;							// vecteur position
 		COORD vitesse;							// vecteur vitesse
 		COORD acceleration;						// vecteur acceleration
 		int couche;								// la couche dans laquelle se trouve l'objet(voir dossier)

 		FORME forme;							// sa forme
 		COORD dimensions;						// un vecteur representant sa taille
 		float masse;							// sa masse (utile lors des rebonds en particulier)
 		float frottement;						// un coefficient de frottement par rapport au repere fixe
 		float rebondissement;					// une constante de 'rebondissement' lors de contacts avec d'autres objets
 		float solidite;							// sa solidite representant le nombre d'agressions qu'il peut subir avant de disparaitre
 		float attraction;						// un coefficient d'attraction ou de repulsion s'il est negatif
 		float agressivite;						// une constante d'agressivite permettant de faire varier les dommages infliges par l'objet aux objets qu'il rencontre

 		char* graphique;						// une chaine de caractere indiquant l'image associee a l'objet
        char* texte;							// une chaine de caractere indiquant le texte affiche sur l'objet
        COULEUR couleur;						// sa couleur
		float chronometre;						// un chronometre pour declencher des actions

 		
} OBJET, *PTROBJET;

// La structure CELLULE est la base de la liste chainee contenant les objets
typedef struct cellulestruct
{
 		struct objetstruct* element; 			// un pointeur vers l'objet represente par la cellule
 		struct identifiantstruct* identifiant;	// un pointeur vers l'identifiant theoriquement unique representant la cellule et son contenu
		struct cellulestruct* suivant; 			// un pointeur vers le prochain element de la liste
		struct cellulestruct* precedent;		// un pointeur vers l'element precedent de la liste
} CELLULE, *PTRCELLULE;


/*VARIABLES GLOBALES*/
PTRCELLULE origineliste;						// pointe vers le premier element CELLULE de la liste chainee des objets
PTRCELLULE fenetre;								// pointe vers l'objet fenetre contenu dans la liste (raccourci)
PTRCELLULE raquette;							// pointe vers l'objet raquette contenu dans la liste (raccourci)
PTRCELLULE focus;								// pointe vers l'objet suivi par la fenetre de jeu (le plus souvent l'objet fenetre immobile a l'origine)

int fini;										// une variable definissant si la boucle de jeu se termine
FILE* journal;									// le fichier log pouvant permettre le debogage des scripts utilisateur et la comprehension des erreurs
char repertoire[LONGCHAINE];					// le repertoire dans lequel se trouve le niveau joue

float DT;										// le pas de temps du jeu en secondes
float SENSIBILITE;								// la sensibilite au deplacement de la raquette et de la fenetre
float ATTRACTION;								// la 'constante de gravitation'
int modefonctionnement;							// le mode de fonctionnement 0=normal, 1=debug, 2=debug+pauses

/*=======================================================*/
/*                   Actions.c                           */
/*=======================================================*/
/* Ce fichier contient certaines fonctions relatives     */
/* aux actions que l'utilisateur peut effectuer          */
/* Ces fonctions sont appellees depuis la fonction       */
/* executercommande dans commandes.c.                    */
/* D'autres fonctions plus simples relatives aux actions */
/* sont integrées dans la fonction executercommande      */
/*=======================================================*/

//jouer un fichier(le plus souvent un son)
void action_jouer(char* chaine);

//charger un fichier(le plus souvent un son)
void action_charger(char* chaine);

//creer un objet
void action_creerobjet(char* chaine);

//supprimer un objet
void action_supprimerobjet(char* chaine);

//modifier les proprietes d'un objet
void action_modifierpropriete(char* chaine);

//initialiser le niveau
void action_initialiser(char* chaine);

//afficher le nom des objets(debug)
void action_affichernoms(char* chaine);

//cacher le nom des objets(debug)
void action_cachernoms(char* chaine);

//executer un fichier
void action_executer(char* chaine);

//imprimer un texte dans la console
void action_ecrire(char* chaine);

//modifier une variable globale du jeu (DT, SENSIBILITE, ATTRACTION, mode ...)
void action_modifierparametre(char* chaine);


/*=======================================================*/
/*                   Geometrie.c                         */
/*=======================================================*/
/* Ce fichier contient les fonctions de base de la       */
/* géometrie, en s'appuyant principalement sur           */
/* le TDA 'COORD' et les reels                           */
/* Ces fonctions sont principalement utilisees par       */
/* le moteur physique, mais peuvent aussi etre appelees  */
/* par l'utilisateur                                     */
/*=======================================================*/

// generer un vecteur a partir de deux reels
COORD vecteur(float x, float y);

// generer un vecteur a partir de coordonnes polaires
COORD polaire2cartesien(COORD a);

// generer les coordonnes polaires d un vecteur en coordonnees cartesiennes
COORD cartesien2polaire(COORD a);

// somme de deux vecteurs
COORD somme(COORD a, COORD b);

// oppose d'un vecteur
COORD oppose(COORD a);

// difference de deux vecteurs
COORD difference(COORD a, COORD b);

// inverse d'un vecteur
COORD inverse(COORD a);

// multiplication des composantes de deux vecteurs
COORD multiplication(COORD a, COORD b);

// multiplication des composantes d'un vecteur par un scalaire
COORD multiplicationscalaire(COORD a, float k);

// produit scalaire de deux vecteurs
float produitscalaire(COORD a, COORD b);

// normalisation d'un vecteur (norme ramenee a 1)
COORD normalisation(COORD a);

// distance en les extremites de deux vecteurs
float distance(COORD a, COORD b);

// norme d'un vecteur
float norme(COORD a);

// somme des deux composantes d'un vecteur
float total(COORD a);

// arrondi des coordonnes d'un vecteur
COORD arrondi(COORD a);


/*=======================================================*/
/*                   Interface.c                         */
/*=======================================================*/
/* Ce fichier contient les fonctions liees a l'interface */
/* utilisateur, c'est a dire les fonctions d'affichage   */
/* et de verification des touches activees               */
/*=======================================================*/

// mettre le jeu en pause
void pause(void);

// dessiner tout les objets
void dessin(void);

// reperer les touches appuyees et agir en consequence
void clavier(void);

// dessiner un objet
void dessiner(PTRCELLULE pcellule);

// ecrire le contenu de la liste chainee dans le journal
void decrireLISTE(void);

// ecrire le contenu d'une cellule dans le journal
void decrireCELLULE(PTRCELLULE pcellule);

// ecrire le contenu detaille (avec le contenu des objet et leurs proprietes) de la liste chainee dans le journal
void decrireLISTEdetail(void);

// initialiser le jeu
void initialisation(void);

// fermer le jeu
void cloture(void);

// initialiser le moteur graphique du jeu
void initialisationgraphique(void);

// fermer le moteur graphique du jeu
void cloturegraphique(void);


/*=======================================================*/
/*                   Manipulations.c                     */
/*=======================================================*/
/* Ce fichier contient toutes les fonction concernant    */
/* la gestion des listes, des cellules, de leur contenu  */
/* (objets et identifiant), la modification des          */
/* parametres , la recherhce d'elements etc...           */
/*=======================================================*/

// MANIPULATION DU TDA OBJET

// creation a partir de ses proprietes
PTROBJET creerobjet
(
        COORD position,
 		COORD vitesse,
 		COORD acceleration,
 		int couche,

 		FORME forme,
 		COORD dimensions,
 		float masse,
 		float frottement,
 		float rebondissement,
 		float attraction,
 		float solidite,
 		float agressivite,

 		char* graphique,
        char* texte,
        COULEUR couleur,
		float chronometre
);

// copie a partir d'un pointeur
PTROBJET copierobjet(PTROBJET pobjet);

// creation d'un objet par defaut
PTROBJET nouvelobjet(void);

// suppression
void supprimerobjet(PTROBJET pobjet);


// MANIPULATION DU TDA IDENTIFIANT

// creation a partir de ses proprietes
PTRIDENTIFIANT creeridentifiant
(
 		char* type,
        char* nom,
        int numero
);

// copie a partir d'un pointeur
PTRIDENTIFIANT copieridentifiant(PTRIDENTIFIANT pidentifiant);

// creation d'un identifiant par defaut
PTRIDENTIFIANT nouvelidentifiant(void);

// suppression
void supprimeridentifiant(PTRIDENTIFIANT pidentifiant);


// Manipulation du TDA CHAINELISTE

PTRCHAINELISTE creerchaineliste
(
	char* nom,
	char* chaine,
	PTRCHAINELISTE suivant
);
void lierchaineliste(PTRCHAINELISTE originechaineliste,PTRCHAINELISTE element);
PTRCHAINELISTE longueurchaineliste(PTRCHAINELISTE originechaineliste);
PTRCHAINELISTE chainelisteelementnumero(PTRCHAINELISTE originechaineliste, int i);
PTRCHAINELISTE chainelistepremierelement(PTRCHAINELISTE originechaineliste);
PTRCHAINELISTE chainelistedernierelement(PTRCHAINELISTE originechaineliste);
PTRCHAINELISTE nouvellechaineliste(void);
void supprimerchaineliste(PTRCHAINELISTE pchaineliste);

// creation a partir de ses proprietes
PTRCHAINELISTE creerchaineliste
(
	char* chaine,
	PTRCHAINELISTE suivant
);

// creation par defaut
PTRCHAINELISTE nouvellechaineliste(void);

PTRCHAINELISTE longueurchaineliste(PTRCHAINELISTE originechaineliste);
PTRCHAINELISTE chainelisteelementnumero(PTRCHAINELISTE originechaineliste, int i);

// suppression
void supprimerchaineliste(PTRCHAINELISTE pchaineliste);

// MANIPULATION DU TDA CELLULE

// creation a partir de ses proprietes
PTRCELLULE creercellule
(
    PTROBJET element, 
 	PTRIDENTIFIANT identifiant,
	PTRCELLULE suivant,
	PTRCELLULE precedent
);

// copie a partir d'un pointeur
PTRCELLULE copiercellule(PTRCELLULE pcellule);

// creation d'une cellule par defaut
PTRCELLULE nouvellecellule(void);

// suppression
void supprimercellule(PTRCELLULE pcellule);

// annexes
void liercellules(PTRCELLULE pcellulea, PTRCELLULE pcelluleb);
void verifiercellules(PTRCELLULE pcellulea, PTRCELLULE pcelluleb);
void verifierpointeur(char* p);


// FONCTIONS DE RECHERCHE

// premiere cellule de la liste chainee
PTRCELLULE premierecellule(void);

// derniere cellule de la liste chainee
PTRCELLULE dernierecellule(void);

// recherche de la cellule associee a un identifiant
PTRCELLULE rechercher(PTRIDENTIFIANT pidentifiant);

// recherche de la cellule numero i dans la liste chainee
PTRCELLULE cellulenumero(int i);

// nombre de celllules dans la liste chainee
int nombrecellules(void);

// prochaine indexation de l'identifiant en fonction de son type et de son nom
PTRIDENTIFIANT prochainidentifiant(PTRIDENTIFIANT pidentifiantdepart);

// nombre de cellule de type correspondant a l'identifiant
int nombretype(PTRIDENTIFIANT pidentifiant);

// nombre de cellule de type et nom correspondant a l'identifiant
int nombretypenom(PTRIDENTIFIANT pidentifiant);

// nombre de cellule de type, nom et numero correspondant a l'identifiant (normalement 1 seule car l'identifiant est unique)
int nombretypenomnumero(PTRIDENTIFIANT pidentifiant);

// recherche des cellules de type correspondant a l'identifiant
PTRCELLULE recherchertype(PTRIDENTIFIANT pidentifiant,  PTRCELLULE pi, int sens);

// recherche des cellules de type et nom correspondant a l'identifiant
PTRCELLULE recherchertypenom(PTRIDENTIFIANT pidentifiant,  PTRCELLULE pi, int sens);

// recherche des cellules de type, nom et numero correspondant a l'identifiant
PTRCELLULE recherchertypenomnumero(PTRIDENTIFIANT pidentifiant,  PTRCELLULE pi, int sens);

// comparaison des types de deux identifiants
int compareridentifiantstype(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb);

// comparaison des types et noms de deux identifiants
int compareridentifiantstypenom(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb);

// comparaison des types, noms et numeros de deux identifiants
int compareridentifiantstypenomnumero(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb);

// creation d'une chaine de caractere de longueur appropriee a la chaine
char* creerchaine(char* chaine);
void supprimerchaine(char* chaine);
char* modifierchaine(char* anciennechaine,char* nouvellechaine);

// transformation d'un entier en chaine et inversement
int lireint(char* chaine);
char* ecrireint(int a);

// transformation d'un reel en chaine et inversement
float lirefloat(char* chaine);
char* ecrirefloat(float a);

// transformation d'un vecteur en chaine et inversement
COORD lireCOORD(char* chaine);
char* ecrireCOORD(COORD a);

// transformation d'une FORME en chaine et inversement
FORME lireFORME(char* chaine);
char* ecrireFORME(FORME a);

// transformation d'une COULEUR en chaine et inversement
COULEUR lireCOULEUR(char* chaine);
char* ecrireCOULEUR(COULEUR a);

// transformation d'un IDENTIFIANT en chaine et inversement
IDENTIFIANT lireIDENTIFIANT(char* chaine);
char* ecrireIDENTIFIANT(IDENTIFIANT a);

// ecriture d'une chaine representant la liste chainee
char* ecrireLISTE(void);

// recherhce de l'objet d'identifiant represente dans une chaine
PTRCELLULE lireOBJET(char* chaine);

// ecriture d'une chaine representant un objet
char* ecrireOBJET(OBJET a);

// modifier la propriete d'un objet
void entrerpropriete(PTRCELLULE pcellule, char* propriete, char* valeur);

// afficher la propriete d'un objet
char* afficherpropriete(PTRCELLULE pcellule, char* propriete);

// modifier un parametre du jeu
char* afficherparametre(char* chaine);


/*=======================================================*/
/*                       Physique.c                      */
/*=======================================================*/
/* Ce fichier contient le moteur physique du jeu, cad    */
/* la gestion des collisions, des différentes couches,   */
/* de l'attraction entre les objets, les rebonds etc...  */
/*=======================================================*/

// executer le mouvements d'un objet
void mouvement(PTROBJET objet);

// executer les mouvements de tout les objets
void mouvements(void);

// calculer la position suivante d'un objet
OBJET positionsuivante(OBJET objet);

// calculer le rebond de deux objets
void rebond(PTRCELLULE pcellulea, PTRCELLULE pcelluleb);

// calculer l'interaction gravitationelle de deux objets
void gravitation(PTRCELLULE pcellulea, PTRCELLULE pcelluleb);

// calculer le frottement applique a un objet
void frottement(PTRCELLULE pcellule);

// gerer la degradation d'un objet par les chocs
void degradation(PTRCELLULE pcellule);

// gerer le chrnonometre integre dans chaque cellule
void chronometrer(PTRCELLULE pcellule);

// calculer la normale de contact entre deux ojets (utilisee pour les rebonds)
COORD normalecontact(OBJET objeta, OBJET objetb);

// calculer la position relative de deux ojets (utilisee pour la gravitation)
COORD positionrelative(OBJET objeta, OBJET objetb);

// calculer toutes les interactions de tous les objets
void interactions(void);


/*=======================================================*/
/*                   Commandes.c                         */
/*=======================================================*/
/* Ce fichier contient les fonctions relatives aux       */
/* commandes donnees par l'utilisateur, l'interpretation,*/
/* l'execution, l'appel à des sous commandes etc...      */
/*=======================================================*/

// transformer un fichier en chaine de caracteres formatee
char* fichier2chaine(FILE* fichier)

// calculer la longueur d'un fichier
int longueurfichier(FILE* fichier)

// classer les parametres d'une ligne de commande brute dans une table
char* lireligne(char* lignecommande);

// executer les sous commandes de arguments d'une commande
void executerargument(PTRCHAINELISTE arguments, PTRCHAINELISTE argumentsfichierparent, int a, int b);

// executer les commandes comprises dans un fichier
char* executerfichier(char* parametres);

// executer une commande sous forme de chaine de caracteres
char* executercommande(char* lignecommande,char* argumentsfichierparent);

// demander a l'utilisateur les parametres manquants
void demanderparametres(int argc, char *argv[]);
