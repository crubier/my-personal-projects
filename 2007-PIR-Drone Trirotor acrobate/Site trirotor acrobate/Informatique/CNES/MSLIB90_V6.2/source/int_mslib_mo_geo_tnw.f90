module int_mslib_mo_geo_tnw

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mo_geo_tnw( pos_car, vit_car, vect_geo, vect_tnw, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_mo_geo_tnw.h'

     end subroutine mo_geo_tnw
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mo_geo_tnw.f90,v 1.2 2003/05/06 15:50:33 mslibatv Exp $ '

end module int_mslib_mo_geo_tnw
