/*********************************************
 * OPL 6.3 Model
 * Author: lecrubier
 * Creation Date: 29 juin 2010 at 22:56:08
 *********************************************/


//Nombre de modeles de paniers
int NBPANIERS = ...;
//Intervalle associe
range Panier = 0..(NBPANIERS-1);
//Nom des modeles de paniers
string NomPanier[Panier] = ...;
//Puissance maximum delivree par chaque modele de panier
int PuissanceMaximum[Panier] = ...;
//Nombre de connexions disponibles par panier
int NombreConnexions[Panier] = ...;
//Prix de chaque panier
int Prix[Panier] = ...;



//Nombre de modèles de cartes
int NBCARTES = ...;
//Intervalle associe
range Carte = 0..(NBCARTES-1);
//Noms des modeles de cartes
string NomCarte[Carte] = ...;
//Puissance consomme par les cartes
int PuissanceConsommee[Carte] = ...;
//Nombre de cartes de chaque type a placer
int NombreDemande[Carte] = ...;



//Nombre de carte d un certain type dans les paniers d'un certain type
dvar int+ Nombre[Carte][Panier];

//Nombre de paniers de chaque type utilise
dvar int+ Utilisation[Panier];



//On minimise le prix total qui est la somme des prix des paniers fois leur quantite
minimize 
	sum (p in Panier) 
		Utilisation[p]*Prix[p];



//Contraintes
constraints {

	//Contrainte sur la puissance consommee dans chaque panier
	forall (p in Panier) 
		sum(c in Carte) 
			Nombre[c][p] * PuissanceConsommee[c] <= PuissanceMaximum[p] * Utilisation[p];
			
	//Contrainte sur le nombre de connexions pour chaque panier
	forall (p in Panier) 
		sum(c in Carte) 
			Nombre[c][p] <= NombreConnexions[p] * Utilisation[p];
	
	//Toutes les cartes doivent êtres placées
	forall (c in Carte) 
		sum(p in Panier)
			Nombre[c][p] >= NombreDemande[c];
};

execute {
//On imprime le resultat de maniere un peu plus conviviale
	for(var p in Panier) {
		writeln();
		writeln(Utilisation[p]," x Panier ",NomPanier[p], " = ",Utilisation[p]," x ",Prix[p],"$ = ", Utilisation[p]*Prix[p],"$");
		writeln();
		writeln("					Quantite	Puissance");
		for(var c in Carte) {
			writeln("    Cartes ",NomCarte[c],"		", Nombre[c][p]," / ", NombreConnexions[p]*Utilisation[p],"		", Nombre[c][p]*PuissanceConsommee[c]," / ", PuissanceMaximum[p]*Utilisation[p]);
		};
	};
};
