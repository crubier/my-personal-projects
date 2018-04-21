*******************************************************************************
*     $<AM-V1.0>
*     
*     $Type
*     DEF
*     
*     $Projet
*     
*     $Application
*     
*     $Nom
*     
*     $Resume
*     fichier d'implantation de la classe XXXX
*     
*     $Description
*     Module de définition de la classe
*     
*     $Contenu
*     
*     $Historique
*     $Log: prgm_BodyEphemF.f,v $
*     Revision 1.3  2003/10/22 13:08:41  marmottes
*     DM 0026, 0027
*     FA 0031
*
*     Revision 1.2  2003/07/29 11:50:10  marmottes
*     lecture du nom du fichier senseurs sur la ligne de commande pour
*     permettre des configurations hors de l'espace des sources
*
*     Revision 1.1  2003/07/08 14:06:31  marmottes
*     FA-ID 0023 Modification du type des fonctions fortran dans enregistreCorps : Programme principal de test
*
*     Revision 1.1  2003/07/07 07:13:29  marmottes
*     FA-ID 0023 Modification du type des fonctions fortran dans enregistreCorps
*     
*     $Version
*     $Id: prgm_BodyEphemF.f,v 1.3 2003/10/22 13:08:41 marmottes Exp $
*     
*     $Auteur
*     F.Auguie
*     
*     $<>
*******************************************************************************

      program MainBodyEphemF
c     
      implicit none
c     

c #include "marmottes/InterfaceF.h"

c     programme de test de haut niveau des fonctionnalitées d'enregistrement
c     de fonctions utilisateurs lors de l'appel de la classe BodyEphem a partir d'un 
c     sous programme Fortran


c     Déclaration des variables globales
c     ----------------------------------

c     Déclaration des variables locales
c     ---------------------------------

c     rayon equatorial terrestre
c     aplatissement de la Terre
c     vitesse de rotation de la Terre sur elle-meme
c     valeur bidon pour utiliser la valeur par defaut


      double precision r_terre, aplatissement, vit_bidon 
      double precision r_lune_bidon, r_soleil_bidon
      double precision date, orbite(6), position(3), vitesse(3)
      double precision attitude(4), spin(3), mesures(3)  
      double precision mu, pas, m 
      double precision date_lue, pos_lue(3), vit_lue(3)
      double precision att_lue(4), spin_lu(3)  
      character*20     senseurs(3)

      integer idmarm, cr_ap, iter
      character*256 fichier
      character*1000  messageErreur 

      double precision M_PI
      double precision dt
      parameter (M_PI=3.14159265358979323846)



c     Declaration des fonctions
c     -------------------------

      double precision tsidrLocal
      external         tsidrLocal
      external         sunLocal, moonLocal, earthLocal
      integer          MarmottesCreer ,MarmottesEnregistreCorps 
      double precision MarmottesTempsSideralParDefaut 
      integer          MarmottesAttitude ,MarmottesMesure 
      integer          MarmottesLireParametres 

c     Declaration des external
c     ------------------------
      external         MarmottesCreer ,MarmottesEnregistreCorps 
      external         MarmottesTempsSideralParDefaut 
      external         MarmottesPositionSoleilParDefaut 
      external         MarmottesPositionTerreParDefaut 
      external         MarmottesPositionLuneParDefaut 
      external         MarmottesAttitude ,MarmottesMesure 
      external         MarmottesDetruire ,MarmottesLireParametres


c -------------------------
c     Debut des instructions 
c --------------------------

c     Initialisations
c     ---------------

