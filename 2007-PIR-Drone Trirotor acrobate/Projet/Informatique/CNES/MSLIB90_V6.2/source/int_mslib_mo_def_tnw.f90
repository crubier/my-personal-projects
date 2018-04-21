module int_mslib_mo_def_tnw

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mo_def_tnw ( pos_car, vit_car, t, n, w, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mo_def_tnw.h'

     end subroutine mo_def_tnw
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mo_def_tnw.f90,v 1.2 2003/05/06 15:50:32 mslibatv Exp $ '

end module int_mslib_mo_def_tnw
