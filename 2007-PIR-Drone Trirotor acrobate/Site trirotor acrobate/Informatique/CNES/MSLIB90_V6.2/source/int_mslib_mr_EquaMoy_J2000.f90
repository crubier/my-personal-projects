module int_mslib_mr_EquaMoy_J2000

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_EquaMoy_J2000 ( model, jul1950, delta_tai, pos_EquaMoy, pos_J2000, code_retour, &
          inertiel, vit_EquaMoy, vit_J2000, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_EquaMoy_J2000.h'

     end subroutine mr_EquaMoy_J2000
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_EquaMoy_J2000.f90,v 1.4 2004/10/14 09:02:13 mslibatv Exp $ '

end module int_mslib_mr_EquaMoy_J2000
