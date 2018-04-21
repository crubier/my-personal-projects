/*
 * LanceurRayonApp.java
 */

package LanceurRayon;

import LanceurRayon.IHM.*;
import LanceurRayon.Physique.Couleur;
import LanceurRayon.Scene.Scene;
import LanceurRayon.IHM.Arbre.ArbreXMLModel;
import LanceurRayon.Physique.Materiau;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.Image;
import LanceurRayon.Util.Liste;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.URL;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JColorChooser;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JTextPane;
import javax.swing.filechooser.FileFilter;
import org.jdesktop.application.Action;
import org.jdesktop.application.Application;
import org.jdesktop.application.SingleFrameApplication;
import org.jdesktop.application.Task;
import org.jdom.Document;
import org.jdom.Element;

/**
 * The main class of the application.
 */
public class LanceurRayonApp extends SingleFrameApplication {
	private FenetrePrincipale fenetre;
	private FenetreBibliotheque bibli;
	private HandlerExceptions handler;
	private Liste<String> arguments;

	public FenetrePrincipale getFenetre() {

		return fenetre;
	}

	@Override
	protected void initialize(String[] arg0) {
		super.initialize(arg0);
		arguments = new Liste<String>();
		for(int i = 0;i<arg0.length;i++ ) {
			arguments.add(arg0[i]);
		}
	}
		
		

	/**
     * At startup create and show the main frame of the application.
     */
    @Override protected void startup() {
		try {
			fenetre = new FenetrePrincipale();
			
			show(fenetre);
			
			fenetre.setIconImage(
				LanceurRayonApp.getInstance(LanceurRayon.LanceurRayonApp.class).getContext().getResourceMap(LanceurRayonApp.class).getImageIcon("Application.icon").getImage()
				 );
			handler = new HandlerExceptions(fenetre);
//			bibli = new FenetreBibliotheque(fenetre);
			Logger.getLogger("Journal").addHandler(handler);
					
		} catch (Exception ex) {
			Logger.getLogger(LanceurRayonApp.class.getName()).log(Level.SEVERE, null, ex);
		}
		
	}

    /**
     * This method is to initialize the specified window by injecting resources.
     * Windows shown in our application come fully initialized from the GUI
     * builder, so this additional configuration is not needed.
	 * @param root 
	 */
    @Override protected void configureWindow(java.awt.Window root) {
    }

	@Override
	protected void ready() {
		super.ready();
		for(String arg : arguments ) {
			if(arg!=null){
				File fileTemp = new File(arg);
				ArbreXMLModel arbreTemp = new ArbreXMLModel();
				arbreTemp.ouvrir(fileTemp);
				this.addDocument(arbreTemp, fileTemp);
			}
		}
	}

	public ArbreXMLModel getDocumentActuel() {
		if(this.getFenetre()!=null) {
			if(this.getFenetre().getEditeur() != null) {
				return this.getFenetre().getEditeur().getArbre();
			}
			else {
				Logger.getLogger("Journal").log(Level.INFO,"Document vide !");
				return null;
			}
		}
		else {
			Logger.getLogger("Journal").log(Level.INFO,"Aucune fenetre !");
			return null;
		}

	}

	public void addDocument(ArbreXMLModel documentActuel,File fichier) {
		fenetre.addProjet(documentActuel,fichier);
	}
	
	 /**
     * A convenient static getter for the application instance.
     * @return the instance of LanceurRayonApp
     */
    public static LanceurRayonApp getApplication() {
        return Application.getInstance(LanceurRayonApp.class);
    }

    /**
     * Main method launching the application.
	 * @param args 
	 */
    public static void main(String[] args) {
		launch(LanceurRayonApp.class, args);
    }

