
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine me_brouwer_moy
                                                       
real(pm_reel), intent(in)                :: r_equa      !rayon equatorial
real(pm_reel), intent(in), dimension(2:5):: cn0         !coefficients harmoniques zonaux C20 a C50 denormalises
type(tm_orb_kep), intent(in)             :: ecart_admi  !ecarts admissibles sur a, e et les angles i, pom, gom et M
type(tm_orb_kep), intent(in)             :: osc         !parametres osculateurs (a,e,i,pom,gom,M)

type(tm_orb_kep), intent(out)            :: moy         !parametres moyens au sens de Brouwer
type(tm_code_retour), intent(out)        :: code_retour !code retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_me_brouwer_moy.h,v 1.1.1.1 2002/10/24 08:34:11 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

