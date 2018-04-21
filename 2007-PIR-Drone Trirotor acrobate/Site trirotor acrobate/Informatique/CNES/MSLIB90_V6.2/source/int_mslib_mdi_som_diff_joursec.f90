module int_mslib_mdi_som_diff_joursec

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mdi_som_diff_joursec(joursec1, joursec2, retour, joursec_somme, joursec_diff)

       use type_mslib
       use precision_mslib

       include 'arg_mdi_som_diff_joursec.h'

     end subroutine mdi_som_diff_joursec
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mdi_som_diff_joursec.f90,v 1.2 2003/05/06 15:50:31 mslibatv Exp $ '

end module int_mslib_mdi_som_diff_joursec
