#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include "key.h"

/**
 * ATTENTION : les coordonnées graphiques en informatique ont toujours leur
 * origine dans le coin supérieur gauche.
 * L'axe des abscisses est croissant vers la droite.
 * L'axes des ordonnées est par contre croissant vers le bas.
 * Toutes les coordonnées et les distances (largeur, hauteur, x, y, ...) sont 
 * données en pixels. Tout dépend donc de la résolution de l'écran. Une résolution
 * de 1024 x 768 veut donc dire qu'il y a 1024 pixels de largeur à l'écran et 768
 * pixels en hauteur.
 */

#define TRUE 1
#define FALSE 0

typedef int BOOLEAN;

typedef enum { WHITE, BLACK, RED, BLUE, GREEN, YELLOW, CYAN, GRAY, MAGENTA, ORANGE, PINK } COLOR;

typedef enum { PLAIN, BOLD, ITALIC } STYLE;

/**
 * Méthode de création de la fenêtre dans laquelle dessiner.
 * Cette méthode doit être appelée en 1er pour pouvoir utiliser toutes
 * les autres fonctions.
 * width : largeur de la fenêtre.
 * height : hauteur de la fenêtre.
 */
void start(int width, int height);

/**
 * Méthode à appeler à la fin du programme. Elle permet d'attendre
 * la fermeture de la fenêtre pour arrêter le programme courant (sinon
 * la fenêtre se fermerait automatiquement)
 */
void finish();

/**
 * Bloque l'exécution du programme pendant le temps indiqué en paramètre.
 * Cette méthode est à appeler par exemple si on veut redessiner le contenu
 * de la fenêtre toutes les 20 ms, en lui passant 20 comme argument.
 * millis : temps d'attente en millisecondes.
 */
void sleepAWhile(long millis);

/**
 * Spécifie la couleur de 1er plan. C'est la couleur utilisée par les
 * méthode draw... et fill...
 * color : la couleur de 1er plan.
 * cf. l'énumération COLOR pour la liste des couleurs disponibles.
 */
void setForegroundColor(COLOR color);

/**
 * Spécifie la couleur d'arrière-plan. C'est la couleur utilisée par la
 * méthode clearRect pour "effacer" le rectangle spécifié (le rectangle est
 * en fait rempli avec cette couleur).
 * color : la couleur d'arrière-plan.
 * cf. l'énumération COLOR pour la liste des couleurs disponibles. */
void setBackgroundColor(COLOR color);

/**
 * "Efface" le rectangle spécifié avec la couleur d'arrière-plan.
 * x : abscisse du coin supérieur gauche du rectangle.
 * y : ordonnée du coin supérieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 */
void clearRect(int x, int y, int width, int height);

/**
 * Dessine un arc de cercle.
 * x : abscisse du coin supérieur gauche du rectangle circonscrit.
 * y : ordonnée du coin supérieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 * startAngle : angle de départ de l'arc de cercle (en degrés). Un angle de 0
 * correspond à l'axe des abscisses. Un angle positif suit le sens trigonométrique.
 * endAngle : longueur angulaire de l'arc (à partir de l'angle de départ).
 */
void drawArc(int x, int y, int width, int height, int startAngle, int arcAngle);

/**
 * Dessine une image.
 * filepath : chemin de l'image (.jpg, .gif, .png, ...) en relatif (par rapport
 * au répertoire de lancement de l'application) ou en absolu ("c:\...." ou "/home..").
 * ATTENTION : sous Windows, il est possible (et préférable) d'utiliser "/" 
 * au lieu de "\" pour spécifier le chemin d'un fichier (p.ex. : "toto/titi/image.jpg").
 * Ceci a l'avantage de ne pas être obligé de modifier le code lors de la compilation
 * sous un autre système d'exploitation.
 * x : abscisse du coin supérieur gauche de l'image.
 * y : ordonnée du coin supérieur gauche de l'image.
 */
void drawImage(const char *filepath, int x, int y);

/**
 * Dessine une ligne.
 * x1 : abscisse du 1er point.
 * y1 : ordonnée du 1er point.
 * x2 : abscisse du 2ème point.
 * y2 : ordonnée du 2ème point.
 */
void drawLine(int x1, int y1, int x2, int y2);  

/**
 * Dessine un ovale inscrit dans le rectangle spécifié.
 * x : abscisse du coin supérieur gauche du rectangle circonscrit.
 * y : ordonnée du coin supérieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 */
void drawOval(int x, int y, int width, int height);

