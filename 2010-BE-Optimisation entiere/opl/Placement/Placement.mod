/*********************************************
 * OPL 6.3 Model
 * Author: lecrubier
 * Creation Date: 29 juin 2010 at 22:56:08
 *********************************************/

{string} Carte = {"1","2","3","4"};
{string} Panier = {"1","2"};

string NomCarte[Carte] = ["c1","c2","c3","c4"];
string NomPanier[Panier] = ["p1","p2"];

int PuissanceConsommee[Carte] = [20,40,50,75];
int NombreDemande[Carte] = [10,4,2,1];

int PuissanceMaximum[Panier] = [150,200];
int NombreConnexions[Panier] = [8,16];
int Prix[Panier] = [150,200];

//Nombre de carte d un certain type dans les paniers d'un certain type
dvar int+ Nombre[Carte][Panier];
dvar int+ Utilisation[Panier];

minimize 
	sum (p in Panier) 
		Utilisation[p]*Prix[p];

constraints {

	forall (p in Panier) 
		sum(c in Carte) 
			Nombre[c][p] * PuissanceConsommee[c] <= PuissanceMaximum[p] * Utilisation[p];
			
	forall (p in Panier) 
		sum(c in Carte) 
			Nombre[c][p] <= NombreConnexions[p] * Utilisation[p];
	
	forall (c in Carte) 
		sum(p in Panier)
			Nombre[c][p] >= NombreDemande[c];
};

execute {

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
