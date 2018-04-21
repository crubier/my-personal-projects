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
//>       prgm_TamponLigne.cc
//
//$Resume
//        fichier d'implantation du test prgm_TamponLigne
//
//$Description
//       teste les classes TamponAscii et IterateurLigne
//
//$Contenu
//>       int Parcours()              
//>       int Insertion()             
//>       int Suppression()           
//>       int Remplacement()          
//>       int ParcoursCasDegrade()    
//>       int InsertionCasDegrade()   
//>       int SuppressionCasDegrade() 
//>       int RemplacementCasDegrade()
//>       int IterateurInvalide()     
//>       int main()                  
//
//$Historique
//       $Log: prgm_TamponLigne.cpp,v $
//       Revision 1.8  2003/02/07 16:30:49  club
//       DM-ID 18 Optimisation du code (supression de strstream et sstream)
//
//       Revision 1.7  2003/02/03 14:38:20  club
//       DM-ID 12 Mise à jour d'un include selon la norme C++ & mise à jour du code en conséquence
//
//       Revision 1.6  2001/06/21 15:22:46  club
//       correction d'une signature de directive catch
//
//       Revision 1.5  2000/10/25 09:10:39  club
//       modification des includes du standard C++ : suppression du ".h" dans le
//       nom du fichier inclus.
//
//       Revision 1.4  2000/10/24 14:23:12  club
//       ajout de l'include ClubConfig.h et des tests de configuration.
//
//       Revision 1.3  2000/10/24 08:36:34  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 1.2  2000/09/07 08:36:18  club
//       mise à jour du cartouche du fichier.
//
//       Revision 1.1  1999/07/07 08:14:34  club
//       nouveaux programmes pour tester les Iterateurs
//       sur un TamponAscii
//
//$Version
//       $Id: prgm_TamponLigne.cpp,v 1.8 2003/02/07 16:30:49 club Exp $
//$Auteur
//        P-A.Cros  CSSI
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
# include <iostream>
#endif

#include "club/TamponAscii.h"
#include "club/IterateurLigne.h"
#include "club/TamponTexte.h"

int Parcours( TamponAscii &t )
{
  cout << endl << "\t\tPARCOURS" << endl;
  cout << endl << "\t1- Parcours Incremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;

  IterateurLigne itl( t );

  for( itl.premier(); !itl.termine() ; itl++ ){
    cout << itl.valeur() << "," << endl;
  }
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t2- Parcours Decremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;
  int i = itl.nombreIterations();
  itl.dernier();
  while(i){
    cout << itl.valeur() << endl;
    itl--;
    i--;
  }
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t3- Acces direct" << endl;
  cout <<         "\t   ~~~~~~~~~~~~" << endl;
  cout << " valeur de la ligne 10 : " ;
  itl.allerSur( 10 );
  cout << itl.valeur() << endl;
  return 0;
}

