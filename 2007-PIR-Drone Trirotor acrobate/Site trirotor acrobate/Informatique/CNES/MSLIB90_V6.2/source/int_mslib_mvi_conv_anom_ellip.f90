module int_mslib_mvi_conv_anom_ellip

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_conv_anom_ellip (e, type_anom1, anom1, type_anom2, anom2, retour)

       use type_mslib
       use precision_mslib

       include 'arg_mvi_conv_anom_ellip.h'

     end subroutine mvi_conv_anom_ellip
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_conv_anom_ellip.f90,v 1.2 2005/01/24 14:52:30 mslibdev Exp $ '

end module int_mslib_mvi_conv_anom_ellip
