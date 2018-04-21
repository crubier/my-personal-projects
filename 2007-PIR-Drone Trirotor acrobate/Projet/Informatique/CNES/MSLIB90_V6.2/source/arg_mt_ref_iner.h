
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mt_ref_iner

real(pm_reel) , intent(in)                   :: vit_rot ! vitesse de rotation de la Terre
real(pm_reel) , intent(in)                   :: long    ! longitude de l'axe Ox du repere inertiel a la date t0
real(pm_reel) , intent(in)                   :: sec     ! nombre de secondes ecoulees depuis la date t0
real(pm_reel) , intent(in), dimension(3)     :: pos_ref ! position dans le repere terrestre de reference
real(pm_reel) , intent(out), dimension(3)    :: pos_iner! position dans le repere inertiel
type(tm_code_retour), intent(out)            :: code_retour
real(pm_reel) , intent(in), dimension(3), optional    :: vit_ref ! vitesse dans le repere terrestre de reference
real(pm_reel) , intent(out), dimension(3), optional   :: vit_iner! vitesse dans le repere inertiel
real(pm_reel) , intent(out), dimension(6,6), optional :: jacob   ! jacobien de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mt_ref_iner.h,v 1.1.1.1 2002/10/24 08:34:11 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

