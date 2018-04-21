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
//>       prgm_TamponChampLigne.cc
//
//$Resume
//        fichier d'implantation du test prgm_TamponChampLigne
//
//$Description
//       teste les classes TamponAscii et IterateurChampLigne
//
//$Contenu
//>       int Parcours()          
//>       int Insertion()         
//>       int Remplacement()      
//>       int Suppression()       
//>       int ParcoursCasDegrade()
//>       int IterateurInvalide() 
//>       int main()              
//
//$Historique
//       $Log: prgm_TamponChampLigne.cpp,v $
//       Revision 1.8  2003/02/07 16:30:31  club
//       DM-ID 18 Optimisation du code (supression de strstream et sstream)
//
//       Revision 1.7  2003/02/03 14:37:56  club
//       DM-ID 12 Mise à jour d'un include selon la norme C++ & mise à jour du code en conséquence
//
//       Revision 1.6  2001/06/21 15:22:33  club
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
//       $Id: prgm_TamponChampLigne.cpp,v 1.8 2003/02/07 16:30:31 club Exp $
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
#include "club/IterateurChampLigne.h"


int Parcours( TamponAscii &t )
{
  cout << endl << "\t\tPARCOURS" << endl;
  cout << endl << "\t1- Parcours Incremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;

  cout << "mon tampon "<<endl << t.total()<<endl;

  IterateurChampLigne itc( t );


  itc.premier();
  cout << "apres itc.prem"<<endl;
  cout << itc.valeur()<<": valeur de itc"<<endl;
  cout << " nombre de lignes : " << itc.nombreIterations()<<endl;
  cout << "nombre de champs : " << itc.nombreIterationsChamps()<<endl;

  for( itc.premier(); !itc.termine() ; itc++ ){
    cout << "VAL :"<<itc.valeur() << "," << endl;
  }


  cout << endl << "\t2- Parcours Decremental" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~" << endl;
  itc.dernier();
  do
  {
    cout << itc.valeur()<<endl;
  }while(itc--);

  cout << endl<<endl
       <<"se positionner sur une ligne vide (champ 0, ligne 5)"<<endl;
  itc.allerSur(0,5);
  cout<<"valeur : "<<itc.valeur()<<endl;
  cout << "apres incrementation du pointeur"<<endl;
  itc++;
  cout<<"valeur : "<<itc.valeur()<<endl;
  



  return 0;
}

int Insertion(TamponAscii &t )
{
  IterateurChampLigne itc( t );
  cout << endl << "\t\tINSERTIONS" <<endl;
  cout << endl << "\t1- Insertion en debut" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~" << endl;
  cout <<endl <<"insertion du numero de l'element au debut de chacun d'eux.";
  cout << endl;
  char numLig[10]="\0";
  int i=0;
    int maxI=0;
    int j=0;
      for( itc.premier(); !itc.termine(); itc++ )
      {
        numLig[0] = '\0';
        if( i >= maxI ){
          i = 0;
          maxI = itc.nombreIterationsChamps();
          sprintf(numLig, "[%d]1", ++j);
        } else {
          sprintf(numLig, "%d", i + 1);
        }
        i++;
   
        t.insereFin( itc, numLig );
      }

  cout <<endl<< "Contenu du tampon : "<<endl<<t.total()<<endl;
  return 0;
}


int Remplacement(TamponAscii &t )
{
  IterateurChampLigne itc( t );
  cout << endl << "\t\tREMPLACEMENTS\n" <<endl;
  cout << endl << "\t1- Remplacements simples" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Remplacer l'element 3,10  par \"TOTO\"." << endl;  
  itc.allerSur(3, 10);
  t.remplace( itc, "TOTO" );
  cout << endl << "\t2- Remplacements multi-elements" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Remplacer les elements 2,7 a 4,7  par \"UNE CHAINE\"."<<endl;  
  itc.allerSur( 2, 7 );
  IterateurChampLigne itc2( t );
  itc2.allerSur( 4, 7 );
  t.remplace( itc, itc2, "UNE CHAINE" );
  cout << endl << "~~~~~~~ contenu du tampon apres remplacements ~~~~~~";
  cout << endl;
  cout << t;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  return 0;
}

