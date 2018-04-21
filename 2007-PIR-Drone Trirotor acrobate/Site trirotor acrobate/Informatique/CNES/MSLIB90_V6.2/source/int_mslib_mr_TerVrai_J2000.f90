module int_mslib_mr_TerVrai_J2000

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_TerVrai_J2000 ( model, jul1950, delta_tu1, delta_tai, pos_TerVrai, pos_J2000, code_retour, &
                              vit_TerVrai, vit_J2000, jacob )

       use type_mslib
       use precision_mslib
       implicit none

       include 'arg_mr_TerVrai_J2000.h'

     end subroutine mr_TerVrai_J2000
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_TerVrai_J2000.f90,v 1.4 2003/08/19 14:48:21 mslibatv Exp $ '

end module int_mslib_mr_TerVrai_J2000
