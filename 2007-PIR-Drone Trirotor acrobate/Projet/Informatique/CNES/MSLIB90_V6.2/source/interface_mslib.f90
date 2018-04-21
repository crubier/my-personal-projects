
module interface_mslib

! (C) Copyright CNES - MSLIB - 1997-2004

!************************************************************************
!
! But:  Definition des interfaces explicites des routines MSLIB. 
! ===
!
! Note d'utilisation:  Ce module est accessible a l'utilisateur via le module mslib.
! ==================
!
! Historique:
! ==========
!   + Version 0.1 (SP 174 ed01 rev00): creation
!   + Version 1.0 (DE globale 182 ed01 rev01): creation chaine info_utilisateur
!                 (sans DE)                  : ajout de nouveaux modules interfaces
!   + Version 2.0 (sans DE)                  : ajout de nouveaux modules interfaces
!   + Version 3.0 (sans DE)                  : ajout de nouveaux modules interfaces
!   + Version 4.0 (sans DE)                  : ajout de nouveaux modules interfaces
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!   + Version 5.0 (sans DE)                  : ajout de nouveaux modules interfaces
!   + Version 6.0 (sans DE)                  : ajout de nouveaux modules interfaces
!   + Version 6.1 (sans DE)                  : ajout de nouveaux modules interfaces
!   + Version 6.2 (sans DE)                  : ajout de nouveaux modules interfaces
!************************************************************************


  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  ! liste de tous les modules interfaces existants
  ! ==============================================
  ! (le classement se fait par ordre alphabetique car cela permet de verifier si tous
  !  les modules interfaces existants sont pris en compte ici par comparaison avec le contenu
  !  du repertoire version/source/ )

  use int_mslib_mc_GRS1980 
  use int_mslib_mc_math 
  use int_mslib_mc_phys
  use int_mslib_mc_test

  use int_mslib_md_calend_julien
  use int_mslib_md_comp_joursec
  use int_mslib_md_duree_jhms
  use int_mslib_md_jourfrac_joursec
  use int_mslib_md_joursec_jourfrac
  use int_mslib_md_joursec_norme
  use int_mslib_md_julien_calend
  
  use int_mslib_me_brouwer
  use int_mslib_me_brouwer_moy
  use int_mslib_me_deriv_secul_j2
  use int_mslib_me_eck_hech
  use int_mslib_me_eck_hech_moy
  use int_mslib_me_lyddane
  use int_mslib_me_lyddane_moy

  use int_mslib_mm_impul_car
  use int_mslib_mm_impul_kep

  use int_mslib_mo_def_qsw
  use int_mslib_mo_def_tnw
  use int_mslib_mo_geo_qsw
  use int_mslib_mo_geo_tnw
  use int_mslib_mo_qsw_geo
  use int_mslib_mo_tnw_geo

  use int_mslib_mp_atm_US76

  use int_mslib_mr_mat_nuta
  use int_mslib_mr_nuta
  use int_mslib_mr_obli_moy
  use int_mslib_mr_rep_fon
  use int_mslib_mr_tsid_aoki
  use int_mslib_mr_tsid_veis
  use int_mslib_mr_tsid_vrai
  use int_mslib_mr_TerVrai_TerRef
  use int_mslib_mr_TerRef_TerVrai
  use int_mslib_mr_TerVrai_veis
  use int_mslib_mr_veis_TerVrai
  use int_mslib_mr_veis_J2000
  use int_mslib_mr_J2000_TerVrai
  use int_mslib_mr_J2000_veis
  use int_mslib_mr_EquaMoy_J2000
  use int_mslib_mr_EquaMoy_EquaVrai
  use int_mslib_mr_J2000_EquaMoy
  use int_mslib_mr_veis_EquaVrai
  use int_mslib_mr_EquaVrai_veis
  use int_mslib_mr_EquaVrai_EquaMoy
  use int_mslib_mr_EquaVrai_TerVrai
  use int_mslib_mr_TerVrai_EquaVrai
  use int_mslib_mr_TerVrai_J2000
  use int_mslib_mr_J2000_EcliJ2000
  use int_mslib_mr_EcliJ2000_J2000
  use int_mslib_mr_J2000_EquaUAI
  use int_mslib_mr_EquaUAI_J2000
  use int_mslib_mr_PlanetVrai_EquaUAI
  use int_mslib_mr_EquaUAI_PlanetVrai
  use int_mslib_mr_PlaVrai_PlaIner
  use int_mslib_mr_PlaIner_PlaVrai
  use int_mslib_mr_J2000_BBR
  use int_mslib_mr_mat_J2000_BBR

  use int_mslib_ms_pos_soleil_lune

  use int_mslib_mt_car_geoc
  use int_mslib_mt_car_geod
  use int_mslib_mt_def_topo_N
  use int_mslib_mt_geoc_car
  use int_mslib_mt_geod_car
  use int_mslib_mt_iner_ref
  use int_mslib_mt_ref_iner
  use int_mslib_mt_ref_topo_N
  use int_mslib_mt_topo_car_E_N
  use int_mslib_mt_topo_car_N_E
  use int_mslib_mt_topo_E_car_sgd
  use int_mslib_mt_topo_E_sgd_car
  use int_mslib_mt_topo_N_car_sgd
  use int_mslib_mt_topo_N_ref
  use int_mslib_mt_topo_N_sgd_car
  use int_mslib_mt_topo_sgd_E_N
  use int_mslib_mt_topo_sgd_N_E
 
  use int_mslib_mu_3rot_quat
  use int_mslib_mu_angle2
  use int_mslib_mu_angle3
  use int_mslib_mu_axe_angle_quat
  use int_mslib_mu_compar_rot_quat
  use int_mslib_mu_mat_quat
  use int_mslib_mu_norme
  use int_mslib_mu_prod_quat
  use int_mslib_mu_prod_vect
  use int_mslib_mu_quat_axe_angle
  use int_mslib_mu_quat_conjug
  use int_mslib_mu_quat_mat
  use int_mslib_mu_quat_norme
  use int_mslib_mu_quat_rep
  use int_mslib_mu_quat_3rot

  use int_mslib_mv_car_cir
  use int_mslib_mv_car_cir_equa
  use int_mslib_mv_car_equa
  use int_mslib_mv_car_kep
  use int_mslib_mv_cir_car
  use int_mslib_mv_cir_equa_car
  use int_mslib_mv_cir_equa_kep
  use int_mslib_mv_cir_kep
  use int_mslib_mv_conv_anom
  use int_mslib_mv_equa_car
  use int_mslib_mv_equa_kep
  use int_mslib_mv_kep_car
  use int_mslib_mv_kep_cir
  use int_mslib_mv_kep_cir_equa
  use int_mslib_mv_kep_equa
  use int_mslib_mv_kepler_bar
  use int_mslib_mv_kepler_gene
  use int_mslib_mv_kepler_std
  
  use int_mslib_mz_numero_routine
  use int_mslib_mz_val_code_retour

  implicit none

  character(len=pm_longueur_info_utilisateur), private :: info_utilisateur = &
                     '@(#) Fichier MSLIB interface_mslib.f90: derniere modification V6.2 >'

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: interface_mslib.f90,v 1.25 2005/02/28 07:49:56 mslibdev Exp $ '

end module interface_mslib
