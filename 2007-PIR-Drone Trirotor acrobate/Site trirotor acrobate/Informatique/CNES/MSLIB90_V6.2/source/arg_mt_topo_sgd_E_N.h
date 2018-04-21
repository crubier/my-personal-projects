
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mt_topo_sgd_E_N

type(tm_sgd), intent(in)               ::  pos_E  ! position en site, gisement, distance avec la convention axe Ox vers l'Est
type(tm_sgd), intent(out)              ::  pos_N  ! position en site, gisement, distance avec la convention axe Ox vers le Nord
type(tm_code_retour), intent(out)      ::  code_retour
type(tm_sgd), intent(in), optional     ::  vit_E  ! vitesse en site, gisement, distance avec la convention axe Ox vers l'Est
type(tm_sgd), intent(out) , optional   ::  vit_N  ! vitesse en site, gisement, distance avec la convention axe Ox vers le Nord
real(pm_reel), dimension(6,6), intent(out), optional  ::  jacob   ! jacobien de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mt_topo_sgd_E_N.h,v 1.1.1.1 2002/10/24 08:34:15 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

