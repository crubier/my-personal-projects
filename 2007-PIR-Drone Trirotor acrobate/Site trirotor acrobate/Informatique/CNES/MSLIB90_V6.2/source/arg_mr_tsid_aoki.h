
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_tsid_aoki

type(tm_jour_sec), intent(in)      ::  jul1950     !  date julienne 1950 (jour, seconde)
real(pm_reel), intent(in)          ::  delta_tu1   !  ecart de datation entre TU1 et l'echelle de datation utilisee pour jul1950
real(pm_reel), intent(out)         ::  tsid        !  temps sideral
type(tm_code_retour), intent(out)  ::  code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_tsid_aoki.h,v 1.1.1.1 2002/10/24 08:34:10 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

