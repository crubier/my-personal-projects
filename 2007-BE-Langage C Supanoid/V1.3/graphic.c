#include <stdlib.h>
#include <jni.h>

#ifndef WIN32
#include <unistd.h>
#endif

#include "graphic.h"

static JNIEnv *env;

static jclass frame_cls;
static jclass panel_cls;
static jclass color_cls;
static jclass imageIcon_cls;
static jclass font_cls;
static jobject panel;
static jobject frame;

static void manageException()
{
  jthrowable exception = (*env)->ExceptionOccurred(env);
  if (exception) {
    (*env)->ExceptionDescribe(env);
    (*env)->ExceptionClear(env);
  }
}

void start(int width, int height)
{
  JavaVM *jvm;
  JavaVMOption options[4];
  JavaVMInitArgs vm_args;
  long result;

  jmethodID frame_constructor_method;


  jfieldID panel_field;

  options[0].optionString = "-Djava.compiler=NONE";           /* disable JIT */
#ifdef WIN32
  options[1].optionString = "-Djava.class.path=.;out/classes;graphics.jar"; /* user classes */
  // EN ATTENDANT
  //  options[1].optionString = "-Djava.class.path=.;out/classes"; /* user classes */
#else
  options[1].optionString = "-Djava.class.path=.:out/classes:graphics.jar"; /* user classes */
  // EN ATTENDANT
  //  options[1].optionString = "-Djava.class.path=.:out/classes"; /* user classes */
#endif
  //  options[2].optionString = "-Djava.library.path=.";  /* set native library path */
  //  options[3].optionString = "-verbose:jni";         

  //  JNI_GetDefaultJavaVMInitArgs(&vm_args);
  
  vm_args.version=JNI_VERSION_1_4;
  vm_args.options=options;
  vm_args.nOptions = 2;
  vm_args.ignoreUnrecognized = JNI_TRUE;

  // Lancement de la machine virtuelle
  result = JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
  if (result == JNI_ERR) {
    printf("%ld\n", result);
    exit(-2);
  }

  (*jvm)->AttachCurrentThreadAsDaemon(jvm, (void **)&env, NULL);

  // Chargement des classes
  frame_cls = (*env)->FindClass(env, "MainFrame");
  if (frame_cls == NULL) {
    manageException();
    exit(-3);
  }

  panel_cls = (*env)->FindClass(env, "DrawPanel");
  if (panel_cls == NULL) {
    manageException();
    exit(-3);
  }

  color_cls = (*env)->FindClass(env, "java/awt/Color");
  if (color_cls == NULL) {
    manageException();
    exit(-3);
  }

  imageIcon_cls = (*env)->FindClass(env, "javax/swing/ImageIcon");
  if (imageIcon_cls == NULL) {
    manageException();
    exit(-3);
  }

  font_cls = (*env)->FindClass(env, "java/awt/Font");
  if (font_cls == NULL) {
    manageException();
    exit(-3);
  }

  // Méthode Contructeur de la Frame
  frame_constructor_method = (*env)->GetMethodID(env, frame_cls, "<init>", "(II)V");
  if (frame_constructor_method == NULL) {
    manageException();
    exit(-4);
  }

  // Création de la Frame
  frame = (*env)->NewObject(env, frame_cls, frame_constructor_method, width, height);
  if (frame == NULL) {
    manageException();
    exit(-5);
  }

  // Récupération du champ Panel (qui est une champ de la Frame)
  panel_field = (*env)->GetFieldID(env, frame_cls, "_pnlDraw", "LDrawPanel;");
  if (panel_field == NULL) {
    manageException();
    exit(-6);
  }

  // Récupération du Panel (l'objet)
  panel = (*env)->GetObjectField(env, frame, panel_field);
}

void sleepAWhile(long millis)
{
  static jmethodID sleep_method = NULL;
  
  // Méthode sleep du panel
  if (sleep_method == NULL) {
    sleep_method = (*env)->GetMethodID(env, panel_cls, "sleep", "(J)V");
  }

  // Appel de sleep
  (*env)->CallVoidMethod(env, panel, sleep_method, (jlong)millis);
}

void clearRect(int x, int y, int width, int height)
{
  static jmethodID clearRect_method = NULL;
  
  // Méthode clearRect du panel
  if (clearRect_method == NULL) {
    clearRect_method = (*env)->GetMethodID(env, panel_cls, "clearRect", "(IIII)V");
  }

  // Appel de clearRect
  (*env)->CallVoidMethod(env, panel, clearRect_method, (jint)x, (jint)y, (jint)width, (jint)height);
}

