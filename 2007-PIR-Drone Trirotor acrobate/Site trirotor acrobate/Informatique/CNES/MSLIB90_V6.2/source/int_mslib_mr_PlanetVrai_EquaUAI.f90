module int_mslib_mr_PlanetVrai_EquaUAI

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_PlanetVrai_EquaUAI ( planete, modeleUAI, jul1950, pos_PlanetVrai, pos_EquaUAI, code_retour, &
          tsid, deriv_tsid, vit_PlanetVrai, vit_EquaUAI, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_PlanetVrai_EquaUAI.h'

     end subroutine mr_PlanetVrai_EquaUAI
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_PlanetVrai_EquaUAI.f90,v 1.1 2003/11/05 16:33:38 mslibatv Exp $ '

end module int_mslib_mr_PlanetVrai_EquaUAI
