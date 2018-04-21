module int_mslib_mz_val_code_retour

  use longueur_chaine_mslib

  implicit none

  public

  interface
     subroutine mz_val_code_retour (valeur, signification, code_retour)

       use type_mslib

       include 'arg_mz_val_code_retour.h'

     end subroutine mz_val_code_retour
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mz_val_code_retour.f90,v 1.2 2003/05/06 15:50:45 mslibatv Exp $ '

end module int_mslib_mz_val_code_retour

