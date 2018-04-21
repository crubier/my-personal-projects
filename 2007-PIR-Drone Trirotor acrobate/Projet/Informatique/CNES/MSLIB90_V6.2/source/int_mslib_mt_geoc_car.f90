module int_mslib_mt_geoc_car

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_geoc_car( pos_geoc, pos_car, code_retour, vit_geoc, vit_car, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mt_geoc_car.h'

     end subroutine mt_geoc_car
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_geoc_car.f90,v 1.4 2003/05/06 15:50:39 mslibatv Exp $ '

end module int_mslib_mt_geoc_car
