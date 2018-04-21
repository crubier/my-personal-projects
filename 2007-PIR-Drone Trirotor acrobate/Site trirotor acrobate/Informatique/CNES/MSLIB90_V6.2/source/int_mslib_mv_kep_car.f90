module int_mslib_mv_kep_car

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_kep_car( mu, kep, pos_car, vit_car, code_retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mv_kep_car.h'

     end subroutine mv_kep_car
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_kep_car.f90,v 1.2 2003/05/06 15:50:43 mslibatv Exp $ '

end module int_mslib_mv_kep_car
