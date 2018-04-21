module int_mslib_mr_tsid_aoki

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_tsid_aoki(jul1950, delta_tu1, tsid, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_mr_tsid_aoki.h'

     end subroutine mr_tsid_aoki
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_tsid_aoki.f90,v 1.2 2003/05/06 15:50:35 mslibatv Exp $ '

end module int_mslib_mr_tsid_aoki
