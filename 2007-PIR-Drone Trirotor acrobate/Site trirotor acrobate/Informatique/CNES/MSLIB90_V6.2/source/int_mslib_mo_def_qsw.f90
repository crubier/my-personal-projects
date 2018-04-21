module int_mslib_mo_def_qsw

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mo_def_qsw ( pos_car, vit_car, q, s, w, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mo_def_qsw.h'

     end subroutine mo_def_qsw
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mo_def_qsw.f90,v 1.2 2003/05/06 15:50:32 mslibatv Exp $ '

end module int_mslib_mo_def_qsw
