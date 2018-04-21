module int_mslib_mvi_equa_car_parab

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_equa_car_parab(equa,mu,pos_car,vit_car,retour,jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mvi_equa_car_parab.h'

     end subroutine mvi_equa_car_parab
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_equa_car_parab.f90,v 1.2 2003/05/06 15:50:45 mslibatv Exp $ '

end module int_mslib_mvi_equa_car_parab
