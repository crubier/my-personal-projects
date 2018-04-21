
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_EquaUAI_J2000


integer,                       intent(in)            ::  planete       ! planete
integer,                       intent(in)            ::  modeleUAI     ! modele UAI definissant le pole de rotation de l'astre
type(tm_jour_sec),             intent(in)            ::  jul1950       ! date julienne 1950 en jours secondes
real(pm_reel), dimension(3),   intent(in)            ::  pos_EquaUAI   ! position dans le repere equatorial planetaire de l'astre
real(pm_reel), dimension(3),   intent(out)           ::  pos_J2000     ! position dans le repere EME2000
type(tm_code_retour),          intent(out)           ::  code_retour
real(pm_reel),                 intent(in),  optional ::  asc_droite    ! ascension droite (alpha0) du pole
real(pm_reel),                 intent(in),  optional ::  declinaison   ! declinaison (delta0) du pole
real(pm_reel), dimension(3),   intent(in),  optional ::  vit_EquaUAI   ! vitesse dans le repere equatorial planetaire de l'astre
real(pm_reel), dimension(3),   intent(out), optional ::  vit_J2000     ! vitesse dans le repere EME2000
real(pm_reel), dimension(6,6), intent(out), optional ::  jacob         ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_EquaUAI_J2000.h,v 1.2 2003/12/12 10:30:42 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

