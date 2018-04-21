#!/bin/csh

 ############################################################################
 ##  #####  ####      ####  #########    ###      ########     ######      ##
 ##   ###   ###  ####  ###  ##########  ####  ###  ######  ###   ###   ##   #
 ##  #   #  ###  ####  ###  ##########  ####  ####  ####  #####  ###  ####  #
 ##  ## ##  ####  ########  ##########  ####  ###  #####  #####  ###  ####  #
 ##  #####  ######  ######  ##########  ####      #######  ###   ###  ####  #
 ##  #####  ########  ####  ##########  ####  ###  ########   #  ###  ####  #
 ##  #####  ###  ####  ###  ##########  ####  ####  ###########  ###  ####  #
 ##  #####  ###  ####  ###  ##########  ####  ###  #####  #####  ###   ##   #
 ##  #####  ####      ####        ###    ###      #######       #####      ##
 ############################################################################

###############################################################################

# Role   Generation de la librairie MSLIB90 (avec le(s) binaire(s) lie(s) au
# ====   module mslib) sous le directory lib/

# Limitation de cette procedure
# =============================
#       Valable (testee et utilisee) sur Sun avec l'environnement lie au WorkShop 6.2 Fortran 95 
#       par defaut.

#       Pour changer de version de compilateur et de Workshop, modifier les variables: 
#                ENVIRONNEMENT et SUFFIX_MOD

# Besoins/Conseils: 
# ================
#     1) avoir configure son environnement pour acceder au compilateur f90 du Workshop Sun

#     2) verifier le contenu de la variable ENVIRONNEMENT
#        definissant le nom du binaire. En particulier au niveau de la version de systeme SunOS,


# Utilisation   Se placer dans le directory de travail (endroit ou se trouve cette procedure)
# ===========
#     1) verifier que ce fichier possede bien en droit d'acces
#                     le "x" (eXecute)
#     2) Si oui, lancer:
#                      genere_libMSLIB90.csh
#        Si non, lancer:
#                      csh genere_libMSLIB90.csh


# Information (sur cette procedure): Cette procedure est ecrite en C-shell et a ete creee sur SUN
# ================================= 


# Creation: 04/2001 - A partir de la procedure de generation du SGC
# Modification: 04/2002 - version MSLIB 3.2
#               Ajout d'un alias (alias f90 'f95') pour mise a jour du compilateur fortran
# Modification: 03/2003 - version MSLIB 4.0
#               Mise a jour de la liste des routines.
# Modification: 10/2004 - version MSLIB 6.1
#               Mise a jour de la procedure et de la liste des routines.
# Modification: 03/2005 - version MSLIB 6.2
#               Mise a jour de la procedure et de la liste des routines.
###############################################################################


# INITIALISATIONS
# ===============

# generation des listes de routines et de programmes de tests
# (reportees a la fin de ce shell pour eviter d'alourdir le debut du shell)
# -------------------------------------------------------------------------
goto definition

debut:



# alias propre a ce shell
# -----------------------
alias rm '\rm   '   # on est sur de l'effacement !
alias mv '\mv   '   # on est sur de l'ecrasement
alias cp '\cp -i'   # pour eviter ecrasement si existe deja


# alias pour renommage du compilateur reellement utilise
# -----------------------------------------------------
alias f90 '\f95'  # a partir du Forte/Workshop 6: le nom du compilateur est f95
                  # sinon mettre cet alias en commentaire


# verification de la version du compilateur
# ------------------------------------------

echo ""
echo "Compilation avec le compilateur: "
f90 -V
echo ""
echo "et la version systeme :"
uname -a
echo ""




#                *************************************************
#                *************************************************
#                *  Structure de l'arborescence projet           *
#                *  utiles pour la generation de la librairie et *
#                *  les programmes de tests                      *
#                *************************************************
#                *************************************************
#                                         
#          Le repertoire de travail contient
#
#                   ------------------------
#                  /          |             \
#              source        lib           doc
#


# initialisations des directorys utiles
# -------------------------------------
set dir_lib="lib"
set dir_source_routine="source"
set dir_include="$dir_source_routine"


