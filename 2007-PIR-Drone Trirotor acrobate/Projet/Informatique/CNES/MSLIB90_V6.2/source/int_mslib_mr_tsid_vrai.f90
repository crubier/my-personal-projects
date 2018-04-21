module int_mslib_mr_tsid_vrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_tsid_vrai ( model, jul1950, delta_tu1, delta_tai, tsid_vrai, code_retour, deriv_tsid_vrai )

       use type_mslib
       use precision_mslib
       implicit none

       include 'arg_mr_tsid_vrai.h'

     end subroutine mr_tsid_vrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_tsid_vrai.f90,v 1.2 2003/05/06 15:50:35 mslibatv Exp $ '

end module int_mslib_mr_tsid_vrai
