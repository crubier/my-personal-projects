module int_mslib_mr_mat_nuta

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_mat_nuta(nuta, obli_moy, mat_nuta, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_mr_mat_nuta.h'

     end subroutine mr_mat_nuta
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_mat_nuta.f90,v 1.2 2003/05/06 15:50:34 mslibatv Exp $ '

end module int_mslib_mr_mat_nuta
