module int_mslib_mt_def_topo_N

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_def_topo_N( lat, long, vect_i, vect_j, vect_k, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mt_def_topo_N.h'

     end subroutine mt_def_topo_N
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_def_topo_N.f90,v 1.2 2003/05/06 15:50:39 mslibatv Exp $ '

end module int_mslib_mt_def_topo_N
