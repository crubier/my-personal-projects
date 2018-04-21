
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mt_car_geoc

real(pm_reel), dimension(3), intent(in)              ::  pos_car  ! coordonnees cartesiennes dans le repere de reference
type(tm_geocentrique), intent(out)                   ::  pos_geoc ! latitude, longitude et distance geocentriques 
type(tm_code_retour), intent(out)                    ::  code_retour

real(pm_reel), dimension(3), intent(in), optional    ::  vit_car  ! vitesse cartesienne dans le repere de reference
type(tm_geocentrique), intent(out), optional         ::  vit_geoc ! vitesse en geocentrique
real(pm_reel), dimension(6,6), intent(out), optional ::  jacob    ! jacobienne de la transfomation

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mt_car_geoc.h,v 1.3 2003/03/05 16:23:34 mslibdev Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

