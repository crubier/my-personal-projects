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
//>       prgm_TamponCaractere.cc
//
//$Resume
//       fichier d'implantation du test prgm_TamponCaractere
//
//$Description
//       teste la classe TamponCaractere
//
//$Contenu
//>       void Parcours()              
//>       void Insertion()             
//>       void Suppression()           
//>       void Remplacement()          
//>       void ParcoursCasDegrade()    
//>       void SuppressionCasDegrade() 
//>       void RemplacementCasDegrade()
//>       void IterateurInvalide()     
//>       int main()                   
//
//$Historique
//       $Log: prgm_TamponCaractere.cpp,v $
//       Revision 1.11  2003/02/07 16:29:54  club
//       DM-ID 18 Optimisation du code (supression de strstream et sstream)
//
//       Revision 1.10  2003/02/03 14:37:07  club
//       DM-ID 12 Mise à jour d'un include selon la norme C++ & mise à jour du code en conséquence
//
//       Revision 1.9  2001/06/21 15:23:13  club
//       correction d'une signature de directive catch
//
//       Revision 1.8  2000/10/25 09:10:39  club
//       modification des includes du standard C++ : suppression du ".h" dans le
//       nom du fichier inclus.
//
//       Revision 1.7  2000/10/24 14:23:12  club
//       ajout de l'include ClubConfig.h et des tests de configuration.
//
//       Revision 1.6  2000/10/24 08:36:33  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 1.5  2000/09/07 08:35:52  club
//       utilisation de string de la STL au lieu de ChaineSimple.
//       mise à jour du cartouche.
//
//       Revision 1.4  1999/07/07 08:12:38  club
//       adaptation a la gestion des erreurs par
//       mecanisme d'exception.
//
//       Revision 1.3  1999/03/19 13:30:18  club
//       deplacement de la declaration du tampon pour capter les exceptions
//
//       Revision 1.2  1999/03/18 10:10:17  club
//       recherche des fichiers de donnée dans un répertoire passé en argument
//
//       Revision 1.1  1999/03/15 15:47:34  club
//       version initiale
//
//$Version
//       $Id: prgm_TamponCaractere.cpp,v 1.11 2003/02/07 16:29:54 club Exp $
//$Auteur
//        P-A.Cros    CSSI
//        O. Queyrut  CSSI
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/TamponAscii.h"
#include "club/IterateurCaractere.h"


