module int_mslib_mvi_car_kep_parab

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_car_kep_parab(pos_car,vit_car,moment_cinetique,norme_vect_pos,norme_moment_cinetique,&
                                  e, parametre,pos_fois_vit,mu,kep,retour,jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mvi_car_kep_parab.h'

     end subroutine mvi_car_kep_parab
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_car_kep_parab.f90,v 1.2 2003/05/06 15:50:44 mslibatv Exp $ '

end module int_mslib_mvi_car_kep_parab
