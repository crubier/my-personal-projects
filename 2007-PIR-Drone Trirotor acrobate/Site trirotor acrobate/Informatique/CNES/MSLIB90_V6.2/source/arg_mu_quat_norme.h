
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mu_quat_norme

type(tm_quat), intent(in)                            ::  quat        ! quaternion (q0, q1, q2, q3)
type(tm_quat), intent(out)                           ::  quat_norme  ! quaternion norme
real(pm_reel), intent(out)                           ::  norme       ! norme du quaternion
type(tm_code_retour), intent(out)                    ::  code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mu_quat_norme.h,v 1.1.1.1 2002/10/24 08:34:17 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
