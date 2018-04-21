module int_mslib_mc_math

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mc_math (code_retour, pi, deux_pi, pi_sur2, deg_rad, rad_deg)

       use type_mslib
       use precision_mslib

       include 'arg_mc_math.h'

     end subroutine mc_math
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mc_math.f90,v 1.2 2003/05/06 15:50:30 mslibatv Exp $ '

end module int_mslib_mc_math
