
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mv_kepler_gene
                                                       
real(pm_reel), intent(in)                            :: pso_M       !  argument du perigee + anomalie moyenne (+ longitude du noeud ascendant)
real(pm_reel), intent(in)                            :: ex          !  composante x du vecteur excentricite
real(pm_reel), intent(in)                            :: ey          !  composante y du vecteur excentricite

real(pm_reel), intent(out)                           :: pso_E       ! argument du perigee + anomalie excentrique (+ longitude du noeud ascendant)
type(tm_code_retour), intent(out)                    :: code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mv_kepler_gene.h,v 1.1.1.1 2002/10/24 08:34:11 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