/**
 * Dessine un polygone.
 * Chaque point est relié au suivant par un segment ainsi que le dernier 
 * point avec le premier s'ils sont différents.
 * xPoints : tableau des abscisses des points.
 * yPoints : tableau des ordonnées des points.
 * nPoints : nombre total de points.
 */
void drawPolygon(int *xPoints, int *yPoints, int nPoints);

/**
 * Dessine une séquence de points reliés.
 * Chaque point est relié au suivant par un segment. 
 * xPoints : tableau des abscisses des points.
 * yPoints : tableau des ordonnées des points.
 * nPoints : nombre total de points.
 */
void drawPolyline(int *xPoints, int *yPoints, int nPoints);

/**
 * Dessine un rectangle.
 * x : abscisse du coin supérieur gauche du rectangle.
 * y : ordonnée du coin supérieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 */
void drawRect(int x, int y, int width, int height);

/**
 * Dessine un rectangle surligné en 3D.
 * x : abscisse du coin supérieur gauche du rectangle.
 * y : ordonnée du coin supérieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 * raised : un booleén spécifiant si le rectangle doit apparaître surélevé
 * ou abaissé.
 */
void draw3DRect(int x, int y, int width, int height, BOOLEAN raised);

/**
 * Dessine un rectangle dont les coins sont arrondis.
 * x : abscisse du coin supérieur gauche du rectangle circonscrit.
 * y : ordonnée du coin supérieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 * arcWidth : largeur du rectangle cirsconscrit à l'arc utilisé pour arrondir les angles.
 * arcHeight : hauteur du rectangle cirsconscrit à l'arc utilisé pour arrondir les angles.
 */
void drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight);

/**
 * Dessine un texte à l'écran.
 * text : le texte à afficher.
 * x : l'abscisse de la 1ère lettre du texte.
 * y : l'ordonnée du texte.
 * cf. setFontSize et setFontStyle.
 */
void drawText(const char *text, int x, int y);

/**
 * Spécifie la taille de la police à utiliser par la méthode drawText.
 * size : taille de la police utilisée pour afficher du texte (la taille
 * par défaut doit être 12).
 * cf. drawText.
 */
void setFontSize(float size);

/**
 * Spécifie le style de la police à utiliser par la méthode drawText.
 * style : style à appliquer à la police (BOLD = gras, ITALIC = italique,
 * PLAIN = normal).
 * cf. l'énumération STYLE.
 */
void setFontStyle(STYLE style);

/**
 * Dessine et remplit un arc de cercle (comme une part de gâteau).
 * x : abscisse du coin supérieur gauche du rectangle circonscrit.
 * y : ordonnée du coin supérieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 * startAngle : angle de départ de l'arc de cercle (en degrés). Un angle de 0
 * correspond à l'axe des abscisses. Un angle positif suit le sens trigonométrique.
 * endAngle : longueur angulaire de l'arc (à partir de l'angle de départ).
 */
void fillArc(int x, int y, int width, int height, int startAngle, int arcAngle);

/**
 * Dessine et remplit un ovale inscrit dans le rectangle spécifié.
 * x : abscisse du coin supérieur gauche du rectangle circonscrit.
 * y : ordonnée du coin supérieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 */
void fillOval(int x, int y, int width, int height);

/**
 * Dessine et remplit un polygone.
 * Chaque point est relié au suivant par un segment ainsi que le dernier 
 * point avec le premier s'ils sont différents.
 * xPoints : tableau des abscisses des points.
 * yPoints : tableau des ordonnées des points.
 * nPoints : nombre total de points.
 */
void fillPolygon(int *xPoints, int *yPoints, int nPoints);

/**
 * Dessine et remplit un rectangle.
 * x : abscisse du coin supérieur gauche du rectangle.
 * y : ordonnée du coin supérieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 */
void fillRect(int x, int y, int width, int height);

/**
 * Dessine et remplit un rectangle dont les coins sont arrondis.
 * x : abscisse du coin supérieur gauche du rectangle circonscrit.
 * y : ordonnée du coin supérieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 * arcWidth : largeur du rectangle cirsconscrit à l'arc utilisé pour arrondir les angles.
 * arcHeight : hauteur du rectangle cirsconscrit à l'arc utilisé pour arrondir les angles.
 */
void fillRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight);

/**
 * Dessine et remplit un rectangle surligné en 3D.
 * x : abscisse du coin supérieur gauche du rectangle.
 * y : ordonnée du coin supérieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 * raised : un booleén spécifiant si le rectangle doit apparaître surélevé
 * ou abaissé.
 */
void fill3DRect(int x, int y, int width, int height, BOOLEAN raised);

