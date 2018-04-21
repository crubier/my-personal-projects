/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.IHM;

import LanceurRayon.LanceurRayonApp;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.Date;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.LogRecord;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

/**
 *
 * @author Lecrubier
 */
public class HandlerExceptions extends Handler{
	
	private FenetreJournal journal ;
	private FenetrePrincipale fenetre;
	private PrintWriter bob;
	private StringWriter joe;
	
	public void afficherJournal() {
		this.journal.setVisible(true);
	}
	
	public HandlerExceptions(FenetrePrincipale fenetre) {
		this.fenetre = fenetre;
		this.journal = new FenetreJournal("Journal");
		joe = new StringWriter();
		bob = new PrintWriter(joe);
		publish(new LogRecord(Level.INFO, "Debut de journal"));
	}

	@Override
	public void publish(LogRecord record) {
		Date date = new Date(System.currentTimeMillis());
		bob.print(date.toString()+ " : " + record.getLevel().toString() + " : ");
		
		if(record.getMessage()!=null) {
			bob.println(record.getMessage());
			fenetre.setEtat(record.getMessage());
		}
		if(record.getThrown()!=null) {
			ImageIcon a = new ImageIcon(LanceurRayonApp.getInstance(LanceurRayon.LanceurRayonApp.class).getContext().getResourceMap(LanceurRayonApp.class).getImageIcon("Erreur.icon").getImage());
			JOptionPane.showMessageDialog(null, new JLabel(record.getThrown().getMessage()), "Erreur", JOptionPane.ERROR_MESSAGE, a);
			bob.println(record.getThrown().getMessage());
		}
		refreshJournal();
	}

	@Override
	public void flush() {
	}

	@Override
	public void close() throws SecurityException {
	}
	
	public void refreshJournal() {
		journal.setText(this.getText());
	}
	
	public String getText() {
		return joe.toString();
	}

}