	@Action
	public void ouvrir()  {
		JFileChooser chooser = new JFileChooser();
		
		FileFilter filtre = new FileFilter() {

			@Override
			public boolean accept(File f) {
				return f.canRead() && (f.isDirectory() || (f.isFile() && f.getName().endsWith(".xml")));
			}

			@Override
			public String getDescription() {
				return "Fichiers XML (*.xml)";
			}
		};
				
		chooser.setAcceptAllFileFilterUsed(false);
		chooser.setFileFilter(filtre);
		
		int returnVal = chooser.showOpenDialog(fenetre);
	
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			String nomFichier = chooser.getSelectedFile().getPath();
			ArbreXMLModel doc = new ArbreXMLModel();
			doc.ouvrir(chooser.getSelectedFile());
			this.addDocument(doc,chooser.getSelectedFile());
			Logger.getLogger("Journal").log(Level.INFO,nomFichier+ " ouvert");
		}
		else {
			if(chooser.getSelectedFile()!=null) {
				String nomFichier = chooser.getSelectedFile().getPath();
				Logger.getLogger("Journal").log(Level.SEVERE,null,new Exception("Impossible d'ouvrir " + nomFichier));
			}
		}
		
	}

	@Action
	public void enregistrer() {
		enregistrerSous();
	}

	@Action
	public void enregistrerSous() {
		JFileChooser chooser = new JFileChooser();
		
		FileFilter filtre = new FileFilter() {

			@Override
			public boolean accept(File f) {
				return f.canRead() && (f.isDirectory() || (f.isFile() && f.getName().endsWith(".xml")));
			}

			@Override
			public String getDescription() {
				return "Fichiers XML (*.xml)";
			}
		};
				
		chooser.setAcceptAllFileFilterUsed(false);
		chooser.setFileFilter(filtre);
		
		int returnVal = chooser.showSaveDialog(fenetre);
	
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			String nomFichier = chooser.getSelectedFile().getPath();
			if( ! nomFichier.endsWith(".xml")) {
				nomFichier = nomFichier.concat(".xml");
			}
			ArbreXMLModel doc = this.getDocumentActuel();
			if(doc != null) {
				doc.enregistrer(nomFichier);
				Logger.getLogger("Journal").log(Level.INFO,nomFichier+ " enregistré");
			}
			else {
				Logger.getLogger("Journal").log(Level.INFO,"Document vide !");
			}
		}
		else {
			if(chooser.getSelectedFile()!=null) {
				String nomFichier = chooser.getSelectedFile().getPath();
				Logger.getLogger("Journal").log(Level.SEVERE,null,new Exception("Impossible d'enregistrer " + nomFichier));
			}
		}
	}

	@Action
	public void couper() {
		fenetre.getEditeur().cut();
	}


	@Action
	public void copier() {
		fenetre.getEditeur().copy();
	}

	@Action
	public void coller() {
		fenetre.getEditeur().paste();
	}

	@Action
	public void nouveau() {	
		this.addDocument(new ArbreXMLModel(new Scene().toJdom("","Principale")),null);
	}

	@Action
	public void annuler() {
		this.fenetre.getEditeur().undo();
	}

	@Action
	public void restaurer() {
		this.fenetre.getEditeur().redo();
	}

	@Action
	public void supprimer() {
		this.fenetre.getEditeur().supprimer();
	}

	@Action
	public void aide() {
	}

	@Action
	public void aPropos() {
		FenetreAPropos a = new FenetreAPropos();
		show(a);
	}
	
	@Action
	public void selecteurCouleur() {
		Color selection = JColorChooser.showDialog(fenetre, "Selecteur de couleurs", Color.BLACK);
		if(selection != null) {
			Couleur.fromRGB(selection);
			this.fenetre.getEditeur().ajouter(new ArbreXMLModel(Couleur.fromRGB(selection).toJdom("NouvelleCouleur", "")));
		}
	}
	
	@Action
	public void selecteurVecteur() {
		String vect = JOptionPane.showInputDialog(fenetre,"Expression du vecteur sous la forme \"x y z\"");
		Scanner scanner = new Scanner(vect);
        scanner.useDelimiter(" ");
		Double x,y,z;
		if(scanner.hasNextDouble()) {
			x = scanner.nextDouble();
		}
		else {
			x = 0.;
		}
		if(scanner.hasNextDouble()) {
			y = scanner.nextDouble();
		}
		else {
			y = 0.;
		}		
		if(scanner.hasNextDouble()) {
			z = scanner.nextDouble();
		}
		else {
			z = 0.;
		}
		Vecteur res = new Vecteur(x,y,z);
		ArbreXMLModel a = new ArbreXMLModel(res.toJdom("NouveauVecteur",""));
		this.fenetre.getEditeur().ajouter(a);
	}
	
	@Action
	public void selecteurMateriau() {
		this.fenetre.getEditeur().ajouter(new ArbreXMLModel(new Materiau().toJdom("NouveauMateriau", "")));
	}
	
	@Action
	public void preferences() {
		
	}

	@Action
	public void proprietes() {
		
	}

	@Action
	public void selecteurFichier() {
//		this.fenetre.getEditeur().remp
		
//		this.wait;
		
		final JFileChooser chooser = new JFileChooser();
		final JTextPane accessoire = new JTextPane();
		final String nomDossier = System.getProperty("user.dir") + "\\Bibliotheque";
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
		chooser.setMultiSelectionEnabled(false);
		chooser.setAcceptAllFileFilterUsed(false);
		chooser.setCurrentDirectory(new File(nomDossier));
		chooser.setFileFilter(filtre);
		chooser.setControlButtonsAreShown(true);
		chooser.addPropertyChangeListener(new PropertyChangeListener() {

			public void propertyChange(PropertyChangeEvent evt) {
				try {
					if (chooser.getSelectedFile() != null) {

						if (chooser.getSelectedFile().getPath().endsWith(".xml")) {
							accessoire.setPage("file:///" + chooser.getSelectedFile().getPath() + ".html");
						} else {
							accessoire.setPage("file:///" + System.getProperty("user.dir") + "\\Bibliotheque\\Defaut.html");
						}
					} else {
						accessoire.setPage("file:///" + System.getProperty("user.dir") + "\\Bibliotheque\\Defaut.html");
					}
				} catch (IOException ex) {
					
				} 
			}
		});
		
		
		chooser.setAccessory(accessoire);
		accessoire.setEditable(false);
		accessoire.setContentType("text/html");
		Dimension tailleAccessoire = new Dimension(400,300);
		accessoire.setSize(tailleAccessoire);
		accessoire.setMinimumSize(tailleAccessoire);
		accessoire.setMaximumSize(tailleAccessoire);
		accessoire.setPreferredSize(tailleAccessoire);
		
		int returnVal = chooser.showDialog(fenetre, "Importer");
	
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			String nomFichier = chooser.getSelectedFile().getPath();
			ArbreXMLModel doc = new ArbreXMLModel();
			doc.ouvrir(chooser.getSelectedFile());
			this.fenetre.getEditeur().remplacer(doc);
			Logger.getLogger("Journal").log(Level.INFO,nomFichier+ " importé");
		}

	}

	@Action
	public Task calculerRendu() {
			
//			Tests.test();
			return new CalculerRenduTask(org.jdesktop.application.Application.getInstance(LanceurRayon.LanceurRayonApp.class));
	}

    private class CalculerRenduTask extends org.jdesktop.application.Task<Image, Void> {
		ArbreXMLModel docAct;
        CalculerRenduTask(org.jdesktop.application.Application app) {
            // Runs on the EDT.  Copy GUI state that
            // doInBackground() depends on from parameters
            // to CalculerRenduTask fields, here.
            super(app);
			docAct = ((LanceurRayonApp)app).getDocumentActuel();
        }
        @Override protected Image doInBackground() {
			try {
				// Your Task's code here.  This method runs
				// on a background thread, so don't reference
				// the Swing GUI from here
				Scene scene = new Scene();
				scene = scene.fromJdom(docAct.getRootElement());
				Element s = scene.toJdom("", "");
				new ArbreXMLModel(s).enregistrer("c:/testscene.xml");
				Image rendue = scene.calculer(0);
				rendue = rendue.normaliserMax();
				
				rendue.exporter("temp.png");
								
				return rendue; // return your result
			} catch (Exception ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				return null;
			}
        }
        @Override protected void succeeded(Image result) {
            // Runs on the EDT.  Update the GUI based on
            // the result computed by doInBackground().
			new FenetreAffichage("temp.png");
        }
    }

	@Action
	public void afficherImage() {
		new FenetreAffichage("temp.png");
//		return new CalculerRenduTask(org.jdesktop.application.Application.getInstance(LanceurRayon.LanceurRayonApp.class));
	}

	@Action
	public void rechercher() throws Exception {
		
	}

	@Action
	public void remplacer() {
		
	}

	@Action
	public void selectionnerTout() {

	}

	@Action
	public void fermer() {
		switch(JOptionPane.showConfirmDialog(fenetre,"Ceci entrainera la perte des données non sauvegardées.  \nEtes vous sur ?")) {
			case -1 : 
			case 2 :
			case 1 :
				break;
			case 0 :
				fenetre.removeProjet();
				break;
		}
	}

	@Action
	public void rafraichir() {
		this.getFenetre().getEditeur().refresh();
		
	}

	@Action
	public void afficherJournal() {
		handler.afficherJournal();
	}

	@Action
	public void editer() {
		this.getFenetre().getEditeurArbre().editer();
	}
	
	

	
}