c      M_PI = 3.14159265358979323846
      cr_ap = 0
      r_terre = 6378.39
      aplatissement = 1.0 / 298.256

      vit_bidon      = -1.0 
      r_lune_bidon   = -1.0 
      r_soleil_bidon = -1.0 

      orbite(1) = 42164.0
      orbite(2) = 0.0
      orbite(3) = 0.0
      orbite(4) = 0.0
      orbite(5) = 0.0
      orbite(6) = 0.0

      mu = 398600.436

      attitude(1) = 0.5
      attitude(2) = -0.5
      attitude(3) = -0.5
      attitude(4) = 0.5

      spin(1) = 0.0
      spin(2) = 0.0
      spin(3) = 0.0

      senseurs(1) = 'DSS_1_PITCH'
      mesures(1) = 2.5 

      senseurs(2) = 'GEOIRS_1_ROLL'
      mesures(2) = 2.7 

      senseurs(3) = 'DSS_1_YAW'
      mesures(3) = -0.2 

      pas = 20

      date = 1600
c     (22/10/93)
      if (iargc () .lt. 1) then
         write (0, *) 'usage: prgm_BodyEphemF fichier'
         stop
      endif
      call getarg (1, fichier)

c     creation d'un simulateur Marmottes
c     ----------------------------------
      call cartesiens (orbite, mu, position, vitesse) 
      idmarm = MarmottesCreer (date, position, vitesse,attitude,spin,
     >     fichier, 
     >     senseurs(1), 
     >     senseurs(2),
     >     senseurs(3),
     >     messageErreur)
      if (idmarm .eq. 0) then
         print *, ' ERREUR a l appel de MarmottesCreer : ',
     >        messageErreur
         stop
      endif

      write(6,*) ' --------------------------------------------------',
     >     ' --------------------'
      write(6,*) ' Appel a MarmottesEnregistreCorps en utilisant les',
     >     ' fonctions par defaut'
      write(6,*) ' --------------------------------------------------',
     >     ' --------------------'

c     appel a MarmottesEnregistreCorps en utilisant les fonctions par defaut
c     ----------------------------------------------------------------------
      cr_ap = MarmottesEnregistreCorps (idmarm, r_terre, aplatissement,
     >     vit_bidon, r_lune_bidon, r_soleil_bidon,
     >     MarmottesTempsSideralParDefaut,
     >     MarmottesPositionSoleilParDefaut,
     >     MarmottesPositionLuneParDefaut,
     >     MarmottesPositionTerreParDefaut, messageErreur)
      if (cr_ap .lt. 0) then
c     traitement
         write(6,*) ' ERREUR a l appel de MarmottesEnregistreCorps : ',
     >        messageErreur
         stop
      endif

c     appel a MarmottesAttitude
c     -------------------------
      cr_ap = MarmottesAttitude (idmarm, date, position, vitesse,
     >     mesures (1), mesures (2), mesures (3), attitude, spin,
     >     messageErreur)
      if (cr_ap .lt. 0) then
c     traitement
         write(6,*) ' ERREUR a l appel de MarmottesAttitude : ',
     >        messageErreur
         stop
      endif

c     appel a MarmottesMesure pour le 1er senseur
c     -------------------------------------------
      cr_ap = MarmottesMesure (idmarm, senseurs (1), m,
     >     messageErreur)
      if (cr_ap .lt. 0) then
c     traitement
         write(6,*) ' ERREUR a l appel de MarmottesMesure : ',
     >        messageErreur
         call MarmottesDetruire (idmarm) 
         stop
      endif

      write(6,*) ' Mesure realisee par le 1er senseur',m

      write(6,*) ' --------------------------------------------------',
     >     ' ----------------------'
      write(6,*) ' Appel a MarmottesEnregistreCorps en utilisant les',
     >     ' fonctions utilisateurs'
      write(6,*) ' --------------------------------------------------',
     >     ' ----------------------'


c     appel a MarmottesEnregistreCorps en utilisant les fonctions utilisateur
c     -----------------------------------------------------------------------
      cr_ap = MarmottesEnregistreCorps (idmarm, r_terre, aplatissement,
     >     vit_bidon, r_lune_bidon, r_soleil_bidon,
     >     tsidrLocal, sunLocal, moonLocal, earthLocal,
     >     messageErreur)
      if (cr_ap .lt. 0) then
