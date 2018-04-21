module int_mslib_mr_nuta

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_nuta ( model_nuta, jul1950, nuta, code_retour, delta_tai, deriv1_nuta, deriv2_nuta)

       use type_mslib
       use precision_mslib

       include 'arg_mr_nuta.h'

     end subroutine mr_nuta
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_nuta.f90,v 1.2 2003/05/06 15:50:35 mslibatv Exp $ '

end module int_mslib_mr_nuta
