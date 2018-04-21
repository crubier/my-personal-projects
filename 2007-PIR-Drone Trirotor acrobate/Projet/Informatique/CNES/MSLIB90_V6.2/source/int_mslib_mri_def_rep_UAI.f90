module int_mslib_mri_def_rep_UAI

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mri_def_rep_UAI ( planete, modeleUAI, jul1950, alpha0, delta0, tsid, deriv_tsid, retour )

       use type_mslib
       use precision_mslib

       include 'arg_mri_def_rep_UAI.h'

     end subroutine mri_def_rep_UAI
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mri_def_rep_UAI.f90,v 1.1 2003/11/05 16:33:40 mslibatv Exp $ '

end module int_mslib_mri_def_rep_UAI
