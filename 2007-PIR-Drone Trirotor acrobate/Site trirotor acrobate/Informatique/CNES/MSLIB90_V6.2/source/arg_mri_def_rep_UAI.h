
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mri_def_rep_UAI


integer,                intent(in) ::  planete          ! planete
integer,                intent(in) ::  modeleUAI        ! modele UAI definissant les parametres du repere
type(tm_jour_sec),      intent(in) ::  jul1950          ! date julienne 1950 en jours secondes
real(pm_reel),          intent(out)::  alpha0           ! ascension droite du pole
real(pm_reel),          intent(out)::  delta0           ! declinaison du pole
real(pm_reel),          intent(out)::  tsid             ! longitude du meridien origine
real(pm_reel),          intent(out)::  deriv_tsid       ! derivee de cette longitude en fonction du temps
integer,                intent(out)::  retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mri_def_rep_UAI.h,v 1.1 2003/11/05 16:33:23 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

