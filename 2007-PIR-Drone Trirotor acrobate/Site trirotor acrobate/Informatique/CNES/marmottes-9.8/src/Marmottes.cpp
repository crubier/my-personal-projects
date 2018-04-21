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
//       Marmottes
//
//$Nom
//>       Marmottes.cpp
//
//$Resume
//       fichier d'implantation de la classe Marmottes
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Marmottes
//>         initialiseSenseurs()
//>         recupParNom()
//>         valideNouvelEtat()
//>         Marmottes()
//>         operator =()
//>         reinitialise()
//>         senseurs()
//>         nouveauRepere()
//>         calage()
//>         modifieCible()
//>         initialiseGyro()
//>         initialiseDerive()
//>         modifieReference()
//>         deuxConsignes()
//>         attitude()
//>         imposeAttitude()
//>         imposeSpin()
//>         repereBase()
//>         repere()
//>         mesure()
//>         controlable()
//>         criteresControlabilite()
//>         unitesPositionVitesse()
//>         respecterConsignes()
//>         convertirConsignes()
//>         respecterMesures()
//>         convertirMesures()
//>         wMax()
//>         convergence()
//>         dichotomie()
//>         autoriseExtrapolation()
//>         interditExtrapolation()
//>         accesSenseur()
//>         enregistreCorps()
//
//$Historique
//       $Log: Marmottes.cpp,v $
//       Revision 3.53  2003/10/22 13:00:38  marmottes
//       DM 0027
//
//       Revision 3.52  2003/10/08 09:39:40  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 3.51  2003/02/27 16:40:31  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 3.50  2003/02/04 16:29:29  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 3.49  2002/12/11 17:29:31  marmottes
//       DM-ID 12 Ajout de l'initialisation de pointeur.
//
//       Revision 3.48  2002/12/03 13:55:21  marmottes
//       FA-ID 0019 Correction des valeurs int en double et cast des fonctions dans l'ajout à l'appel à enregistreCorps dans Marmottes::reinitialise - Ajout des appels a Calltrace dans les méthodes Marmottes::enregistreCorps.
//
//       Revision 3.47  2002/11/28 09:44:25  marmottes
//       FA-ID 0019 Ajout de l'appel à enregistreCorps dans la méthode Marmottes::reinitialise
//
//       Revision 3.46  2002/09/13 08:16:58  marmottes
//       Correction de la FA 12.
//
//       Revision 3.45  2002/09/09 14:29:11  marmottes
//       ajout de la méthode enregistreCorps et modification de
//       l'initialisation de l'instance etatestime (DM 0007)
//
//       Revision 3.44  2002/04/17 16:07:38  marmottes
//       Modifications des méthodes modelise2Consignes et attitude suite à un anomalie de la mise à jour des cibles.
//
//       Revision 3.43  2002/04/12 14:35:39  marmottes
//       Modification de la méthode accesSenseur
//
//       Revision 3.42  2002/04/04 09:46:42  marmottes
//       Introduction de la méthode accesSenseur (DM 0004)
//
//       Revision 3.41  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 3.40  2002/02/22 09:31:32  marmottes
//       Création de l'interface liée à la prise en compte de la DM0002 (méthode Marmottes::initialiseDerive)
//
//       Revision 3.39  2002/01/17 09:26:19  marmottes
//       correction de spécifications throw
//
//       Revision 3.38  2001/07/17 15:46:50  luc
//       lancement de CantorErreurs par toutes les fonctions
//       pouvant lire un nouveau senseur
//
//       Revision 3.37  2001/06/06 08:16:52  luc
//       prise en compte du déplacement de CallTrace vers club
//
//       Revision 3.36  2001/04/04 12:26:08  luc
//       ajout de la méthode criteresControlabilite
//
//       Revision 3.35  2001/02/27 12:34:30  luc
//       ajout des méthodes imposeAttitude et imposeSpin
//
//       Revision 3.34  2001/02/08 09:02:04  luc
//       vidage de l'ancienne table des senseurs dans l'affectation
//
//       Revision 3.33  2001/02/07 16:52:09  luc
//       remplacement de la classe non standard hash_map par map
//       correction d'erreurs de copie des pointeurs de senseurs dans le
//       constructeur par copie et l'affectation (qui pouvait conduire
//       à des violations mémoire lorsque l'objet copié libérait ses
//       pointeurs)
//
//       Revision 3.32  2000/10/10 10:23:01  luc
//       correction de l'affichage manquant des valeurs de retour des méthodes
//       deuxConsignes et attitude lors des extrapolations
//
//       Revision 3.31  2000/10/09 11:07:11  luc
//       initialisation de attitude et spin dès le début de la résolution
//
//       Revision 3.30  2000/10/06 09:13:49  luc
//       élimination de la séparation entre états résolu et extrapolé
//
//       Revision 3.29  2000/10/02 16:47:41  luc
//       ajout d'un destructeur
//       prise en compte de l'évolution de l'interface publique de CallTrace
//       remplacement de certains attributs entiers en booléens
//
//       Revision 3.28  2000/09/13 09:41:53  luc
//       remplacement de tous les ChaineSimple par des string
//       remplacement de Adressage par hash_map
//
//       Revision 3.27  2000/09/08 15:59:34  luc
//       ajout des résultats dans les traces d'exécution
//
//       Revision 3.26  2000/09/08 08:01:17  luc
//       ajout du spin dans la trace de l'appel à reinitialise,
//       transfert des méthodes wMax, convergence, autoriseExtrapolation et
//       interditExtrapolation depuis le .h pour inclure les traces d'exécution
//
//       Revision 3.25  2000/09/05 13:31:22  luc
//       ajout du mécanisme de trace d'exécution
//
//       Revision 3.24  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 3.23  2000/03/29 16:32:27  luc
//       vérification de la contrôlabilité des senseurs lors de
//       l'extrapolation, également pour deuxConsignes
//
//       Revision 3.22  2000/03/29 16:25:36  luc
//       vérification de la contrôlabilité des senseurs lors de l'extrapolation
//
//       Revision 3.21  1999/08/20 07:37:29  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 3.20  1999/08/06 13:32:13  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 3.19  1999/04/26 11:37:17  luc
//       remplacement de abs par fabs
//
//       Revision 3.18  1998/10/05 15:09:30  luc
//       élimination de valeurs par défaut inutiles (ce sont les déclarations
//       qui les spécifient, pas les définitions)
//
//       Revision 3.17  1998/08/13 12:30:01  luc
//       prise en compte des unités dans les cibles définies par l'utilisateur
//
//       Revision 3.16  1998/07/15 12:40:42  luc
//       ajout des méthodes : modifieCible, initialiseGyro et modifieReference
//       ajout de la méthode privée valideNouvelEtat
//       propagation de l'état aux senseurs en fin de résolution
//       (pour les gyros intégrateurs)
//
//       Revision 3.15  1998/06/24 19:57:09  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 3.14  1998/06/02 15:37:57  hotbird
//       ajout d'une instanciation explicite oubliée
//
//       Revision 3.13  1998/05/17 15:22:59  luc
//       intégration des fonctionnalités de la classe ListeSenseurs
//       directement dans la classe Marmottes
//
//       Revision 3.12  1998/04/29 16:15:52  luc
//       transfert des fonctions de l'interface C dans un fichier séparé
//
//       Revision 3.11  1998/04/26 18:25:02  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.10  1998/04/26 18:18:30  luc
//       ajout d'une gestion d'unités de position et de vitesse variables
//
//       Revision 3.9  1998/02/19 16:17:40  luc
//       déplacement d'un constructeur inline dans le .cc
//       pour contourner un problème d'optimiseur avec g++ 2.8.0
//
//       Revision 3.8  1997/09/21 19:40:57  luc
//       ajout de la possibilité de faire gérer les unités
//       par chaque instance de senseur
//
//       Revision 3.7  1997/08/20 16:50:57  luc
//       ajout d'une fonction de réinitialisation de simulateur Marmottes
//
//       Revision 3.6  1997/08/20 11:49:46  luc
//       remontée du choix de la résolution rapide par extrapolation
//       au niveau de l'utilisateur (résolution rapide autorisée par défaut)
//
//       Revision 3.5  1997/08/20 08:17:35  luc
//       ajout d'un en-tête de fichier
//       utilisation de ChaineSimple à la place de char *
//       récupération d'une erreur retournée par le filtrage des solutions parasites
//
//       Revision 3.4  1997/04/27 19:35:07  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//
//       Revision 3.3  1997/02/13 12:27:51  luc
//       suppression de la vérification sur les dates trop proches
//       dans Marmottes::deuxConsignes
//
//       Revision 3.2  1997/02/11 08:38:02  luc
//       suppression de la vérification sur les dates trop proche
//       devenue inutile depuis la version 3.1 de etat.cc
//       (le spin est toujours valide, il n'y a plus de risque de division par 0)
//
//       Revision 3.1  1997/01/28 12:39:32  luc
//       ajout de la vitesse et du spin à la création et à la réinitialisation
//       ajout de la vitesse pour les calculs d'attitude
//       prise en compte des changements de la classe Etat (3.1)
//       ajout de qualificateurs "const"
//
//       Revision 2.2  1996/09/11 16:26:19  luc
//       ajout d'un constructeur par copie et d'une méthode deuxConsignes
//       ajouts des fonctions C correspondantes
//       prise en compte de l'allocation de nouveaux senseurs lors des copies
//
//       Revision 2.1  1996/07/31 16:13:14  luc
//       abandon des tools.h++ (Rogue Wave)
//       ajout des fonctions MarmottesNouveauRepere, MarmottesCalage,
//       MarmottesRepereBase, MarmottesRepere
//       (et des fonctions correspondantes de la classe Marmottes)
//       élimination de la limitation à quatre simulateurs simultanés
//
//       Revision 1.6  1995/02/10 16:16:41  mercator
//       correction de l'oubli de la reinitialisation du spin dans l'etat extrapole
//
//       Revision 1.5  1995/02/06 07:56:47  mercator
//       normalisation du quaternion donne par l'utilisateur a la creation
//
//       Revision 1.4  1995/01/30 09:43:33  mercator
//       ajout de l'initialisation de pointeurs d'erreur en sortie
//       ajout d'initialisations des cibles de senseurs geometriques
//
//       Revision 1.3  1995/01/27 16:59:54  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//
//       Revision 1.2  1995/01/26 15:23:08  mercator
//       ajout d'une verification sur l'ecart de date avec l'etat precedent
//
//       Revision 1.1  1995/01/26 08:41:23  mercator
//       Initial revision
//
//$Version
//       $Id: Marmottes.cpp,v 3.53 2003/10/22 13:00:38 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/Marmottes.h"
#include "marmottes/Lecture.h"
#include "club/CallTrace.h"
#include "club/Traducteur.h"

