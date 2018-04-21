module int_mslib_mvi_car_kep_ellip

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_car_kep_ellip(pos_car,vit_car,moment_cinetique,norme_vect_pos,norme_vect_vit,&
                              un_sur_a,e,pos_fois_vit,mu,kep,retour,jacob)
       use type_mslib
       use precision_mslib

       include 'arg_mvi_car_kep_ellip.h'

     end subroutine mvi_car_kep_ellip
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_car_kep_ellip.f90,v 1.2 2003/05/06 15:50:44 mslibatv Exp $ '

end module int_mslib_mvi_car_kep_ellip
