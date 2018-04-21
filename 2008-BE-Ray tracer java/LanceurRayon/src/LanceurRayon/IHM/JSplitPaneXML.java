/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package LanceurRayon.IHM;

import LanceurRayon.IHM.Annulation.UndoableEditXML;
import LanceurRayon.IHM.Arbre.JTreeXML;
import LanceurRayon.IHM.Arbre.ArbreXMLModel;
import java.awt.Dimension;
import java.io.File;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JEditorPane;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.ScrollPaneConstants;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.TreePath;
import org.bounce.text.xml.XMLEditorKit;
import javax.swing.undo.UndoManager;
import javax.swing.undo.UndoableEditSupport;


public class JSplitPaneXML extends JSplitPane {

	private JScrollPane PaneSepareGauche;
	private JTreeXML EditeurArbre ;
	private JScrollPane PaneSepareDroit;
	private JEditorPane EditeurTexte;
	private UndoableEditSupport support ;
	private UndoManager manager;
	private FenetrePrincipale fenetre;
	private File fichier;
	

	public JSplitPaneXML(FenetrePrincipale fen, ArbreXMLModel arbre, File fichierAOuvrir) {
		this.fenetre=fen;
		this.fichier=fichierAOuvrir;
		
		PaneSepareGauche = new JScrollPane();
		EditeurArbre = new JTreeXML(arbre,this);
		PaneSepareDroit = new JScrollPane();
		EditeurTexte = new JEditorPane();
		this.setName("PaneSepare"); // NOI18N

		PaneSepareGauche.setName("PaneSepareGauche"); // NOI18N

		PaneSepareGauche.setPreferredSize(new Dimension(400, 100));
		EditeurArbre.setName("EditeurArbre"); // NOI18N
		PaneSepareGauche.setViewportView(EditeurArbre);

		this.setLeftComponent(PaneSepareGauche);

		PaneSepareDroit.setName("PaneSepareDroit");
		PaneSepareDroit.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);

		EditeurTexte.setName("EditeurTexte");
		EditeurTexte.setContentType("text/xml");
		EditeurTexte.setEditorKit(new XMLEditorKit());
//		EditeurTexte.setEditorKit(new HTMLEditorKit());
		PaneSepareDroit.setViewportView(EditeurTexte);

		this.setRightComponent(PaneSepareDroit);

		EditeurArbre.addTreeSelectionListener(
			new TreeSelectionListener() {

				public void valueChanged(TreeSelectionEvent e) {
//					System.out.println(e.getPath().getPathCount());

				}
			});
			
		support = new UndoableEditSupport(this);
		manager = new UndoManager();
		support.addUndoableEditListener(manager);
  
		EditeurTexte.setEditable(false);
		
		support.beginUpdate();
		support.postEdit( new UndoableEditXML(this,  this.getEditeurArbre().getModel(),  this.getEditeurArbre().getModel(), "Creation") );
		support.endUpdate();
		
		this.synchroniserFichier();
		this.refresh();
	}

	public void copy() {
		throw new UnsupportedOperationException("Not yet implemented");
	}

	public void cut() {
		throw new UnsupportedOperationException("Not yet implemented");
	}

	public ArbreXMLModel getArbre() {
		return EditeurArbre.getModel();
	}

	public void paste() {
		throw new UnsupportedOperationException("Not yet implemented");
	}

	public void setArbre(ArbreXMLModel doc) {
		EditeurArbre.setModel(doc);
		this.refresh();
	}
	
	public void ajouter(ArbreXMLModel element) {
		ArbreXMLModel avant = this.getEditeurArbre().getModel();
		this.getEditeurArbre().add(element);
		ArbreXMLModel apres = this.getEditeurArbre().getModel();
		support.beginUpdate();
		support.postEdit( new UndoableEditXML(this,  avant,  apres , "Ajout " + this.getEditeurArbre().getSelectionPath().toString()) );
		support.endUpdate();
		Logger.getLogger("Journal").log(Level.INFO,"Ajout effectué");
		this.refresh();
	}
	
	public void remplacer(ArbreXMLModel element) {
		ArbreXMLModel avant = this.getEditeurArbre().getModel();
		this.getEditeurArbre().replace(element);
		ArbreXMLModel apres = this.getEditeurArbre().getModel();
		support.beginUpdate();
		support.postEdit( new UndoableEditXML(this,  avant,  apres , "Remplacement " + this.getEditeurArbre().getSelectionPath().toString()) );
		support.endUpdate();
		Logger.getLogger("Journal").log(Level.INFO,"Remplacement effectué");
		this.refresh();
	}
	
	public void supprimer() {
		ArbreXMLModel avant = this.getEditeurArbre().getModel();
		this.getEditeurArbre().remove();		
		ArbreXMLModel apres = this.getEditeurArbre().getModel();
		support.beginUpdate();
		support.postEdit( new UndoableEditXML(this,  avant,  apres , "Suppression " + this.getEditeurArbre().getSelectionPath().toString()) );
		support.endUpdate();
		Logger.getLogger("Journal").log(Level.INFO,"Suppression effectuée");
		this.refresh();
	}
	
	public void refreshEditeurArbre() {
		getEditeurArbre().getModel().fromString(getEditeurTexte().getText());
		getEditeurArbre().updateUI();
	}
	
	public void refreshEditeurTexte() {
		getEditeurTexte().setText(getEditeurArbre().getModel().toString());
		getEditeurTexte().updateUI();
	}
	
	public void refresh() {

		getEditeurTexte().setText(this.getArbre().toString());
		TreePath temp = getEditeurArbre().getSelectionPath();
//		TreePath[] temp = getEditeurArbre().getSelectionPaths();
		getEditeurArbre().updateUI();
//		getEditeurArbre().setSelectionPaths(temp);
		getEditeurArbre().setSelectionPath(temp);

		getEditeurArbre().update(getEditeurArbre().getGraphics());
		getEditeurTexte().updateUI();


	}

	public void synchroniserFichier() {
		if(fichier!=null ) {
			this.getArbre().ouvrir(fichier);
			Logger.getLogger("Journal").log(Level.INFO,fichier.getPath()+ " synchronisé");
		}
	}
	
	public JTreeXML getEditeurArbre() {
		return EditeurArbre;
	}

	public JEditorPane getEditeurTexte() {
		return EditeurTexte;
	}

	public File getFichier() {
		return fichier;
	}

	public void setFichier(File fichier) {
		this.fichier = fichier;
		this.synchroniserFichier();
		this.refresh();
	}
	
	public void undo() {
		if(manager.canUndo()) {
			manager.undo();
			
			Logger.getLogger("Journal").log(Level.INFO, manager.getUndoPresentationName());
		} 
		else {
			Logger.getLogger("Journal").log(Level.WARNING, null, new Exception(manager.getUndoPresentationName()));
		}
	}
	
	public void redo() {
		if(manager.canRedo()) {
			manager.redo();
			Logger.getLogger("Journal").log(Level.INFO, manager.getRedoPresentationName());
		}
		else {
			Logger.getLogger("Journal").log(Level.WARNING, null, new Exception(manager.getRedoPresentationName()));
		}
	}

}