Marmottes::~Marmottes ()
{
  // nettoyage de l'ancienne table des senseurs
  for (map<string, Senseur *>::iterator iter = senseurs_.begin ();
       iter != senseurs_.end ();
       ++iter)
    delete iter->second;

}

void Marmottes::initialiseSenseurs (const string& nomFichier)
  throw (ClubErreurs, MarmottesErreurs)
{
  // initialisation éventuelle de la table des senseurs
  if (nomFichier != fichier_.nomFichier ())
  {
    InitDomaineMarmottes ();

    // lecture du nouveau fichier
    // la méthode lit peut "lancer" un ClubErreurs
    fichier_.lit (nomFichier);

    // nettoyage de l'ancien dictionnaire
    for (map<string, Senseur *>::iterator iter = senseurs_.begin ();
         iter != senseurs_.end ();
         ++iter)
      delete iter->second;
    senseurs_.clear ();

  }
}


Senseur* Marmottes::recupParNom (const string& nom)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  // C'est la méthode LireSenseur qui "lance" une MarmottesErreurs

  map<string, Senseur *>::iterator found = senseurs_.find (nom);

  if (found == senseurs_.end ())
  { // le senseur n'est pas dans le dictionnaire, on essaie le fichier
    Senseur *s = NULL;
    if ((s = LireSenseur (&fichier_, nom)) != 0)
    { // on incorpore ce nouveau senseur au dictionnaire
      senseurs_ [nom] = s;
      return s;
    }
  }
  else
  { // on retourne un pointeur sur l'élément trouvé dans le dictionnaire
    return found->second;
  }
  return 0;
}


