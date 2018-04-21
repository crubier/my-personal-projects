module int_mslib_mr_TerVrai_veis

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_TerVrai_veis ( jul1950, delta_tu1, pos_TerVrai, pos_veis, code_retour, vit_TerVrai, vit_veis, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_TerVrai_veis.h'

     end subroutine mr_TerVrai_veis
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_TerVrai_veis.f90,v 1.3 2003/08/19 09:00:59 mslibatv Exp $ '

end module int_mslib_mr_TerVrai_veis