void Parcours( TamponAscii &t )
{
  cout << endl << "\t\tPARCOURS" << endl;
  cout << endl << "\t1- Parcours Incremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;

  try 
  {
    IterateurCaractere itc( t );

    for( itc.premier(); !itc.termine() ; itc++ )
    {
      cout << itc.valeur() << ",";
    }
    cout << endl << "\t------------------------" << endl; 
    cout << endl << "\t2- Parcours Decremental" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;
    int i = itc.nombreIterations();
    itc.dernier();
    while(i)
    {
      cout << itc.valeur();
      itc--;
      i--;
    }
    cout << endl << "\t------------------------" << endl; 
    cout << endl << "\t3- Acces direct" << endl;
    cout <<         "\t   ~~~~~~~~~~~~" << endl;
    cout << " valeur de l'element 10 : " ;
    itc.allerSur( 10 );
    cout << itc.valeur() << endl;
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
  
}

void Insertion( TamponAscii &t )
{
  try
  {
    IterateurCaractere itc( t );
    cout << endl << "\t\tINSERTIONS" <<endl;
    cout << endl << "\t1- Insertion en debut" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~" << endl;
    cout <<endl <<"insertions du numero de l'element au debut de chacun d'eux.( par pas de 50).";
    cout << endl;
    char numLig[5]="\0";
    int i=0;
    for( itc.premier(), i = 1; !itc.termine(); itc++, i++ )
    {
      if( (i % 50) == 0 )
      {
        sprintf(numLig, "%d", i);
        t.insereDebut( itc, numLig );
      }
    }
    cout << endl << "\t2- Insertion en fin" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "insertion de \"HAPPY\" a la fin de l'element 12 : " << endl;
    itc.allerSur(12);
    t.insereFin( itc, "HAPPY" );
    cout << endl << "~~~~~~~ contenu du tampon apres insertions ~~~~~~" << endl;
    cout << t;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
  
}

void Suppression( TamponAscii &t )
{
  try
  {
    cout << endl << "\t\tSUPRESSIONS\n" <<endl;
    cout << endl << "\t1- Suppressions element simple" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Supprime l'element 25." << endl;
    IterateurCaractere itc(t);
    itc.allerSur( 25 );
    t.supprime( itc );
    cout << endl << "\t2- Suppressions multi-elements" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Supprime les elements 15 a 20" << endl;
    itc.allerSur(15  );
    IterateurCaractere itc2(t);//sinon -> erreur de synchro
    itc2.allerSur( 20 );
    t.supprime( itc, itc2 );
    cout << endl << "~~~~~~~ contenu du tampon apres suppressions ~~~~~~"<< endl;
    cout << t;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
}

void Remplacement(TamponAscii &t )
{
  try 
  {
    IterateurCaractere itc( t );
    cout << endl << "\t\tREMPLACEMENTS\n" <<endl;
    cout << endl << "\t1- Remplacements simples" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~" << endl;
    itc.allerSur(42);
    cout << endl << "Remplacer l'element 42 " << itc.valeur() << "par \"EURYDICE\"." << endl;  
    t.remplace( itc, "EURYDICE" );
    cout << itc.valeur()<<endl;
    cout << endl << "\t2- Remplacements multi-elements" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Remplacer les elements 30 a 34  par \"UNE CHAINE\"."<<endl;  
    itc.allerSur( 30 );
    IterateurCaractere itc2( t );
    itc2.allerSur( 34 );
    t.remplace( itc, itc2, "UNECHAINE" );
    cout << endl << "~~~~~~~ contenu du tampon apres remplacements ~~~~~~";
    cout << endl;
    cout << t;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
}


void ParcoursCasDegrade( TamponAscii &t )
{
  cout << endl << "\t\tPARCOURS" << endl;
  cout << endl << "\t1- Parcours Incremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;
  IterateurCaractere itc(t);
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
  try 
  {
    itc.allerSur(0);
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
  cout <<"acces element 0  :" <<endl;
  try 
  {
    cout << itc.valeur() << endl;
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
  try 
  {
    itc.allerSur(-1);
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
  try 
  {
    cout << endl <<"acces element 4 elements au-dela de la fin du tampon:"<<endl;
    itc.allerSur(itc.nombreIterations()+4);
  
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
}




void SuppressionCasDegrade( TamponAscii& t )
{
  try 
  {
    IterateurCaractere itc( t );
    cout << endl << "\t\tSUPRESSIONS\n" <<endl;
    cout << endl << "\t1- Suppressions element simple" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "suppression de l'element -1." << endl;
    itc.allerSur(-1);
    t.supprime( itc );
    cout <<"suppression de l'element "<< itc.nombreIterations() + 5;
    cout << "(5 element apres la fin du tampon)."<< endl;
    itc.allerSur(itc.nombreIterations()+5);
    t.supprime( itc );
    cout << endl ;
    cout << "~~~~~~~ contenu du tampon apres supressions simples ~~~~~~" << endl;
    cout << t;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "\t2- Suppressions multi-elements" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "suppression des elements -3 a 2." << endl;
    IterateurCaractere itc2( t );
    itc.allerSur(-1);
    itc2.allerSur(2);
    t.supprime( itc, itc2 );
    cout <<"suppression des elements "<< itc.nombreIterations() - 2;
    cout << " a "<< itc.nombreIterations() + 3;
    cout << "(de 2 elements avant a 3 apres la fin du tampon)." <<  endl;
    itc.allerSur(itc.nombreIterations()-2);
    itc2.allerSur( itc2.nombreIterations() + 3 );
    t.supprime( itc, itc2 );
    cout << endl <<"suppression des elements 12 a 9 " ;
    cout << "(zone invalide -> pas de suppression)."<<endl;
    itc.allerSur( 12 );
    itc2.allerSur( 9 );
    t.supprime( itc, itc2 );
    cout << endl << "~~~~~~~ contenu du tampon apres supressions multi-elements ~~~~~~" << endl;
    cout << t;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
}


void RemplacementCasDegrade( TamponAscii& t )
{
  try 
  {
    IterateurCaractere itc( t );
    cout << endl << "\t\tREMPLACEMENTS\n" <<endl;
    cout << endl << "\t1- Remplacements simples" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "remplacer l'element 0 par 'bug's spirit'." << endl;
    itc.allerSur(0);
    t.remplace( itc, "bug's spirit" );
    cout << endl <<"remplacer l'element "<< itc.nombreIterations() + 5;
    cout << " par 'no way' (5 elements apres la fin du tampon)."<< endl;
    itc.allerSur(itc.nombreIterations()+5);
    t.remplace( itc, "no way" );
    cout << endl << "~~~~~~~ contenu du tampon apres remplacement simples ~~~~~~" << endl;
    cout << t;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "\t2- Remplacements multi-elements" << endl;
    cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "remplacer les elements -3 a 2 par 'un test de plus'." << endl;
    itc.allerSur(-3);
    IterateurCaractere itc2(t);
    itc2.allerSur(2);
    t.remplace( itc, itc2, "un test de plus" );
    cout << "remplacer les elements "<< itc.nombreIterations() - 2;
    cout << " a "<< itc.nombreIterations() + 3 << " par 'hocus pocus'";
    cout << " (de 2 elements avant a 3 elements apres la fin du tampon)."<< endl;
    itc.allerSur(itc.nombreIterations()-2);
    itc2.allerSur( itc2.nombreIterations() + 3 );
    t.remplace( itc, itc2, "hocus pocus" );
    cout <<"remplacer les elements 12 a 9 par 'magic circus'.";
    cout <<" (zone de remplacement invalide -> pas de remplacement)."<<endl;
    itc.allerSur( 12 );
    itc2.allerSur( 9 );
    t.remplace( itc, itc2, "magic circus" );
    cout << endl << "~~~~~~~ contenu du tampon apres remplacements multi-elements ~~~~~~" << endl;
    cout << t;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }
}


void IterateurInvalide( TamponAscii& t )
{
  IterateurCaractere itc( t );
  IterateurCaractere itc2( t );
  cout << "\t\tITERATEURS INVALIDES\n" <<endl;
  cout << endl << "supressions de l'element n -3 (iterateur 1)." << endl;
  itc.allerSur(itc.nombreIterations() -3);
  itc2.allerSur(6);
  t.supprime( itc );
  try 
  {
    cout << "tentative d'acces a l'element 6 (iterateur 2)";
    cout << endl;
    itc2++;
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }

  
}



int main( int argc, char** argv )
{
  if( argc != 2 )
  {
    cerr << "usage : " << argv[0] << " répertoire" << endl;
    return 1;
  }
  string repertoire (argv [1]);
  try
  {
    TamponAscii mon_tampon ((repertoire + "/test_TamponCaractere.don").c_str ());
 

    cout << " contenu du tampon : " << endl;
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
    mon_tampon.ecrit ("test_TamponCaractere.sortie");
    cout << endl << "\tTEST FONCTIONNEMENT DEGRADE" << endl;
    cout << endl << "\t------------------------" << endl; 
    ParcoursCasDegrade( mon_tampon  );
    cout << endl << "------------------------" << endl; 
    IterateurInvalide( mon_tampon );

    cout << endl << "fin du test." << endl; 

  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    ce.correction();
  }


}
