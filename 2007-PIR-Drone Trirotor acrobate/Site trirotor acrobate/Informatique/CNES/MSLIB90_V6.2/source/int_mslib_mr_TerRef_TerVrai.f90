module int_mslib_mr_TerRef_TerVrai

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_TerRef_TerVrai( U, V, pos_ref, pos_vrai, code_retour, vit_ref, vit_vrai, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_TerRef_TerVrai.h'

     end subroutine mr_TerRef_TerVrai
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_TerRef_TerVrai.f90,v 1.3 2003/08/01 15:54:04 mslibatv Exp $ '

end module int_mslib_mr_TerRef_TerVrai
