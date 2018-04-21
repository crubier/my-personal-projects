
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mu_quat_rep

real(pm_reel), dimension(3), intent(in)    ::  vect1 ! coordonnees du vecteur dans le repere R1
type(tm_quat), intent(in)                  ::  quat  ! quaternion de la transformation R1 -> R2
real(pm_reel), dimension(3), intent(out)   ::  vect2 ! coordonnees du vecteur dans le repere R2
type(tm_code_retour), intent(out)          ::  code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mu_quat_rep.h,v 1.1.1.1 2002/10/24 08:34:17 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

