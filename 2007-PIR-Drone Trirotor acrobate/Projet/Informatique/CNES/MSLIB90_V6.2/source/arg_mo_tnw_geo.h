
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mo_tnw_geo
                                                       
real(pm_reel),        dimension(3), intent(in)  :: pos_car     ! position du satellite en coordonnees cartesiennes dans le repere geocentrique inertiel
real(pm_reel),        dimension(3), intent(in)  :: vit_car     ! idem pour la vitesse 
real(pm_reel),        dimension(3), intent(in)  :: vect_tnw    ! projections (Gt,Gn,Gw) du vecteur G suivant les axes du repere orbital local (t,n,w)
real(pm_reel),        dimension(3), intent(out) :: vect_geo    ! composantes (Gx,Gy,Gz) du vecteur G dans le repere geocentrique inertiel
type(tm_code_retour),               intent(out) :: code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mo_tnw_geo.h,v 1.2 2003/09/11 14:26:04 mslibatv Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

