module int_mslib_me_brouwer

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine me_brouwer( mu, r_equa, cn0, t1, moy_t1, t2, moy_t2, code_retour, osc_t2 )

       use type_mslib
       use precision_mslib

       include 'arg_me_brouwer.h'

     end subroutine me_brouwer
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_me_brouwer.f90,v 1.2 2003/05/06 15:50:31 mslibatv Exp $ '

end module int_mslib_me_brouwer