void Marmottes::valideNouvelEtat (double date,
                                 const VecDBL& position,
                                 const VecDBL& vitesse,
                                 const RotDBL& attitude,
                                 const VecDBL& spin)
{ // mémorisation d'un état après résolution
  etat_.reinitialise (date, position, vitesse, attitude);
  etat_.reinitialise (spin);

  // transmission de l'état aux senseurs
  // (les gyros intégrateurs par exemple en ont besoin)
  for (map<string, Senseur *>::iterator iter = senseurs_.begin ();
       iter != senseurs_.end ();
       ++iter)
    iter->second->prendEtatEnCompte (etat_);

}


Marmottes::Marmottes ()
 : initialise_ (false)
{}


Marmottes::Marmottes (const Marmottes& m)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
  : initialise_ (m.initialise_), extrapolationOk_ (m.extrapolationOk_),
    etat_ (m.etat_), solveur_ (m.solveur_), fichier_ (m.fichier_)
{ // constructeur par copie

  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) &m))
      throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->registerObject ((void *) this);
    trace->startCall (string ("Marmottes::copyConstructor"), (void *) this);
    trace->logPointer ((void *) &m);
    trace->endCall ();
  }

  // copie de la table des senseurs
  Senseur *s = NULL;
  for (map<string, Senseur *>::const_iterator iter = m.senseurs_.begin ();
       iter != m.senseurs_.end ();
       ++iter)
    if ((s = LireSenseur (&fichier_, iter->second->nom ())) != 0)
    { // on incorpore ce nouveau senseur dans la table
      senseurs_ [iter->second->nom ()] = s;
    }

  string nom1 ("");
  if (m.solveur_.s1 ())
    nom1 = m.solveur_.s1 ()->nom ();

  string nom2 ("");
  if (m.solveur_.s2 ())
    nom2 = m.solveur_.s2 ()->nom ();

  string nom3 ("");
  if (m.solveur_.s3 ())
    nom3 = m.solveur_.s3 ()->nom ();

  if ((nom1 != "") && (nom2 != "") && (nom3 != ""))
  { // le simulateur était déjà initialisé avec des senseurs existants
    trace->putToSleep();
    try
    {
      senseurs (fichier_.nomFichier (), nom1, nom2, nom3);
    }

    catch (MarmottesErreurs me)
    {
      me.correction ();
    }
    trace->wakeUp();
  }

}


Marmottes& Marmottes::operator = (const Marmottes& m)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ if (&m != this)     // protection contre x = x
  {
    CallTrace *trace = CallTrace::getInstance ();
    if (trace->isActive ())
    {
      if (! trace->isRegistered ((void *) &m))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
      trace->registerObject ((void *) this);
      trace->startCall (string ("Marmottes::operator="), (void *) this);
      trace->logPointer ((void *) &m);
      trace->endCall ();
    }

    initialise_      = m.initialise_;
    extrapolationOk_ = m.extrapolationOk_;
    etat_            = m.etat_;

    solveur_         = m.solveur_;

    fichier_         = m.fichier_;

    // vidage de l'ancienne table des senseurs
    for (map<string, Senseur *>::iterator iter = senseurs_.begin ();
         iter != senseurs_.end ();
         ++iter)
      delete iter->second;
    senseurs_.clear ();

    // copie de la table des senseurs
    Senseur *s = NULL;
    for (map<string, Senseur *>::const_iterator iter = m.senseurs_.begin ();
         iter != m.senseurs_.end ();
         ++iter)
      if ((s = LireSenseur (&fichier_, iter->second->nom ())) != 0)
      { // on incorpore ce nouveau senseur au dictionnaire
        senseurs_ [iter->second->nom ()] = s;
      }

    string nom1 ("");
    if (m.solveur_.s1 ())
      nom1 = m.solveur_.s1 ()->nom ();

    string nom2 ("");
    if (m.solveur_.s2 ())
      nom2 = m.solveur_.s2 ()->nom ();

    string nom3 ("");
    if (m.solveur_.s3 ())
      nom3 = m.solveur_.s3 ()->nom ();

    if ((nom1 != "") && (nom2 != "") && (nom3 != ""))
    { // le simulateur était déjà initialisé avec des senseurs existants
      trace->putToSleep();
      try
      {
        senseurs (fichier_.nomFichier (), nom1, nom2, nom3);
      }

      catch (MarmottesErreurs me)
      {
        me.correction ();
      }
      trace->wakeUp();
    }

  }

  return *this;

}