c     traitement
         write(6,*) ' ERREUR a l appel de MarmottesEnregistreCorps : ',
     >        messageErreur
         stop
      endif

c     appel a MarmottesAttitude
c     -------------------------
      cr_ap = MarmottesAttitude (idmarm, date, position, vitesse,
     >     mesures (1), mesures (2), mesures (3), attitude, spin,
     >     messageErreur)
      if (cr_ap .lt. 0) then
c     traitement
         write(6,*) ' ERREUR a l appel de MarmottesAttitude : ',
     >        messageErreur
         stop
      endif

c     appel a MarmottesMesure pour le 1er senseur
c     -------------------------------------------
      cr_ap = MarmottesMesure (idmarm, senseurs (1), m,
     >     messageErreur)
      if (cr_ap .lt. 0) then
c     traitement
         write(6,*) ' ERREUR a l appel de MarmottesMesure : ',
     >        messageErreur
         call MarmottesDetruire (idmarm) 

         stop
      endif

      write(6,*) ' Mesure realisee par le 1er senseur',m

c     recuperation des valeurs courantes des parametres    
c     ------------------------------------------------
      cr_ap = MarmottesLireParametres (idmarm, date_lue, pos_lue, 
     > vit_lue, att_lue, spin_lu,  messageErreur)
      if (cr_ap .lt. 0) then
c     traitement
         write(6,*) ' ERREUR a l appel de MarmottesLireParametres : ',
     >        messageErreur
         call MarmottesDetruire (idmarm) 
         stop
      endif

      write(6,*) ' Lecture des parametres courants :'
      write(6,*) '  date :',date_lue
      write(6,*) '  position : x=',pos_lue(1),' y=',pos_lue(2),' z=', 
     > pos_lue(3)
      write(6,*) '  vitesse  : x=',vit_lue(1),' y=',vit_lue(2),' z=', 
     > vit_lue(3)
      write(6,*) '  attitude : q0=',att_lue(1),' q1=',att_lue(2),' q2=', 
     > att_lue(3),' q3=', att_lue(4) 
       write(6,*)'  spin     : x=', spin_lu(1),' y=', spin_lu(2),' z=', 
     > spin_lu(3)

c     Destruction du simulateur marmotte
c     ----------------------------------
      call MarmottesDetruire (idmarm) 

      stop
      end program MainBodyEphemF


*******************************************************************************
*     SUBROUTINES & FUNCTIONS
*******************************************************************************

      subroutine cartesiens (orbite, mu, position, vitesse)

c     
      implicit none
c     

c     arguments
      double precision orbite(6), mu, position(3), vitesse(3)

c     declaration des variables locales
      double precision anoExc 
      double precision E, n, xp, xq, vp, vq, cosI, sinI, cosPOM, sinPOM
      double precision cosGOM, sinGOM, px, py, pz, qx, qy, qz


c     conversion des paramètres orbitaux keplériens en coordonnées cartésiennes
      E  = anoExc (orbite(6), orbite (2))
      n  = dsqrt (mu / orbite(1)) / orbite(1)

      xp =  orbite(1) * (dcos (E) - orbite(2))
      xq =  orbite(1) * dsqrt (1.0 - orbite(2) * orbite(2)) * dsin (E)
      vp = -orbite(1) * dsin (E) * n / (1 - orbite(2) * dcos (E))
      vq =  orbite(1) * dcos (E) * n / (1 - orbite(2) * dcos (E))*
     >     dsqrt (1.0 - orbite(2) * orbite(2))

      cosI   = dcos (orbite(3))
      sinI   = dsin (orbite(3))
      cosPOM = dcos (orbite(4))
      sinPOM = dsin (orbite(4))
      cosGOM = dcos (orbite(5))
      sinGOM = dsin (orbite(5))

      px = cosPOM * cosGOM - sinPOM * cosI * sinGOM
      py = cosPOM * sinGOM + sinPOM * cosI * cosGOM
      pz = sinPOM * sinI

      qx = -sinPOM * cosGOM - cosPOM * cosI * sinGOM
      qy = -sinPOM * sinGOM + cosPOM * cosI * cosGOM
      qz = cosPOM * sinI

      position(1) = xp * px + xq * qx
      position(2) = xp * py + xq * qy
      position(3) = xp * pz + xq * qz

      vitesse(1) = vp * px + vq * qx
      vitesse(2) = vp * py + vq * qy
      vitesse(3) = vp * pz + vq * qz

      return
      end subroutine cartesiens

