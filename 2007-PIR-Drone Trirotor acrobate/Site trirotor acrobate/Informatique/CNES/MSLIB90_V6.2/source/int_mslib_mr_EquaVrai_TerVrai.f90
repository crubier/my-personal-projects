module int_mslib_mr_EquaVrai_TerVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_EquaVrai_TerVrai ( model, jul1950, delta_tu1, delta_tai, pos_EquaVrai, pos_TerVrai, code_retour, &
                                      inertiel, vit_EquaVrai, vit_TerVrai, jacob )

       use type_mslib
       use precision_mslib
       implicit none

       include 'arg_mr_EquaVrai_TerVrai.h'

     end subroutine mr_EquaVrai_TerVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_EquaVrai_TerVrai.f90,v 1.4 2004/05/27 09:34:47 mslibdev Exp $ '

end module int_mslib_mr_EquaVrai_TerVrai
