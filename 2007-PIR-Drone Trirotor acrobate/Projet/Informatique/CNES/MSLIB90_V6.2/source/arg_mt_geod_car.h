
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mt_geod_car

type(tm_geodesique), intent(in)                      ::  pos_geod     ! latitude, longitude,  hauteur geodesiques                                         
real(pm_reel), intent(in)                            ::  r_equa       ! rayon equatorial terrestre
real(pm_reel), intent(in)                            ::  apla         ! aplatissement terrestre
real(pm_reel), dimension(3), intent(out)             ::  pos_car      ! position en coordonnees cartesiennes
type(tm_code_retour), intent(out)                    ::  code_retour
real(pm_reel), dimension(3,3), intent(out), optional ::  jacob        ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mt_geod_car.h,v 1.2 2003/08/29 14:33:08 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

