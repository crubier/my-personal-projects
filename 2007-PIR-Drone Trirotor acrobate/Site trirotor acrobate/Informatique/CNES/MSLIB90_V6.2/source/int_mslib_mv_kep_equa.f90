module int_mslib_mv_kep_equa

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_kep_equa ( kep, equa, code_retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mv_kep_equa.h'

     end subroutine mv_kep_equa
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_kep_equa.f90,v 1.1 2004/03/12 17:07:25 msatv2 Exp $ '

end module int_mslib_mv_kep_equa
