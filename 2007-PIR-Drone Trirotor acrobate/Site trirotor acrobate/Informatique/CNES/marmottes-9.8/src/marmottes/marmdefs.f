************************************************************************
*$<AM-V1.0>
*
*$Nom
*       marmdefs.f
*
*$Type
*       DEF
*
*$Projet
*       Marmottes
*
*$Application
*       Marmottes
*
*$Resume
*       Fichier de déclaration de constantes pour le fortran
*
*$Version
*       $Id: marmdefs.f,v 1.1 2001/04/05 11:53:40 luc Exp $
*
*$Auteur
*       L. Maisonobe
*
*$Description
*       Fichier de déclaration de constantes pour le fortran
*
*$Historique
*       $Log: marmdefs.f,v $
*       Revision 1.1  2001/04/05 11:53:40  luc
*       version initiale
*
*
*$<>
*
************************************************************************
      INTEGER MrmNonSig, MrmSoleil, MrmLune, MrmCentral, MrmAucun
C
      PARAMETER (MrmNonSig  = 1)
      PARAMETER (MrmSoleil  = 2)
      PARAMETER (MrmLune    = 3)
      PARAMETER (MrmCentral = 4)
      PARAMETER (MrmAucun   = 5)
