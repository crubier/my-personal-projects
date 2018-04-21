
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine ms_pos_soleil_lune

type(tm_jour_sec), intent(in)                        ::  date      ! date (JJCNES)
real(pm_reel), dimension(3), intent(out)             ::  dir_sol   ! cosinus directeur du Soleil dans Veis
real(pm_reel), intent(out)                           ::  dist_sol  ! distance Terre-Soleil
real(pm_reel), dimension(3), intent(out)             ::  dir_lune  ! cosinus directeur de la Lune dans Veis
real(pm_reel), intent(out)                           ::  dist_lune ! distance Terre-Lune 
type(tm_code_retour), intent(out)                    ::  code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_ms_pos_soleil_lune.h,v 1.2 2004/10/14 09:02:13 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

