module int_mslib_mc_GRS1980

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres
  
  implicit none

  public

  interface
     subroutine mc_GRS1980 ( code_retour, r_equa, inv_apla, apla )

       use type_mslib
       use precision_mslib

       include 'arg_mc_GRS1980.h'

     end subroutine mc_GRS1980
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mc_GRS1980.f90,v 1.2 2003/05/06 15:50:30 mslibatv Exp $ '

end module int_mslib_mc_GRS1980