void Marmottes::reinitialise    (double date,
                                const VecDBL& position, const VecDBL& vitesse,
                                const RotDBL& attitude, const VecDBL& spin,
                                const string& fichier,
                                const string& senseur1,
                                const string& senseur2,
                                const string& senseur3)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{

  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    trace->registerObject ((void *) this);
    trace->startCall (string ("Marmottes::reinitialise"), (void *) this);
    trace->logDouble (date);
    trace->logDouble (position.x ());
    trace->logDouble (position.y ());
    trace->logDouble (position.z ());
    trace->logDouble (vitesse.x ());
    trace->logDouble (vitesse.y ());
    trace->logDouble (vitesse.z ());
    trace->logDouble (attitude.q0 ());
    trace->logDouble (attitude.q1 ());
    trace->logDouble (attitude.q2 ());
    trace->logDouble (attitude.q3 ());
    trace->logDouble (spin.x ());
    trace->logDouble (spin.y ());
    trace->logDouble (spin.z ());
    trace->logString (string (fichier));
    trace->logString (string (senseur1));
    trace->logString (string (senseur2));
    trace->logString (string (senseur3));
    trace->endCall ();
  }

  // mise à jour des attributs
  trace->putToSleep ();
  senseurs (fichier, senseur1, senseur2, senseur3);
  enregistreCorps(-1.0, -1.0, -1.0, -1.0, -1.0,
                  (BodyEphemC::TypeFuncTsid *) NULL,
                  (BodyEphemC::TypeFuncPos *) NULL,
                  (BodyEphemC::TypeFuncPos *) NULL,
                  (BodyEphemC::TypeFuncPos *) NULL);
  trace->wakeUp ();

  valideNouvelEtat (date, position, vitesse, attitude, spin);

  initialise_      = true;
  extrapolationOk_ = true;

}


void Marmottes::senseurs (const string& fichier,
                          const string& senseur1,
                          const string& senseur2,
                          const string& senseur3)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::senseurs"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur1));
    trace->logString (string (senseur2));
    trace->logString (string (senseur3));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // recherche des senseurs
  Senseur *s1 = NULL;
  s1 = recupParNom (senseur1);
  Senseur *s2 = NULL;
  s2 = recupParNom (senseur2);
  Senseur *s3 = NULL;
  s3 = recupParNom (senseur3);

  // reconfiguration du résolveur
  solveur_.reinitialise (s1, s2, s3);

}


void Marmottes::nouveauRepere (const string& fichier,
                               const string& senseur,
                               const RotDBL& nouveau)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::nouveauRepere"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->logDouble (nouveau.q0 ());
    trace->logDouble (nouveau.q1 ());
    trace->logDouble (nouveau.q2 ());
    trace->logDouble (nouveau.q3 ());
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // changement du repère
  s->nouveauRepere (nouveau);

}


void Marmottes::calage (const string& fichier,
                        const string& senseur,
                        double c)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::calage"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->logDouble (c);
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // modification de l'angle de calage du senseur
  s->calage (c);

}


void Marmottes::modifieCible (const string& fichier,
                              const string& senseur,
                              const VecDBL& cible)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::modifieCible"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->logDouble (cible.x ());
    trace->logDouble (cible.y ());
    trace->logDouble (cible.z ());
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // modification de la cible
  s->modifieCible (cible * etat_.coeffPosition ());

}

void Marmottes::initialiseGyro (const string& fichier,
                                const string& senseur,
                                double date, double angle)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::initialiseGyro"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->logDouble (date);
    trace->logDouble (angle);
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // modification de l'angle intégré
  s->initialiseGyro (date, angle);

}

void Marmottes::initialiseDerive (const string& fichier,
                                  const string& senseur,
                                  double derive)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::initialiseDerive"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->logDouble (derive);
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // modification de la dérive
  s->initialiseDerive (derive);

}

void Marmottes::modifieReference (const string& fichier,
                                  const string& senseur,
                                  const RotDBL&       reference)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::modifieReference"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->logDouble (reference.q0 ());
    trace->logDouble (reference.q1 ());
    trace->logDouble (reference.q2 ());
    trace->logDouble (reference.q3 ());
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // modification du repère de référence
  s->modifieReference (reference);

}

void Marmottes::desinitialise  ()
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::desinitialise"), (void *) this);
    trace->endCall ();
    trace->unregisterObject ((void *) this);
  }

  initialise_ = false;
  senseurs_.clear ();
  etat_.desinitialise ();

}

