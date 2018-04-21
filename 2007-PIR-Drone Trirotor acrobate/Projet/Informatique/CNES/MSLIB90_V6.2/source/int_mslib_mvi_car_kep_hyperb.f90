module int_mslib_mvi_car_kep_hyperb

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_car_kep_hyperb(pos_car,vit_car,moment_cinetique,norme_vect_pos,norme_vect_vit,norme_moment_cinetique,&
                                   un_sur_a,excentricite, parametre,pos_fois_vit,mu,kep,retour,jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mvi_car_kep_hyperb.h'

     end subroutine mvi_car_kep_hyperb
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_car_kep_hyperb.f90,v 1.2 2003/05/06 15:50:44 mslibatv Exp $ '

end module int_mslib_mvi_car_kep_hyperb
