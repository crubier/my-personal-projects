
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_PlanetVrai_EquaUAI


integer,                       intent(in)            ::  planete          ! planete
integer,                       intent(in)            ::  modeleUAI        ! modele UAI definissant le meridien origine
type(tm_jour_sec),             intent(in)            ::  jul1950          ! date julienne 1950 en jours secondes
real(pm_reel), dimension(3),   intent(in)            ::  pos_PlanetVrai   ! position dans le repere planetocentrique
real(pm_reel), dimension(3),   intent(out)           ::  pos_EquaUAI      ! position dans le repere equatorial planetaire de l'astre
type(tm_code_retour),          intent(out)           ::  code_retour
real(pm_reel),                 intent(in),  optional ::  tsid             ! position du meridien origine
real(pm_reel),                 intent(in),  optional ::  deriv_tsid       ! derivee du meridien origine = vitesse de rotation
real(pm_reel), dimension(3),   intent(in),  optional ::  vit_PlanetVrai   ! position dans le repere planetocentrique
real(pm_reel), dimension(3),   intent(out), optional ::  vit_EquaUAI      ! vitesse dans le repere equatorial planetaire de l'astre
real(pm_reel), dimension(6,6), intent(out), optional ::  jacob            ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_PlanetVrai_EquaUAI.h,v 1.2 2003/12/12 10:30:49 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

