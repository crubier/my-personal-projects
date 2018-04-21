
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine md_julien_calend

type(tm_jour_sec), intent(in)           :: jul1950         ! jours juliens CNES
                                                       
integer, intent(out)                    :: an              ! annee
integer, intent(out)                    :: mois            ! numero du mois dans l'annee
integer, intent(out)                    :: jour            ! numero du jour dans le mois
integer, intent(out)                    :: heure           ! heure du jour
integer, intent(out)                    :: min             ! minutes dans l'heure
real(pm_reel), intent(out)              :: sec             ! secondes decimales dans la minute

type(tm_code_retour), intent(out)       :: code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_md_julien_calend.h,v 1.1.1.1 2002/10/24 08:34:11 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

