************************************************************************
*$<AM-V1.0>
*
*$Nom
*       cantdefs.f
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
*       $Id: cantdefs.f,v 1.1 2001/06/05 15:36:29 cantor Exp $
*
*$Auteur
*       L. Maisonobe
*
*$Description
*       Fichier de déclaration de constantes pour le fortran
*
*$Historique
*       $Log: cantdefs.f,v $
*       Revision 1.1  2001/06/05 15:36:29  cantor
*       initial version
*
*$<>
*
************************************************************************
      INTEGER CtrXYZ, CtrXZY, CtrYXZ, CtrYZX, CtrZXY, CtrZYX
      INTEGER CtrXYX, CtrXZX, CtrYXY, CtrYZY, CtrZXZ, CtrZYZ
C
      PARAMETER (CtrXYZ =  1)
      PARAMETER (CtrXZY =  2)
      PARAMETER (CtrYXZ =  3)
      PARAMETER (CtrYZX =  4)
      PARAMETER (CtrZXY =  5)
      PARAMETER (CtrZYX =  6)
      PARAMETER (CtrXYX =  7)
      PARAMETER (CtrXZX =  8)
      PARAMETER (CtrYXY =  9)
      PARAMETER (CtrYZY = 10)
      PARAMETER (CtrZXZ = 11)
      PARAMETER (CtrZYZ = 12)
