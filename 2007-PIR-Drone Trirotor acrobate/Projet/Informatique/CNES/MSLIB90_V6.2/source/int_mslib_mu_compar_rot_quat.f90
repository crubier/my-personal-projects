module int_mslib_mu_compar_rot_quat

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mu_compar_rot_quat ( quat1, quat2, angle, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mu_compar_rot_quat.h'

     end subroutine mu_compar_rot_quat
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mu_compar_rot_quat.f90,v 1.1 2004/03/12 17:05:47 msatv2 Exp $ '

end module int_mslib_mu_compar_rot_quat
