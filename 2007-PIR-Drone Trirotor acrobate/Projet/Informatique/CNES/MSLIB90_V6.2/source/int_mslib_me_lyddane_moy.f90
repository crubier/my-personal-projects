module int_mslib_me_lyddane_moy

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine me_lyddane_moy ( r_equa, cn0, osc, moy, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_me_lyddane_moy.h'

     end subroutine me_lyddane_moy
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_me_lyddane_moy.f90,v 1.1 2004/03/03 16:55:19 msatv2 Exp $ '

end module int_mslib_me_lyddane_moy
