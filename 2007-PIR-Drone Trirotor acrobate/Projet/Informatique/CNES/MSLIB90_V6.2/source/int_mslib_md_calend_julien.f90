module int_mslib_md_calend_julien

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine md_calend_julien(an, mois, jour, heure, min, sec, jul1950, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_md_calend_julien.h'

     end subroutine md_calend_julien
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_md_calend_julien.f90,v 1.2 2003/05/06 15:50:31 mslibatv Exp $ '

end module int_mslib_md_calend_julien