# verification et creation du repertoire de generation
# ----------------------------------------------------
if (! -e $dir_lib) mkdir $dir_lib


# initialisations MSLIB
# ---------------------

# Initialisation de la version de la librairie
# ............................................
set VERSION_MSLIB="6.2"

# Initialisation de l'environnement de creation de la librairie
# .............................................................

# Pour Sun et Workshop
set ENVIRONNEMENT="_SunOS5.8_f95Sunv6.2_V$VERSION_MSLIB"

# Initialisation du nom de librairie
# ..................................
set LIBMSLIB90A="libmslib90$ENVIRONNEMENT.a"


echo " "
echo " La librairie MSLIB 90 sera nommee: "
echo "         " $LIBMSLIB90A
echo " "
echo " D'accord (coherente avec la version de compilateur utilisee ici) ?"
echo -n "          Return = oui - n,N = non "

set rep=$< 
if ($rep == n || $rep == N) then
   echo " reinitialiser dans le shell la variable:   ENVIRONNEMENT  "
   set SUFFIX_MOD=".mod" # sinon probleme d'effacement
   goto fin_exit
endif
echo " "


# DEBUT du traitement
# ===================

# Initialisation liees aux modules (fonction du compilateur)
# ==========================================================

# Flag de compilation pour acces au directory contenant le module mslib
# ---------------------------------------------------------------------
set DIR_MODULE="-M"

# Extension pour les modules (hors .o) cree par le compilateur
# ------------------------------------------------------------
# Sun Workshop 4.2 (f90 v1.2)
# set SUFFIX_MOD=".M"

# Sun Workshop : a partir de la version 5.0 (f90 v2.0)
set SUFFIX_MOD=".mod"

# Nom des binaires lies au module mslib
# (ces noms dependent du compilateur)
# -------------------------------------
set mod_mslibM="mslib$SUFFIX_MOD"
set mod_mslibO="mslib.o"


# Choix sur les flags de compilation des objets
# =============================================
set FLAGS="-I$dir_include"
echo " "
echo " Les routines et modules seront compiles avec les options suivantes: "
echo "         " $FLAGS
echo " "



####################################################
# Generation de la librairie et du module mslib
####################################################


# Menage preliminaire pour etre sur de ne utiliser une mauvaise version
#  en cas de plantage de la procedure
if (-e $dir_lib/$LIBMSLIB90A) rm $dir_lib/$LIBMSLIB90A 
if (-e $dir_lib/$mod_mslibM)  rm $dir_lib/$mod_mslibM
if (-e $dir_lib/$mod_mslibO)  rm $dir_lib/$mod_mslibO


# Generation des objets/binaires des modules utiles
# =================================================

# ATTENTION: l'ordre de compilation est important

echo ""
echo " ***************************************************************************"
echo "           GENERATION de la librairie et du module mslib"
echo " "


echo " =======> Compilation des modules"

# ATTENTION: l'ordre de compilation est important

# communs a toutes les routines
foreach module_commun (`cat liste_modules_communs_$$`)

    echo "compilation du module commun "$module_commun
    f90 $FLAGS -c $dir_source_routine/$module_commun".f90"

end

# specifiques a certaines routines ou modules
foreach module_specifique (`cat liste_modules_specifiques_$$`)

    echo "compilation du module specifique "$module_specifique
    f90 $FLAGS -c $dir_source_routine/$module_specifique".f90"

end
echo " "


# specifiques a certaines routines

# sans objet


###############################################################
# lignes A DECOMMENTER si OPTION -I n'existe pas:
###############################################################
#echo " =======> Recopie des includes des routines (utilises dans les modules interfaces des routines ainsi que dans les routines) ...."

# # servent aussi pour les modules interfaces
#\cp $dir_source_routine/arg_m*.h .
#echo " "
###############################################################



echo " =======> Compilation des modules interfaces de chaque routine de la librairie"

foreach routine (`cat liste_routine_$$`)

    echo "compilation du module interface de "$routine
    f90 $FLAGS -c $dir_source_routine/int_mslib_$routine".f90"

end
echo " "




echo " =======> Compilation du module interface pour l'utilisateur"

# module non utilise en interne MSLIB (mais fait pour l'utilisateur)
f90 $FLAGS -c $dir_source_routine/interface_mslib.f90
echo " "



