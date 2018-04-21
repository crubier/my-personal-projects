module int_mslib_mt_car_geoc

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_car_geoc( pos_car, pos_geoc, code_retour, vit_car, vit_geoc, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mt_car_geoc.h'

     end subroutine mt_car_geoc
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_car_geoc.f90,v 1.3 2003/05/06 15:50:39 mslibatv Exp $ '

end module int_mslib_mt_car_geoc
