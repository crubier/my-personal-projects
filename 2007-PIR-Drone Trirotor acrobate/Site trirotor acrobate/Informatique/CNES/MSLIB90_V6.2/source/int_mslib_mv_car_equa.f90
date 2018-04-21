module int_mslib_mv_car_equa

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_car_equa( mu, pos_car, vit_car, equa, code_retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mv_car_equa.h'

     end subroutine mv_car_equa
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_car_equa.f90,v 1.2 2003/05/06 15:50:43 mslibatv Exp $ '

end module int_mslib_mv_car_equa
