module int_mslib_mt_topo_sgd_N_E

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_topo_sgd_N_E(pos_N, pos_E, code_retour, vit_N, vit_E, jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mt_topo_sgd_N_E.h'

     end subroutine mt_topo_sgd_N_E
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_topo_sgd_N_E.f90,v 1.2 2003/05/06 15:50:41 mslibatv Exp $ '

end module int_mslib_mt_topo_sgd_N_E
