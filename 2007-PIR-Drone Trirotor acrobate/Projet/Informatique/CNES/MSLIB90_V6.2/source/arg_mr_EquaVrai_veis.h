
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_EquaVrai_veis


integer,                            intent(in)            :: model        ! indicateur des modeles de precession et de nutation
type(tm_jour_sec),                  intent(in)            :: jul1950      ! date julienne 1950 t (non normalisee) en jour et secondes
real(pm_reel),                      intent(in)            :: delta_tu1    ! ecart entre l'echelle de temps TU1 et l'echelle de temps utilisee pour la date t
real(pm_reel),                      intent(in)            :: delta_tai    ! ecart entre l'echelle de temps TAI et l'echelle de temps utilisee pour la date t
real(pm_reel),        dimension(3), intent(in)            :: pos_EquaVrai ! vecteur position dans le repere equatorial vrai a la date t
real(pm_reel),        dimension(3), intent(out)           :: pos_veis     ! vecteur position dans le repere de Veis a la date t 
type(tm_code_retour),               intent(out)           :: code_retour
real(pm_reel),        dimension(3), intent(in),  optional :: vit_EquaVrai ! vecteur vitesse dans le repere equatorial vrai a la date t
real(pm_reel),        dimension(3), intent(out), optional :: vit_veis     ! vecteur vitesse dans le repere de Veis a la date t 
real(pm_reel),      dimension(6,6), intent(out), optional :: jacob        ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_EquaVrai_veis.h,v 1.2 2003/08/19 14:48:00 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

