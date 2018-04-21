module int_mslib_me_brouwer_moy

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine me_brouwer_moy( r_equa, cn0, ecart_admi, osc, moy, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_me_brouwer_moy.h'

     end subroutine me_brouwer_moy
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_me_brouwer_moy.f90,v 1.2 2003/05/06 15:50:32 mslibatv Exp $ '

end module int_mslib_me_brouwer_moy