void Marmottes::deuxConsignes (double date,
                               const VecDBL& position, const VecDBL& vitesse,
                               double m1, double m2,
                               RotDBL *attitude, VecDBL *spin)
  throw (CantorErreurs, MarmottesErreurs)
{ // calcul d'une attitude donnée par seulement deux consignes

  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::deuxConsignes"), (void *) this);
    trace->logDouble (date);
    trace->logDouble (position.x ());
    trace->logDouble (position.y ());
    trace->logDouble (position.z ());
    trace->logDouble (vitesse.x ());
    trace->logDouble (vitesse.y ());
    trace->logDouble (vitesse.z ());
    trace->logDouble (m1);
    trace->logDouble (m2);
    trace->endCall ();
  }

  // pour éviter les confusions, on impose que les mesures m1 et m2 données
  // par l'utilisateur soient celles de ses premiers senseurs
  // ceux-ci doivent donc être compatibles
  // (on sait qu'alors Marmottes n'a rien réordonné et que le modèle courant
  //  porte bien sur ces deux premiers senseurs)
  if (solveur_.s1 ()->methode () != solveur_.s2 ()->methode ())
    throw MarmottesErreurs (MarmottesErreurs::types_incompatibles,
                            solveur_.s1 ()->nom ().c_str (),
                            solveur_.s2 ()->nom ().c_str ());

  // extrapolation de l'attitude
  *attitude = etat_.attitudeExtrapolee (date);
  *spin     = etat_.spin ();
  Etat etatEstime (etat_);
  etatEstime.reinitialise (date, position, vitesse, *attitude);
  etatEstime.reinitialise (*spin);

  Senseur *s1 = solveur_.s1 ();
  Senseur *s2 = solveur_.s2 ();

  s1->modeliseConsigne (etatEstime, m1);
  s2->modeliseConsigne (etatEstime, m2);

  if (extrapolationOk_ && (solveur_.s1 () != 0))
  { // tentative de calcul par simple extrapolation du mouvement précédent

    // mesures produites dans l'attitude extrapolée
    double m1Extrapolee = s1->mesure (etatEstime);
    double m2Extrapolee = s2->mesure (etatEstime);

    // test de tolérance de l'erreur d'extrapolation
    if ((fabs (m1Extrapolee - m1) <= 0.1 * s1->precision ())
        &&
        (fabs (m2Extrapolee - m2) <= 0.1 * s2->precision ())
        &&
        s1->controlable (etatEstime)
        &&
        s2->controlable (etatEstime))
    { // l'extrapolation respecte les consignes, on la valide
      valideNouvelEtat (date, position, vitesse, *attitude, *spin);
      if (trace->isActive ())
      {
        trace->startResult ();
        trace->logDouble (attitude->q0 ());
        trace->logDouble (attitude->q1 ());
        trace->logDouble (attitude->q2 ());
        trace->logDouble (attitude->q3 ());
        trace->logDouble (spin->x ());
        trace->logDouble (spin->y ());
        trace->logDouble (spin->z ());
        trace->endResult ();
      }
      return;
    }

  }

  // l'extrapolation a échoué, il faut faire un calcul complet

  // mise à jour de la modélisation des mesures dans les senseurs
  solveur_.modeliseConsignes (etat_, etatEstime, m1, m2);

  // application du modèle à deux consignes
  SpinAtt sol;
  solveur_.deuxConsignes (&sol);

  *attitude = sol.attitude ();
  *spin     = sol.spin     ();

  // mise à jour de l'état de référence et de l'état extrapolé
  valideNouvelEtat (date, position, vitesse, *attitude, *spin);

  if (trace->isActive ())
  {
    trace->startResult ();
    trace->logDouble (attitude->q0 ());
    trace->logDouble (attitude->q1 ());
    trace->logDouble (attitude->q2 ());
    trace->logDouble (attitude->q3 ());
    trace->logDouble (spin->x ());
    trace->logDouble (spin->y ());
    trace->logDouble (spin->z ());
    trace->endResult ();
  }

}


