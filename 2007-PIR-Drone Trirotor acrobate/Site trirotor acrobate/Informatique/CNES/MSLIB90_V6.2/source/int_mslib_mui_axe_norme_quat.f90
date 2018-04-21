module int_mslib_mui_axe_norme_quat

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     function mui_axe_norme_quat ( axe_norme, angle )

       use type_mslib
       use precision_mslib

       include 'arg_mui_axe_norme_quat.h'

     end function mui_axe_norme_quat
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mui_axe_norme_quat.f90,v 1.1 2003/10/27 11:05:16 msatv2 Exp $ '

end module int_mslib_mui_axe_norme_quat
