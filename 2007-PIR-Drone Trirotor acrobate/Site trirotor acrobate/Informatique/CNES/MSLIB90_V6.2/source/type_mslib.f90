module type_mslib

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Definition des types derives MSLIB. 
! ===
!
! Note d'utilisation: Ce module est accessible a l'utilisateur via le module mslib.
! ==================
!
! Historique:
! ==========
!   + Version 0.1 (SP 149 ed01 rev00): creation
!   + Version 0.1.1 (DE globale 182 ed01 rev00): modification regle de marquage pour info_utilisateur
!                         et rajout de commentaires
!   + Version 1.0 (DE 216 ed01 rev00) : ajout de nouveaux types 
!   + Version 2.0 (DE 405 ed01 rev00) : ajout de commentaires sur le champ %a pour certains types
!                         et changement (expres) de l'ordre d'apparition des champs dans la structure
!   + Version 3.0 (DE 428 ed01 rev00) : ajout du type quaternion tm_quat 
!   + Version 3.1 (DE 440 ed01 rev00) : ajout des champs biblio et message pour tm_code_retour
!                         et mise dans un ordre logique l'apparition des champs dans la structure (cf volume 3)
!   + Version 3.2 (DE 449 ed01 rev00) : ajout de l'attribut sequence a tous les types derives
!************************************************************************


use precision_mslib           ! definition des precisions retenues
use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

implicit none


type tm_code_retour     
   ! utile pour toutes les routines utilisateurs

   sequence
   integer                   :: valeur    ! valeur du code retour
   integer                   :: routine   ! numero de la routine
   integer                   :: biblio    ! bibliotheque
   character(len=pm_message) :: message   ! message

end type tm_code_retour


type tm_sgd             
   ! utile aussi bien pour des positions que pour des vitesses,
   ! que l'axe des X soit a l'Est ou au Nord.

   sequence
   real(pm_reel) :: s   ! site
   real(pm_reel) :: g   ! gisement
   real(pm_reel) :: d   ! distance

end type tm_sgd

type tm_jour_sec 
   ! utilise pour des dates juliennes ou des durees

   sequence  
   integer(pm_entier) :: jour      ! nombre de jours
   real(pm_reel)      :: sec       ! nombres de secondes dans le jour

end type tm_jour_sec

! Les types de structures suivants (tm_orb_...) sont utilises aussi bien pour les parametres osculateurs que pour les 
! parametres moyens, ou que pour les ecarts admissibles dans les routines d'extrapolation d'orbite.

type tm_orb_kep

   sequence
   real(pm_reel) :: a   ! demi-grand axe (ou parametre p pour la parabole)
   real(pm_reel) :: e   ! excentricite
   real(pm_reel) :: i   ! inclinaison
   real(pm_reel) :: pom ! argument du perigee
   real(pm_reel) :: gom ! longitude du noeud ascendant
   real(pm_reel) :: M   ! anomalie moyenne

end type tm_orb_kep

type tm_orb_cir

   sequence
   real(pm_reel) :: a     ! demi-grand axe
   !    vecteur excentricite
   real(pm_reel) :: ex    
   real(pm_reel) :: ey    
   real(pm_reel) :: i     ! inclinaison
   real(pm_reel) :: gom   ! longitude du noeud ascendant
   real(pm_reel) :: pso_M ! argument du perigee + anomalie moyenne

end type tm_orb_cir

type tm_orb_equa

   sequence
   real(pm_reel) :: a      ! demi-grand axe (ou parametre p pour la parabole)
   real(pm_reel) :: e      ! excentricite
   real(pm_reel) :: pgom   ! argument du perigee + longitude du noeud ascendant
   !    vecteur inclinaison
   real(pm_reel) :: ix     
   real(pm_reel) :: iy     
   real(pm_reel) :: M      ! anomalie moyenne

end type tm_orb_equa

type tm_orb_cir_equa

   sequence
   real(pm_reel) :: a      ! demi-grand axe
   !    vecteur excentricite
   real(pm_reel) :: ex   
   real(pm_reel) :: ey   
   !    vecteur inclinaison
   real(pm_reel) :: ix 
   real(pm_reel) :: iy 
   real(pm_reel) :: pso_M   ! argument du perigee + longitude du noeud ascendant + anomalie moyenne

end type tm_orb_cir_equa

type tm_geodesique

   sequence    
   real(pm_reel) :: lat     ! latitude geodesique
   real(pm_reel) :: long    ! longitude 
   real(pm_reel) :: haut    ! hauteur

end type tm_geodesique

type tm_geocentrique

   sequence
   real(pm_reel) :: lat     ! latitude geocentrique
   real(pm_reel) :: long    ! longitude 
   real(pm_reel) :: dist    ! distance centre Terre

end type tm_geocentrique

type tm_nuta
              ! Ce type de structure est utilise aussi bien pour la nutation, que pour la derivee premiere
              ! de la nutation, ou que la derivee seconde de la nutation

   sequence
   real(pm_reel) :: long    ! longitude
   real(pm_reel) :: obli    ! obliquite

end type tm_nuta

type tm_quat                            
       ! type quaternion
  
   sequence
   real(pm_reel)                :: q0   ! partie reelle q0
   real(pm_reel),dimension(1:3) :: q123 ! partie imaginaire = vecteur (q1, q2, q3)

end type tm_quat

!................................................................................................................

character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
     '@(#) Fichier MSLIB type_mslib.f90: derniere modification V3.2 >'

!................................................................................................................

character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: type_mslib.f90,v 1.4 2003/04/04 14:57:42 mslibatv Exp $ '

end module type_mslib
