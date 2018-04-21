module int_mslib_mt_car_geod

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_car_geod( pos_car, r_equa, apla, pos_geod, code_retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mt_car_geod.h'

     end subroutine mt_car_geod
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_car_geod.f90,v 1.3 2003/08/29 14:33:10 mslibatv Exp $ '

end module int_mslib_mt_car_geod
