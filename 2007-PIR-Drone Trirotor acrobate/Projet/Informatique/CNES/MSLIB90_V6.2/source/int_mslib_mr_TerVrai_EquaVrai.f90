module int_mslib_mr_TerVrai_EquaVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_TerVrai_EquaVrai ( model, jul1950, delta_tu1, delta_tai, pos_TerVrai, pos_EquaVrai, code_retour, &
                                      inertiel, vit_TerVrai, vit_EquaVrai, jacob )

       use type_mslib
       use precision_mslib
       implicit none

       include 'arg_mr_TerVrai_EquaVrai.h'

     end subroutine mr_TerVrai_EquaVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_TerVrai_EquaVrai.f90,v 1.4 2004/05/27 09:34:50 mslibdev Exp $ '

end module int_mslib_mr_TerVrai_EquaVrai