*******************************************************************************
      double precision function anoExc (M, e)

c     
      implicit none
c     

c     arguments
      double precision M, e
      
c     résolution de l'équation de Kepler
      double precision Eold, Enew

      Eold = M
      Enew = 0

c     1 iteration de + ?
      do while ((dabs(Enew - Eold)).gt.(1.0e-6))
         Enew = M + e * dsin (Eold)
         Eold = Enew;
      end do

      anoExc = Enew

      return
      end function anoExc

*******************************************************************************

      double precision function tsidrLocal (t, offset)
c     
      implicit none
c     

c     arguments
      double precision t, offset

c     Déclaration des variables globales

c     sidereal time upgraded wrt the CNES julian date t (seconds are expressed in fraction of day)
      double precision a1, a3, eps, r 

      double precision M_PI
      parameter (M_PI=3.14159265358979323846)


      a1  = 0.1746647708617871e1 
      a3  = 0.7292115146705e-04 
      eps = 1.7202179573714597e-02 

      r = t - idint(t) 
      r = a1 + eps * t + a3 * offset + (M_PI + M_PI) * r 

c     On recalle r entre [0, 2PI]
c      if (r.gt.(2*M_PI)) then
      do while (r.gt.(2*M_PI))
         r = r - (2*M_PI)
      end do  
c      else 
      do while (r.lt.(0.0))
         r = r + (2*M_PI)
      end do  
c      endif
      
      tsidrLocal = r

      return
      end function tsidrLocal

*******************************************************************************

      subroutine sunLocal (t, bodysun)
c     
      implicit none
c     

c     arguments
      double precision t, bodysun(3)

c     Déclaration des variables globales

c     computation of the Sun  position wrt the central body (units: km)
c     =================================================================
c     In this case : central body = Earth

      double precision M_PI
      parameter (M_PI=3.14159265358979323846)

      double precision date, f, d, xlp, g, e, ce, se, rot, cr, sr
      double precision cl, sl, q, sx, sy, earthsun(3), dasr

      date   = t - 10000.0 
      f   = (225.768 + 13.2293505 * date) * M_PI / 180.0 
      d   = (11.786 + 12.190749 * date) * M_PI / 180.0
      xlp = (134.003 + 0.9856 * date) * M_PI / 180.0 
      g   = (282.551 + 0.000047 * date) * M_PI / 180.0
      e   = (23.44223 - 3.5626e-07 * date) * M_PI / 180.0
      ce  = dcos (e) 
      se  = dsin (e) 
      rot = 0.6119022e-06 * t 
      cr  = dcos (rot) 
      sr  = dsin (rot) 
      

