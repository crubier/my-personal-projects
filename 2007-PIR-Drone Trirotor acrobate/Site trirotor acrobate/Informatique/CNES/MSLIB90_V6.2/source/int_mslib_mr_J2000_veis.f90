module int_mslib_mr_J2000_veis

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_J2000_veis ( model, jul1950, delta_tu1, delta_tai, pos_J2000, pos_veis, code_retour, &
          vit_J2000, vit_veis, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_J2000_veis.h'

     end subroutine mr_J2000_veis
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_J2000_veis.f90,v 1.3 2003/08/19 14:48:18 mslibatv Exp $ '

end module int_mslib_mr_J2000_veis