void  Marmottes::attitude (double date,
                           const VecDBL& position, const VecDBL& vitesse,
                           double m1, double m2, double m3,
                           RotDBL *attitude, VecDBL *spin)
  throw (CantorErreurs, MarmottesErreurs)
{ // calcul d'une attitude donnée par trois consignes

  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::attitude"), (void *) this);
    trace->logDouble (date);
    trace->logDouble (position.x ());
    trace->logDouble (position.y ());
    trace->logDouble (position.z ());
    trace->logDouble (vitesse.x ());
    trace->logDouble (vitesse.y ());
    trace->logDouble (vitesse.z ());
    trace->logDouble (m1);
    trace->logDouble (m2);
    trace->logDouble (m3);
    trace->endCall ();
  }

  // extrapolation de l'attitude
  *attitude = etat_.attitudeExtrapolee (date);
  *spin     = etat_.spin ();
  Etat etatEstime (etat_);
  etatEstime.reinitialise (date, position, vitesse, *attitude);
  etatEstime.reinitialise (*spin);

  Senseur *s1 = solveur_.s1 ();
  Senseur *s2 = solveur_.s2 ();
  Senseur *s3 = solveur_.s3 ();

  s1->modeliseConsigne (etatEstime, m1);
  s2->modeliseConsigne (etatEstime, m2);
  s3->modeliseConsigne (etatEstime, m3);

  if (extrapolationOk_ && (solveur_.s1 () != 0))
  { // tentative de calcul par simple extrapolation du mouvement précédent

    // mesures produites dans l'attitude extrapolée
    double m1Extrapolee = s1->mesure (etatEstime);
    double m2Extrapolee = s2->mesure (etatEstime);
    double m3Extrapolee = s3->mesure (etatEstime);

    // test de tolérance de l'erreur d'extrapolation et de la contrôlabilité
    if ((fabs (m1Extrapolee - m1) <= 0.1 * s1->precision ())
        &&
        (fabs (m2Extrapolee - m2) <= 0.1 * s2->precision ())
        &&
        (fabs (m3Extrapolee - m3) <= 0.1 * s3->precision ())
        &&
        s1->controlable (etatEstime)
        &&
        s2->controlable (etatEstime)
        &&
        s3->controlable (etatEstime))
    { // l'extrapolation respecte les consignes, on la valide
      valideNouvelEtat (date, position, vitesse, *attitude, *spin);
      if (trace->isActive ())
      {
        trace->startResult ();
        trace->logDouble (attitude->q0 ());
        trace->logDouble (attitude->q1 ());
        trace->logDouble (attitude->q2 ());
        trace->logDouble (attitude->q3 ());
        trace->logDouble (spin->x ());
        trace->logDouble (spin->y ());
        trace->logDouble (spin->z ());
        trace->endResult ();
      }
      return;
    }

  }

  // l'extrapolation a échoué, il faut faire un calcul complet

  // mise à jour de la modélisation des mesures dans les senseurs
  solveur_.modeliseConsignes (etat_, etatEstime, m1, m2, m3);

  // résolution du modèle pour respecter la troisième consigne
  // cette méthode peut "lancer" un CantorErreurs
  solveur_.trouveTout ();

  // filtrage des solutions engendrées par la modélisation mathématique
  solveur_.elimineExcedentaires ();

  // récupération de la "meilleure" solution
  SpinAtt sol = solveur_.selection ();
  *attitude   = sol.attitude ();
  *spin       = sol.spin     ();

  // mise à jour de l'état de référence et de l'état extrapolé
  valideNouvelEtat (date, position, vitesse, *attitude, *spin);

  if (trace->isActive ())
  {
    trace->startResult ();
    trace->logDouble (attitude->q0 ());
    trace->logDouble (attitude->q1 ());
    trace->logDouble (attitude->q2 ());
    trace->logDouble (attitude->q3 ());
    trace->logDouble (spin->x ());
    trace->logDouble (spin->y ());
    trace->logDouble (spin->z ());
    trace->endResult ();
  }
}

void Marmottes::imposeAttitude (double date,
                                const VecDBL& position, const VecDBL& vitesse,
                                const RotDBL& attit) 
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::imposeAttitude"), (void *) this);
    trace->logDouble (date);
    trace->logDouble (position.x ());
    trace->logDouble (position.y ());
    trace->logDouble (position.z ());
    trace->logDouble (vitesse.x ());
    trace->logDouble (vitesse.y ());
    trace->logDouble (vitesse.z ());
    trace->logDouble (attit.q0 ());
    trace->logDouble (attit.q1 ());
    trace->logDouble (attit.q2 ());
    trace->logDouble (attit.q3 ());
    trace->endCall ();
  }

  // calcul du spin
  VecDBL spin = etat_.spinExtrapole (date, attit);

  // mise à jour de l'état
  valideNouvelEtat (date, position, vitesse, attit, spin);

}

void Marmottes::imposeSpin (double date,
                            const VecDBL& position, const VecDBL& vitesse,
                            const VecDBL& spin) 
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::imposeSpin"), (void *) this);
    trace->logDouble (date);
    trace->logDouble (position.x ());
    trace->logDouble (position.y ());
    trace->logDouble (position.z ());
    trace->logDouble (vitesse.x ());
    trace->logDouble (vitesse.y ());
    trace->logDouble (vitesse.z ());
    trace->logDouble (spin.x ());
    trace->logDouble (spin.y ());
    trace->logDouble (spin.z ());
    trace->endCall ();
  }

  double dtSur2    = 43200.0 * (date - etat_.date ());
  double demiAngle = spin.norme () * dtSur2;

  double sinCardinal;
  if (fabs (demiAngle) < 4.0e-4)
  { // si l'angle est trop petit, on utilise un développement limité
    // pour calculer sin (alpha) / alpha. En se limitant à l'ordre 4,
    // on obtient les erreurs relatives suivantes : 8.1e-25 sur
    // la valeur, 9.1e-17 pour la dérivée (pour des demi-angles
    // inférieurs à 4e-4)
    double alpha2 = demiAngle * demiAngle;
    sinCardinal = (120.0 - alpha2 * (20.0 - alpha2)) / 120.0;
  }
  else
    sinCardinal = sin (demiAngle) / demiAngle;

  // rotation autour de l'axe de spin depuis la date de l'attitude précédente
  double q0 = cos (demiAngle);
  VecDBL q  = spin * (sinCardinal * dtSur2);
  RotDBL evolution (q0, q.x (), q.y (), q.z ());

  // calcul de l'attitude après évolution
  RotDBL attit = evolution (etat_.attitude ());

  // mise à jour de l'état
  valideNouvelEtat (date, position, vitesse, attit, spin);

}


