module int_mslib_me_eck_hech

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine me_eck_hech( mu, r_equa, cn0, t1, moy_t1, t2, moy_t2, code_retour, osc_t2 )

       use type_mslib
       use precision_mslib

       include 'arg_me_eck_hech.h'

     end subroutine me_eck_hech
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_me_eck_hech.f90,v 1.2 2003/05/06 15:50:32 mslibatv Exp $ '

end module int_mslib_me_eck_hech
