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
//>       prgm_TamponChamp.cc
//
//$Resume
//        fichier d'implantation du test prgm_TamponChamp
//
//$Description
//       teste les classes TamponAscii et IterateurChamp
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
//       $Log: prgm_TamponChamp.cpp,v $
//       Revision 1.8  2003/02/07 16:30:16  club
//       DM-ID 18 Optimisation du code (supression de strstream et sstream)
//
//       Revision 1.7  2003/02/03 14:37:33  club
//       DM-ID 12 Mise à jour d'un include selon la norme C++ & mise à jour du code en conséquence
//
//       Revision 1.6  2001/06/21 15:22:22  club
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
//       $Id: prgm_TamponChamp.cpp,v 1.8 2003/02/07 16:30:16 club Exp $
//$Auteur
//        P-A.Cros    CSSI
//        G. Lajon    CSSI
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/TamponAscii.h"
#include "club/IterateurChamp.h"


int Parcours( TamponAscii &t )
{
  cout << endl << "\t\tPARCOURS" << endl;
  cout << endl << "\t1- Parcours Incremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;

  IterateurChamp itc( t );

  for( itc.premier(); !itc.termine() ; itc++ ){
    cout << itc.valeur() << "," << endl;
  }
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t2- Parcours Decremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;
  int i = itc.nombreIterations();
  itc.dernier();
  while(i){
    cout << itc.valeur() << endl;
    itc--;
    i--;
  }
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t3- Acces direct" << endl;
  cout <<         "\t   ~~~~~~~~~~~~" << endl;
  cout << " valeur de l'element 10 : " ;
  itc.allerSur( 10 );
  cout << itc.valeur() << endl;
  return 0;
}

