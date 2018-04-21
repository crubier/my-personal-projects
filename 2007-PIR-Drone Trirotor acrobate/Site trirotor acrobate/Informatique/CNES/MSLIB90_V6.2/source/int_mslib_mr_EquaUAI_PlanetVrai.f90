module int_mslib_mr_EquaUAI_PlanetVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_EquaUAI_PlanetVrai ( planete, modeleUAI, jul1950, pos_EquaUAI, pos_PlanetVrai, code_retour, &
          tsid, deriv_tsid, vit_EquaUAI, vit_PlanetVrai, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_EquaUAI_PlanetVrai.h'

     end subroutine mr_EquaUAI_PlanetVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_EquaUAI_PlanetVrai.f90,v 1.1 2003/11/05 16:33:30 mslibatv Exp $ '

end module int_mslib_mr_EquaUAI_PlanetVrai
