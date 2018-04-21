
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mc_phys
                                                       
type(tm_code_retour), intent(out)        :: code_retour          ! code retour
real(pm_reel), intent(out), optional     :: ua                   ! unite astronomique (km)
real(pm_reel), intent(out), optional     :: vit_lum              ! celerite (m/s)
real(pm_reel), intent(out), optional     :: i_critique_non_retro ! inclinaison critique non retrograde solution de 1-5cos^2(i)=0
real(pm_reel), intent(out), optional     :: i_critique_retro     ! inclinaison critique retrograde solution de 1-5cos^2(i)=0

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mc_phys.h,v 1.1.1.1 2002/10/24 08:34:07 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