void drawArc(int x, int y, int width, int height, int startAngle, int arcAngle)
{
 static jmethodID drawArc_method = NULL;
  
  // Méthode drawArc du panel
  if (drawArc_method == NULL) {
    drawArc_method = (*env)->GetMethodID(env, panel_cls, "drawArc", "(IIIIII)V");
  }

  // Appel de drawArc
  (*env)->CallVoidMethod(env, panel, drawArc_method, (jint)x, (jint)y, (jint)width, (jint)height,
			 (jint)startAngle, (jint)arcAngle);
}

void drawImage(const char *filename, int x, int y)
{
  static jmethodID drawImage_method = NULL;

  jstring image_filename = (*env)->NewStringUTF(env, filename);

  // Méthode drawImage du panel
  if (drawImage_method == NULL) {
    drawImage_method = (*env)->GetMethodID(env, panel_cls, "drawImage", "(Ljava/lang/String;II)V");
  }
  // Appel de drawImage du panel
  //  (*env)->CallObjectMethod(env, panel, drawImage_method, image_obj, (jint)x, (jint)y);
  (*env)->CallObjectMethod(env, panel, drawImage_method, image_filename, (jint)x, (jint)y);
}

void drawLine(int x1, int y1, int x2, int y2)
{
  static jmethodID drawLine_method = NULL;
  
  // Méthode drawLine du panel
  if (drawLine_method == NULL) {
    drawLine_method = (*env)->GetMethodID(env, panel_cls, "drawLine", "(IIII)V");
  }

  // Appel de drawLine
  (*env)->CallVoidMethod(env, panel, drawLine_method, (jint)x1, (jint)y1, (jint)x2, (jint)y2);
}

void drawOval(int x, int y, int width, int height)
{
  static jmethodID drawOval_method = NULL;
  
  // Méthode drawOval du panel
  if (drawOval_method == NULL) {
    drawOval_method = (*env)->GetMethodID(env, panel_cls, "drawOval", "(IIII)V");
  }

  // Appel de drawOval
  (*env)->CallVoidMethod(env, panel, drawOval_method, (jint)x, (jint)y, (jint)width, (jint)height);
}

void drawPolygon(int *xPoints, int *yPoints, int nPoints)
{
  static jmethodID drawPolygon_method = NULL;
  jintArray xTab = (*env)->NewIntArray(env, (jint)nPoints);
  jintArray yTab = (*env)->NewIntArray(env, (jint)nPoints);
  int i = 0;

  // Remplissage des tableaux
  for (i = 0; i < nPoints; i++) {
    (*env)->SetIntArrayRegion(env, xTab, (jsize)i, (jsize)1, (jint *)&(xPoints[i]));
    (*env)->SetIntArrayRegion(env, yTab, (jsize)i, (jsize)1, (jint *)&(yPoints[i]));
  }

  // Methode drawPolygon du panel
  if (drawPolygon_method == NULL) {
    drawPolygon_method = (*env)->GetMethodID(env, panel_cls, "drawPolygon", "([I[II)V");
  }

  // Appel de drawPolygon
  (*env)->CallVoidMethod(env, panel, drawPolygon_method, xTab, yTab, (jint)nPoints);
}

void drawPolyline(int *xPoints, int *yPoints, int nPoints)
{
  static jmethodID drawPolyline_method = NULL;
  jintArray xTab = (*env)->NewIntArray(env, (jint)nPoints);
  jintArray yTab = (*env)->NewIntArray(env, (jint)nPoints);
  int i = 0;

  // Remplissage des tableaux
  for (i = 0; i < nPoints; i++) {
    (*env)->SetIntArrayRegion(env, xTab, (jsize)i, (jsize)1, (jint *)&(xPoints[i]));
    (*env)->SetIntArrayRegion(env, yTab, (jsize)i, (jsize)1, (jint *)&(yPoints[i]));
  }

  // Methode drawPolyline du panel
  if (drawPolyline_method == NULL) {
    drawPolyline_method = (*env)->GetMethodID(env, panel_cls, "drawPolyline", "([I[II)V");
  }

  // Appel de drawPolygon
  (*env)->CallVoidMethod(env, panel, drawPolyline_method, xTab, yTab, (jint)nPoints);
}

void drawRect(int x, int y, int width, int height) 
{
  static jmethodID drawRect_method = NULL;
  
  // Méthode drawRect du panel
  if (drawRect_method == NULL) {
    drawRect_method = (*env)->GetMethodID(env, panel_cls, "drawRect", "(IIII)V");
  }

  // Appel de drawRect
  (*env)->CallVoidMethod(env, panel, drawRect_method, (jint)x, (jint)y, (jint)width, (jint)height);
}

