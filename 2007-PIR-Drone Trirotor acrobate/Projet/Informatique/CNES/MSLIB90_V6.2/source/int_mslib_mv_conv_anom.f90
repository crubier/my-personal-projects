module int_mslib_mv_conv_anom

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_conv_anom (e, type_anom1, anom1, type_anom2, anom2, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_mv_conv_anom.h'

     end subroutine mv_conv_anom
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_conv_anom.f90,v 1.2 2005/01/24 14:52:27 mslibdev Exp $ '

end module int_mslib_mv_conv_anom
