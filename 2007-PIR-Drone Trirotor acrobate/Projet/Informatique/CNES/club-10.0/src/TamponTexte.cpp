///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Club
//
//$Nom
//>       TamponTexte.cpp
//$Resume
//       fichier d'implantation de la classe TamponTexte
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class TamponTexte        
//>         TamponTexte()        
//>         operator =()           
//>         lit()                  
//>         ecrit()                
//>         elimineCommentaires()  
//>         elimineBlancs()        
//>         insereAAdresse()       
//>         elimineZone()          
//>         remplaceTout()         
//>         nombreLignes()         
//>         ligne()                
//>         insereDebutLigne()     
//>         insereFinLigne()       
//>         elimineLigne()         
//>         remplaceLigne()        
//>         nombreChampsLigne()    
//>         champLigne()           
//>         insereAvantChampLigne()
//>         ajouteApresChampLigne()
//>         elimineChampLigne()    
//>         remplaceChampLigne()   
//>         nombreChamps()         
//>         champ()                
//>         insereAvantChamp()     
//>         ajouteApresChamp()     
//>         elimineChamp()         
//>         remplaceChamp()        
//>         actualiseIterateurs()
//$Historique
//       $Log: TamponTexte.cpp,v $
//       Revision 3.23  2003/10/22 12:53:54  club
//       DM 0029
//
//       Revision 3.22  2003/02/03 14:00:55  club
//       DM-ID 17 Mise à jour des extensions des fichiers & correction du passage par référence des objets ClubErreurs
//
//       Revision 3.21  2001/03/14 11:14:11  club
//       correction d'une fuite de mémoire dans le destructeur
//
//       Revision 3.20  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 3.19  2000/09/07 08:06:52  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.18  2000/07/03 08:57:21  club
//       Ajout du copyright CNES
//
//       Revision 3.17.2.2  2000/04/04 07:15:50  club
//       déplacement du copyright
//
//       Revision 3.17.2.1  2000/03/30 14:46:52  club
//       ajout du copyright CNES
//
//       Revision 3.17  1999/07/07 07:55:17  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 3.16  1999/06/17 16:32:52  club
//       suppression du retour inutile de ptrErreur
//
//       Revision 3.15  1999/06/17 14:23:14  club
//       création d'un TamponAscii dans le traitement d'erreur des constructeurs
//       et operator =
//
//       Revision 3.14  1999/06/09 14:43:52  club
//       correction d'un bug dans le constructeur par copie (recopie de l'attribut
//       tampon_)
//
//       Revision 3.13  1999/06/09 12:37:25  club
//       correction d'un bug dans l'opérateur d'affectation (recopie de l'attribut
//       tampon_)
//
//       Revision 3.12  1999/03/15 15:34:54  club
//       simplification des constructeurs, la lecture des fichiers est appelee
//       directement par les constructeurs de TamponAscii
//       correction de la méthode operator=
//
//       Revision 3.11  1999/03/15 13:30:41  club
//       modification totale de TamponTexte, qui repose sur la hiérarchie de TamponAscii
//       et des itérateurs, sans changement de l'interface utilisateur
//       TamponTexte bloquent les exceptions des objets utilisés et conserve en
//       interface le système d'erreur ClubErreur
//
//       Revision 3.10  1998/11/17 11:49:12  club
//       élimination de l'inclusion de ctype.h
//       ajout de (void) explicite pour indiquer que l'on ignore certains retours
//
//       Revision 3.9  1998/07/27 10:13:51  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.8  1998/06/21 15:57:27  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//
//       Revision 3.7  1998/04/26 13:02:53  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.6  1998/01/22 08:23:10  luc
//       suppression d'une variable locale inutilisée
//
//       Revision 3.5  1997/08/24 13:35:05  luc
//       reconnaissance des chaînes de caractères du fortran
//       utilisation de la classe AnalyseurLexical
//       traitement en bloc des commentaires
//       dans le cas de l'interprétation des guillemets
//       (sinon, on confond les apostrophes dans les commentaires
//       avec les spécificateurs de chaînes fortran)
//
//       Revision 3.4  1997/08/21 16:44:08  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:49:24  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:04:04  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:20:58  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:30:19  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       
//       Revision 1.10  1995/07/12 15:00:48  mercator
//       ajout de signatures pour aider le compilateur SUN a comprendre ...
//       
//       Revision 1.9  1995/07/07 14:02:52  mercator
//       transformation de toutes les fonctions de lecture en fonctions "const"
//       (on estime licite de modifier des attributs d'optimisation invisibles
//       de l'exterieur dans des fonctions "const")
//       
//       Revision 1.8  1994/12/13 07:55:21  mercator
//       ajout d'une interface en FILE* a la construction et a la lecture
//       
//       Revision 1.7  1994/12/09 13:55:01  mercator
//       ajout d'une possibilite de mettre hors-circuit l'interpretation des '"'
//       
//       Revision 1.6  1994/11/09 15:03:00  mercator
//       elimination des directives #pragma
//       
//       Revision 1.5  1994/09/30 10:33:54  mercator
//       transformation des routines d'insertion dans les lignes
//       ajout de tests de validite des numeros de champs et lignes
//       elimination de tests redondants entre appelants et appeles
//       
//       Revision 1.4  1994/09/28 16:17:54  mercator
//       ajout d'une possibilite de personnalisation des separateurs
//       ajout de pointeurs d'erreur optionnels dans les signatures des methodes
//       
//       Revision 1.3  1994/09/15 16:39:30  mercator
//       correction d'un bug si le dernier champ d'un fichier est directement
//       suivi d'un '\0'
//       
//       Revision 1.2  1994/08/30 12:54:23  mercator
//       remplacement de "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 12:05:50  luc
//       Initial revision
//
//$Version
//       $Id: TamponTexte.cpp,v 3.23 2003/10/22 12:53:54 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       P-A. Cros    CSSI
//       M. Julien    CSSI
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif

#include "club/ClubErreurs.h"
#include "club/TamponAscii.h"
#include "club/TamponTexte.h"
#include "club/IterateurCaractere.h"
#include "club/IterateurChamp.h"
#include "club/IterateurLigne.h"
#include "club/IterateurChampLigne.h"


TamponTexte::TamponTexte (FILE* ptrFic, int interprete) 
  throw(ClubErreurs) : tampon_ (0), parcoursChamp_ (0), parcoursLigne_ (0), parcoursChampLigne_ (0)
{
  tampon_ = new TamponAscii(ptrFic,interprete);
  parcoursCaractere_ = new IterateurCaractere(tampon_);
  parcoursChamp_ = new IterateurChamp (tampon_);
  parcoursLigne_ = new IterateurLigne (tampon_);
  parcoursChampLigne_ = new IterateurChampLigne (tampon_);
}

TamponTexte::TamponTexte (const char* nom        ,
                          int interprete         ) 
  throw(ClubErreurs) : tampon_(0), parcoursChamp_ (0), parcoursLigne_ (0), parcoursChampLigne_ (0)
{
    tampon_ = new TamponAscii(nom,interprete);
    parcoursCaractere_ = new IterateurCaractere(tampon_);
    parcoursChamp_ = new IterateurChamp (tampon_);
    parcoursLigne_ = new IterateurLigne (tampon_);
    parcoursChampLigne_ = new IterateurChampLigne (tampon_);
}

TamponTexte::TamponTexte (const TamponTexte& t)
  throw(ClubErreurs)  : tampon_ (0)
{
  tampon_ = new TamponAscii(*(t.tampon_)); 
  parcoursCaractere_ = new IterateurCaractere(tampon_);
  parcoursChamp_= new IterateurChamp(tampon_);
  parcoursLigne_= new IterateurLigne(tampon_);
  parcoursChampLigne_ = new IterateurChampLigne (tampon_);
}


TamponTexte& TamponTexte::operator = (const TamponTexte& t)
  throw(ClubErreurs)
{ 
  if (this != &t)       // protection contre x = x
  { 
    *tampon_ = *(t.tampon_);
    if (parcoursCaractere_ != NULL)
      delete parcoursCaractere_;
    if (parcoursChamp_ != NULL)
      delete parcoursChamp_;
    if (parcoursLigne_ != NULL)
      delete parcoursLigne_;
    if (parcoursChampLigne_)
      delete parcoursChampLigne_;

    parcoursCaractere_ = new IterateurCaractere(tampon_);
    parcoursChamp_= new IterateurChamp(tampon_);
    parcoursLigne_= new IterateurLigne(tampon_);
    parcoursChampLigne_ = new IterateurChampLigne (tampon_);    

  }
  return *this;
}

