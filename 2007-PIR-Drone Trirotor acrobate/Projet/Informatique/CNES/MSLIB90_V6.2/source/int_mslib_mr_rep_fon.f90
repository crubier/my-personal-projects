module int_mslib_mr_rep_fon

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_rep_fon(trsf, model, jul1950_t1, jul1950_t2, mat_pass, code_retour, delta_tai)

       use type_mslib
       use precision_mslib

       include 'arg_mr_rep_fon.h'

     end subroutine mr_rep_fon
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_rep_fon.f90,v 1.2 2003/05/06 15:50:35 mslibatv Exp $ '

end module int_mslib_mr_rep_fon
