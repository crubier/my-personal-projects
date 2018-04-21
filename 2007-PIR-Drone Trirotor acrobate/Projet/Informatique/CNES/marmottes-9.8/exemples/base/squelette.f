c     Ce fichier montre un squelette d'utilisation de Marmottes pour
c     simuler une attitude à consignes constantes et en déduire la
c     mesure d'un senseur. Sans aucune modification du code, on peut simuler
c     des cas simples tels qu'un pointage solaire ou un yaw steering, mais
c     on peut également regarder ce qui se passe en présence de biais de pilotage,
c     et avec des senseurs décalés par rapport aux axes nominaux. Il suffit
c     pour cela de changer les consignes lues en entrée, ou de modifier le
c     repère du senseur dans le fichier senseur.

      program pointe
c
c     Déclaration des variables
      integer npas, idmarm, i, ier
      character*40  sensctr (3), senseur
      character*256 msg
      double precision date, pos (3), vit (3), attit (4), spin (3)
      double precision pas, mesctr (3), mes
c
c     Déclaration des fonctions Marmottes
      integer MarmottesCreer, MarmottesAttitude, MarmottesMesure
      external MarmottesCreer, MarmottesAttitude
      external MarmottesMesure, MarmottesDetruire
c
c     Déclaration des fonctions externes
c     (pour faire fonctionner ce squelette, il faut écrire ces fonctions ...)
      external extrap, lecture
c
c     Lecture des données
      call lecture (sensctr, mesctr, date, pos, vit, pas, npas, senseur)
c
c     On ne connait pas l'attitude initiale, on la pose arbitrairement
      attit (1) = 1.0d0
      do 10 i = 1, 3
         attit (i+1) = 0.0d0
         spin  (i)   = 0.0d0
 10   continue
c
c     Initialisation du simulateur,
c     pour un pointage solaire, l'utilisateur définit les contrôles :
c     'tangage-soleil', 'lacet-soleil', 'RTL-roulis' (et des valeurs nulles
c     si le pilotage est sans biais), pour un pointage terre avec yaw-steering,
c     l'utilisateur donne : 'RTL-roulis', 'RTL-tangage', 'lacet-soleil'
c     (et des valeurs nulles si le pilotage est sans biais), pour un pointage terre
c     classique l'utilisateur donne : 'RTL-roulis', 'RTL-tangage', 'RTL-lacet'
c     (et des valeurs nulles si le pilotage est sans biais)
      idmarm = MarmottesCreer (date, pos, vit, attit, spin,
     >                         'senseurs.fr', sensctr (1),
     >                         sensctr (2), sensctr (3),
     >                         msg)
      if (idmarm .eq. 0) then
c       Il y a eu un problème quelque part
         write (0, '(a)') msg (1:lnblnk (msg))
         stop
      endif
c
c     Boucle de calcul
      do 20 i = 1, npas
c
c        Extrapolation
c        (le but de cet exemple n'est pas de montrer un extrapolateur)
         date = date + pas
         call extrap (date, pos, vit)
c
c        Simulation d'attitude (dans ce cas, les consignes sont constantes)
         if (MarmottesAttitude (idmarm, date, pos, vit,
     >                          mesctr (1), mesctr (2), mesctr (3),
     >                          msg) .ne. 0) then
            call MarmottesDetruire (idmarm)
            write (0, '(a)') msg (1:lnblnk (msg))
            stop
         endif
c
c        tracé de la mesure du senseur testé (on ne sait pas lequel)
c        (on décide ici d'ignorer les erreurs)
         ier = MarmottesMesure (idmarm, senseur, mes, msg)
         write (6, '(14.8f, %11.4e)') date, mes

 20   continue
c
c     Fin normale
      call MarmottesDetruire (idmarm)
      stop
      end