int Suppression( TamponAscii &t )
{
  cout << endl << "\t\tSUPRESSIONS\n" <<endl;
  cout << endl << "\t1- Suppressions element simple" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Supprime l'element 3, 7." << endl;
  IterateurChampLigne itc(t);
  itc.allerSur( 3, 7 );
  t.supprime( itc );
  cout << endl << "\t2- Suppressions multi-elements" << endl;
  cout <<         "\t   ~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl << "Supprime les elements 1,10 a 2,10" << endl;
  itc.allerSur( 1, 10 );
  IterateurChampLigne itc2(t);//sinon -> erreur de synchro
  itc2.allerSur( 2, 10 );
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
  IterateurChampLigne itc(t);
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
  cout << "totoe bo"<<endl;
  itc--;
  cout <<"apres --"<<endl;
  cout <<"apres operateur --          :" << itc.valeur() << endl;
  itc--;
  cout <<"deuxieme appel a operateur--:" << itc.valeur() << endl;
  cout << endl << "\t------------------------" << endl; 
  cout << endl << "\t3- Acces direct" << endl;
  cout <<         "\t   ~~~~~~~~~~~~" << endl;
  try
  {
    cout << " Aller sur l'element 1, 1 " <<endl;
    itc.allerSur(1,1);
    cout <<"contenu element 1,1  :" << itc.valeur() << endl;  
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout <<"Se positionner sur l'element 0,1 "<<endl;
    itc.allerSur(0,1);
    cout <<"affichage valeur"<<endl;
    cout << itc.valeur() << endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout << "Se positionner sur l'element 0,0 "<<endl;
    itc.allerSur(0,0);
    cout <<"affichage valeur"<<endl;
    cout << itc.valeur() << endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    itc.premier();
    cout <<"Se positionner sur l'element -1 " <<endl;
    itc.allerSur(-1);
    cout <<"affichage valeur"<<endl;
    cout <<itc.valeur() << endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    itc.dernier();
    itc.allerSur(itc.nombreIterationsChamps());
    cout <<"acces element "<<itc.nombreIterationsChamps();
    cout <<"," << itc.nombreIterations()<<" (dernier element):";
    cout <<itc.valeur()<<endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  try
  {
    cout <<"Se positionner sur le dernier element +1"<<endl;
    itc.allerSur(itc.nombreIterationsChamps()+1);
    cout <<"acces element "<<itc.nombreIterationsChamps()+1;
    cout <<","<< itc.nombreIterations();
    cout <<" (un element au-dela de la fin du tampon):"<<itc.valeur()<<endl;
  }
  catch (ClubErreurs ce)
  {
    cout << " Exception levee : "<< ce.why()<<endl;
    ce.correction();
  }
  return 0;
}


int IterateurInvalide( TamponAscii& t )
{
  try
  {
    IterateurChampLigne itc( t );
    IterateurChampLigne itc2( t );
    cout << "\t\tITERATEURS INVALIDES\n" <<endl;
    cout << endl << "supressions de l'element 3 (iterateur 1)." << endl;
    itc.allerSur(3);
    t.supprime( itc );
    cout << "tentative d'acces a l'element 6 ( iterateur 2 non valide)";
    cout << endl;
    itc2.allerSur(6);
    cout << endl << "cette ligne ne doit pas apparaitre:" 
         << itc2.valeur()<<endl;
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
    cout << " Contenu du tampon : " << endl;
    cout << mon_tampon.total()<<endl;

    // mon_tampon.elimineCommentaires();
    //  cout << " Contenu du tampon apres elimination des commentaires :"<<endl;
    cout << mon_tampon.total()<<endl;


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
    IterateurInvalide( mon_tampon );
    cout << endl << "fin du test." << endl; 
  }
  catch(ClubErreurs ce)
  {
    cout << ce.why() << endl;
    cout << endl << "fin anormale du test, verifier le fichier d'entree" 
         << endl;
  }
  
}
