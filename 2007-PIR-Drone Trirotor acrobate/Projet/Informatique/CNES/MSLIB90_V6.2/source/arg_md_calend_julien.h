
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine md_calend_julien
                                                       
integer, intent(in)                      :: an              ! annee
integer, intent(in)                      :: mois            ! numero du mois dans l'annee
integer, intent(in)                      :: jour            ! numero du jour dans le mois
integer, intent(in)                      :: heure           ! heure du jour
integer, intent(in)                      :: min             ! minutes dans l'heure
real(pm_reel), intent(in)                :: sec             ! secondes decimales dans la minute

type(tm_jour_sec), intent(out)           :: jul1950         ! jours juliens CNES
type(tm_code_retour), intent(out)        :: code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_md_calend_julien.h,v 1.1.1.1 2002/10/24 08:34:09 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

