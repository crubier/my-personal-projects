
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mv_kep_cir_equa

type(tm_orb_kep), intent(in)        :: kep      ! parametres kepleriens
type(tm_orb_cir_equa), intent(out)  :: cir_equa ! parametres adaptes aux orbites circulaires equatoriales
type(tm_code_retour), intent(out)   ::  code_retour
real(pm_reel), dimension(6,6), intent(out), optional :: jacob  ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mv_kep_cir_equa.h,v 1.1 2004/03/03 16:54:34 msatv2 Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

