module int_mslib_ms_pos_soleil_lune

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine ms_pos_soleil_lune (date, dir_sol, dist_sol, dir_lune, dist_lune, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_ms_pos_soleil_lune.h'

     end subroutine ms_pos_soleil_lune
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_ms_pos_soleil_lune.f90,v 1.2 2004/10/14 09:02:13 mslibatv Exp $ '

end module int_mslib_ms_pos_soleil_lune
