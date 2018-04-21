module int_mslib_mu_axe_angle_quat

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mu_axe_angle_quat ( axe, angle, quat, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mu_axe_angle_quat.h'

     end subroutine mu_axe_angle_quat
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mu_axe_angle_quat.f90,v 1.2 2003/05/06 15:50:42 mslibatv Exp $ '

end module int_mslib_mu_axe_angle_quat
