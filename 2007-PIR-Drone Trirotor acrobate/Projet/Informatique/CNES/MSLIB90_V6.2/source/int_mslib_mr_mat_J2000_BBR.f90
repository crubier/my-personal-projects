module int_mslib_mr_mat_J2000_BBR

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_mat_J2000_BBR (pos_Pla1, vit_Pla1, pos_Pla2, vit_Pla2, mat, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_mr_mat_J2000_BBR.h'

     end subroutine mr_mat_J2000_BBR
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_mat_J2000_BBR.f90,v 1.1 2004/11/22 10:52:57 msatv2 Exp $ '

end module int_mslib_mr_mat_J2000_BBR
