module int_mslib_mri_arg_fon

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mri_arg_fon (jul1950, model, arg_fon, retour, arg_deriv)

       use type_mslib
       use precision_mslib

       include 'arg_mri_arg_fon.h'

     end subroutine mri_arg_fon
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mri_arg_fon.f90,v 1.2 2003/05/06 15:50:36 mslibatv Exp $ '

end module int_mslib_mri_arg_fon
