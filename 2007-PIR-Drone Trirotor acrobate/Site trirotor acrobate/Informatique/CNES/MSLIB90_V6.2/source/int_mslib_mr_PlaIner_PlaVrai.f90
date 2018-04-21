module int_mslib_mr_PlaIner_PlaVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_PlaIner_PlaVrai ( planete, modeleUAI, long, pos_PlaIner, pos_PlaVrai, code_retour, &
          vit_rot, jul1950, vit_PlaIner, vit_PlaVrai, jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mr_PlaIner_PlaVrai.h'

     end subroutine mr_PlaIner_PlaVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_PlaIner_PlaVrai.f90,v 1.1 2003/11/17 16:49:21 mslibatv Exp $ '

end module int_mslib_mr_PlaIner_PlaVrai
