import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Paint;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.Stroke;
import java.util.HashMap;

import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class DrawPanel extends JPanel
{
  private Image _img = null;
  private Graphics2D _g = null;
  
  private static HashMap _imgMap = new HashMap();
  
  public DrawPanel() {
  }
  
  public void init(int width, int height) {
    this._img = this.createImage(width, height);
    this._g = (Graphics2D)this._img.getGraphics();
    _g.setBackground(Color.BLACK);
    _g.setColor(Color.WHITE);
    _g.clearRect(0, 0, width, height);
    
    _g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_OFF);
    _g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);
    /** Demande de rendu rapide */
    _g.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_SPEED);
    _g.setRenderingHint(RenderingHints.KEY_COLOR_RENDERING, RenderingHints.VALUE_COLOR_RENDER_SPEED);
    _g.setRenderingHint(RenderingHints.KEY_FRACTIONALMETRICS, RenderingHints.VALUE_FRACTIONALMETRICS_OFF);
    _g.setRenderingHint(RenderingHints.KEY_DITHERING, RenderingHints.VALUE_DITHER_DISABLE);
    
    this.repaint();
  }

  /** 
   * @see javax.swing.JComponent#paint(java.awt.Graphics)
   */
  public void paint(Graphics g) {
    if (_img != null) {
      g.drawImage(_img, 0, 0, null);
    }
  }
  
  /** 
   * @see java.awt.Component#repaint()
   */
  public void repaint() {
    super.repaint();
  }
  
  public void sleep(long millis) {
    try {
      Thread.sleep(millis);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
  
  ///////////////////////////////////////////
  // DELEGATION DES METHODES POUR DESSINER //
  ///////////////////////////////////////////
  public void clearRect(int x, int y, int width, int height) {
    _g.clearRect(x, y, width, height);
  }
  public void drawArc(int x, int y, int width, int height, int startAngle,
                      int arcAngle) {
    _g.drawArc(x, y, width - 1, height - 1, startAngle, arcAngle);
  }
  public void drawLine(int x1, int y1, int x2, int y2) {
    _g.drawLine(x1, y1, x2, y2);
  }
  public void drawOval(int x, int y, int width, int height) {
    _g.drawOval(x, y, width - 1, height - 1);
  }
  public void drawPolygon(int[] xPoints, int[] yPoints, int nPoints) {
    _g.drawPolygon(xPoints, yPoints, nPoints);
  }
  public void drawPolyline(int[] xPoints, int[] yPoints, int nPoints) {
    _g.drawPolyline(xPoints, yPoints, nPoints);
  }
  public void drawRect(int x, int y, int width, int height) {
    _g.drawRect(x, y, width - 1, height - 1);
  }
  public void draw3DRect(int x, int y, int width, int height, boolean raised) {
    _g.draw3DRect(x, y, width - 1, height - 1, raised);
  }
  public void drawRoundRect(int x, int y, int width, int height, int arcWidth,
                            int arcHeight) {
    _g.drawRoundRect(x, y, width - 1, height - 1, arcWidth, arcHeight);
  }
  public void drawString(String str, int x, int y) {
    _g.drawString(str, x, y);
  }
  public void fill3DRect(int x, int y, int width, int height, boolean raised) {
    _g.fill3DRect(x, y, width, height, raised);
  }
  public void fillArc(int x, int y, int width, int height, int startAngle,
                      int arcAngle) {
    _g.fillArc(x, y, width, height, startAngle, arcAngle);
  }
  public void fillOval(int x, int y, int width, int height) {
    _g.fillOval(x, y, width, height);
  }
  public void fillPolygon(int[] xPoints, int[] yPoints, int nPoints) {
    _g.fillPolygon(xPoints, yPoints, nPoints);
  }
  public void fillRect(int x, int y, int width, int height) {
    _g.fillRect(x, y, width, height);
  }
  public void fillRoundRect(int x, int y, int width, int height, int arcWidth,
                            int arcHeight) {
    _g.fillRoundRect(x, y, width, height, arcWidth, arcHeight);
  }
  public void setForegroundColor(Color c) {
    _g.setColor(c);
  }
  public void setBackgroundColor(Color c) {
    _g.setBackground(c);
  }
  
  public void drawImage(String filename, int x, int y) {
    if (!_imgMap.containsKey(filename)) {
      _imgMap.put(filename, new ImageIcon(filename).getImage());
    }
    _g.drawImage((Image)_imgMap.get(filename), x, y, null);
  }
  
  public void drawImage(Image img, int x, int y) {
    _g.drawImage(img, x, y, null);
  }
  public void setPaint(Paint paint) {
    _g.setPaint(paint);
  }
  public void setStroke(Stroke s) {
    _g.setStroke(s);
  }
  
  public Font getGraphicsFont() {
    return _g.getFont();
  }
  
  public void setGraphicsFont(Font font) {
    _g.setFont(font);
  }
  
  public void setClip(int x, int y, int width, int height) {
    _g.setClip(x, y, width, height);
  }
  
  public void addClip(int x, int y, int width, int height) {
    Rectangle rect = _g.getClipBounds();
    if (rect == null) {
      rect = new Rectangle(x, y, width, height);
    } else {
      rect = SwingUtilities.computeUnion(x, y, width, height, rect);
    }
    _g.setClip(rect);
    rect = _g.getClipBounds();
  }
}
