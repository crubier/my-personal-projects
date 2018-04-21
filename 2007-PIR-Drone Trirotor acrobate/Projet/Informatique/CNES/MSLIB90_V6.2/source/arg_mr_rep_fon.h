
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mr_rep_fon

integer, intent(in)    ::  trsf  ! numero de la transformation:
                                 ! entier a deux chiffres ou le premier (dans {1,2,3,4}) represente le repere
                                 ! de depart a t1 et le second dans {1,2,3,4} represente le repere d'arrivee a t2
                                 ! 1 - code du repere equatorial moyen
                                 ! 2 - code du repere equatorial vrai
                                 ! 3 - code du repere ecliptique moyen
                                 ! 4 - code du repere ecliptique vrai
integer,                       intent(in)           :: model       ! indicateur du modele --> pm_lieske_wahr: LIESKE + WAHR
type(tm_jour_sec),             intent(in)           :: jul1950_t1  ! date du repere initial
type(tm_jour_sec),             intent(in)           :: jul1950_t2  ! date du repere final

real(pm_reel), dimension(3,3), intent(out)          :: mat_pass    ! matrice de passage entre les 2 reperes

type(tm_code_retour),          intent(out)          :: code_retour
real(pm_reel),                 intent(in), optional :: delta_tai   ! ecart entre l'echelle de temps TAI et l'echelle de temps utilisee pour les dates jul1950_t1 et jul1950_t2

! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mr_rep_fon.h,v 1.1.1.1 2002/10/24 08:34:13 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

