module int_mslib_mr_J2000_EquaMoy

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_J2000_EquaMoy ( model, jul1950, delta_tai, pos_J2000, pos_EquaMoy, code_retour, &
     inertiel, vit_J2000, vit_EquaMoy, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_J2000_EquaMoy.h'

     end subroutine mr_J2000_EquaMoy
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_J2000_EquaMoy.f90,v 1.4 2004/10/14 09:02:13 mslibatv Exp $ '

end module int_mslib_mr_J2000_EquaMoy