/**
 * Affiche le graphique dans la fenêtre.
 * Toutes les figures dessinées avec les méthodes ci-dessus (drawRect, drawArc, fillRect, 
 * fillOval, etc...) n'apparaissent dans la fenêtre qu'une fois que paint() a été
 * appelé.
 */
void paint();

/**
 * "Enregistre" la touche du clavier passée en paramètre.
 * Cette méthode doit être appelée au début du programme (avant d'utiliser
 * la méthode "getLastKeyPressed") en passant en paramètre la touche du
 * clavier que l'on veut écouter.
 * Par exemple : registerKeyPressed(VK_LEFT); va "écouter" la touche flèche
 * gauche du clavier.
 * key : code de la touche du clavier (cf. key.h pour la liste des codes)
 * cf. getLastKeyPressed
 */
void registerKeyPressed(int key);

/**
 * Renvoie la touche du clavier pressée ou -1 si aucune touche n'est pressée.
 * Seule les touches qui auront été enregistrée avec la méthode registerKeyPressed
 * sont écoutées.
 * Exemple : Voici le code d'une application qui permet de faire bouger un ballon
 * vers le haut ou vers le bas en fonction de l'appui des touches Flèche Haut et Bas.
 * 
 * #include "graphic.h"
 * #include "key.h"
 * 
 * int main() {
 *   int y = 400;                     // ordonnée du ballon (haut du ballon)
 *   int fini = 0;                    // valeur booléenne initialisée à FAUX
 * 
 *   start(800, 800);                 // création d'une fenêtre 800 x 800
 *   setBackgroundColor(BLACK);       // couleur de fond = NOIR
 *   setForegroundColor(RED);         // couleur de 1er plan = ROUGE
 *   clearRect(0, 0, 800, 800);       // la fenêtre est painte entièrement en noir 
 *
 *   registerKeyPressed(VK_UP);       // Enregistrement de la touche Flèche Haut
 *   registerKeyPressed(VK_DOWN);     // Enregistrement de la touche Flèche Bas
 * 
 *   fillOval(400, y, 40, 40);        // Dessin du ballon de diamètre 40, à l'abscisse
 *                                    // 400 et à l'ordonnée y (angle gauche-haut)
 * 
 *   while (!fini) {                  // boucle infinie
 *     switch (getLastKeyPressed()) { // Récupération de la touche pressée en cours
 *       case -1:                     // aucune touche pressée
 *         break;                     // On ne fait rien 
 *       case VK_UP:                  // Si la touche pressée est la flèche Haut
 *         y--;                       // On décrémente y, le ballon ira vers le haut
 *         break;
 *       case VK_DOWN:                // Si la touche pressée est la flèche Bas
 *         y++;                       // On incrémente y, le ballon ira vers le bas
 *         break;
 *       case VK_ESCAPE:              // par défaut la touche "escape" est toujours écoutée
 *         fini = 1;                  // sortira de la boucle à la prochaine itération
 *         break;
 *     }
 *     clearRect(0, 0, 800, 800);     // On efface la fenêtre (toute en noir donc)
 *     fillOval(400, y, 40, 40);      // On redessine le ballon à sa nouvelle position
 *     paint();                       // On affiche le résultat
 *     sleepAWhile(5);                // On patiente 5 ms, ce qui fera un affichage
 *                                    // de 200 images/s, ce qui est largement suffisant
 *   }
 *   finish();                       // Cette méthode doit toujours être appelée en fin de programme
 * }
 */
int getLastKeyPressed();

/**
 * "Enregistre" le son passé en paramètre.
 * Cette méthode doit être appelée avant d'appeler "playSound).
 * Ce son doit être un fichier de type "wav" (avec l'extension ".wav").
 * filepath : chemin du fichier son en relatif (par rapport au répertoire de 
 * lancement de l'application) ou en absolu ("c:\...." ou "/home..").
 * ATTENTION : sous Windows, il est possible (et préférable) d'utiliser "/" 
 * au lieu de "\" pour spécifier le chemin d'un fichier (p.ex. : "toto/titi/son.wav").
 * Ceci a l'avantage de ne pas être obligé de modifier le code lors de la compilation
 * sous un autre système d'exploitation.
 * L'enregistrement des fichiers sons est obligatoire pour pouvoir ensuite jouer le son
 */
void registerSound(char *filepath);

/**
 * Joue le son préalablement enregistré (le chemin du fichier doit être le
 * même que lors de l'appel à registrerSound).
 */
void playSound(char *filepath);

void setClip(int x, int y, int width, int height);

void addClip(int x, int y, int width, int height);


#endif