TamponTexte::~TamponTexte ()
  throw() 
{
  if (tampon_) 
    delete (tampon_); 
  if (parcoursCaractere_)
    delete (parcoursCaractere_);
  if (parcoursChamp_) 
    delete (parcoursChamp_);
  if (parcoursLigne_)
    delete (parcoursLigne_);
  if (parcoursChampLigne_)
    delete (parcoursChampLigne_);
}


void TamponTexte::lit (FILE* ptrFic, int interprete)
  throw(ClubErreurs)
{
  tampon_->positionneInterprete( interprete );
  tampon_->lit( ptrFic );
  actualiseIterateurs();
}

void TamponTexte::lit (const char* nom, int interprete)
  throw(ClubErreurs)
{
    tampon_->positionneInterprete( interprete );
    tampon_->lit( nom );
    actualiseIterateurs();
}

void TamponTexte::ecrit (const char* nom) const
  throw(ClubErreurs)
{
  tampon_->ecrit( nom );
}

void TamponTexte::elimineCommentaires ()
  throw(ClubErreurs)
{ 
  tampon_->elimineCommentaires();
  actualiseIterateurs();  
}

void TamponTexte::elimineBlancs ()
  throw(ClubErreurs)
{
  tampon_->elimineBlancs();
  actualiseIterateurs();
}

//
// gestion commentaires et separateurs :
//


void TamponTexte::initCarCommentaires   (const char* chaine)
  throw()
{ 
  tampon_->initCarCommentaires( chaine ); 
}

void TamponTexte::ajouteCarCommentaires (const char* chaine)
  throw()
{ 
  tampon_->ajouteCarCommentaires( chaine ); 
}


const string& TamponTexte::carCommentaires () const
  throw()
{ 
  return tampon_->carCommentaires();
}


void TamponTexte::initSeparateurs       (const char* chaine)
  throw()
{ 
  tampon_->initSeparateurs( chaine ); 
}


void TamponTexte::ajouteSeparateurs (const char* chaine)
  throw()
{ 
  tampon_->ajouteSeparateurs( chaine ); 
}


const string& TamponTexte::separateurs () const
  throw()
{ 
  return tampon_->separateurs(); 
}



// routines d'accès globales

const char* TamponTexte::nom () const
  throw()
{ 
  return tampon_->nom();
}


int TamponTexte::estVide () const
  throw()
{ 
  return tampon_->estVide(); 
}


const char* TamponTexte::total () const
  throw()
{
  return tampon_->total();
}

int TamponTexte::longueur () const
  throw()
{ 
  return tampon_->longueur(); 
}

void TamponTexte::insereAAdresse (const char* adresse, const char* chaine)
  throw(ClubErreurs)
{ 
    int deplacement = adresse - tampon_->total();
    if( deplacement < 1 )
      deplacement = 1;
    if( deplacement > tampon_->longueur() )
      deplacement = tampon_->longueur();

    parcoursCaractere_->allerSur( deplacement );
    tampon_->insereFin( *parcoursCaractere_, chaine );
    actualiseIterateurs();  
}

void TamponTexte::ajouteALaFin (const char* chaine)
  throw(ClubErreurs)
{ 
  insereAAdresse (tampon_->total()+ tampon_->longueur(), chaine); 
  actualiseIterateurs();  
}
  
void TamponTexte::elimineZone (char* debut, char* fin)
  throw(ClubErreurs)
{ 
    int indiceDebut = debut - tampon_->total();
    int indiceFin   = fin   - tampon_->total() + 1;

    if (indiceDebut < 1 ) 
      return ;

    if( indiceFin   < 1 ) 
      return ;

    if( indiceDebut > tampon_->longueur() ) 
      return ;
    if( indiceFin   > tampon_->longueur() ) 
      return ;

    if( indiceDebut > indiceFin ) 
      return ;
  
    IterateurCaractere icFin  ( tampon_ );

    parcoursCaractere_->allerSur( indiceDebut );
    icFin.allerSur  ( indiceFin   );

    tampon_->supprime( *parcoursCaractere_, icFin );
    actualiseIterateurs();  
}

void TamponTexte::remplaceTout (const char* chaine)
  throw(ClubErreurs)
{ 
    tampon_->nettoie();
    parcoursCaractere_->premier();
    tampon_->insereDebut( *parcoursCaractere_, chaine );
    actualiseIterateurs();  
}

int TamponTexte::nombreLignes () const 
  throw(ClubErreurs)
{
    return parcoursLigne_->nombreIterations();
}

