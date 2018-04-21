module int_mslib_md_jourfrac_joursec

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine md_jourfrac_joursec(jourfrac, joursec, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_md_jourfrac_joursec.h'

     end subroutine md_jourfrac_joursec
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_md_jourfrac_joursec.f90,v 1.2 2003/05/06 15:50:31 mslibatv Exp $ '

end module int_mslib_md_jourfrac_joursec
