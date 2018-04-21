module int_mslib_mr_TerVrai_TerRef

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_TerVrai_TerRef ( U, V, pos_vrai, pos_ref, code_retour, vit_vrai, vit_ref, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_TerVrai_TerRef.h'

     end subroutine mr_TerVrai_TerRef
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_TerVrai_TerRef.f90,v 1.3 2003/08/01 15:54:08 mslibatv Exp $ '

end module int_mslib_mr_TerVrai_TerRef
