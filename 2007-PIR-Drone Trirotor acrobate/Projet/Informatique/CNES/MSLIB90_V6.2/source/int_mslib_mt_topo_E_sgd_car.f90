module int_mslib_mt_topo_E_sgd_car

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_topo_E_sgd_car(pos_sgd, pos_car, code_retour, vit_sgd, vit_car, jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mt_topo_E_sgd_car.h'

     end subroutine mt_topo_E_sgd_car
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_topo_E_sgd_car.f90,v 1.2 2003/05/06 15:50:40 mslibatv Exp $ '

end module int_mslib_mt_topo_E_sgd_car