void draw3DRect(int x, int y, int width, int height, BOOLEAN raised)
{
  static jmethodID draw3DRect_method = NULL;
  jboolean bRaised;

  // Méthode drawRect du panel
  if (draw3DRect_method == NULL) {
    draw3DRect_method = (*env)->GetMethodID(env, panel_cls, "draw3DRect", "(IIIIZ)V");
  }

  switch (raised) {
  case TRUE:
    bRaised = JNI_TRUE;
    break;
  case FALSE:
    bRaised = JNI_FALSE;
    break;
  }

  // Appel de drawRect
  (*env)->CallVoidMethod(env, panel, draw3DRect_method, (jint)x, (jint)y, (jint)width, (jint)height, bRaised);
}

void drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight)
{
  static jmethodID drawRoundRect_method = NULL;
  
  // Méthode drawRoundRect du panel
  if (drawRoundRect_method == NULL) {
    drawRoundRect_method = (*env)->GetMethodID(env, panel_cls, "drawRoundRect", "(IIIIII)V");
  }

  // Appel de drawRect
  (*env)->CallVoidMethod(env, panel, drawRoundRect_method, (jint)x, (jint)y, (jint)width, (jint)height, 
			 (jint)arcWidth, (jint)arcHeight);
}

void drawText(const char *text, int x, int y)
{
  jmethodID drawString_method;
  jstring string = (*env)->NewStringUTF(env, text);

  drawString_method = (*env)->GetMethodID(env, panel_cls, "drawString", "(Ljava/lang/String;II)V");

  // Appel de drawString
  (*env)->CallVoidMethod(env, panel, drawString_method, string, (jint)x, (jint)y);
}

void fillArc(int x, int y, int width, int height, int startAngle, int arcAngle)
{
 static jmethodID fillArc_method = NULL;
  
  // Méthode fillArc du panel
  if (fillArc_method == NULL) {
    fillArc_method = (*env)->GetMethodID(env, panel_cls, "fillArc", "(IIIIII)V");
  }

  // Appel de fillArc
  (*env)->CallVoidMethod(env, panel, fillArc_method, (jint)x, (jint)y, (jint)width, (jint)height,
			 (jint)startAngle, (jint)arcAngle);
}

void fillOval(int x, int y, int width, int height)
{
  static jmethodID fillOval_method = NULL;
  
  // Méthode fillOval du panel
  if (fillOval_method == NULL) {
    fillOval_method = (*env)->GetMethodID(env, panel_cls, "fillOval", "(IIII)V");
  }

  // Appel de fillOval
  (*env)->CallVoidMethod(env, panel, fillOval_method, (jint)x, (jint)y, (jint)width, (jint)height);
}

void fillPolygon(int *xPoints, int *yPoints, int nPoints)
{
  static jmethodID fillPolygon_method = NULL;
  jintArray xTab = (*env)->NewIntArray(env, (jint)nPoints);
  jintArray yTab = (*env)->NewIntArray(env, (jint)nPoints);
  int i = 0;

  // Remplissage des tableaux
  for (i = 0; i < nPoints; i++) {
    (*env)->SetIntArrayRegion(env, xTab, (jsize)i, (jsize)1, (jint *)&(xPoints[i]));
    (*env)->SetIntArrayRegion(env, yTab, (jsize)i, (jsize)1, (jint *)&(yPoints[i]));
  }

  // Methode fillPolygon du panel
  if (fillPolygon_method == NULL) {
    fillPolygon_method = (*env)->GetMethodID(env, panel_cls, "fillPolygon", "([I[II)V");
  }

  // Appel de fillPolygon
  (*env)->CallVoidMethod(env, panel, fillPolygon_method, xTab, yTab, (jint)nPoints);
}

void fillRect(int x, int y, int width, int height) 
{
  static jmethodID fillRect_method = NULL;
  
  // Méthode fillRect du panel
  if (fillRect_method == NULL) {
    fillRect_method = (*env)->GetMethodID(env, panel_cls, "fillRect", "(IIII)V");
  }

  // Appel de fillRect
  (*env)->CallVoidMethod(env, panel, fillRect_method, (jint)x, (jint)y, (jint)width, (jint)height);
}

