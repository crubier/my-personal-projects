module int_mslib_mv_kep_cir

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_kep_cir ( kep, cir, code_retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mv_kep_cir.h'

     end subroutine mv_kep_cir
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_kep_cir.f90,v 1.1 2004/03/12 17:07:23 msatv2 Exp $ '

end module int_mslib_mv_kep_cir
