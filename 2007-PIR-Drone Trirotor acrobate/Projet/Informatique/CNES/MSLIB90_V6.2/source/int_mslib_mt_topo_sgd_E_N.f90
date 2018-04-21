module int_mslib_mt_topo_sgd_E_N

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_topo_sgd_E_N(pos_E, pos_N, code_retour, vit_E, vit_N, jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mt_topo_sgd_E_N.h'

     end subroutine mt_topo_sgd_E_N
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_topo_sgd_E_N.f90,v 1.2 2003/05/06 15:50:41 mslibatv Exp $ '

end module int_mslib_mt_topo_sgd_E_N