int Insertion( TamponAscii &t )
{
  IterateurLigne itl( t );
  cout << endl << "\t\tINSERTIONS" <<endl;
  cout << endl << "\t1- Insertion en debut" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~" << endl;
  cout <<endl <<"insertion du numero de la ligne au debut de chaque ligne.";
  cout << endl;
  char numLig[5]="\0";
  int i=0;
  for( itl.premier(), i = 1; !itl.termine(); itl++, i++ ){
    sprintf(numLig, "%d", i);
    t.insereDebut( itl, numLig );
  }
  cout << endl << "\t2- Insertion en fin" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "insertion de \"HAPPY\" a la fin de la ligne 12 : " << endl;
  itl.allerSur(12);
  t.insereFin( itl, "HAPPY" );
  cout << endl << "~~~~~~~ contenu du tampon apres insertions ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}

int Remplacement(TamponAscii &t )
{
  IterateurLigne itl( t );
  cout << endl << "\t\tREMPLACEMENTS\n" <<endl;
  cout << endl << "\t1- Remplacements simples" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Remplacer la ligne 11  par \"TOTO\"." << endl;  
  itl.allerSur(11);
  t.remplace( itl, "TOTO" );
  cout << endl << "\t2- Remplacements multi-lignes" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Remplacer les lignes 6 a 8  par \"UNE CHAINE\"."<<endl;  
  itl.allerSur( 6 );
  IterateurLigne itl2( t );
  itl2.allerSur( 8 );
  t.remplace( itl, itl2, "UNE CHAINE" );
  cout << endl << "~~~~~~~ contenu du tampon apres remplacements ~~~~~~";
  cout << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}


int Suppression( TamponAscii &t )
{
  cout << endl << "\t\tSUPPRESSIONS\n" <<endl;
  cout << endl << "\t1- Suppression ligne simple" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Supprime la ligne 4." << endl;
  IterateurLigne itl(t);
  itl.allerSur( 4 );
  t.supprime( itl );
  cout << endl << "\t2- Suppression multi-lignes" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Supprime les lignes 5 a 7" << endl;
  itl.allerSur(5  );
  IterateurLigne itl2(t);//sinon -> erreur de synchro
  itl2.allerSur( 7 );
  t.supprime( itl, itl2 );
  cout << endl << "~~~~~~~ contenu du tampon apres suppressions ~~~~~~"<< endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}

int ParcoursCasDegrade( TamponAscii &t )
{
  cout << endl << "\t\tPARCOURS" << endl;
  cout << endl << "\t1- Parcours Incremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;
  IterateurLigne itl(t);
  itl.dernier();
  cout << endl <<"valeur derniere ligne       :" << itl.valeur() << endl;
  itl++;
  cout <<"apres operateur ++          :" << itl.valeur() << endl;
  itl++;
  cout <<"deuxieme appel a operateur++:" << itl.valeur() << endl;
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t2- Parcours Decremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;
  itl.premier();
  cout << endl <<"valeur premiere ligne       :" << itl.valeur() << endl;
  itl--;
  cout <<"apres operateur --          :" << itl.valeur() << endl;
  itl--;
  cout <<"deuxieme appel a operateur--:" << itl.valeur() << endl;
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t3- Acces direct" << endl;
  cout <<         "\t   ~~~~~~~~~~~~" << endl;
  itl.allerSur(1);
  cout << endl <<"acces ligne 1  :" << itl.valeur() << endl;
  try
  {
    cout << "Tentative acces ligne0 " << endl;
    itl.allerSur(0);
    cout <<"acces ligne 0  :" << itl.valeur() << endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout << "Tentative acces ligne -1"<<endl;
    itl.allerSur(-1);
    cout <<"acces ligneE -1 :" << itl.valeur() << endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  itl.allerSur(itl.nombreIterations());
  cout <<"acces ligne "<<itl.nombreIterations()<<" (derniere ligne):";
  cout <<itl.valeur()<<endl;
  try
  {
    cout << "Tentative acces une ligne au dela de la fin du tampon"
         << endl;
    itl.allerSur(itl.nombreIterations()+1);
    cout <<"acces ligne "<<itl.nombreIterations()+1;
    cout <<" (une ligne au-dela de la fin du tampon):"<<itl.valeur()<<endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  return 0;
}


int InsertionCasDegrade( TamponAscii& t)
{
  IterateurLigne itl( t );
  cout << endl << "\t\tINSERTIONS" <<endl;
  cout << endl << "\t1- Insertion en debut" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~" << endl;
  itl.premier();
  cout << endl <<"valeur premiere ligne       :" << itl.valeur() << endl;
  try
  {
    cout << "Insertion avant la ligne 0 de 'It's all rigth'."<< endl;
    itl.allerSur(0);
    t.insereDebut( itl, "It's all right" );
    itl.allerSur(itl.nombreIterations()+3);
    t.insereDebut( itl, "It's funny" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }

  cout << endl << "\t2- Insertion en fin" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~" << endl;
  cout << endl <<"Insertion en fin de la ligne 0 de 'nevermind'."<< endl;
  try
  {
    itl.premier();
    itl.allerSur(0);
    t.insereFin( itl, "nevermind" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout <<"Insertion en fin de la ligne "<< itl.nombreIterations()+3;
    cout << " de 'That's all folks' (3 lignes apres la fin du tampon)" <<endl;
    itl.allerSur(itl.nombreIterations()+3);
    t.insereFin( itl, "That's all folks" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  cout << endl << "~~~~~~~ contenu du tampon apres insertions ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}

int SuppressionCasDegrade( TamponAscii& t )
{
  IterateurLigne itl( t );
  cout << endl << "\t\tSUPPRESSIONS\n" <<endl;
  cout << endl << "\t1- Suppressions ligne simple" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  try
  {
    cout << endl << "suppression de la ligne -1." << endl;
    itl.allerSur(-1);
    t.supprime( itl );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout <<"suppression de la ligne "<< itl.nombreIterations() + 5;
    cout << "(5 lignes apres la fin du tampon)."<< endl;
    itl.allerSur(itl.nombreIterations()+5);
    t.supprime( itl );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  cout << endl ;
  cout << "~~~~~~~ contenu du tampon apres suppressions simples ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "\t2- Suppressions multi-lignes" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "suppression des lignes -1 a 2." << endl;
  IterateurLigne itl2( t );
  try
  {
    itl.allerSur(-1);
    itl2.allerSur(2);
    t.supprime( itl, itl2 );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }

  try
  {
    cout <<"suppression des lignes "<< itl.nombreIterations() - 2;
    cout << " a "<< itl.nombreIterations() + 3;
    cout << "(de 2 lignes avant a 3 apres la fin du tampon)." <<  endl;
    itl.allerSur(itl.nombreIterations()-2);
    itl2.allerSur( itl2.nombreIterations() + 3 );
    t.supprime( itl, itl2 );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }

  try
  {
    cout << endl <<"suppression des lignes 5 a 2 " ;
    cout << "(zone invalide -> pas de suppression)."<<endl;
    itl.allerSur( 5 );
    itl2.allerSur( 2 );
    t.supprime( itl, itl2 );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  cout << endl << "~~~~~~~ contenu du tampon apres suppressions multi-lignes ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}


int RemplacementCasDegrade( TamponAscii& t )
{
  IterateurLigne itl( t );
  cout << endl << "\t\tREMPLACEMENTS\n" <<endl;
  cout << endl << "\t1- Remplacements simples" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~" << endl;
  try
  {
    cout << endl << "remplacer la ligne 0 par 'bug's spirit'." << endl;
    itl.allerSur(0);
    t.remplace( itl, "bug's spirit" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout << endl <<"remplacer la ligne "<< itl.nombreIterations() + 5;
    cout << " par 'no way' (5 lignes apres la fin du tampon)."<< endl;
    itl.allerSur(itl.nombreIterations()+5);
    t.remplace( itl, "no way" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  cout << endl << "~~~~~~~ contenu du tampon apres remplacement simples ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "\t2- Remplacements multi-lignes" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "remplacer les lignes -3 a 2 par 'un test de plus'." << endl;
  IterateurLigne itl2(t);
  try
  {
    itl.allerSur(-3);
    itl2.allerSur(2);
    t.remplace( itl, itl2, "un test de plus" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout << "remplacer les lignes "<< itl.nombreIterations() - 2;
    cout << " a "<< itl.nombreIterations() + 3 << " par 'hocus pocus'";
    cout << " (de 2 lignes avant a 3 lignes apres la fin du tampon)."<< endl;
    itl.allerSur(itl.nombreIterations()-2);
    itl2.allerSur( itl2.nombreIterations() + 3 );
    t.remplace( itl, itl2, "hocus pocus" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout <<"remplacer les lignes 5 a 2 par 'magic circus'.";
    cout <<" (zone de remplacement invalide -> pas de remplacement)."<<endl;
    itl.allerSur( 5 );
    itl2.allerSur( 2 );
    t.remplace( itl, itl2, "magic circus" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  cout << endl << "~~~~~~~ contenu du tampon apres remplacements multi-lignes ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}


int IterateurInvalide( TamponAscii& t )
{
  IterateurLigne itl( t );
  IterateurLigne itl2( t );
  cout << "\t\tITERATEURS INVALIDES\n" <<endl;
  cout << endl << "suppressions de la ligne 3 (iterateur 1)." << endl;
  itl.allerSur(3);
  t.supprime( itl );
  try
  {
    cout << "tentative d'acces a l'element 6 ( iterateur 2 non valide)";
    cout << endl;
    itl2.allerSur(6);
    cout << endl << "cette ligne ne doit pas apparaitre:" 
         << itl2.valeur()<<endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  return 0;
}

int main( int argc, char** argv )
{
  try{
    if( argc != 2 ){
      cerr << "USAGE : " << argv[0] << " <fichier_entree>" << endl;
      return 1;
    }
    TamponAscii        mon_tampon(argv[1]);
    cout << " Contenu initial du tampon : " << endl;
    cout << mon_tampon.total();
    cout << endl << endl;
    cout << endl << "\t------------------------" << endl; 
    cout << endl << "\tTEST FONCTIONNEMENT NOMINAL" << endl;
    cout << endl << "\t------------------------" << endl; 
    Parcours( mon_tampon );
    cout << endl << "\t------------------------" << endl; 
    Insertion( mon_tampon );
    cout << endl << "\t------------------------" << endl; 
    Remplacement( mon_tampon );
    cout << endl << "\t------------------------" << endl; 
    Suppression( mon_tampon );
    cout << endl << "\t------------------------" << endl; 
    cout << endl << "\tTEST FONCTIONNEMENT DEGRADE" << endl;
    cout << endl << "\t------------------------" << endl; 
    ParcoursCasDegrade( mon_tampon  );
    cout << endl << "------------------------" << endl; 
    InsertionCasDegrade( mon_tampon );
    cout << endl << "------------------------" << endl; 
    SuppressionCasDegrade( mon_tampon );
    cout << endl << endl << "------------------------" << endl; 
    RemplacementCasDegrade( mon_tampon );
    cout << endl << "------------------------" << endl; 
    IterateurInvalide( mon_tampon );
    
    cout << endl << "fin du test." << endl; 
  }
  catch(ClubErreurs ce){
    cout << " Si cette ligne apparait, le test a echoue (exception inattendue)"
         << endl;
    cout << ce.why() << endl;
    cout << endl << "fin du test" << endl;
  }
  
}