c     Newcomb's theory

      cl   = 99972.0 * dcos (xlp + g) + 1671.0 * dcos (xlp + xlp + g) - 
     >     1678.0 * dcos (g) 
      cl   = cl + 32.0 * dcos (3.0 * xlp + g) + dcos (4.0 * xlp + g) + 
     >     2.0 * dcos (xlp + d + g) 
      cl   = cl - 4.0 * dcos (g - xlp) - 2.0 * dcos (xlp - d + g) + 
     >     4.0 * dcos (f - d) 
      cl   = cl - 4.0 * dcos (xlp + xlp - f + d + g + g) 
      cl   = cl * 1.e-05 

      sl   = 99972.0 * dsin (xlp + g) + 1671.0 * dsin (xlp + xlp + g) - 
     >     1678.0 * dsin (g) 
      sl   = sl + 32.0 * dsin (3.0 * xlp + g) + dsin (4.0 * xlp + g) + 
     >     2.0 * dsin (xlp + d + g) 
      sl   = sl - 4.0 * dsin (g - xlp) - 2.0 * dsin (xlp - d + g) + 
     >     4.0 * dsin (f - d) 
      sl   = sl - 4.0 * dsin (xlp + xlp - f + d + g + g) 
      sl   = sl * 1.e-05 

      q    = dsqrt (cl * cl + sl * sl) 
      sx   = cl / q 
      sy   = sl * ce / q 

      earthsun(1) = sx * cr + sy * sr 
      earthsun(2) = sy * cr - sx * sr 
      earthsun(3) = sl * se / q 

      dasr = 1672.2 * dcos (xlp) + 28.0 * dcos (xlp + xlp) -
     >     0.35 * dcos (d) 

c     units: km
      bodysun(1) = earthsun(1) * 149597870.0 / (1.0 + 1.e-05 * dasr) 
      bodysun(2) = earthsun(2) * 149597870.0 / (1.0 + 1.e-05 * dasr) 
      bodysun(3) = earthsun(3) * 149597870.0 / (1.0 + 1.e-05 * dasr) 

      return  
      end subroutine sunLocal

*******************************************************************************

      subroutine moonLocal (t, bodymoon)

c     
      implicit none
c     

c     arguments
      double precision t, bodymoon(3)

c     Déclaration des variables globales

c     computation of the Moon position wrt the central body (units: km)
c     =================================================================
c     In this case : central body = Earth

      double precision M_PI
      parameter (M_PI=3.14159265358979323846)

      double precision date, f, xl, d, xlp, e, ce, se, rot, cr, sr
      double precision dl, b, u, cu, su, cb, sb, rx, ry
      double precision earthmoon(3), dasr 

      date   = t - 10000.0 
      f   = (225.768 + 13.2293505 * date) * M_PI / 180.0 
      xl  = (185.454 + 13.064992 * date) * M_PI / 180.0 
      d   = (11.786 + 12.190749 * date) * M_PI / 180.0 
      xlp = (134.003 + 0.9856 * date) * M_PI / 180.0 
      e   = (23.44223 - 3.5626e-07 * date) * M_PI / 180.0 
      ce  = dcos (e) 
      se  = dsin (e) 
      rot = 0.6119022e-06 * t 
      cr  = dcos (rot) 
      sr  = dsin (rot) 

