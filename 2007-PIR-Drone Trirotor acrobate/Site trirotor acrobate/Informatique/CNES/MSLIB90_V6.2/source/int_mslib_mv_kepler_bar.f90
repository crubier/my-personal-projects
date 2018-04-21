module int_mslib_mv_kepler_bar

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_kepler_bar( anom_M, e, anom_E_D, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mv_kepler_bar.h'

     end subroutine mv_kepler_bar
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_kepler_bar.f90,v 1.2 2003/05/06 15:50:43 mslibatv Exp $ '

end module int_mslib_mv_kepler_bar
