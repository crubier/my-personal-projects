module int_mslib_mt_topo_N_car_sgd

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_topo_N_car_sgd(pos_car, pos_sgd, code_retour, vit_car, vit_sgd, jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mt_topo_N_car_sgd.h'

     end subroutine mt_topo_N_car_sgd
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_topo_N_car_sgd.f90,v 1.2 2003/05/06 15:50:41 mslibatv Exp $ '

end module int_mslib_mt_topo_N_car_sgd
