
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_J2000_BBR

real(pm_reel), dimension(3), intent(in)            :: pos_J2000 ! position dans le J2000
real(pm_reel), dimension(3), intent(in)            :: pos_Pla1  ! position de la planete 1 dans le J2000
real(pm_reel), dimension(3), intent(in)            :: vit_Pla1  ! vitesse de la planete 1 dans le J2000
real(pm_reel), dimension(3), intent(in)            :: pos_Pla2  ! position de la planete 2 dans le J2000
real(pm_reel), dimension(3), intent(in)            :: vit_Pla2  ! vitesse de la planete 2 dans le J2000
real(pm_reel), dimension(3), intent(out)           :: pos_BBR   ! position dans le BBR
type(tm_code_retour), intent(out)                  :: code_retour
real(pm_reel), dimension(3), intent(in), optional  :: vit_J2000 ! vitesse dans le J2000
real(pm_reel), dimension(3), intent(out), optional :: vit_BBR   ! vitesse dans le BBR


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_J2000_BBR.h,v 1.2 2005/01/13 18:15:47 mslibdev Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