echo " =======> Compilation des routines MSLIB composant la librairie"

foreach routine (`cat liste_routine_$$`)

    echo "compilation de la routine "$routine
    f90 $FLAGS -c $dir_source_routine/$routine".f90"

end
echo " "


###############################################################
# lignes A DECOMMENTER si OPTION -I n'existe pas:
###############################################################
#echo " =======> Suppression des includes des routines ...."

#rm arg_m*.h
#echo " "
###############################################################



echo " =======> Generation de la librairie et copie sous lib/ "

# on archive tous les .o 
# (la liste est definie a partir de la liste des routines
# tel que pour chacune on rajoute ".o" en fin de mot, 
# et on concatene le tout sur une seule ligne)
sed -e 's+ *$+.o+' liste_routine_$$ > liste_o_$$
sed -e 's+ *$+.o+' liste_modules_communs_$$ >> liste_o_$$
sed -e 's+ *$+.o+' liste_modules_specifiques_$$ >> liste_o_$$

ar rv $LIBMSLIB90A `paste -s -d" " liste_o_$$`

chmod 640 $LIBMSLIB90A

# Si une version du fichier existe sous lib: elle sera ecrasee sans confirmation
mv $LIBMSLIB90A $dir_lib

echo " "


echo " ***************************************************************************"

echo " =======> Compilation et copie sous lib/ du module utilisateur: mslib"

f90 $FLAGS -c $dir_source_routine/mslib.f90

# Si une version du fichier existe sous lib: elle sera ecrasee sans confirmation
mv $mod_mslibM $dir_lib
mv $mod_mslibO $dir_lib

echo " "
echo " ***************************************************************************"
echo " "



##########
# Menage
##########

fin_exit:

foreach file (liste_routine_std_$$ liste_routine_interne_$$ liste_routine_mz_$$ liste_routine_$$ liste_o_$$ liste_modules_specifiques_$$ liste_modules_communs_$$)
  if (-e $file) rm $file    # effacage du fichier s'il existe
end

ls *.o *$SUFFIX_MOD > tempo_$$

if (! -z tempo_$$) then # fichier non vide donc il y a des fichiers .o ou *$SUFFIX_MOD
   foreach file (*.o *$SUFFIX_MOD)
      if (-e $file) rm $file    # effacage du fichier s'il existe
   end
endif

\rm tempo_$$

# FIN du shell proprement dit
# ============

exit 0

##############################################################################
# Definition de la liste contenant les routines de la librairie

definition:

# ROUTINES:
# ========
# liste des routines standard de la librairie 
# (accessibles a l'utilisateur)
cat > liste_routine_std_$$ << FIN_routine_std
mc_GRS1980
mc_math
mc_phys
mc_test
md_calend_julien
md_comp_joursec
md_duree_jhms
md_jourfrac_joursec
md_joursec_jourfrac
md_joursec_norme
md_julien_calend
me_brouwer
me_brouwer_moy
me_deriv_secul_j2
me_eck_hech
me_eck_hech_moy
me_lyddane
me_lyddane_moy
mm_impul_car
mm_impul_kep
mo_def_qsw
mo_def_tnw
mo_geo_qsw
mo_geo_tnw
mo_qsw_geo
mo_tnw_geo
mp_atm_US76
mr_EcliJ2000_J2000
mr_EquaMoy_EquaVrai
mr_EquaMoy_J2000
mr_EquaUAI_J2000
mr_EquaUAI_PlanetVrai
mr_EquaVrai_EquaMoy
mr_EquaVrai_TerVrai
mr_EquaVrai_veis
mr_J2000_BBR
mr_J2000_EcliJ2000
mr_J2000_EquaMoy
mr_J2000_EquaUAI
mr_J2000_TerVrai
mr_J2000_veis
mr_mat_J2000_BBR
mr_PlaIner_PlaVrai
mr_PlanetVrai_EquaUAI
mr_PlaVrai_PlaIner
mr_TerRef_TerVrai
mr_TerVrai_EquaVrai
mr_TerVrai_J2000
mr_TerVrai_TerRef
mr_TerVrai_veis
mr_mat_nuta
mr_nuta
mr_obli_moy
mr_rep_fon
mr_tsid_aoki
mr_tsid_veis
mr_tsid_vrai
mr_veis_EquaVrai
mr_veis_J2000
mr_veis_TerVrai
ms_pos_soleil_lune
mt_car_geoc
mt_car_geod
mt_def_topo_N
mt_geoc_car
mt_geod_car
mt_iner_ref
mt_ref_iner
mt_ref_topo_N
mt_topo_E_car_sgd
mt_topo_E_sgd_car
mt_topo_N_car_sgd
mt_topo_N_ref
mt_topo_N_sgd_car
mt_topo_car_E_N
mt_topo_car_N_E
mt_topo_sgd_E_N
mt_topo_sgd_N_E
mu_angle2
mu_angle3
mu_axe_angle_quat
mu_compar_rot_quat
mu_mat_quat
mu_norme
mu_prod_quat
mu_prod_vect
mu_3rot_quat
mu_quat_3rot
mu_quat_axe_angle
mu_quat_conjug
mu_quat_mat
mu_quat_norme
mu_quat_rep
mv_car_cir
mv_car_cir_equa
mv_car_equa
mv_car_kep
mv_cir_car
mv_cir_equa_car
mv_cir_equa_kep
mv_cir_kep
mv_conv_anom
mv_equa_car
mv_equa_kep
mv_kep_car
mv_kep_cir
mv_kep_cir_equa
mv_kep_equa
mv_kepler_bar
mv_kepler_gene
mv_kepler_std
FIN_routine_std