void fill3DRect(int x, int y, int width, int height, BOOLEAN raised)
{
  static jmethodID fill3DRect_method = NULL;
  jboolean bRaised;

  // Méthode fillRect du panel
  if (fill3DRect_method == NULL) {
    fill3DRect_method = (*env)->GetMethodID(env, panel_cls, "fill3DRect", "(IIIIZ)V");
  }

  switch (raised) {
  case TRUE:
    bRaised = JNI_TRUE;
    break;
  case FALSE:
    bRaised = JNI_FALSE;
    break;
  }

  // Appel de fillRect
  (*env)->CallVoidMethod(env, panel, fill3DRect_method, (jint)x, (jint)y, (jint)width, (jint)height, bRaised);
}

void fillRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight)
{
  static jmethodID fillRoundRect_method = NULL;
  
  // Méthode fillRoundRect du panel
  if (fillRoundRect_method == NULL) {
    fillRoundRect_method = (*env)->GetMethodID(env, panel_cls, "fillRoundRect", "(IIIIII)V");
  }

  // Appel de fillRect
  (*env)->CallVoidMethod(env, panel, fillRoundRect_method, (jint)x, (jint)y, (jint)width, (jint)height, 
			 (jint)arcWidth, (jint)arcHeight);
}

void setFontSize(float size)
{
  static jmethodID getFont_method = NULL;
  static jmethodID deriveFont_method = NULL;
  static jmethodID setFont_method = NULL;
  jobject font = NULL;

  // Méthode getFont du panel
  if (getFont_method == NULL) {
    getFont_method = (*env)->GetMethodID(env, panel_cls, "getGraphicsFont", "()Ljava/awt/Font;");
  }
  // Récupération de la police du panel
  font = (*env)->CallObjectMethod(env, panel, getFont_method);

  // Méthode deriveFont de Font
  if (deriveFont_method == NULL) {
    deriveFont_method = (*env)->GetMethodID(env, font_cls, "deriveFont", "(F)Ljava/awt/Font;");
  }
  // Appel à deriveFont 
  font = (*env)->CallObjectMethod(env, font, deriveFont_method, (jfloat)size);

  // Méthode setFont du panel
  if (setFont_method == NULL) {
    setFont_method = (*env)->GetMethodID(env, panel_cls, "setGraphicsFont", "(Ljava/awt/Font;)V");
  }
  // Appel à setFont
  (*env)->CallVoidMethod(env, panel, setFont_method, font);
}

void setFontStyle(STYLE style) 
{
  static jmethodID getFont_method = NULL;
  static jmethodID deriveFont_method = NULL;
  static jmethodID setFont_method = NULL;

  static jfieldID ITALIC_field = NULL;
  static jfieldID BOLD_field = NULL;
  static jfieldID PLAIN_field = NULL;

  jobject font = NULL;
  jint jstyle = -1;

  // Méthode getFont du panel
  if (getFont_method == NULL) {
    getFont_method = (*env)->GetMethodID(env, panel_cls, "getGraphicsFont", "()Ljava/awt/Font;");
  }
  // Récupération de la police du panel
  font = (*env)->CallObjectMethod(env, panel, getFont_method);

  // Méthode deriveFont de Font
  if (deriveFont_method == NULL) {
    deriveFont_method = (*env)->GetMethodID(env, font_cls, "deriveFont", "(I)Ljava/awt/Font;");
  }

  // Champs BOLD, ITALIC et PLAIN de FonT
  if (ITALIC_field == NULL) {
    ITALIC_field = (*env)->GetStaticFieldID(env, font_cls, "ITALIC", "I");
    BOLD_field = (*env)->GetStaticFieldID(env, font_cls, "BOLD", "I");
    PLAIN_field = (*env)->GetStaticFieldID(env, font_cls, "PLAIN", "I");
  }
  // Récupération de la valeur du style
  switch (style) {
  case BOLD:
    jstyle = (*env)->GetStaticIntField(env, font_cls, BOLD_field);
    break;
  case ITALIC:
    jstyle = (*env)->GetStaticIntField(env, font_cls, ITALIC_field);
    break;
  case PLAIN:
    jstyle = (*env)->GetStaticIntField(env, font_cls, PLAIN_field);
  }
    
  // Appel à deriveFont 
  font = (*env)->CallObjectMethod(env, font, deriveFont_method, style);

  // Méthode setFont du panel
  if (setFont_method == NULL) {
    setFont_method = (*env)->GetMethodID(env, panel_cls, "setGraphicsFont", "(Ljava/awt/Font;)V");
  }
  // Appel à setFont
  (*env)->CallVoidMethod(env, panel, setFont_method, font);
}


