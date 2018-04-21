module int_mslib_mr_EquaVrai_EquaMoy

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_EquaVrai_EquaMoy ( model, jul1950, delta_tai, pos_EquaVrai, pos_EquaMoy, code_retour, &
                                  inertiel, vit_EquaVrai, vit_EquaMoy, jacob )

       use type_mslib
       use precision_mslib
       implicit none

       include 'arg_mr_EquaVrai_EquaMoy.h'

     end subroutine mr_EquaVrai_EquaMoy
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_EquaVrai_EquaMoy.f90,v 1.5 2004/10/14 09:02:13 mslibatv Exp $ '

end module int_mslib_mr_EquaVrai_EquaMoy
