
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mt_def_topo_N

real(pm_reel), intent(in)                  ::  lat                     ! latitude geodesique de l'origine du repere topocentrique
real(pm_reel), intent(in)                  ::  long                    ! longitude geodesique de l'origine du repere topocentrique
real(pm_reel), intent(out), dimension(3)   ::  vect_i, vect_j, vect_k  ! vecteurs i, j et k dans le repere de reference
type(tm_code_retour), intent(out)           ::  code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mt_def_topo_N.h,v 1.1.1.1 2002/10/24 08:34:11 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

