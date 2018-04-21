module int_mslib_mv_kepler_gene

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mv_kepler_gene( pso_M, ex, ey, pso_E, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mv_kepler_gene.h'

     end subroutine mv_kepler_gene
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mv_kepler_gene.f90,v 1.2 2003/05/06 15:50:43 mslibatv Exp $ '

end module int_mslib_mv_kepler_gene
