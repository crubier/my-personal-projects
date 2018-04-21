
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mm_impul_kep

real(pm_reel),                      intent(in)  :: mu           ! constante de la gravitation
type(tm_orb_kep),                   intent(in)  :: kep_avant    ! parametres kepleriens avant la manoeuvre
integer,                            intent(in)  :: rep          ! indicateur du repere dans lequel est 
                                                                ! defini le vecteur impulsion
real(pm_reel), dimension(3),        intent(in)  :: impul        ! vecteur impulsion
type(tm_orb_kep),                   intent(out) :: kep_apres    ! parametres kepleriens apres la manoeuvre
type(tm_code_retour),               intent(out) :: code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mm_impul_kep.h,v 1.1.1.1 2002/10/24 08:34:08 cvsmslib Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

