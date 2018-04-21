
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_nuta

integer, intent(in)                 :: model_nuta      ! indicateur du modele de nutation 
type(tm_jour_sec), intent(in)       :: jul1950         ! date julienne

type(tm_nuta), intent(out)          :: nuta            ! nutation en longitude et en obliquite
type(tm_code_retour), intent(out)   :: code_retour
real(pm_reel), intent(in),  optional:: delta_tai       ! ecart entre l'echelle de temps TAI et l'echelle de temps utilisee pour la date jul1950
type(tm_nuta), intent(out), optional:: deriv1_nuta     ! derivee premiere de la nutation en longitude et en obliquite
type(tm_nuta), intent(out), optional:: deriv2_nuta     ! derivee seconde de la nutation en longitude et en obliquite



! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_nuta.h,v 1.1.1.1 2002/10/24 08:34:12 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

