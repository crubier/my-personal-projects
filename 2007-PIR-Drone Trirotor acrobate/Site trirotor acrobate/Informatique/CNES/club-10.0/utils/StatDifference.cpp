////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Bibam
//$Application
//        Club
//$Nom
//
//$Resume
//       fichier d'implantation de la classe StatDifference
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       inline const char* trad()
//>       class StatDifference
//>         traiterDifference()           
//>         calculerStat()
//>         afficherSynthese()
//$Historique
//       $Log: StatDifference.cpp,v $
//       Revision 1.10  2000/09/07 08:42:03  club
//       utilisation de string de la STL au lieu de ChaineSimple conformément
//       aux évolutions réalisées sur les classes de l'interface publique de club.
//
//       Revision 1.9  2000/08/04 09:45:46  club
//       calcul et affichage du décalage maximal rencontré.
//
//       Revision 1.8  2000/08/03 08:33:46  club
//       modification des chaînes max et min en maximum et minimum.
//
//       Revision 1.7  2000/07/28 13:03:00  club
//       Ajout de la valeur du seuil max toléré dans la synthèse.
//
//       Revision 1.6  2000/07/26 12:19:17  club
//       Modification du test permettant d'affecter une valeur à minMessage.
//
//       Revision 1.5  2000/07/26 09:49:13  club
//       Modification des #include suite au déplacement des fichiers .h dans
//       le répertoire club/utils.
//
//       Revision 1.4  2000/07/26 07:34:25  club
//       modification des méthodes de la classe pour fournir de nouvelles
//       options à l'utilisateur (ne pas afficher les messages par exemple)
//       et pour améliorer les informations fournies dans la synthèse
//       (numéros des messages affichés, moyenne des erreurs numériques ...).
//
//       Revision 1.3  2000/07/07 12:08:06  club
//       création des méthodes permettant de calculer et d'afficher des
//       statistiques sur les différences numériques rencontrées.
//       modification de l'attribut nbMessagesDiffMax_ en un tableau à deux
//       éléments qui indiquent l'intervalle des messages à afficher.
//
//       Revision 1.2  2000/07/06 07:31:19  club
//       modification de l'attribut nbMessagesDiffMax_ (représentant le
//       nombre maximal de messages de différence à afficher) en un tableau
//       à deux éléments qui indiquent respectivement le numéro du premier
//       et le numéro du dernier message à afficher
//
//       Revision 1.1  2000/07/03 09:36:58  club
//       création de cette classe permettant de gérer les statistiques de difference
//
//$Version
//       $Id: StatDifference.cpp,v 1.10 2000/09/07 08:42:03 club Exp $
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


#include "StatDifference.h"


// permet de traduire les messages de différence
inline const char* trad (const char* s) { return TraduitFormatCVersExterne (s); }


bool StatDifference::traiterDifference ()
{
  nbErrAffichees_++;

  if (afficherMessages_ == false)
    return false;

  if ((!nbMessagesDiffFini_) ||
      (nbErrAffichees_ >= messagesAffiches_ [0]) &&
      (nbErrAffichees_ <= messagesAffiches_ [1]))
  {
    return true;
  }

  return false;
}


void StatDifference::calculerStat (double& errMinRelative, double& errMaxRelative, 
                                   double& moyenne)
{
  if (nbDifferencesNumeriques_ > 0)
  {
    errMinRelative = differencesNumeriques_ [1];
    errMaxRelative = differencesNumeriques_ [1];
    double total = differencesNumeriques_ [1];

    for (int i=2;i<=nbDifferencesNumeriques_;i++)
    {
      if (differencesNumeriques_[i] < errMinRelative)
        errMinRelative = differencesNumeriques_ [i];
      
      if (differencesNumeriques_[i] > errMaxRelative)
        errMaxRelative =  differencesNumeriques_ [i];

      total += differencesNumeriques_ [i];
    }
    
    moyenne = total / nbDifferencesNumeriques_;
  }
  else
  {
    errMinRelative = 0;
    errMaxRelative = 0;
    moyenne = 0;
  }  
}


void StatDifference::afficherSynthese (const double precision, const int decalage)
{
  if (afficherSynthese_ == false)
    return;

  char* tampon = new char [1024];

  double errMaxRelative;
  double errMinRelative;
  double moyenne;

  calculerStat (errMinRelative, errMaxRelative, moyenne);

  int minMessage = 0;
  int maxMessage = 0;

  if ((! nbMessagesDiffFini_) && (nbErrAffichees_ > 0))
  {
    minMessage = 1;
    maxMessage = nbErrAffichees_;    
  }
  else if (nbErrAffichees_ < messagesAffiches_ [0])
  {
    minMessage = 0;
    maxMessage = 0;
  }
  else if (nbErrAffichees_ <= messagesAffiches_ [1])
  {
    minMessage = messagesAffiches_ [0];
    maxMessage = nbErrAffichees_;
  }
  else
  {
    minMessage = messagesAffiches_ [0];
    maxMessage = messagesAffiches_ [1];
  }


  // on retourne le resultat

  (void) sprintf (tampon, trad ("nombre de messages de difference      : %d"),
                  nbErrAffichees_);
  cout << tampon << endl;

  if (afficherMessages_)
  {
    (void) sprintf (tampon, trad ("numeros des messages affiches         : %d a %d"),
                    minMessage, maxMessage, nbErrAffichees_);
    cout << tampon << endl;
  }

  (void) sprintf (tampon, trad ("nombre d'erreurs non acceptees        : %d\n"
                                "\t%d erreur(s) numerique(s)\n"
                                "\t%d erreur(s) lexicale(s)"),
                  nbErrNonAcceptees_, nbErrNonAccepteesNumeriques_,
                  nbErrNonAcceptees_ - nbErrNonAccepteesNumeriques_);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("nombre d'erreurs numeriques acceptees : %d"),
                  nbErrAcceptees_);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("decalage maximal rencontre            : %d"),
                  decalage);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("seuil de tolerance numerique          : %12.6e"),
                  precision);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("erreur numerique minimale             : %12.6e"),
                  errMinRelative);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("erreur numerique maximale             : %12.6e"),
                  errMaxRelative);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("moyenne des erreurs numeriques        : %12.6e"),
                  moyenne);
  cout << tampon << endl;
}
