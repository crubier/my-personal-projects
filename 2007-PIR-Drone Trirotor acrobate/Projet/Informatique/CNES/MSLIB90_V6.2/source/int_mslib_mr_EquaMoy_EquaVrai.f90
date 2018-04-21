module int_mslib_mr_EquaMoy_EquaVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_EquaMoy_EquaVrai ( model, jul1950, delta_tai, pos_EquaMoy, pos_EquaVrai, code_retour,  &
                                       inertiel, vit_EquaMoy, vit_EquaVrai, jacob )

       use type_mslib
       use precision_mslib
       implicit none

       include 'arg_mr_EquaMoy_EquaVrai.h'

     end subroutine mr_EquaMoy_EquaVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_EquaMoy_EquaVrai.f90,v 1.5 2004/10/14 09:02:13 mslibatv Exp $ '

end module int_mslib_mr_EquaMoy_EquaVrai
