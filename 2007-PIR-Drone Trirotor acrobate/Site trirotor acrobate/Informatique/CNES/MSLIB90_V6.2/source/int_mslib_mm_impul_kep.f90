module int_mslib_mm_impul_kep

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mm_impul_kep( mu, kep_avant, rep, impul, kep_apres, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mm_impul_kep.h'

     end subroutine mm_impul_kep
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mm_impul_kep.f90,v 1.2 2003/05/06 15:50:32 mslibatv Exp $ '

end module int_mslib_mm_impul_kep
