module int_mslib_mr_obli_moy

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_obli_moy(model_prec, jul1950, obli_moy, code_retour, delta_tai, deriv1_obli, deriv2_obli)

       use type_mslib
       use precision_mslib

       include 'arg_mr_obli_moy.h'

     end subroutine mr_obli_moy
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_obli_moy.f90,v 1.2 2003/05/06 15:50:35 mslibatv Exp $ '

end module int_mslib_mr_obli_moy
