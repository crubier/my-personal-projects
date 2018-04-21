/*********************************************
 * OPL 6.3 Model
 * Author: lecrubier
 * Creation Date: 29 juin 2010 at 21:48:28
 *********************************************/

using CP;

//Dimensions du tableau
int N = 9;
//Intervalle associé
range Rn = 1..N;

//Nombre de couleurs
int C=3;
//Intervalle associé
range Rc = 0..C;

//Tableau de travail
dvar int cellule[Rn,Rn] in Rc;

constraints {
 	//On choisit les coordonnées des points selon l axe X
	forall ( ordered x1,x2 in Rn ) {
		//On choisit les coordonnées des points selon l axe Y
		forall (ordered y1,y2 in  Rn) {
			//Cette conjonction de trois contraintes suffit, la quatrieme serait superflue.
			(cellule[x1,y1] != cellule[x1,y2]) || (cellule[x1,y1] != cellule[x2,y2]) || (cellule[x1,y1] != cellule[x2,y1]);
		}
	}
}


execute {
	for(var y in Rn) {
		for(var x in Rn) {
			//On imprime le contenu de la cellule
			write ( cellule[x][y]);
		}
		//On passe a la ligne en fin de ligne
		writeln();
	}
}
