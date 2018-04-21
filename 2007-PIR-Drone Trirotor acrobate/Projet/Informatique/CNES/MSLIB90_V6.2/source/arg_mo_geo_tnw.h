
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mo_geo_tnw
                                                       
real(pm_reel), dimension(3), intent(in)              :: pos_car  ! vecteur position du satellite en geocentrique inertiel
real(pm_reel), dimension(3), intent(in)              :: vit_car  ! vecteur vitesse du satellite en geocentrique inertiel
real(pm_reel), dimension(3), intent(in)              :: vect_geo ! composantes du vecteur considere dans le repere geocentrique inertiel

real(pm_reel), dimension(3), intent(out)             :: vect_tnw ! projection du vecteur considere suivant les axes du repere (t,n,w)
type(tm_code_retour), intent(out)                    :: code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mo_geo_tnw.h,v 1.1.1.1 2002/10/24 08:34:13 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

