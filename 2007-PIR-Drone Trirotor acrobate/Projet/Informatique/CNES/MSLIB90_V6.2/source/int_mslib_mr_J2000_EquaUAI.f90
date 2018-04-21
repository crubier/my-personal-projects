module int_mslib_mr_J2000_EquaUAI

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_J2000_EquaUAI ( planete, modeleUAI, jul1950, pos_J2000, pos_EquaUAI, code_retour, &
          asc_droite, declinaison, vit_J2000, vit_EquaUAI, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_J2000_EquaUAI.h'

     end subroutine mr_J2000_EquaUAI
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_J2000_EquaUAI.f90,v 1.1 2003/11/05 16:33:35 mslibatv Exp $ '

end module int_mslib_mr_J2000_EquaUAI
