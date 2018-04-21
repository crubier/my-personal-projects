/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.IHM;
import java.awt.Container;

import java.awt.image.BufferedImage;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;


public class AffichageImage extends JFrame {
    
    public AffichageImage(String titre, BufferedImage image) {
        super(titre);

		// on change l'icone

		super.setIconImage(image);
		
        Container c = this.getContentPane();
        c.add(new JLabel(new ImageIcon(image)));

		this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE); ///ATTENTION
		this.setResizable(false);
        this.pack();
        this.setVisible(true);
    }
	
	

}
