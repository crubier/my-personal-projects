module int_mslib_mt_ref_topo_N

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_ref_topo_N( orig_topo, r_equa, apla, pos_ref, pos_topo, code_retour, vit_ref, vit_topo, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mt_ref_topo_N.h'

     end subroutine mt_ref_topo_N
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_ref_topo_N.f90,v 1.2 2003/05/06 15:50:40 mslibatv Exp $ '

end module int_mslib_mt_ref_topo_N
