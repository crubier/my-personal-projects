module int_mslib_mu_quat_3rot

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mu_quat_3rot ( def_3rot,quat,angle1,angle2,angle3,code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mu_quat_3rot.h'

     end subroutine mu_quat_3rot
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mu_quat_3rot.f90,v 1.1 2003/10/27 11:05:07 msatv2 Exp $ '

end module int_mslib_mu_quat_3rot
