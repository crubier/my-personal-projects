module int_mslib_mv_cir_kep

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_cir_kep ( cir, kep, code_retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mv_cir_kep.h'

     end subroutine mv_cir_kep
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_cir_kep.f90,v 1.1 2004/03/12 17:07:18 msatv2 Exp $ '

end module int_mslib_mv_cir_kep
