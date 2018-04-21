module int_mslib_mt_topo_N_ref

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_topo_N_ref(orig_topo, r_equa, apla, pos_topo, pos_ref, code_retour, vit_topo, vit_ref, jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mt_topo_N_ref.h'

     end subroutine mt_topo_N_ref
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_topo_N_ref.f90,v 1.2 2003/05/06 15:50:41 mslibatv Exp $ '

end module int_mslib_mt_topo_N_ref
