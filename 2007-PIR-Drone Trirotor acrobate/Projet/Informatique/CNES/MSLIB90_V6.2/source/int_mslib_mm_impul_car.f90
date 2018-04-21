module int_mslib_mm_impul_car

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mm_impul_car( pos_car, vit_car_avant, rep, impul, vit_car_apres, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mm_impul_car.h'

     end subroutine mm_impul_car
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mm_impul_car.f90,v 1.2 2003/05/06 15:50:32 mslibatv Exp $ '

end module int_mslib_mm_impul_car