const char* TamponTexte::ligne (int l) const
  throw(ClubErreurs)
{
    parcoursLigne_->allerSur( l );
    return parcoursLigne_->valeur();
}

void TamponTexte::insereDebutLigne (int l, const char* chaine)
  throw(ClubErreurs)
{ 
    parcoursLigne_->allerSur( l );
    tampon_->insereDebut( *parcoursLigne_ , chaine );
    actualiseIterateurs();  
}

void TamponTexte::insereFinLigne (int l, const char* chaine)
  throw(ClubErreurs)
{ 
    parcoursLigne_->allerSur( l );
    tampon_->insereFin( *parcoursLigne_, chaine );
    actualiseIterateurs();  
}

void TamponTexte::elimineLigne (int l)
  throw(ClubErreurs)
{ 
    parcoursLigne_->allerSur( l );
    tampon_->supprime( *parcoursLigne_ );
    actualiseIterateurs();  
}

void TamponTexte::remplaceLigne (int l, const char* chaine)
  throw(ClubErreurs)
{ 
    parcoursLigne_->allerSur( l );
    tampon_->remplace( *parcoursLigne_, chaine );
    actualiseIterateurs();  
}

int TamponTexte::nombreChampsLigne (int l) const
  throw(ClubErreurs)
{
    return parcoursChampLigne_->nombreIterationsChamps( l );
}

const char* TamponTexte::champLigne (int c, int l) const
  throw(ClubErreurs)
{ 
    parcoursChampLigne_->allerSur( c, l );
    return parcoursChampLigne_->valeur();
}

void TamponTexte::insereAvantChampLigne (int c, int l, const char* chaine)
  throw(ClubErreurs)
{ 
    parcoursChampLigne_->allerSur( c, l );
    tampon_->insereDebut( *parcoursChampLigne_, chaine );
    actualiseIterateurs();
}

void TamponTexte::ajouteApresChampLigne (int c, int l, const char* chaine)
  throw(ClubErreurs)
{ 
    parcoursChampLigne_->allerSur( c, l );
    tampon_->insereFin( *parcoursChampLigne_, chaine );
    actualiseIterateurs();
  
}

void TamponTexte::elimineChampLigne (int c, int l)
  throw(ClubErreurs)
{ 
    parcoursChampLigne_->allerSur( c, l );
    tampon_->supprime( *parcoursChampLigne_ );
    actualiseIterateurs();
}

void TamponTexte::remplaceChampLigne (int c, int l, const char* chaine)
  throw(ClubErreurs)
{
    parcoursChampLigne_->allerSur( c, l);
    tampon_->remplace( *parcoursChampLigne_ , chaine);
    actualiseIterateurs();
}


int TamponTexte::nombreChamps () const
  throw()
{
  try
  {
    return parcoursChamp_->nombreIterations();
  }
  catch( ClubErreurs ce )
  {
    (void)ClubErreurs::erreur( &ce, ce.why() );
    return 0;
  }
  
}

const char* TamponTexte::champ (int c) const
  throw(ClubErreurs)
{
    int champ_courant = c;
    parcoursChamp_->allerSur( champ_courant );
    return parcoursChamp_->valeur();
}

void TamponTexte::insereAvantChamp (int c, const char* chaine)
  throw(ClubErreurs)
{ 
    parcoursChamp_->allerSur( c );

    tampon_->insereDebut( *parcoursChamp_, chaine );
    actualiseIterateurs();\
}

void TamponTexte::ajouteApresChamp (int c, const char* chaine)
  throw(ClubErreurs)
{ 
    parcoursChamp_->allerSur( c );
    tampon_->insereFin( *parcoursChamp_, chaine );
    actualiseIterateurs();
}

void TamponTexte::elimineChamp (int c)
  throw(ClubErreurs)
{
    parcoursChamp_->allerSur( c );
    tampon_->supprime( *parcoursChamp_ );
    actualiseIterateurs();
}


void TamponTexte::remplaceChamp (int c, const char* chaine)
  throw(ClubErreurs)
{
    parcoursChamp_->allerSur( c );
    tampon_->remplace( *parcoursChamp_, chaine );
    actualiseIterateurs();
}

void TamponTexte::actualiseIterateurs()
{
  parcoursChamp_->actualise();
  parcoursLigne_->actualise();
  parcoursChampLigne_->actualise();
}

const TamponAscii* TamponTexte::getTampon()  
{return tampon_;}
