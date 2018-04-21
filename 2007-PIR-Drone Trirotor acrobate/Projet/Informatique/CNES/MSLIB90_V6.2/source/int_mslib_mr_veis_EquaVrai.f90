module int_mslib_mr_veis_EquaVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_veis_EquaVrai ( model, jul1950, delta_tu1, delta_tai, pos_veis, pos_EquaVrai, code_retour, &
                                   vit_veis, vit_EquaVrai, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_veis_EquaVrai.h'

     end subroutine mr_veis_EquaVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_veis_EquaVrai.f90,v 1.3 2003/08/19 14:48:23 mslibatv Exp $ '

end module int_mslib_mr_veis_EquaVrai
