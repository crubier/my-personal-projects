module int_mslib_mo_geo_qsw

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mo_geo_qsw( pos_car, vit_car, vect_geo, vect_qsw, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mo_geo_qsw.h'

     end subroutine mo_geo_qsw
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mo_geo_qsw.f90,v 1.2 2003/05/06 15:50:32 mslibatv Exp $ '

end module int_mslib_mo_geo_qsw
