module int_mslib_mr_PlaVrai_PlaIner

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_PlaVrai_PlaIner ( planete, modeleUAI, long, pos_PlaVrai, pos_PlaIner, code_retour, &
          vit_rot, jul1950, vit_PlaVrai, vit_PlaIner, jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mr_PlaVrai_PlaIner.h'

     end subroutine mr_PlaVrai_PlaIner
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_PlaVrai_PlaIner.f90,v 1.1 2003/11/17 16:49:24 mslibatv Exp $ '

end module int_mslib_mr_PlaVrai_PlaIner