void Marmottes::repereBase (const string& fichier,
                            const string& senseur,
                            RotDBL *r)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::repereBase"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // récupération du repère de base
  *r = s->repereBase ();

  if (trace->isActive ())
  {
    trace->startResult ();
    trace->logDouble (r->q0 ());
    trace->logDouble (r->q1 ());
    trace->logDouble (r->q2 ());
    trace->logDouble (r->q3 ());
    trace->endResult ();
  }

}


void Marmottes::repere (const string& fichier,
                        const string& senseur,
                        RotDBL *r)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::repere"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // récupération du repère courant
  *r = s->repere ();

  if (trace->isActive ())
  {
    trace->startResult ();
    trace->logDouble (r->q0 ());
    trace->logDouble (r->q1 ());
    trace->logDouble (r->q2 ());
    trace->logDouble (r->q3 ());
    trace->endResult ();
  }

}


void Marmottes::mesure (const string& fichier,
                        const string& senseur, double *m)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::mesure"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // calcul de la mesure
  *m = s->mesure (etat_);

  if (trace->isActive ())
  {
    trace->startResult ();
    trace->logDouble (*m);
    trace->endResult ();
  }

}


void Marmottes::controlable (const string& fichier,
                             const string& senseur, int *c)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::controlable"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // calcul de la contrôlabilité
  *c = s->controlable (etat_);

  if (trace->isActive ())
  {
    trace->startResult ();
    trace->logInt (*c);
    trace->endResult ();
  }

}


void Marmottes::criteresControlabilite (const string& fichier,
                                        const string& senseur,
                                        Senseur::codeAstre *inhibant,
                                        Senseur::codeAstre *eclipsant,
                                        double *ecartFrontiere,
                                        bool *amplitudeSignificative) 
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::criteresControlabilite"),
                      (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // calcul des critères
  s->criteresControlabilite (etat_, inhibant, eclipsant,
                             ecartFrontiere, amplitudeSignificative);

  if (trace->isActive ())
  {
    trace->startResult ();
    switch (*inhibant)
    {
      case Senseur::nonSignificatif :
        trace->logString ("nonSignificatif");
        break;
      case Senseur::soleil :
        trace->logString ("soleil");
        break;
      case Senseur::lune :
        trace->logString ("lune");
        break;
      case Senseur::corpsCentral :
        trace->logString ("corpsCentral");
        break;
      case Senseur::aucunAstre :
        trace->logString ("aucunAstre");
        break;
      default :
        trace->logString ("???");
        break;
    }
    switch (*eclipsant)
    {
      case Senseur::nonSignificatif :
        trace->logString ("nonSignificatif");
        break;
      case Senseur::soleil :
        trace->logString ("soleil");
        break;
      case Senseur::lune :
        trace->logString ("lune");
        break;
      case Senseur::corpsCentral :
        trace->logString ("corpsCentral");
        break;
      case Senseur::aucunAstre :
        trace->logString ("aucunAstre");
        break;
      default :
        trace->logString ("???");
        break;
    }
    trace->logDouble   (*ecartFrontiere);
    trace->logBool     (*amplitudeSignificative);
    trace->endResult   ();
  }

}

void Marmottes::unitesPositionVitesse (const string& unitePos,
                                       const string& uniteVit)
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::unitesPositionVitesse"), (void *) this);
    trace->logString (string (unitePos));
    trace->logString (string (uniteVit));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture

  // prise en compte des nouvelles unités
  string unitePosTrad (TraduitVersInterne (unitePos.c_str ()));
  string uniteVitTrad (TraduitVersInterne (uniteVit.c_str ()));
  etat_.unitesPositionVitesse (unitePosTrad, uniteVitTrad);

}


void Marmottes::respecterConsignes (const string& fichier,
                                    const string& senseur)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::respecterConsignes"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // initialisation de la non-conversion
  s->respecterConsignes ();

}


void Marmottes::convertirConsignes (const string& fichier,
                                    const string& senseur)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::convertirConsignes"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // initialisation de la conversion
  s->convertirConsignes ();

}


void Marmottes::respecterMesures (const string& fichier,
                                  const string& senseur)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::respecterMesures"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // initialisation de la non-conversion
  s->respecterMesures ();

}


void Marmottes::convertirMesures (const string& fichier,
                                  const string& senseur)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::convertirMesures"), (void *) this);
    trace->logString (string (fichier));
    trace->logString (string (senseur));
    trace->endCall ();
  }

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  Senseur *s = NULL;
  s = recupParNom (senseur);

  // initialisation de la conversion
  s->convertirMesures ();

}

void Marmottes::wMax (double omega)
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::wMax"), (void *) this);
    trace->logDouble (omega);
    trace->endCall ();
  }

  solveur_.miseAJourOmegaMax (omega);

}

void Marmottes::convergence (double seuil)
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::convergence"), (void *) this);
    trace->logDouble (seuil);
    trace->endCall ();
  }

  solveur_.miseAJourConvergence (seuil);

}

void Marmottes::dichotomie (int tranches)
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::dichotomie"), (void *) this);
    trace->logInt (tranches);
    trace->endCall ();
  }

  solveur_.miseAJourDichotomie (tranches);

}

