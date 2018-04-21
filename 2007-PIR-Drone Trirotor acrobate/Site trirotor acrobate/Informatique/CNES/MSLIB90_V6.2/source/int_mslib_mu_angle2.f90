module int_mslib_mu_angle2

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mu_angle2 (x, y, angle, code_retour)

       use type_mslib
       use precision_mslib

       include 'arg_mu_angle2.h'

     end subroutine mu_angle2
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mu_angle2.f90,v 1.2 2003/05/06 15:50:41 mslibatv Exp $ '

end module int_mslib_mu_angle2

