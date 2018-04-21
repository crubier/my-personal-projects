
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_TerRef_TerVrai


real(pm_reel),                      intent(in)            :: U           ! coordonnee U du pole vrai a la date t dans le repere R
real(pm_reel),                      intent(in)            :: V           ! coordonnee V du pole vrai a la date t dans le repere R
real(pm_reel),        dimension(3), intent(in)            :: pos_ref     ! vecteur position dans le repere terrestre de reference
real(pm_reel),        dimension(3), intent(out)           :: pos_vrai    ! vecteur position dans le repere terrestre vrai a la date t
type(tm_code_retour),               intent(out)           :: code_retour
real(pm_reel),        dimension(3), intent(in) , optional :: vit_ref     ! vecteur vitesse dans le repere terrestre de reference
real(pm_reel),        dimension(3), intent(out), optional :: vit_vrai    ! vecteur vitesse dans le repere terrestre vrai a la date t
real(pm_reel),      dimension(6,6), intent(out), optional :: jacob       ! jacobienne de la transformation


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_TerRef_TerVrai.h,v 1.2 2003/08/01 15:53:44 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

