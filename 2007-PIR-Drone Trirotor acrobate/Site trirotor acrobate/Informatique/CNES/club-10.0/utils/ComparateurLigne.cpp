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
//>       ComparateurLigne.cpp
//$Resume
//       fichier d'implantation de la classe ComparateurLigne
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       inline const char* trad()
//>       class ComparateurLigne   
//>         initialiser()           
//>         analyserLigne()
//>         lexemesSuivantsIdentiques()        
//>         comparerLigne()
//>         formaterMessage()
//>         comparerLexeme()       
//$Historique
//       $Log: ComparateurLigne.cpp,v $
//       Revision 1.11  2003/02/03 14:46:11  club
//       DM-ID 17 Mise à jour de l'extensions du fichier dans le bandeau
//
//       Revision 1.10  2001/06/22 05:38:50  club
//       inclusion de cmath
//
//       Revision 1.9  2001/05/03 13:22:38  club
//       élimination d'une violation mémoire lors de l'affichage des
//       différences entres lignes très longues (merci à Ole Kristian
//       Kverneland)
//
//       Revision 1.8  2000/09/11 13:19:07  club
//       suppression des blancs au début des chaînes à analyser.
//
//       Revision 1.7  2000/09/07 08:42:02  club
//       utilisation de string de la STL au lieu de ChaineSimple conformément
//       aux évolutions réalisées sur les classes de l'interface publique de club.
//
//       Revision 1.6  2000/08/03 08:32:23  club
//       utilisation d'un code de retour plutôt que la levée d'une exception
//       pour la fonction analyserLigne.
//
//       Revision 1.5  2000/07/28 13:04:28  club
//       amélioration de la forme des messages de différence
//
//       Revision 1.4  2000/07/26 09:49:13  club
//       Modification des #include suite au déplacement des fichiers .h dans
//       le répertoire club/utils.
//
//       Revision 1.3  2000/07/26 07:36:32  club
//       modification importante de la classe pour améliorer le recalage
//       des analyseurs lexicaux lorsque certains lexèmes sont propres
//       à un seul d'entre eux. Amélioration des algorithmes pour diminuer
//       leur complexité et donc le temps de calcul.
//
//       Revision 1.2  2000/07/07 12:09:34  club
//       création d'une méthode permettant de formater le message de différence.
//       suppression du formatage du message de la fonction comparerLigne.
//
//       Revision 1.1  2000/07/03 09:37:51  club
//       création de cette classe permettant de comparer deux lignes d'un fichier
//       tout en acceptant une imprécision numérique sur les réels
//
//$Version
//       $Id: ComparateurLigne.cpp,v 1.11 2003/02/03 14:46:11 club Exp $
//$Auteur
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "ComparateurLigne.h"


// permet de traduire les messages de différence
inline const char* trad (const char* s) { return TraduitFormatCVersExterne (s); }


// initialisation du comparateur de lignes
void ComparateurLigne::initialiser (const string& cres, int numLigneRes,
                                    const string& cref, int numLigneRef)
{
  // enregistrement des lignes à comparer (utile pour la formation des messages)
  ligneRes_ = cres;
  ligneRef_ = cref;

  // suppression des blancs initiaux
  int pos = ligneRes_.find_first_not_of ("\n\t\v\b\r ");
  ligneRes_.erase (0, pos);

  pos = ligneRef_.find_first_not_of ("\n\t\v\b\r ");
  ligneRef_.erase (0, pos);

  // enregistrement des numéros des lignes (utile pour la formation des messages)
  numeroLigneRes_ = numLigneRes;
  numeroLigneRef_ = numLigneRef;

  // reinitialisation des analyseurs lexicaux avec les chaines cres et cref
  alres_.reinitialise (ligneRes_);
  alref_.reinitialise (ligneRef_);
}