void Marmottes::autoriseExtrapolation ()
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::autoriseExtrapolation"),
                      (void *) this);
    trace->endCall ();
  }

  extrapolationOk_ = true;

}

void Marmottes::interditExtrapolation ()
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::interditExtrapolation"),
                      (void *) this);
    trace->endCall ();
  }

  extrapolationOk_ = false;

}

Senseur* Marmottes::accesSenseur(const string& fichier,
                                 const string& senseur) 
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  // Méthode qui renvoie le pointeur sur le senseur initialisé
  // par le fichier et son nom
  Senseur * s;

  // vérification de la possibilité de lecture
  initialiseSenseurs (fichier);

  // récupération du senseur
  s = recupParNom (senseur);

  return s;
}

void Marmottes::enregistreCorps (double equatorialRadius, 
                                 double oblateness, double rotationVelocity,
                                 double moonRadius, double sunRadius,
                                 BodyEphemC::TypeFuncTsid *tsidFunc, 
                                 BodyEphemC::TypeFuncPos *sunFunc, BodyEphemC::TypeFuncPos *moonFunc, 
                                 BodyEphemC::TypeFuncPos *earthFunc)
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::enregistreCorps"), (void *) this);
    trace->logDouble (equatorialRadius);
    trace->logDouble (oblateness);
    trace->logDouble (rotationVelocity);
    trace->logDouble (moonRadius);
    trace->logDouble (sunRadius);
    trace->logPointer ((void *) tsidFunc);
    trace->logPointer ((void *) sunFunc);
    trace->logPointer ((void *) moonFunc);
    trace->logPointer ((void *) earthFunc);
    trace->endCall ();
  }

  etat_.enregistreCorps(equatorialRadius, oblateness, rotationVelocity,
                        moonRadius, sunRadius,
                        tsidFunc, sunFunc, moonFunc, earthFunc);
}

void Marmottes::enregistreCorps (double equatorialRadius, 
                                 double oblateness, double rotationVelocity, 
                                 double moonRadius, double sunRadius,
                                 BodyEphemF::TypeFuncTsid *tsidFunc, 
                                 BodyEphemF::TypeFuncPos *sunFunc, BodyEphemF::TypeFuncPos *moonFunc, 
                                 BodyEphemF::TypeFuncPos *earthFunc)
  throw (MarmottesErreurs)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::enregistreCorps"), (void *) this);
    trace->logDouble (equatorialRadius);
    trace->logDouble (oblateness);
    trace->logDouble (rotationVelocity);
    trace->logDouble (moonRadius);
    trace->logDouble (sunRadius);
    trace->logPointer ((void *) tsidFunc);
    trace->logPointer ((void *) sunFunc);
    trace->logPointer ((void *) moonFunc);
    trace->logPointer ((void *) earthFunc);
    trace->endCall ();
  }

  etat_.enregistreCorps(equatorialRadius, oblateness, rotationVelocity, 
                        moonRadius, sunRadius,
                        tsidFunc, sunFunc, moonFunc, earthFunc);
}

void Marmottes::lireParametres  (double *ptrDate,
                                 VecDBL *ptrPosition, VecDBL *ptrVitesse, 
                                 RotDBL *ptrAttitude, VecDBL *ptrSpin) 
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive ())
  {
    if (! trace->isRegistered ((void *) this))
        throw MarmottesErreurs (MarmottesErreurs::objet_inconnu);
    trace->startCall (string ("Marmottes::lireParametres"), (void *) this);
    trace->logDouble (*ptrDate);
    trace->logDouble (ptrPosition->x ());
    trace->logDouble (ptrPosition->y ());
    trace->logDouble (ptrPosition->z ());
    trace->logDouble (ptrVitesse->x ());
    trace->logDouble (ptrVitesse->y ());
    trace->logDouble (ptrVitesse->z ());
    trace->logDouble (ptrAttitude->q0 ());
    trace->logDouble (ptrAttitude->q1 ());
    trace->logDouble (ptrAttitude->q2 ());
    trace->logDouble (ptrAttitude->q3 ());
    trace->logDouble (ptrSpin->x ());
    trace->logDouble (ptrSpin->y ());
    trace->logDouble (ptrSpin->z ());
    trace->endCall ();
  }

  // recuperation des valeurs courantes
  *ptrDate     = etat_.date();
  *ptrPosition = etat_.position();
  *ptrVitesse  = etat_.vitesse();
  *ptrAttitude = etat_.attitude();
  *ptrSpin     = etat_.spin();

  if (trace->isActive ())
  {
    trace->startResult ();
    trace->logDouble (*ptrDate);
    trace->logDouble (ptrPosition->x ());
    trace->logDouble (ptrPosition->y ());
    trace->logDouble (ptrPosition->z ());
    trace->logDouble (ptrVitesse->x ());
    trace->logDouble (ptrVitesse->y ());
    trace->logDouble (ptrVitesse->z ());
    trace->logDouble (ptrAttitude->q0 ());
    trace->logDouble (ptrAttitude->q1 ());
    trace->logDouble (ptrAttitude->q2 ());
    trace->logDouble (ptrAttitude->q3 ());
    trace->logDouble (ptrSpin->x ());
    trace->logDouble (ptrSpin->y ());
    trace->logDouble (ptrSpin->z ());
    trace->endResult ();
  }

}
