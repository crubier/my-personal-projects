module int_mslib_mv_cir_equa_kep

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_cir_equa_kep ( cir_equa, kep, code_retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mv_cir_equa_kep.h'

     end subroutine mv_cir_equa_kep
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_cir_equa_kep.f90,v 1.1 2004/03/03 16:56:52 msatv2 Exp $ '

end module int_mslib_mv_cir_equa_kep
