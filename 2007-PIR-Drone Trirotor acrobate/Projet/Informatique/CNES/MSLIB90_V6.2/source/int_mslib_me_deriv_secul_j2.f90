module int_mslib_me_deriv_secul_j2

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine me_deriv_secul_j2( mu, r_equa, c20, a, e, i, deriv_pom, deriv_gom, deriv_M, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_me_deriv_secul_j2.h'

     end subroutine me_deriv_secul_j2
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_me_deriv_secul_j2.f90,v 1.2 2003/05/06 15:50:32 mslibatv Exp $ '

end module int_mslib_me_deriv_secul_j2
