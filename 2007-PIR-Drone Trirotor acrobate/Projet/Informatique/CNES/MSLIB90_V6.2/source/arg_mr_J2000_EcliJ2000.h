
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_J2000_EcliJ2000

real(pm_reel), dimension(3),   intent(in)            ::  pos_J2000     ! position dans le repere EME2000
real(pm_reel), dimension(3),   intent(out)           ::  pos_EcliJ2000 ! position dans le repere ecliptique J2000
type(tm_code_retour),          intent(out)           ::  code_retour
real(pm_reel),                 intent(in) , optional ::  obliquite     ! obliquite (rad)
real(pm_reel), dimension(3),   intent(in) , optional ::  vit_J2000     ! vitesse dans le repere EME2000
real(pm_reel), dimension(3),   intent(out), optional ::  vit_EcliJ2000 ! vitesse dans le repere ecliptique J2000
real(pm_reel), dimension(6,6), intent(out), optional ::  jacob         ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_J2000_EcliJ2000.h,v 1.2 2003/11/06 15:49:03 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

