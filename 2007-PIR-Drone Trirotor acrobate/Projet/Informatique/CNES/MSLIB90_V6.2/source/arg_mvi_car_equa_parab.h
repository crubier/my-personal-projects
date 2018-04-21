
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mvi_car_equa_parab
                                                       
real(pm_reel),dimension(3), intent(in)               ::  pos_car ! position en coordonnees cartesiennes
real(pm_reel),dimension(3), intent(in)               ::  vit_car ! vitesse en coordonnees cartesiennes
real(pm_reel),dimension(3), intent(in)               ::  rrxv    ! produit vectoriel position x vitesse
real(pm_reel),intent(in)                             ::  norme_vect_pos   !  norme du vecteur position
real(pm_reel),intent(in)                             ::  norme_moment_cinetique   !  norme du produit vectoriel de ces derniers
real(pm_reel),intent(in)                             ::  excentricite     !  excentricite e
real(pm_reel),intent(in)                             ::  parametre        !  parametre p
real(pm_reel),intent(in)                             ::  rscal   ! produit scalaire position.vitesse
real(pm_reel),intent(in)                             ::  mu      ! constante de la gravitation

type(tm_orb_equa), intent(out)                       ::  equa    ! parametres orbitaux de l'orbite equatoriale
integer ,intent(out)                                 ::  retour
real(pm_reel),dimension(6,6), intent(out), optional  :: jacob    ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mvi_car_equa_parab.h,v 1.1.1.1 2002/10/24 08:34:08 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

