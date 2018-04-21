module int_mslib_mp_atm_US76

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mp_atm_US76(alt, tempe, pres, dens, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_mp_atm_US76.h'

     end subroutine mp_atm_US76
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mp_atm_US76.f90,v 1.2 2003/05/06 15:50:33 mslibatv Exp $ '

end module int_mslib_mp_atm_US76
