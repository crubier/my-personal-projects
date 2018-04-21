module int_mslib_mr_J2000_EcliJ2000

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mr_J2000_EcliJ2000 ( pos_J2000, pos_EcliJ2000, code_retour,  &
                                  obliquite, vit_J2000, vit_EcliJ2000, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mr_J2000_EcliJ2000.h'

     end subroutine mr_J2000_EcliJ2000
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mr_J2000_EcliJ2000.f90,v 1.2 2003/11/06 15:49:08 mslibatv Exp $ '

end module int_mslib_mr_J2000_EcliJ2000