int ComparateurLigne::analyserLigne (StatDifference& stats)
{
  int nbErreursDansLigne = 0;
  int pos = 0;
  string chaine;

  string chres, chref;
  char *tampon = 0;

  // on se replace sur le premier lexème
  alres_.redemarre (); alres_.suivant ();
  alref_.redemarre (); alref_.suivant ();

  // analyse lexème par lexème jusqu'à arriver à la fin d'une ligne
  while ((alres_.type () != AnalyseurLexical::codeFin) && 
         (alref_.type () != AnalyseurLexical::codeFin))
  {
    // comparaison du premier lexème de alres_ avec le premier lexème de alref_
    double diff = 0;
    int estDifferent = comparerLexeme (diff);

    if (estDifferent == 0) 
    {
      // les lexèmes sont identiques

      if (diff > 0)
      {
        // l'égalité des deux lexèmes est à diff près. On met à jour les statistiques
        stats.majDifferencesNumeriques (diff);
        stats.majNbErrAcceptees ();
      }
      
      // les deux lexèmes ont été analysés, on les supprime de
      // respectivement alres_ et alref_
      chres = alres_.chaine ().substr (alres_.lexeme ().size (), 
                                       alres_.chaine ().size ());
      pos = chres.find_first_not_of ("\n\t\v\b\r ");
      chres.erase (0, pos);
      alres_.reinitialise (chres);
      alres_.suivant ();

      chref = alref_.chaine ().substr (alref_.lexeme ().size (), 
                                       alref_.chaine ().size ());
      pos = chref.find_first_not_of ("\n\t\v\b\r ");
      chref.erase (0, pos);
      alref_.reinitialise (chref);
      alref_.suivant ();
    }
    else
    {
      // les lexèmes sont différents
      chaine = "";

      // recherche des deux lexèmes suivants identiques
      int indiceRes, indiceRef;
      lexemesSuivantsIdentiques (indiceRes, indiceRef);

      alres_.redemarre (); alres_.suivant ();
      alref_.redemarre (); alref_.suivant ();
      int i = 1;
      int j = 1;

      while ((i < indiceRes) && (j < indiceRef))
      {
        nbErreursDansLigne++;
        // deux lexèmes suivants sont différents
        estDifferent = comparerLexeme (diff);

        // mise à jour des statistiques
        stats.majNbErrNonAcceptees ();
        if (estDifferent == 3)
        {
          // si les deux lexèmes sont des valeurs numériques différentes,
          // il faut mettre à jour l'erreur max relative
          stats.majNbErrNonAccepteesNumeriques ();
          stats.majDifferencesNumeriques (diff);
        }

        // formation du message
        formaterMessage (estDifferent, diff);
        
        // les deux lexèmes ont été analysés, on les supprime de 
        // respectivement alres_ et alref_
        chres = alres_.chaine ().substr (alres_.lexeme ().size (),
                                         alres_.chaine ().size ());
        pos = chres.find_first_not_of ("\n\t\v\b\r ");
        chres.erase (0, pos);
        alres_.reinitialise (chres);
        alres_.suivant ();
        
        chref = alref_.chaine ().substr (alref_.lexeme ().size (), 
                                         alref_.chaine ().size ());
        pos = chref.find_first_not_of ("\n\t\v\b\r ");
        chref.erase (0, pos);
        alref_.reinitialise (chref);
        alref_.suivant ();

        i++;
        j++;
      }

      int lexemesEnPlus = 0;

      while (i < indiceRes)
      {
        lexemesEnPlus = 1;
        chaine += " ";
        chaine += alres_.lexeme ();
        
        // suppression du lexème dans alres_
        string chres = alres_.chaine ().substr (alres_.lexeme ().size (), 
                                                alres_.chaine ().size ());
        pos = chres.find_first_not_of ("\n\t\v\b\r ");
        chres.erase (0, pos);
        alres_.reinitialise (chres);
        alres_.suivant ();
        i++;
      }
      
      while (j < indiceRef)
      {
        lexemesEnPlus = -1;
        chaine += " ";
        chaine += alref_.lexeme ();

        // suppression du lexème de alref_
        string chref = alref_.chaine ().substr (alref_.lexeme ().size (), 
                                                alref_.chaine ().size ());
        pos = chref.find_first_not_of ("\n\t\v\b\r ");
        chref.erase (0, pos);
        alref_.reinitialise (chref);
        alref_.suivant ();
        j++;
      }

      switch (lexemesEnPlus)
      {
        case 0 : // pas de repositionnement à effectuer
          break;

        case 1 : // lexèmes en plus dans alres_
          nbErreursDansLigne++;

          pos = chaine.find_first_not_of ("\n\t\v\b\r ");
          chaine.erase (0, pos);

          // mise à jour des statistiques
          stats.majNbErrNonAcceptees ();

          // formation du message
          tampon = new char [strlen (trad ("la chaine \"%s\" est en"
                                           " plus :\n%s,%d : %s\n"
                                           "%s,%d : %s"))
                            + chaine.size ()
                            + nomFichierRes_.size ()
                            + ligneRes_.size ()
                            + nomFichierRef_.size ()
                            + ligneRef_.size ()
                            + 100];
          (void) sprintf (tampon, trad ("la chaine \"%s\" est en plus :\n%s,%d : %s\n%s,%d : %s"),
                          chaine.c_str (),
                          nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                          nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
          messageDiff_ = tampon;
          delete[] tampon;
          break;

        case -1 : // lexèmes en moins dans alres_
          nbErreursDansLigne++;

          pos = chaine.find_first_not_of ("\n\t\v\b\r ");
          chaine.erase (0, pos);

          // mise à jour des statistiques
          stats.majNbErrNonAcceptees ();

          // formation du message
          tampon = new char [strlen (trad ("la chaine \"%s\" manque :\n"
                                           "%s,%d : %s\n%s,%d : %s"))
                            + chaine.size ()
                            + nomFichierRes_.size ()
                            + ligneRes_.size ()
                            + nomFichierRef_.size ()
                            + ligneRef_.size ()
                            + 100];
          (void) sprintf (tampon, trad ("la chaine \"%s\" manque :\n%s,%d : %s\n%s,%d : %s"),
                          chaine.c_str (), 
                          nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                          nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
          messageDiff_ = tampon;
          delete[] tampon;
          break;

        default :
          // ce cas ne se produit pas
          break;
      }
    }
  
    // alres_ et alref_ ont été réinitialisés avec une chaine ne comportant 
    // plus les lexèmes analysés. Les deux analyseurs sont positionner sur 
    // leur premier lexème

  } // fin de la boucle sur les lexèmes

  // on teste pour savoir si on est bien au bout de la ligne pour
  // les deux analyseurs lexicaux

  if (alres_.type () != AnalyseurLexical::codeFin)
  {
    // une erreur supplémentaire dans la ligne
    nbErreursDansLigne++;
    stats.majNbErrNonAcceptees ();
    
    // il reste des lexèmes dans le tampon résultat
    chaine = alres_.chaine ().substr (alref_.chaine ().size (), 
                                      alres_.chaine ().size ());
    
    tampon = new char [strlen (trad ("la chaine \"%s\" est en plus :\n"
                                     "%s,%d : %s\n%s,%d : %s"))
                      + chaine.size ()
                      + nomFichierRes_.size ()
                      + ligneRes_.size ()
                      + nomFichierRef_.size ()
                      + ligneRef_.size ()
                      + 100];
    (void) sprintf (tampon, trad ("la chaine \"%s\" est en plus :\n%s,%d : %s\n%s,%d : %s"),
                    chaine.c_str (), 
                    nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                    nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
    messageDiff_ = tampon;
    delete[] tampon;
  }
  
  else if (alref_.type () != AnalyseurLexical::codeFin)
  {
    // une erreur supplémentaire dans la ligne
    nbErreursDansLigne++;
    stats.majNbErrNonAcceptees ();

    // il reste des lexèmes dans le tampon référence
    chaine = alref_.chaine ().substr (alres_.chaine ().size (), 
                                      alref_.chaine ().size ());
    tampon = new char [strlen (trad ("la chaine \"%s\" manque :\n"
                                     "%s,%d : %s\n%s,%d : %s"))
                      + chaine.size ()
                      + nomFichierRes_.size ()
                      + ligneRes_.size ()
                      + nomFichierRef_.size ()
                      + ligneRef_.size ()
                      + 100];
    (void) sprintf (tampon, trad ("la chaine \"%s\" manque :\n%s,%d : %s\n%s,%d : %s"),
                    chaine.c_str (), 
                    nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                    nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
    messageDiff_ = tampon;
    delete[] tampon;
  }

  if (nbErreursDansLigne > 1)
  {
      // plusieurs erreurs dans la ligne, on formate un message
      // concernant toute la ligne
    tampon = new char [strlen (trad ("%d differences dans les lignes:\n"
                                     "%s,%d : %s\n%s,%d : %s"))
                      + nomFichierRes_.size ()
                      + ligneRes_.size ()
                      + nomFichierRef_.size ()
                      + ligneRef_.size ()
                      + 100];
    (void) sprintf (tampon, trad ("%d differences dans les lignes:\n"
                                  "%s,%d : %s\n%s,%d : %s"),
                    nbErreursDansLigne,
                    nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                    nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
    messageDiff_ = tampon;
    delete[] tampon;
  }

  return nbErreursDansLigne;
}



// cette fonction permet de trouver les premiers lexèmes de res et ref qui soient égaux
// et qui vérifient :
// - numeroRes et numeroRef doivent être le plus proches possible
// - numeroRes et numeroRef doivent être minimaux
// Ainsi si les lexèmes 3 de res est égal au lexème 1 et 3 de ref et
// si le lexème 1 de res est égal au lexème 5 de ref, la fonction retournera : 
// numeroRes = 3 et numeroRef = 3
//
//               ---->
//        a   b   a   z   c
//       -------------------
//    c  |0   0   0 | 0   1|
//       |          |      |
// |  y  |0   0   0 | 0   0|
// |     |          |      |
// |  a  |1   0   1 | 0   0|
// v     |-----------      |
//    v  |0   0   0   0   0|
//       |                 |
//    w  |0   0   0   0   0|
//       -------------------
//
// En d'autres termes, on cherche le plus petit carré de côté max(numeroRes, numeroRef)
// où numeroRes et numeroRef sont les positions de deux lexèmes égaux. On prend ensuite
// les lexèmes égaux les plus proches du coin inférieur droit de ce carré.
// 

void ComparateurLigne::lexemesSuivantsIdentiques (int& numeroRes, int& numeroRef)
{
  double diff;

  int i = 1;
  int j = 1;

  numeroRes = alres_.nbLexemes ()+1;
  numeroRef = alref_.nbLexemes ()+1;

  alres_.redemarre ();
  alres_.suivant ();

  // on parcourt la ligne res lexème par lexème
  while ((alres_.type () != AnalyseurLexical::codeFin) && 
         (i <= max (numeroRes, numeroRef)))
  {
    alref_.redemarre ();
    alref_.suivant ();
    j = 1;

    // on parcourt la ligne ref lexème par lexème
    while ((alref_.type () != AnalyseurLexical::codeFin) && 
           (j <= max (numeroRes, numeroRef)))
    {
      // si à i et j, les lexèmes sont égaux, on stocke ces valeurs dans numeroRes 
      // et numeroRef.
      if (comparerLexeme (diff) == 0)
      {
        numeroRes = i;
        numeroRef = j;
      }
      j++;
      alref_.suivant ();
    }
    i++;
    alres_.suivant ();
  }
}


// méthode publique permettant de comparer les deux lignes
bool ComparateurLigne::comparerLigne ()
{
  double diff = 0;
  int i=0;

  alres_.redemarre ();
  alref_.redemarre ();
  alres_.suivant ();
  alref_.suivant ();

  // dans chaque ligne, on analyse lexème par lexème
  while ((alres_.type () != AnalyseurLexical::codeFin) && 
         (alref_.type () != AnalyseurLexical::codeFin))
  {
    // comparaison des lexèmes courants
    if (comparerLexeme (diff) != 0)
      return false;

    i++;

    alres_.suivant ();
    alref_.suivant ();
  }

  if ((alres_.type () != AnalyseurLexical::codeFin) ||
      (alref_.type () != AnalyseurLexical::codeFin))
    return false;

  return true;
}


// méthode privée permettant de formater le message de différence
void ComparateurLigne::formaterMessage (int index, double diff)
{

  char *tampon = 0;

  switch (index)
  {
    case 0 : 
      // lexèmes identiques (strictement ou relativement)
      break;
    case 1 :
      // chaines de caractères différentes
      tampon = new char [strlen (trad ("chaines \"%s\" et \"%s\" differentes "
                                       "dans les lignes :\n"
                                       "%s,%d : %s\n%s,%d : %s"))
                        + alres_.lexeme ().size ()
                        + alref_.lexeme ().size ()
                        + nomFichierRes_.size ()
                        + ligneRes_.size ()
                        + nomFichierRef_.size ()
                        + ligneRef_.size ()
                        + 100];
      (void) sprintf (tampon, trad ("chaines \"%s\" et \"%s\" differentes "
                                    "dans les lignes :\n%s,%d : %s\n%s,%d : %s"),
                      alres_.lexeme ().c_str (), alref_.lexeme ().c_str (),
                      nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                      nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());

      messageDiff_ = tampon;
      delete[] tampon;
      break;
    case 2 :
      // entiers différents
      tampon = new char [strlen (trad ("entiers %d et %d differents dans les "
                                       "lignes :\n%s,%d : %s\n%s,%d : %s"))
                        + nomFichierRes_.size ()
                        + ligneRes_.size ()
                        + nomFichierRef_.size ()
                        + ligneRef_.size ()
                        + 100];
      (void) sprintf (tampon, trad ("entiers %d et %d differents dans les "
                                    "lignes :\n%s,%d : %s\n%s,%d : %s"),
                      alres_.entier (), alref_.entier (), 
                      nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str(), 
                      nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());

      messageDiff_ = tampon;
      delete[] tampon;
      break;
    case 3 :
      // valeurs numériques différentes
      tampon = new char [strlen (trad ("difference relative (%12.6e) entre"
                                       " les reels %f et %f superieure"
                                       " au seuil (%12.6e):\n"
                                       "%s,%d : %s\n%s,%d : %s"))
                        + nomFichierRes_.size ()
                        + ligneRes_.size ()
                        + nomFichierRef_.size ()
                        + ligneRef_.size ()
                        + 100];
      (void) sprintf (tampon, trad ("difference relative (%12.6e) entre les reels %f et %f "
                                    "superieure au seuil (%12.6e):\n%s,%d : %s\n%s,%d : %s"),
                      diff, alres_.valeurNumerique (), 
                      alref_.valeurNumerique (), precision_,
                      nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                      nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());

      messageDiff_ = tampon;
      delete[] tampon;
      break;
    default :
      // ce cas ne se produit pas 
      break;
  }
}

// méthode privée permettant de comparer deux lexèmes tout en acceptant une imprécision
// numérique
int ComparateurLigne::comparerLexeme (double& diff)
{
  int typeRes = alres_.type ();
  int typeRef = alref_.type ();

  diff = 0;

  // on considère d'abord les cas où les lexèmes sont de types autres
  // que codeEntier et autres que codeReel
    
  if (((typeRes != AnalyseurLexical::codeReel) && (typeRes != AnalyseurLexical::codeEntier)) || 
      ((typeRef != AnalyseurLexical::codeReel) && (typeRef != AnalyseurLexical::codeEntier)))
  {
    // Au moins un des deux lexèmes n'est pas un entier ou un reel, on analyse donc leur
    // formes brutes et ils doivent être identiques.
    
    if (alres_.lexeme () != alref_.lexeme ())
      return 1;
  }

  // les deux lexèmes sont de type numérique
  else if ((typeRes == typeRef) && (typeRes == AnalyseurLexical::codeEntier))
  {
    // les deux lexèmes sont entiers, ils doivent être strictement égaux
    if (alres_.entier () != alref_.entier ())
      return 2;
  }

  else
  {
    // un des deux lexèmes est de type codeReel. Les deux lexèmes doivent
    // etre comparés de facon relative
    
    double valeurRes = (double) ((typeRes == AnalyseurLexical::codeReel)? 
                                 alres_.reel () : alres_.entier ());
    double valeurRef = (double) ((typeRef == AnalyseurLexical::codeReel)? 
                                 alref_.reel () : alref_.entier ());
    diff = fabs (valeurRes - valeurRef) / (1+fabs (valeurRef));

    alres_.majValeurNumerique (valeurRes);
    alref_.majValeurNumerique (valeurRef);

    if (diff != 0)
    {      
      if (diff < precision_)
      {
        // l'erreur est acceptée
        return 0;
      }
      else
        // l'erreur est trop importante
        return 3;
    }
  }
  return 0;
}
