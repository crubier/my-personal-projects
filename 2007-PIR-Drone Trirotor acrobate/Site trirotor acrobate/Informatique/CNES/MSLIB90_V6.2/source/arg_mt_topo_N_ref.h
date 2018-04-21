
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mt_topo_N_ref


type(tm_geodesique), intent(in)                      :: orig_topo  ! coordonnees geodesiques de l'origine du repere topocentrique
real(pm_reel), intent(in)                            :: r_equa     ! rayon equatorial
real(pm_reel), intent(in)                            :: apla       ! aplatissement
real(pm_reel), dimension(3), intent(in)              :: pos_topo   ! position dans le repere topocentrique Nord
real(pm_reel), dimension(3), intent(out)             :: pos_ref    ! position dans le repere terrestre de reference
type(tm_code_retour), intent(out)                    ::  code_retour
real(pm_reel), dimension(3), intent(in),optional     :: vit_topo   ! vitesse dans le repere topocentrique Nord
real(pm_reel), dimension(3), intent(out), optional   :: vit_ref    ! vitesse dans le repere terrestre de reference
real(pm_reel), dimension(6,6), intent(out), optional :: jacob      ! jacobien de la transformation




! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mt_topo_N_ref.h,v 1.1.1.1 2002/10/24 08:34:13 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

