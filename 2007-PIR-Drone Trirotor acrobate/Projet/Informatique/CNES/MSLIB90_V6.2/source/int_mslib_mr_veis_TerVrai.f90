module int_mslib_mr_veis_TerVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_veis_TerVrai( jul1950, delta_tu1, pos_veis, pos_TerVrai, code_retour, vit_veis, vit_TerVrai, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_veis_TerVrai.h'

     end subroutine mr_veis_TerVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_veis_TerVrai.f90,v 1.3 2003/08/19 09:01:01 mslibatv Exp $ '

end module int_mslib_mr_veis_TerVrai
