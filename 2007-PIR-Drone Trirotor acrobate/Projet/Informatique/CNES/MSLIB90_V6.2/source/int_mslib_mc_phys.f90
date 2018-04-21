module int_mslib_mc_phys

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mc_phys ( code_retour, ua, vit_lum, i_critique_non_retro, i_critique_retro )

       use type_mslib
       use precision_mslib

       include 'arg_mc_phys.h'

     end subroutine mc_phys
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mc_phys.f90,v 1.2 2003/05/06 15:50:30 mslibatv Exp $ '

end module int_mslib_mc_phys
