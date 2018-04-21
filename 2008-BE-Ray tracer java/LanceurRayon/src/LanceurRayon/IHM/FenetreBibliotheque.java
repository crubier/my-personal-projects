/*
 * FenetreBibliotheque.java
 *
 * Created on 30 mars 2008, 17:07
 */

package LanceurRayon.IHM;

import LanceurRayon.IHM.Arbre.ArbreXMLModel;
import LanceurRayon.IHM.Arbre.ArbreXMLNode;
import LanceurRayon.LanceurRayonApp;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileView;

/**
 *
 * @author  Lecrubier
 */
public class FenetreBibliotheque extends javax.swing.JFrame {
	private String nomDossier;
	ArbreXMLModel objetChoisi;
	JFrame appli;
	
	/** Creates new form FenetreBibliotheque
	 * @param aThis 
	 */
	public FenetreBibliotheque(JFrame aThis) {
		initComponents();
		this.appli = aThis;

		this.setDefaultCloseOperation(HIDE_ON_CLOSE);
		this.nomDossier = System.getProperty("user.dir") + "\\Bibliotheque";
		this.jFileChooser1.setMultiSelectionEnabled(false);
		FileFilter filtre = new FileFilter() {

			@Override
			public boolean accept(File f) {
				return f.canRead() && f.getPath().startsWith(nomDossier) && (f.isDirectory() || (f.isFile() && f.getName().endsWith(".xml")));
			}

			@Override
			public String getDescription() {
				return "Fichiers XML (*.xml)";
			}
		};
				
		jFileChooser1.setAcceptAllFileFilterUsed(false);
		jFileChooser1.setCurrentDirectory(new File(nomDossier));
		jFileChooser1.setFileFilter(filtre);
		jFileChooser1.setControlButtonsAreShown(true);
		jTextPane1.setEditable(false);
		objetChoisi = null;
		
				this.setVisible(false);
		
	}

	public FenetreBibliotheque() {
		throw new UnsupportedOperationException("Not yet implemented");
	}
	
	/** This method is called from within the constructor to
	 * initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is
	 * always regenerated by the Form Editor.
	 */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jSplitPane1 = new javax.swing.JSplitPane();
        jFileChooser1 = new javax.swing.JFileChooser();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTextPane1 = new javax.swing.JTextPane();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setName("Form"); // NOI18N

        jPanel1.setName("jPanel1"); // NOI18N

        jSplitPane1.setName("jSplitPane1"); // NOI18N

        jFileChooser1.setName("jFileChooser1"); // NOI18N
        jFileChooser1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jFileChooser1ActionPerformed(evt);
            }
        });
        jFileChooser1.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                jFileChooser1PropertyChange(evt);
            }
        });
        jSplitPane1.setLeftComponent(jFileChooser1);

        jScrollPane1.setName("jScrollPane1"); // NOI18N

        jTextPane1.setName("jTextPane1"); // NOI18N
        jScrollPane1.setViewportView(jTextPane1);

        jSplitPane1.setRightComponent(jScrollPane1);

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSplitPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 964, Short.MAX_VALUE)
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSplitPane1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 581, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

	private void jFileChooser1PropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_jFileChooser1PropertyChange
		if(jFileChooser1.getSelectedFile()!=null) {
			try {
				if(this.jFileChooser1.getSelectedFile().getPath().endsWith(".xml")) {
					this.jTextPane1.setPage("file:///"+this.jFileChooser1.getSelectedFile().getPath()+".html");
				}
			} catch (IOException ex) {
				Logger.getLogger(FenetreBibliotheque.class.getName()).log(Level.SEVERE, null, ex);
			}
		}
	}//GEN-LAST:event_jFileChooser1PropertyChange

	private void jFileChooser1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jFileChooser1ActionPerformed
		System.out.println(evt.getActionCommand());
		if(evt.getActionCommand().compareTo("ApproveSelection")==0) {
			ArbreXMLModel res = new ArbreXMLModel();
			res.ouvrir(jFileChooser1.getSelectedFile());
			objetChoisi =  res;
			appli.notify();
		}
		else {
			objetChoisi = null;
		}
	}//GEN-LAST:event_jFileChooser1ActionPerformed
	
	public ArbreXMLModel objetChoisi(){
		this.setVisible(true);
		try {
			appli.wait();
		} catch (InterruptedException ex) {
			Logger.getLogger(FenetreBibliotheque.class.getName()).log(Level.SEVERE, null, ex);
		}
		this.setVisible(false);

		return objetChoisi;

	}

	
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JFileChooser jFileChooser1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JSplitPane jSplitPane1;
    private javax.swing.JTextPane jTextPane1;
    // End of variables declaration//GEN-END:variables
	
}
