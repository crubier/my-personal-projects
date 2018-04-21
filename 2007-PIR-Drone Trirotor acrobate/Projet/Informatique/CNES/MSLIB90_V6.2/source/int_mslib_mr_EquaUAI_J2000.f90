module int_mslib_mr_EquaUAI_J2000

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_EquaUAI_J2000 ( planete, modeleUAI, jul1950, pos_EquaUAI, pos_J2000, code_retour, &
          asc_droite, declinaison, vit_EquaUAI, vit_J2000, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_EquaUAI_J2000.h'

     end subroutine mr_EquaUAI_J2000
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_EquaUAI_J2000.f90,v 1.1 2003/11/05 16:33:28 mslibatv Exp $ '

end module int_mslib_mr_EquaUAI_J2000
