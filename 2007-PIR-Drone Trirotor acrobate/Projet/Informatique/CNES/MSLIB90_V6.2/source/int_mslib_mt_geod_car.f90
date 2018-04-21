module int_mslib_mt_geod_car

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_geod_car( pos_geod, r_equa, apla, pos_car, code_retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mt_geod_car.h'

     end subroutine mt_geod_car
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_geod_car.f90,v 1.3 2003/08/29 14:33:12 mslibatv Exp $ '

end module int_mslib_mt_geod_car
