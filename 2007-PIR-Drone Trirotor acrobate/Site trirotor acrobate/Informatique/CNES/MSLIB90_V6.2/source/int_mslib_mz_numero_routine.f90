module int_mslib_mz_numero_routine

  use longueur_chaine_mslib

  implicit none

  public

  interface
     subroutine mz_numero_routine (routine, nom, identification, code_retour)

       use type_mslib

       include 'arg_mz_numero_routine.h'

     end subroutine mz_numero_routine
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mz_numero_routine.f90,v 1.2 2003/05/06 15:50:45 mslibatv Exp $ '

end module int_mslib_mz_numero_routine

