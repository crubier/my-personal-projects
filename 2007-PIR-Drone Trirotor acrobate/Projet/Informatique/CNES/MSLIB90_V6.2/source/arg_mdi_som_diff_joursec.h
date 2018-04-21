! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mdi_som_diff_joursec

type(tm_jour_sec),    intent(in)            :: joursec1         ! quantite exprimee en jours et secondes
type(tm_jour_sec),    intent(in)            :: joursec2         ! quantite exprimee en jours et secondes
integer          ,    intent(out)           :: retour           ! code retour de la routine
type(tm_jour_sec),    intent(out), optional :: joursec_somme    ! quantite, somme des deux quantites en entree, exprimee en jours et secondes dans le jour
type(tm_jour_sec),    intent(out), optional :: joursec_diff     ! quantite, difference des deux quantites en entree (joursec1-joursec2), exprimee en jours et secondes dans le jour

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mdi_som_diff_joursec.h,v 1.1.1.1 2002/10/24 08:34:11 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

