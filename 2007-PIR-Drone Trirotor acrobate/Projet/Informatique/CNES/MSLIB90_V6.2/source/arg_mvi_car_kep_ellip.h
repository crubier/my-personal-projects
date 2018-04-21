
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mvi_car_kep_ellip
                                                       
real(pm_reel), dimension(3),intent(in)     :: pos_car, vit_car ! positions vitesses en coordonnees cartesiennes
real(pm_reel), dimension(3),intent(in)     :: moment_cinetique ! moment cinetique du satellite
real(pm_reel),intent(in)                   :: norme_vect_pos   ! rayon vecteur
real(pm_reel),intent(in)                   :: norme_vect_vit   ! norme de la vitesse
real(pm_reel),intent(in)                   :: un_sur_a         ! inverse du demi grand axe
real(pm_reel),intent(in)                   :: e                ! excentricite
real(pm_reel),intent(in)                   :: pos_fois_vit     ! produit scalaire position x vitesse
real(pm_reel),intent(in)                   :: mu               ! constante de la gravitation

type(tm_orb_kep),intent(out)               :: kep              ! parametres osculateurs
integer ,intent(out)                       ::  retour
real(pm_reel), dimension(6,6), intent(out), optional  :: jacob ! jacobienne                  


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mvi_car_kep_ellip.h,v 1.1.1.1 2002/10/24 08:34:14 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

