import java.applet.Applet;
import java.applet.AudioClip;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.net.URL;
import java.util.HashMap;

import javax.swing.AbstractAction;
import javax.swing.InputMap;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.KeyStroke;

public class MainFrame extends JDialog 
{
  private JPanel _pnlContent = null;
  private DrawPanel _pnlDraw = new DrawPanel();
  
  private int _lastKeyPressed = -1;
  private boolean _maintainPressedActivated = false;
  private HashMap _soundMap = new HashMap();
  
  public MainFrame(int width, int height) {
    this._pnlContent = (JPanel)this.getContentPane();
    this._pnlContent.setLayout(new BorderLayout());
    this._pnlContent.setPreferredSize(new Dimension(width, height));
    this.setResizable(false);
    
    this._pnlContent.add(this._pnlDraw, BorderLayout.CENTER);

    this.addWindowListener(new WindowAdapter() {
      /** 
       * @see java.awt.event.WindowAdapter#windowClosing(java.awt.event.WindowEvent)
       */
      public void windowClosing(WindowEvent e) {
        super.windowClosing(e);
        System.exit(0);
      }
    });
    // Il en faut une à l'initialisation pour que registerKey puisse être appelé
    // n'importe quand ensuite
    registerKeyPressed(KeyEvent.VK_ESCAPE);
    
    this.pack();
    this._pnlDraw.init(width, height);
    this.setLocationRelativeTo(null);
    this.setVisible(true);
  }
  
  public void registerKeyPressed(final int key)
  {
    String keyName = KeyEvent.getKeyText(key);
    InputMap inputMap = this.getRootPane().getInputMap(JComponent.WHEN_FOCUSED);
    inputMap.put(KeyStroke.getKeyStroke(key, 0), keyName);
    this.getRootPane().getActionMap().put(keyName, new AbstractAction(keyName) {
      public void actionPerformed(ActionEvent e) {
    	if (key == KeyEvent.VK_ESCAPE) {
    	  System.exit(0);
    	}
        setKeyPressed(key, false);
      }
    });
  }

  public void registerKeyPressedToReleased(final int key)
  {
    String keyNamePressed = KeyEvent.getKeyText(key) + " pressed";
    InputMap inputMap = this.getRootPane().getInputMap(JComponent.WHEN_FOCUSED);
    inputMap.put(KeyStroke.getKeyStroke(key, 0, false), keyNamePressed);
    this.getRootPane().getActionMap().put(keyNamePressed, new AbstractAction(keyNamePressed) {
      public void actionPerformed(ActionEvent e) {
        setKeyPressed(key, true);
      }
    });
    
    String keyNameReleased = KeyEvent.getKeyText(key) + " released";
    inputMap = this.getRootPane().getInputMap(JComponent.WHEN_FOCUSED);
    inputMap.put(KeyStroke.getKeyStroke(key, 0, true), keyNameReleased);
    this.getRootPane().getActionMap().put(keyNameReleased, new AbstractAction(keyNameReleased) {
      public void actionPerformed(ActionEvent e) {
        setKeyPressed(-1, false);
      }
    });

  }

  
  synchronized private void setKeyPressed(int key, boolean maintainPressedActivated) {
    this._lastKeyPressed = key;
    this._maintainPressedActivated = maintainPressedActivated;
  }
  
  synchronized public int getLastKeyPressed() {
    int lastKeyPressed = this._lastKeyPressed;
    if (!this._maintainPressedActivated) {
      this._lastKeyPressed = -1;
    }
    return lastKeyPressed;
  }
  
  public synchronized void registerSound(String filename) {
    if (!_soundMap.containsKey(filename)) {
      // Vérification de la présence du fichier son
      URL url = ClassLoader.getSystemResource(filename);
      if (url == null) {
        System.out.println("ERREUR : fichier " + filename + " introuvable !");
        return;
      }
      File file = new File(url.getFile());
      if (!file.exists()) {
        System.out.println("ERREUR : fichier " + file + " introuvable !");
        return;
      }
      // ajout dans la map des sons
      _soundMap.put(filename, Applet.newAudioClip(url));
    }
  }
  
//  private static final AudioClip _sonRaquetteAC = Applet.newAudioClip(ClassLoader.getSystemResource("sons/raquette.wav"));
  
  public void playSound(final String filename) {
    Thread thread = new Thread(new Runnable() {
      public void run() {
        if (!_soundMap.containsKey(filename)) {
          System.out.println("ERREUR : le fichier son n'a pas été préalablement enregistré avec la méthode registerSound");
          return;
        }
        ((AudioClip)_soundMap.get(filename)).play();
      }
    });
    thread.start();
  }
  
  public static void main(String[] args) {
    final MainFrame frame = new MainFrame(600, 600);
    frame._pnlDraw.setBackground(Color.BLACK);
    frame._pnlDraw.fillArc(300, 300, 50, 50, 45, 90);
    frame._pnlDraw.clearRect(300, 300, 50, 50);
    frame.repaint();
    frame._pnlDraw.setClip(300, 300, 50, 50);
    int P = 5;
    for (int i = 300; i < 500; i += P) {
      frame._pnlDraw.sleep(100);
      frame._pnlDraw.addClip(i - P, i - P, 50, 50);
      frame._pnlDraw.clearRect(i - P, i - P, 50, 50);
      frame._pnlDraw.addClip(i, i, 50, 50);
      frame._pnlDraw.fillArc(i, i, 50, 50, 45, 90);
      frame._pnlDraw.repaint();
      frame._pnlDraw.setClip(i, i, 50, 50); 
    }
  }
}
