module int_mslib_mu_quat_mat

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mu_quat_mat ( quat, mat, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mu_quat_mat.h'

     end subroutine mu_quat_mat
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mu_quat_mat.f90,v 1.1 2003/10/27 11:05:13 msatv2 Exp $ '

end module int_mslib_mu_quat_mat
