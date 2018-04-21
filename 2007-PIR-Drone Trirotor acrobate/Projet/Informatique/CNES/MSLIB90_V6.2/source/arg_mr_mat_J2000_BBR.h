
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_mat_J2000_BBR

real(pm_reel), dimension(3), intent(in)    :: pos_Pla1 ! position de la planete 1 dans le J2000
real(pm_reel), dimension(3), intent(in)    :: vit_Pla1 ! vitesse de la planete 1 dans le J2000
real(pm_reel), dimension(3), intent(in)    :: pos_Pla2 ! position de la planete 2 dans le J2000
real(pm_reel), dimension(3), intent(in)    :: vit_Pla2 ! vitesse de la planete 2 dans le J2000
real(pm_reel), dimension(6,6), intent(out) :: mat      ! matrice de passage de J2000 au BBR
type(tm_code_retour), intent(out)          :: code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_mat_J2000_BBR.h,v 1.2 2005/01/13 18:15:49 mslibdev Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

