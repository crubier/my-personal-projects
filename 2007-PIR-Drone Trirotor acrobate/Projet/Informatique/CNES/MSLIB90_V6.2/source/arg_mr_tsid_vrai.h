
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_tsid_vrai


integer,           intent(in)           :: model      ! indicateur pour les modeles de precession + nutation
type(tm_jour_sec), intent(in)           :: jul1950    ! date julienne 1950 t (non normalisee) en jour et secondes
real(pm_reel),     intent(in)           :: delta_tu1  ! ecart entre l'echelle de temps TU1 et l'echelle de temps utilisee pour la date t
real(pm_reel),     intent(in)           :: delta_tai  ! ecart entre l'echelle de temps TAI et l'echelle de temps utilisee pour la date t
real(pm_reel),     intent(out)          :: tsid_vrai  ! temps sideral vrai (radians)
type(tm_code_retour), intent(out)       :: code_retour
real(pm_reel),     intent(out),optional :: deriv_tsid_vrai ! derivee du temps sideral vrai (radians/sec)


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_tsid_vrai.h,v 1.1 2003/01/20 16:09:07 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

