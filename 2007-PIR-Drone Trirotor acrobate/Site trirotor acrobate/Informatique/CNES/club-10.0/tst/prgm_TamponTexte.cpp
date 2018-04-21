////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//        DEF
//
//$Projet
//        CHOPE
//
//$Application
//        Club
//
//$Nom
//>       prgm_TamponTexte.cc
//
//$Resume
//       fichier de test de la classe TamponTexte
//
//$Description
//       Module de test de la classe avec sauvegarde des
//       resultats dans un fichier .sortie pour la comparaison
//       avec un fichier de reference .ref
//
//$Contenu
//>       int main()
//$Historique
//       $Log: prgm_TamponTexte.cpp,v $
//       Revision 3.15  2001/06/21 15:21:40  club
//       correction d'une signature de directive catch
//
//       Revision 3.14  2000/10/25 09:10:39  club
//       modification des includes du standard C++ : suppression du ".h" dans le
//       nom du fichier inclus.
//
//       Revision 3.13  2000/10/24 14:23:12  club
//       ajout de l'include ClubConfig.h et des tests de configuration.
//
//       Revision 3.12  2000/10/24 08:36:34  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 3.11  2000/09/07 08:35:52  club
//       utilisation de string de la STL au lieu de ChaineSimple.
//       mise à jour du cartouche.
//
//       Revision 3.10  1999/07/07 08:33:31  club
//       *** empty log message ***
//
//       Revision 3.9  1999/07/07 08:12:38  club
//       adaptation a la gestion des erreurs par
//       mecanisme d'exception.
//
//       Revision 3.8  1999/06/01 15:01:55  club
//       ajout d'un test sur la construction d'un TamponTexte vide
//
//       Revision 3.7  1999/03/15 15:51:22  club
//       ajout du cartouche et de l'initialisation de BaseErreurs avec utilisation
//       des exceptions
//
//$Version
//       $Id: prgm_TamponTexte.cpp,v 3.15 2001/06/21 15:21:40 club Exp $
//$Auteur
//        P-A.Cros   CSSI
//        M. Julien  CSSI 
//        O. Queyrut CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/TamponTexte.h"
#include "club/ClubErreurs.h"

int main (int argc, char **argv)
{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

 try {

  if (argc != 2)
  { cerr << "usage : prgm_TamponTexte répertoire" << endl;
    return 1;
  }
  string repertoire (argv [1]);

  //mise en place de la gestion des exceptions
  BaseErreurs::initErreurs(NULL,NULL,1);

  // ouverture du tampon
  TamponTexte tampon ((repertoire + "/test_TamponTexte.don").c_str ());

  // tampon avant traitement
  cout << "avant filtrage, le tampon comporte "
    << tampon.nombreLignes () << " lignes\n";
  cout << "-------------------------------------------------------\n";
  cout << tampon.total ();
  cout << "-------------------------------------------------------\n";

  // filtrage du tampon
  try {
    tampon.elimineCommentaires ();
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
    tampon.elimineBlancs       ();
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  cout << "filtrage effectue\n";

  // test du tampon
  if (tampon.estVide ())
  { cout << "le tampon " << tampon.nom () << " est vide\n";
    return 0;
  }

  // acces global
  cout << "vision globale du tampon: " << tampon.nom () << endl;
  cout << "-------------------------------------------------------\n";
  cout << tampon.total ();
  cout << "-------------------------------------------------------\n";

  // acces par lignes
  cout << endl << endl << endl;
  cout << "vision par lignes du tampon: " << tampon.nom () << endl;
  cout << "nombre de lignes: " << tampon.nombreLignes () << endl;
  int i;
  for (i = tampon.nombreLignes () + 1; i >= 0; i--)
  { 

    try
    { 
      (void)tampon.ligne(i); // peut lever une exception (compatibilite)
      cout << "ligne " << i << ":\n";
      cout << "----------" << tampon.ligne (i) << "----------\n";
    }
    catch(ClubErreurs ce)
    {
      cout << ce.why () << endl;
      ce.correction ();
    }   
  }

  // acces par lignes et par champs
  cout << endl << endl << endl;
  cout << "vision par lignes et champs du tampon: "
       << tampon.nom () << endl;
  cout << "nombre de lignes: " << tampon.nombreLignes () << endl;
  for (i = tampon.nombreLignes (); i >0; i--)
  { 
    try{

      cout << "nombre de champs de la ligne " << i << ": "
           << tampon.nombreChampsLigne (i) << endl;

      for (int j = 0; j <= tampon.nombreChampsLigne (i) + 1; j++)
      { 

        try{
          (void)tampon.champLigne(j,i); // peut lever une exception
          cout << "champ " << j << " de la ligne " << i << ":\n";
          cout << "----------" << tampon.champLigne (j, i) << "----------\n";
        }
        catch(ClubErreurs ce)
        {
          cout << ce.why () << endl;
          ce.correction ();
        } 
      }
    }
    catch(ClubErreurs ce)
    {
      cout << ce.why () << endl;
      ce.correction ();
    }      
  }

  // acces par champs
  cout << endl << endl << endl;
  cout << "vision par champs du tampon: " << tampon.nom () << endl;
  cout << "nombre de champs: " << tampon.nombreChamps () << endl;
  for (i = tampon.nombreChamps () + 1; i >= 0; i--)
  { 
    try{
      (void)tampon.champ(i); // peut lever une exception
      cout << "champ " << i << ":\n";
      cout << "----------" << tampon.champ (i) << "----------\n";
    }
    catch(ClubErreurs ce)
    {
      cout << ce.why () << endl;
      ce.correction ();
    }
  }

  // routines d'insertion
  try{
    tampon.insereAAdresse ((char *) tampon.total () + 2,
                           "<insertion adresse 2>");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }
  
  try{
  tampon.insereDebutLigne (2, "<insertion debut ligne 2>");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
  tampon.insereFinLigne   (2, "<ajout fin ligne 2>");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
  tampon.insereAvantChampLigne (-1, 3,
                                "<insertion avant champ -1, ligne 3>");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
  tampon.ajouteApresChampLigne (2, 3,
                                "<ajout apres champ 2, ligne 3>");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
    tampon.ajouteALaFin ("<ajout a la fin>\n");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
    tampon.insereAvantChamp (tampon.nombreChamps () - 3,
                             "<insertion avant champ n-3>");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
    tampon.ajouteApresChamp (tampon.nombreChamps (),
                             "<ajout apres champ n>");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  // routines de suppression
  try{
    tampon.elimineLigne (1);
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
    tampon.elimineChampLigne (4, 2);
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }
  try{
    tampon.elimineChamp (tampon.nombreChamps () - 2);
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  // routines de remplacement

  try{
    tampon.ajouteALaFin ("aaa bbb cc dd\"\\t\"dd#commentaire\ne e\ne e\n");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
    tampon.elimineCommentaires ();
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
  tampon.remplaceLigne (tampon.nombreLignes () - 1,    "EEEE EEEE");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
  tampon.remplaceChampLigne (2, tampon.nombreLignes () - 2, "\"BBB\"");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }


  try{
    tampon.remplaceChamp      (tampon.nombreChamps () - 1,    "X");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }

  try{
    tampon.ecrit ("test_TamponTexte.sortie");
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why () << endl;
    ce.correction ();
  }
 }
 catch(ClubErreurs ce)
 {// impossibilite de creer le tampon
   cout <<ce.why()<<endl;
   ce.correction();
 }

  return 0;

}
