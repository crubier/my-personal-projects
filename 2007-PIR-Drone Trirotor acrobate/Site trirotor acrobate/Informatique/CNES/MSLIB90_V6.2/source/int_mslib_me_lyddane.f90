module int_mslib_me_lyddane

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine me_lyddane (mu, r_equa, cn0, t1, moy_t1, t2, moy_t2, code_retour, osc_t2 )

       use type_mslib
       use precision_mslib

       include 'arg_me_lyddane.h'

     end subroutine me_lyddane
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_me_lyddane.f90,v 1.1 2004/03/03 16:55:17 msatv2 Exp $ '

end module int_mslib_me_lyddane
