
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_PlaVrai_PlaIner


integer,                       intent(in)            ::  planete          ! planete
integer,                       intent(in)            ::  modeleUAI        ! modele UAI definissant la vitesse de rotation
real(pm_reel),                 intent(in)            ::  long             ! longitude du repere
real(pm_reel), dimension(3),   intent(in)            ::  pos_PlaVrai      ! position dans le repere planetocentrique Vrai
real(pm_reel), dimension(3),   intent(out)           ::  pos_PlaIner      ! position dans le repere planetocentrique Inertiel
type(tm_code_retour),          intent(out)           ::  code_retour
real(pm_reel),                 intent(in),  optional ::  vit_rot          ! vitesse de rotation de la planete
type(tm_jour_sec),             intent(in),  optional ::  jul1950          ! date pour la vit de rotation si planete = Neptune
real(pm_reel), dimension(3),   intent(in),  optional ::  vit_PlaVrai      ! position dans le repere planetocentrique Vrai
real(pm_reel), dimension(3),   intent(out), optional ::  vit_PlaIner      ! vitesse dans le repere  planetocentrique Inertiel
real(pm_reel), dimension(6,6), intent(out), optional ::  jacob            ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_PlaVrai_PlaIner.h,v 1.1 2003/11/17 16:49:19 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

