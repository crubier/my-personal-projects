module int_mslib_mc_test

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mc_test ( code_retour, eps_cir, eps_parab, eps_equa, eps_i_critique )

       use type_mslib
       use precision_mslib

       include 'arg_mc_test.h'

     end subroutine mc_test
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mc_test.f90,v 1.2 2003/05/06 15:50:30 mslibatv Exp $ '

end module int_mslib_mc_test
