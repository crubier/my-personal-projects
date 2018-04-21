module int_mslib_mvi_barker

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_barker( anom_M, D, retour )

       use type_mslib
       use precision_mslib

       include 'arg_mvi_barker.h'

     end subroutine mvi_barker
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_barker.f90,v 1.2 2003/05/06 15:50:44 mslibatv Exp $ '

end module int_mslib_mvi_barker
