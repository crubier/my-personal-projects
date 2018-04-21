module int_mslib_mvi_kepler_hyperb

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_kepler_hyperb( anom_M, e, anom_E, retour )

       use type_mslib
       use precision_mslib

       include 'arg_mvi_kepler_hyperb.h'

     end subroutine mvi_kepler_hyperb
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_kepler_hyperb.f90,v 1.2 2003/05/06 15:50:45 mslibatv Exp $ '

end module int_mslib_mvi_kepler_hyperb
