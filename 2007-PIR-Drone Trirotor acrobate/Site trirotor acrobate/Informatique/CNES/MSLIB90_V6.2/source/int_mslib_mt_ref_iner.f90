module int_mslib_mt_ref_iner

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_ref_iner( vit_rot, long, sec, pos_ref, pos_iner, code_retour, vit_ref, vit_iner, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mt_ref_iner.h'

     end subroutine mt_ref_iner
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_ref_iner.f90,v 1.2 2003/05/06 15:50:40 mslibatv Exp $ '

end module int_mslib_mt_ref_iner