# liste des routines interne de la librairie 
# (non accessible a l'utilisateur)
cat > liste_routine_interne_$$ << FIN_routine_interne
mdi_som_diff_joursec
mri_arg_fon
mri_def_rep_UAI
mri_eclip_M_eclip_V
mri_eclip_M_equa_M
mri_eclip_M_equa_V
mri_eclip_V_eclip_M
mri_eclip_V_equa_M
mri_eclip_V_equa_V
mri_eclip_moy_t1_t2
mri_eclip_vrai_t1_t2
mri_equa_M_eclip_M
mri_equa_M_eclip_V
mri_equa_M_equa_V
mri_equa_V_eclip_M
mri_equa_V_eclip_V
mri_equa_V_equa_M
mri_equa_moy_t1_t2
mri_equa_vrai_t1_t2
mui_axe_norme_quat
mvi_barker
mvi_car_equa_ellip
mvi_car_equa_hyperb
mvi_car_equa_parab
mvi_car_kep_ellip
mvi_car_kep_hyperb
mvi_car_kep_parab
mvi_conv_anom_ellip
mvi_conv_anom_hyperb
mvi_conv_anom_parab
mvi_equa_car_ellip
mvi_equa_car_hyperb
mvi_equa_car_parab
mvi_kep_car_ellip
mvi_kep_car_hyperb
mvi_kep_car_parab
mvi_kepler_hyperb
FIN_routine_interne

# liste des modules communs de la librairie 
# ATTENTION: l'ordre est important
cat > liste_modules_communs_$$ << FIN_modules_communs
longueur_chaine_mslib
precision_mslib
valeur_code_retour_mslib
numero_routine_mslib
type_mslib
FIN_modules_communs

# liste des modules specifiques de la librairie 
# ATTENTION: l'ordre est important
cat > liste_modules_specifiques_$$ << FIN_modules_specifiques
code_anomalies_mslib
code_planetes_mslib
code_transfo_mslib
code_modeles_mslib
indic_reperes_mslib
indic_comp_joursec_mslib
parametre_mslib
math_mslib
phys_mslib
test_mslib
GRS1980_mslib
parametres_internes_mslib
FIN_modules_specifiques

# liste des routines du theme Z de la librairie 
# (accessibles a l'utilisateur)
cat > liste_routine_mz_$$ << FIN_routine_mz
mz_numero_routine
mz_val_code_retour
FIN_routine_mz

# liste de toutes les routines composant la librairie
cat liste_routine_std_$$ liste_routine_interne_$$ liste_routine_mz_$$ > liste_routine_$$

goto debut
##########################################

