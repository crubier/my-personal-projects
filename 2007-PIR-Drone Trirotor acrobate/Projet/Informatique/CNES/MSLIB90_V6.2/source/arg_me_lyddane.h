
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine me_lyddane

real(pm_reel), intent(in)                :: mu          ! constante de la gravitation
real(pm_reel), intent(in)                :: r_equa      ! rayon equatorial terrestre
real(pm_reel), dimension(2:5), intent(in):: cn0         ! coefficients harmoniques zonaux C20 a C50 denormalises
type(tm_jour_sec), intent(in)            :: t1          ! date t1
type(tm_orb_cir_equa), intent(in)        :: moy_t1      ! parametres moyens a la date t1
type(tm_jour_sec), intent(in)            :: t2          ! date t2
type(tm_orb_cir_equa), intent(out)       :: moy_t2      ! parametres moyens a la date t2
type(tm_code_retour), intent(out)        :: code_retour

type(tm_orb_cir_equa), intent(out), optional  :: osc_t2 ! parametres osculateurs a la date t2

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_me_lyddane.h,v 1.2 2004/05/27 09:34:43 mslibdev Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

