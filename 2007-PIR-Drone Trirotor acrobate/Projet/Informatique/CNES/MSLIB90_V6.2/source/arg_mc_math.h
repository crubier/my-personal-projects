
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mc_math

type(tm_code_retour), intent(out)        :: code_retour !code retour                                                      
real(pm_reel), intent(out), optional   :: pi         !     pi
real(pm_reel), intent(out), optional   :: deux_pi    !     2*pi
real(pm_reel), intent(out), optional   :: pi_sur2    !     pi/2
real(pm_reel), intent(out), optional   :: deg_rad    !     constante de conversion degres -> radians
real(pm_reel), intent(out), optional   :: rad_deg    !     constante de conversion radians-> degres

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mc_math.h,v 1.1.1.1 2002/10/24 08:34:15 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

