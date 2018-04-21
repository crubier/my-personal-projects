
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mt_geoc_car

type(tm_geocentrique), intent(in)                    ::  pos_geoc     ! latitude, longitude, distance geocentriques             
real(pm_reel), dimension(3), intent(out)             ::  pos_car      ! position en coordonnees cartesiennes
type(tm_code_retour), intent(out)                    ::  code_retour

type(tm_geocentrique), intent(in), optional          ::  vit_geoc     ! vitesse en geocentrique
real(pm_reel), dimension(3), intent(out), optional   ::  vit_car      ! vitesse en cartesien
real(pm_reel), dimension(6,6), intent(out), optional ::  jacob        ! jacobienne de la transfomation

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mt_geoc_car.h,v 1.2 2002/10/25 09:17:27 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

