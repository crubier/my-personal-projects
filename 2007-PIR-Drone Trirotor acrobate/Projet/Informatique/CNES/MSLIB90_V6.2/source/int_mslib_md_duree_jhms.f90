module int_mslib_md_duree_jhms

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine md_duree_jhms( duree, jour, heure, min, sec, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_md_duree_jhms.h'

     end subroutine md_duree_jhms
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_md_duree_jhms.f90,v 1.2 2003/05/06 15:50:31 mslibatv Exp $ '

end module int_mslib_md_duree_jhms