int Insertion( TamponAscii &t )
{
  // il est preferable d'inserer en fin, sinon, on est susceptible de
  // changer le nombre de champs (lorsque l'on rajoute un nombre devant
  // un commentaire)

  IterateurChamp itc( t );
  cout << endl << "\t\tINSERTIONS" <<endl;
  cout << endl << "\t1- Insertion en fin" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~" << endl;
  cout <<endl <<"Insertion du numero de champ a la fin de chaque element.";
  cout << endl;
  char numLig[5]="\0";
  int i=0;
  for( itc.premier(), i = 1; !itc.termine(); itc++, i++ ){
    sprintf(numLig, "%d", i);
    t.insereFin( itc, numLig );
  }
  cout << endl << "\t2- Insertion en fin" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "insertion de \"HAPPY\" a la fin de l'element 12 : " << endl;
  itc.allerSur(12);
  cout << "Valeur du 12 "<< itc.valeur()<<endl;
  t.insereFin( itc, "HAPPY" );
  cout << endl << "~~~~~~~ contenu du tampon apres insertions ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}


int Remplacement(TamponAscii &t )
{
  IterateurChamp itc( t );
  cout << endl << "\t\tREMPLACEMENTS\n" <<endl;
  cout << endl << "\t1- Remplacements simples" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Remplacer l'element 2  par \"TOTO\"." << endl;  
  itc.allerSur(2);
  t.remplace( itc, "TOTO" );
  cout << endl << "\t2- Remplacements multi-elements" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Remplacer les elements 4 a 6  par \"UNE CHAINE\"."<<endl;  
  itc.allerSur( 4 );
  IterateurChamp itc2( t );
  itc2.allerSur( 6 );
  t.remplace( itc, itc2, "UNE CHAINE" );
  cout << endl << "~~~~~~~ contenu du tampon apres remplacements ~~~~~~";
  cout << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}


int Suppression( TamponAscii &t )
{
  cout << endl << "\t\tSUPPRESSIONS\n" <<endl;
  cout << endl << "\t1- Suppressions element simple" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Supprime l'element 4." << endl;
  IterateurChamp itc(t);
  itc.allerSur( 4 );
  t.supprime( itc );
  cout << endl << "\t2- Suppressions multi-elements" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Supprime les elements 7 a 8" << endl;
  itc.allerSur(7  );
  IterateurChamp itc2(t);//sinon -> erreur de synchro
  itc2.allerSur( 8 );
  t.supprime( itc, itc2 );
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
  IterateurChamp itc(t);
  itc.dernier();
  cout << endl <<"valeur dernier element       :" << itc.valeur() << endl;
  itc++;
  cout <<"apres operateur ++          :" << itc.valeur() << endl;
  itc++;
  cout <<"deuxieme appel a operateur++:" << itc.valeur() << endl;
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t2- Parcours Decremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;
  itc.premier();
  cout << endl <<"valeur premier element       :" << itc.valeur() << endl;
  itc--;
  cout <<"apres operateur --          :" << itc.valeur() << endl;
  itc--;
  cout <<"deuxieme appel a operateur--:" << itc.valeur() << endl;
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t3- Acces direct" << endl;
  cout <<         "\t   ~~~~~~~~~~~~" << endl;
  itc.allerSur(1);
  cout << endl <<"acces element 1  :" << itc.valeur() << endl;
  cout << endl <<"tentative d'acceder a l'element 0"<<endl;
  try
  {
    itc.allerSur(0);
    cout <<"acces element 0 (normalement impossible) :" 
         << itc.valeur() << endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  itc.allerSur(itc.nombreIterations());
  cout << endl;
  cout <<"acces element "<<itc.nombreIterations()<<" (dernier element):";
  cout <<itc.valeur()<<endl;
  try
  {
    cout << endl << "tentative d'acceder au dernier element +1"<<endl;
    itc.allerSur(itc.nombreIterations()+1);
    cout <<"acces element "<<itc.nombreIterations()+1;
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
  IterateurChamp itc( t );
  cout << endl << "\t\tINSERTIONS" <<endl;
  cout << endl << "\t1- Insertions" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~" << endl;
  itc.premier();
  cout << endl <<"valeur premier element       :" << itc.valeur() << endl;
  try
  {
    cout <<endl<<"tentative d'insertion avant l'element 0"<<endl;
    itc.allerSur(0);
    t.insereDebut( itc, "It s all right" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }

  try
  {
    cout << "tentative d'insertion apres le dernier element +3 "<< endl;
    itc.allerSur(itc.nombreIterations()+3);
    t.insereDebut( itc, "It s funny" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }

  return 0;
}

int SuppressionCasDegrade( TamponAscii& t )
{
  IterateurChamp itc( t );
  cout << endl << "\t\tSUPPRESSIONS\n" <<endl;
  cout << endl << "\t1- Suppressions element simple" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  try
  {
    cout << endl << "suppression de l'element -1." << endl;
    itc.allerSur(-1);
    t.supprime( itc );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout <<"suppression de l'element "<< itc.nombreIterations() + 5;
    cout << "(5 elements apres la fin du tampon)."<< endl;
    itc.allerSur(itc.nombreIterations()+5);
    t.supprime( itc );
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
  cout << endl << "\t2- Suppressions multi-elements" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  IterateurChamp itc2( t );
  try
  {
    cout << endl << "tentative suppression des elements -1 a 2." << endl;
    itc.allerSur(-1);
    itc2.allerSur(2);
    t.supprime( itc, itc2 );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }

  try
  {
    cout <<"suppression des elements "<< itc.nombreIterations() - 2;
    cout << " a "<< itc.nombreIterations() + 3;
    cout << "(de 2 elements avant a 3 apres la fin du tampon)." <<  endl;
    itc.allerSur(itc.nombreIterations()-2);
    itc2.allerSur( itc2.nombreIterations() + 3 );
    t.supprime( itc, itc2 );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout << endl <<"suppression des elements 8 a 4 " ;
    cout << "(zone invalide -> pas de suppression)."<<endl;
    itc.allerSur( 8 );
    itc2.allerSur( 4 );
    t.supprime( itc, itc2 );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  cout << endl << "~~~~~~~ contenu du tampon apres suppressions multi-elements ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}


int RemplacementCasDegrade( TamponAscii& t )
{
  IterateurChamp itc( t );
  cout << endl << "\t\tREMPLACEMENTS\n" <<endl;
  cout << endl << "\t1- Remplacements simples" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~" << endl;

  try
  {
    cout << endl << "remplacer l'element 0 par 'bug s spirit'." << endl;
    itc.allerSur(0);
    t.remplace( itc, "bug s spirit" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout << endl <<"remplacer l'element "<< itc.nombreIterations() + 5;
    cout << " par 'no way' (5 elements apres la fin du tampon)."<< endl;
    itc.allerSur(itc.nombreIterations()+5);
    t.remplace( itc, "no way" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  cout << endl << "~~~~~~~ contenu du tampon apres remplacement simples ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  IterateurChamp itc2(t);
  try
  {
    cout << endl << "\t2- Remplacements multi-elements" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "remplacer les elements -3 a 2 par 'un test de plus'." << endl;
    itc.allerSur(-3);
    itc2.allerSur(2);
    t.remplace( itc, itc2, "un test de plus" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout << "remplacer les elements "<< itc.nombreIterations() - 2;
    cout << " a "<< itc.nombreIterations() + 3 << " par 'hocus pocus'";
    cout << " (de 2 elements avant a 3 elements apres la fin du tampon)."<< endl;
    itc.allerSur(itc.nombreIterations()-2);
    itc2.allerSur( itc2.nombreIterations() + 3 );
    t.remplace( itc, itc2, "hocus pocus" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout <<"remplacer les elements 8 a 4 par 'magic circus'.";
    cout <<" (zone de remplacement invalide -> pas de remplacement)."<<endl;
    itc.allerSur( 8 );
    itc2.allerSur( 4 );
    t.remplace( itc, itc2, "magic circus" );
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  cout << endl << "~~~~~~~ contenu du tampon apres remplacements multi-elements ~~~~~~" << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}


int IterateurInvalide( TamponAscii& t )
{
  IterateurChamp itc( t );
  IterateurChamp itc2( t );
  try
  {
    cout << "\t\tITERATEURS INVALIDES\n" <<endl;
    cout << endl << "suppression de l'element 3 (iterateur 1)." << endl;
    itc.allerSur(3);
    t.supprime( itc );
    cout << "tentative d'acces a l'element 6 ( iterateur 2 non valide)";
    cout << endl;
    itc2.allerSur(6);
    cout << endl << "cette ligne ne doit pas apparaitre:" << itc2.valeur()<<endl;
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
  try
  {
    if( argc != 2 )
    {
      cerr << "USAGE : " << argv[0] << " <fichier_entree>" << endl;
      return 1;
    }
    TamponAscii        mon_tampon(argv[1]);
    mon_tampon.positionneInterprete(1);
    cout << " Contenu initial du tampon : " << endl;
    cout << mon_tampon.total()<<endl;
    
    //    mon_tampon.elimineCommentaires();
    //    cout << " contenu apres elimination des commentaires : " << endl;
    //    cout << mon_tampon.total()<<endl;
    
    
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
  catch(ClubErreurs ce)
  {
    cout << " Si cette ligne apparait, le test a echoue (exception inattendue)"
         << endl;
    cout << ce.why() << endl;
    cout << endl << "fin du test" << endl;
  }
  
}