static jobject getColorObject(COLOR color)
{
  jobject color_obj;
  jfieldID color_field;

  switch (color) {
  case BLACK:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "BLACK", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case RED:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "RED", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case BLUE:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "BLUE", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case GREEN:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "GREEN", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case YELLOW:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "YELLOW", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case CYAN:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "CYAN", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case GRAY:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "GRAY", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case MAGENTA:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "MAGENTA", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case ORANGE:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "ORANGE", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case PINK:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "PINK", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
    break;
  case WHITE:
  default:
    color_field = (*env)->GetStaticFieldID(env, color_cls, "WHITE", "Ljava/awt/Color;");
    color_obj = (*env)->GetStaticObjectField(env, color_cls, color_field);
  }
  return color_obj;
}


void setForegroundColor(COLOR color)
{
  static jmethodID setColor_method = NULL;
  jobject color_obj;

  // Méthode setColor du panel
  if (setColor_method == NULL) {
    setColor_method = (*env)->GetMethodID(env, panel_cls, "setForegroundColor", "(Ljava/awt/Color;)V");
  }
  color_obj = getColorObject(color);
  // Appel de setColor
  (*env)->CallVoidMethod(env, panel, setColor_method, color_obj);
}

void setBackgroundColor(COLOR color)
{
  static jmethodID setBackground_method = NULL;
  jobject color_obj;

  // Méthode setBackground du panel
  if (setBackground_method == NULL) {
    setBackground_method = (*env)->GetMethodID(env, panel_cls, "setBackgroundColor", "(Ljava/awt/Color;)V");
  }
  color_obj = getColorObject(color);
  // Appel de setBackground
  (*env)->CallVoidMethod(env, panel, setBackground_method, color_obj);
}

void setClip(int x, int y, int width, int height)
{
  static jmethodID setClip_method = NULL;
  
  // Méthode setClip du panel
  if (setClip_method == NULL) {
    setClip_method = (*env)->GetMethodID(env, panel_cls, "setClip", "(IIII)V");
  }

  // Appel de setClip
  (*env)->CallVoidMethod(env, panel, setClip_method, (jint)x, (jint)y, (jint)width, (jint)height);
}

void addClip(int x, int y, int width, int height)
{
  static jmethodID addClip_method = NULL;
  
  // Méthode addClip du panel
  if (addClip_method == NULL) {
    addClip_method = (*env)->GetMethodID(env, panel_cls, "addClip", "(IIII)V");
  }

  // Appel de addClip
  (*env)->CallVoidMethod(env, panel, addClip_method, (jint)x, (jint)y, (jint)width, (jint)height);
}

void paint()
{
  static jmethodID repaint_method = NULL;

  // Méthode repaint du panel
  if (repaint_method == NULL) {
    repaint_method = (*env)->GetMethodID(env, panel_cls, "repaint", "()V");
  }

  (*env)->CallVoidMethod(env, panel, repaint_method);
}

void finish()
{
#ifdef WIN32
  _sleep(-1);
#else
  usleep(-1);
#endif
}

void registerKeyPressed(int key)
{
  static jmethodID registerKeyPressedToReleased_method = NULL;

  // Méthode registerKeyPressedToReleased de la frame
  if (registerKeyPressedToReleased_method == NULL) {
    registerKeyPressedToReleased_method = (*env)->GetMethodID(env, 
							      frame_cls, 
							      "registerKeyPressedToReleased", "(I)V");
  }

  (*env)->CallVoidMethod(env, frame, registerKeyPressedToReleased_method, (jint)key);

}

int getLastKeyPressed()
{
  static jmethodID getLastKeyPressed_method = NULL;

  // Méthode getLastKeyPressed de la frame
  if (getLastKeyPressed_method == NULL) {
    getLastKeyPressed_method = (*env)->GetMethodID(env, frame_cls, "getLastKeyPressed", "()I");
  }

  return (int)(*env)->CallIntMethod(env, frame, getLastKeyPressed_method);
}

void registerSound(char *filename)
{
  static jmethodID registerSound_method = NULL;
  jstring wavFilename = (*env)->NewStringUTF(env, filename);
  // Méthode getLastKeyPressed de la frame
  if (registerSound_method == NULL) {
    registerSound_method = (*env)->GetMethodID(env, frame_cls, "registerSound", "(Ljava/lang/String;)V");
  }

  (*env)->CallVoidMethod(env, frame, registerSound_method, wavFilename);
}


void playSound(char *filename)
{
  static jmethodID playSound_method = NULL;
  jstring wavFilename = (*env)->NewStringUTF(env, filename);
  // Méthode getLastKeyPressed de la frame
  if (playSound_method == NULL) {
    playSound_method = (*env)->GetMethodID(env, frame_cls, "playSound", "(Ljava/lang/String;)V");
  }

  (*env)->CallVoidMethod(env, frame, playSound_method, wavFilename);
}
