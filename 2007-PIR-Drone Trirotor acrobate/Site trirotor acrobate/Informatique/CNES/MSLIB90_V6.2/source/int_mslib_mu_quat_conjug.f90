module int_mslib_mu_quat_conjug

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mu_quat_conjug ( quat, quat_conjug, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mu_quat_conjug.h'

     end subroutine mu_quat_conjug
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mu_quat_conjug.f90,v 1.2 2003/05/06 15:50:42 mslibatv Exp $ '

end module int_mslib_mu_quat_conjug
