module int_mslib_mv_kepler_std

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_kepler_std (anom_M, e, anom_E, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_mv_kepler_std.h'

     end subroutine mv_kepler_std
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_kepler_std.f90,v 1.2 2003/05/06 15:50:44 mslibatv Exp $ '

end module int_mslib_mv_kepler_std
