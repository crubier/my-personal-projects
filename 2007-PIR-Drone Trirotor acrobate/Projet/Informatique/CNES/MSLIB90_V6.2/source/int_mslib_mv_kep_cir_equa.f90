module int_mslib_mv_kep_cir_equa

use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

implicit none

public

interface

   subroutine mv_kep_cir_equa ( kep, cir_equa, code_retour, jacob )
   use type_mslib
   use precision_mslib

   include 'arg_mv_kep_cir_equa.h'

   end subroutine mv_kep_cir_equa
end interface

character(len=pm_longueur_rcs_id), private :: &
     rcs_id =' $Id: int_mslib_mv_kep_cir_equa.f90,v 1.1 2004/03/03 16:56:54 msatv2 Exp $ '

end module int_mslib_mv_kep_cir_equa
