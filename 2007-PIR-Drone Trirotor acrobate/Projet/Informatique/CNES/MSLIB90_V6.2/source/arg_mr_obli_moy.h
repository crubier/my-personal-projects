
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_obli_moy

integer , intent(in)                             :: model_prec   !  indicateur du modele de precession
type(tm_jour_sec), intent(in)                    :: jul1950      !  date julienne (jour, secondes) 
real(pm_reel) , intent(out)                      :: obli_moy     !  obliquite moyenne
type(tm_code_retour), intent(out)                :: code_retour
real(pm_reel), intent(in),  optional             :: delta_tai    ! ecart entre l'echelle de temps TAI et l'echelle de temps utilisee pour la date jul1950
real(pm_reel), intent(out), optional             :: deriv1_obli  !  derivee premiere
real(pm_reel), intent(out), optional             :: deriv2_obli  !  derivee seconde

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_obli_moy.h,v 1.1.1.1 2002/10/24 08:34:14 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