c     Brown's theory
      dl   = 10976.0 * dsin (xl) - 2224.0 * dsin (xl - d - d) + 
     >     1149.0 * dsin (d + d) 
      dl   = dl + 373.0 * dsin (xl + xl) - 324.0 * dsin (xlp) - 
     >     200.0 * dsin (f + f) 
      dl   = dl - 103.0 * dsin (xl + xl - d - d) - 
     >     100.0 * dsin (xl + xlp - d - d) 
      dl   = dl + 93.0 * dsin (xl + d + d) 
      dl   = dl - 80.0 * dsin (xlp - d - d) + 72.0 * dsin (xl - xlp) - 
     >     61.0 * dsin (d) 
      dl   = dl - 53.0 * dsin (xl + xlp) 
      dl   = dl + 14.0 * dsin (xl - xlp - d - d) +
     >     19.0 * dsin (xl - f - f) 
      dl   = dl - 19.0 * dsin (xl - 4.0 * d) 
      dl   = dl + 17.0 * dsin (3.0 * xl) - 27.0 * dsin (f + f - d - d) 
      dl   = dl - 12.0 * dsin (xlp + d + d) 
      dl   = dl - 22.0 * dsin (xl + f + f) -
     >     15.0 * dsin (xl + xl - 4.0 * d) 
      dl   = dl + 7.0 * dsin (xl + xl + d + d) + 9.0 * dsin (xl - d) 
      dl   = dl - 6.0 * dsin (3.0 * xl - d - d) 
      dl   = dl + 7.0 * dsin (4.0 * d) + 9.0 * dsin (xlp + d) + 
     >     7.0 * dsin (xl - xlp + d + d) 
      dl   = dl + 5.0 * dsin (xl + xl - xlp) 
      dl   = dl * 1.e-05 

      b = 8950.0 * dsin (f) + 490.0 * dsin (xl + f) +
     >     485.0 * dsin (xl - f) 
      b    = b - 302.0 * dsin (f - d - d) 
      b    = b - 97.0 * dsin (xl - f - d - d) -
     >     81.0 * dsin (xl + f - d - d) 
      b    = b + 57.0 * dsin (f + d + d) 
      b    = b - 14.0 * dsin (xlp + f - d - d) + 
     >     16.0 * dsin (xl - f + d + d) 
      b    = b + 15.0 * dsin (xl + xl - f) + 30.0 * dsin (xl + xl + f) 
      b    = b - 6.0 * dsin (xlp - f + d + d) - 
     >     7.0 * dsin (xl + xl + f - d - d) 
      b    = b + 7.0 * dsin (xl + f + d + d) 
      b    = b * 1.e-05 

      u  = ((68.341 + 13.176397 * date) * M_PI / 180.0) + dl 
      cu = dcos (u) 
      su = dsin (u) 
      cb = dcos (b) 
      sb = dsin (b) 
      rx = cu * cb 
      ry = su * cb * ce - sb * se 

      earthmoon(1) =  rx * cr + ry * sr 
      earthmoon(2) =  ry * cr - rx * sr 
      earthmoon(3) =  sb * ce + su * cb * se 

      dasr = 5450.0 * dcos (xl) + 1002.0 * dcos (xl - d - d) + 
     >     825.0 * dcos (d + d) 
      dasr = dasr + 297.0 * dcos (xl + xl) + 90.0 * dcos (xl + d + d) 
      dasr = dasr + 56.0 * dcos (xlp - d - d) 
      dasr = dasr + 42.0 * dcos (xl + xlp - d - d) +
     >     34.0 * dcos (xl - xlp) 
      dasr = dasr - 12.0 * dcos (xlp) - 29.0 * dcos (d) - 
     >     21.0 * dcos (xl - f - f) 
      dasr = dasr + 18.0 * dcos (xl - 4.0 * d) - 28.0 * dcos (xl + xlp) 
      dasr = dasr + 11.0 * dcos (xl + xl - 4.0 * d) +
     >     18.0 * dcos (3.0 * xl) 
      dasr = dasr - 9.0 * dcos (xlp + d + d) -
     >     7.0 * dcos (xl - xlp - d - d) 
      dasr = dasr + 7.0 * dcos (xl - xlp + d+d) 
      dasr = dasr - 9.0 * dcos (xl + xl - d - d) + 
     >     8.0 * dcos (xl + xl + d + d) 
      dasr = dasr + 8.0 * dcos (4.0 * d) 

c     units: km
      bodymoon(1) = earthmoon(1) * 384389.3 / (1.0 + 1.0e-5 * dasr) 
      bodymoon(2) = earthmoon(2) * 384389.3 / (1.0 + 1.0e-5 * dasr) 
      bodymoon(3) = earthmoon(3) * 384389.3 / (1.0 + 1.0e-5 * dasr) 


      return  
      end subroutine moonLocal

*******************************************************************************

      subroutine  earthLocal (t, bodyearth)

c     
      implicit none
c     

c     arguments
      double precision t, bodyearth(3)

c     computation of the Earth position wrt the central body (units: km)
c     =================================================================
c     In this case : central body = Earth

      bodyearth(1) = 0.0  
      bodyearth(2) = 0.0   
      bodyearth(3) = 0.0  

      return  
      end subroutine earthLocal




      
