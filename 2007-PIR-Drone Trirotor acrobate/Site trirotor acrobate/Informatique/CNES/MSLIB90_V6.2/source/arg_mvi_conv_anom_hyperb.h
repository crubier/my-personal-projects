
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mvi_conv_anom_hyperb

real(pm_reel), intent(in) :: e          ! excentricite
integer, intent(in)       :: type_anom1 ! type de l'anomalie d'entree
real(pm_reel), intent(in) :: anom1      ! anomalie d'entree
integer, intent(in)       :: type_anom2 ! type d'anomalie demande
real(pm_reel), intent(out):: anom2      ! anomalie demandee
integer, intent(out)      :: retour

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mvi_conv_anom_hyperb.h,v 1.3 2005/01/24 14:52:22 mslibdev Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

