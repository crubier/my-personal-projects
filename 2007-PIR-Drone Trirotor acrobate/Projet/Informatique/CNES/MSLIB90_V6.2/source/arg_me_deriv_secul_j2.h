
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine me_deriv_secul_j2
                                                       
real(pm_reel), intent(in)                            ::  mu          ! constante de la gravitation
real(pm_reel), intent(in)                            ::  r_equa      ! rayon equatorial du corps attractif
real(pm_reel), intent(in)                            ::  c20         ! coefficient zonal C20 (denormalise)
real(pm_reel), intent(in)                            ::  a           ! demi grand axe de l'orbite
real(pm_reel), intent(in)                            ::  e           ! excentricite de l'orbite
real(pm_reel), intent(in)                            ::  i           ! inclinaison de l'orbite

real(pm_reel), intent(out)                           ::  deriv_pom   ! derive seculaire de l'argument du perigee
real(pm_reel), intent(out)                           ::  deriv_gom   ! derive seculaire de la longitude du noeud ascendant
real(pm_reel), intent(out)                           ::  deriv_M     ! derive seculaire de l'anomalie moyenne
type(tm_code_retour), intent(out)                    ::  code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_me_deriv_secul_j2.h,v 1.1.1.1 2002/10/24 08:34:11 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

