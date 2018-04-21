module int_mslib_mu_3rot_quat

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mu_3rot_quat ( def_3rot,angle1,angle2,angle3,quat,code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mu_3rot_quat.h'

     end subroutine mu_3rot_quat
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mu_3rot_quat.f90,v 1.1 2003/10/27 11:05:02 msatv2 Exp $ '

end module int_mslib_mu_3rot_quat
