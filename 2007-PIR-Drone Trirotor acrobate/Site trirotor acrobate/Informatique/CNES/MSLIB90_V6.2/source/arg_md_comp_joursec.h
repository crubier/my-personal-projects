! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine md_comp_joursec

type(tm_jour_sec),    intent(in)        :: joursec1         ! quantite #1 (en jours, sec) 
type(tm_jour_sec),    intent(in)        :: joursec2         ! quantite #2 (en jours, sec) 
real(pm_reel),        intent(in)        :: eps              ! epsilon de comparaison (en s)
integer,              intent(out)       :: ordre            ! resultat de la comparaison : pm_joursec1_sup_joursec2 si joursec1 > joursec2
                                                            !                              pm_joursec1_egal_joursec2 si joursec1 = joursec2
                                                            !                              pm_joursec1_inf_joursec2 si joursec1 < joursec2
type(tm_code_retour), intent(out)       :: code_retour

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_md_comp_joursec.h,v 1.1.1.1 2002/10/24 08:34:08 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
