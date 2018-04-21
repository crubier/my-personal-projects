
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine me_eck_hech

real(pm_reel),                                  intent(in)  :: mu          ! constante gravitationnelle terrestre
real(pm_reel),                                  intent(in)  :: r_equa      ! rayon equatorial terrestre
real(pm_reel),        dimension(2:6),           intent(in)  :: cn0         ! coeff. zonaux (c20 a c60) du developpement
                                                                           ! potentiel terrestre en harmoniques spheriques
                                                                           ! (denormalises) (le 1er element c10 non utilise)
type(tm_jour_sec),                              intent(in)  :: t1          ! date initiale t1 des parametres moyens (jours, sec)
type(tm_orb_cir),                               intent(in)  :: moy_t1      ! parametres moyens a la date t1
type(tm_jour_sec),                              intent(in)  :: t2          ! date finale t2 des parametres osculateurs (jours, sec)
type(tm_orb_cir),                               intent(out) :: moy_t2      ! parametres moyens a la date t2
type(tm_code_retour),                           intent(out) :: code_retour
type(tm_orb_cir),                     optional, intent(out) :: osc_t2      ! parametres osculateurs extrapoles a t2


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_me_eck_hech.h,v 1.1.1.1 2002/10/24 08:34:10 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

