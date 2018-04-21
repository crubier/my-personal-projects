! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mri_arg_fon

type(tm_jour_sec), intent(in)               :: jul1950         ! date julienne 1950 (secondes en TAI)
integer, intent(in)                         :: model           ! indicateur du modele de nutation --> pm_wahr -> WAHR

real(pm_reel), intent(out),dimension(5)     :: arg_fon         ! arguments fondamentaux (rad)
                                                               ! 1 : anomalie moyenne de la lune
                                                               ! 2 : anomalie moyenne du soleil
                                                               ! 3 : longitude de la lune a partir du noeud ascendant
                                                               ! 4 : angle horaire de la lune au soleil
                                                               ! 5 : longitude du noeud ascendant de la lune
integer, intent(out)                        :: retour
real(pm_reel), intent(out),dimension(5,2), optional :: arg_deriv ! derivees premieres (rad/s) et secondes (rad/s**2)
                                                                 ! des arguments fondamentaux


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mri_arg_fon.h,v 1.1.1.1 2002/10/24 08:34:11 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

