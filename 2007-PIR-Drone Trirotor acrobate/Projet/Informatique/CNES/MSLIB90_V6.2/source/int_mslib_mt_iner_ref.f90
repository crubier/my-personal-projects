module int_mslib_mt_iner_ref

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mt_iner_ref(vit_rot, long, sec, pos_iner, pos_ref, code_retour, vit_iner, vit_ref, jacob)

       use type_mslib
       use precision_mslib

       include 'arg_mt_iner_ref.h'

     end subroutine mt_iner_ref
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mt_iner_ref.f90,v 1.2 2003/05/06 15:50:39 mslibatv Exp $ '

end module int_mslib_mt_iner_ref
