module int_mslib_mri_eclip_vrai_t1_t2

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mri_eclip_vrai_t1_t2 ( model, jul1950_t1, jul1950_t2, mat_pass, retour)

       use type_mslib
       use precision_mslib

       include 'arg_mri_eclip_vrai_t1_t2.h'

     end subroutine mri_eclip_vrai_t1_t2
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mri_eclip_vrai_t1_t2.f90,v 1.2 2003/05/06 15:50:37 mslibatv Exp $ '

end module int_mslib_mri_eclip_vrai_t1_t2
