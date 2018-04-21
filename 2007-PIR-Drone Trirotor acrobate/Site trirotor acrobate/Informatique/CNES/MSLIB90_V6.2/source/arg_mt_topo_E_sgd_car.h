
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mt_topo_E_sgd_car
                                                       
type(tm_sgd), intent(in)                             :: pos_sgd  ! position dans le repere topo Est en sgd
real(pm_reel), dimension(3), intent(out)             :: pos_car  ! position dans le repere topo Est en cartesien
type(tm_code_retour), intent(out)                    :: code_retour

type(tm_sgd), intent(in), optional                   :: vit_sgd  ! vitesse dans le repere topo Est en sgd
real(pm_reel), dimension(3), intent(out), optional   :: vit_car  ! vitesse dans le repere topo Est en cartesien
real(pm_reel), dimension(6,6), intent(out), optional :: jacob    ! jacobienne de la transfomation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mt_topo_E_sgd_car.h,v 1.1.1.1 2002/10/24 08:34:14 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

