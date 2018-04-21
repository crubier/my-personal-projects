module int_mslib_mr_J2000_TerVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_J2000_TerVrai (  model, jul1950, delta_tu1, delta_tai, pos_J2000, pos_TerVrai, code_retour, &
                                  vit_J2000, vit_TerVrai, jacob )

       use type_mslib
       use precision_mslib
       implicit none

       include 'arg_mr_J2000_TerVrai.h'

     end subroutine mr_J2000_TerVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_J2000_TerVrai.f90,v 1.3 2003/08/19 14:48:16 mslibatv Exp $ '

end module int_mslib_mr_J2000_TerVrai
