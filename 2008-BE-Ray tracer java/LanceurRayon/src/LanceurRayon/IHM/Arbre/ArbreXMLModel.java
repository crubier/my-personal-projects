/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.IHM.Arbre;

/**
 *
 * @author Lecrubier
 */
import LanceurRayon.Util.*;
import java.io.*;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.event.TreeModelEvent;
import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreePath;
import org.jdom.*;
import org.jdom.input.*;
import org.jdom.filter.*;
import javax.swing.tree.TreeModel;
import org.jdom.output.Format;
import org.jdom.output.XMLOutputter;

public class ArbreXMLModel implements TreeModel, Cloneable {
	Document document;
	List<TreeModelListener> listeners;

	public ArbreXMLModel(List arg0) {
		document = new Document(arg0);
		listeners = new Liste<TreeModelListener>();
	}

	public ArbreXMLModel(Element arg0) {
		document = new Document(arg0);
		listeners = new Liste<TreeModelListener>();
	}
	
	public ArbreXMLModel(Document arg0) {
		document = (Document) arg0.clone();
		listeners = new Liste<TreeModelListener>();
	}

	public ArbreXMLModel(Element arg0, DocType arg1, String arg2) {
		document = new Document(arg0,arg1,arg2);
		listeners = new Liste<TreeModelListener>();
	}

	public ArbreXMLModel() {
		document = new Document();
		listeners = new Liste<TreeModelListener>();
	}

	public ArbreXMLModel clone() {
		return new ArbreXMLModel(document);
	}

	/**
	 * Importe le fichier URL dans le document
	 * @param URL
	 */
	public void ouvrir(String URL){
		ouvrir(new File(URL));
	}
   
	/**
	 * Importe le fichier dans le document
	 * @param fichier 
	 */
	public void ouvrir(File fichier){
		try {
			
			SAXBuilder builder = new SAXBuilder();

			Document doc = builder.build(fichier);
			document = doc;
			treeStructureChanged();
		} catch (JDOMException ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		} catch (IOException ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}

	}
   
    /**
	* Exporte le document dans le fichier URL
	* 
	 * 
	 * @param URL 
	 */
	public void enregistrer(String URL){
		enregistrer(new File(URL));
	}
   
   /**
	* Exporte le document dans le fichier
	* 
	* @param fichier 
	*/
	public void enregistrer(File fichier)
	{

		FileWriter writer = null;
		try {
			XMLOutputter outputter = new XMLOutputter();
			writer = new FileWriter(fichier);
			outputter.setFormat(Format.getPrettyFormat());
			outputter.output(document, writer);
			writer.flush();
			writer.close();
		} catch (IOException ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		} finally {
			try {
				writer.close();
			} catch (IOException ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			}
		}



	}

   
	public void fromString(String source){
		try {
			Document nouveau = new Document();
			//On crée une instance de SAXBuilder
			SAXBuilder builder = new SAXBuilder();
			StringReader reader = new StringReader(source);
			nouveau = builder.build(reader);
			document = nouveau;
			treeStructureChanged();
		} catch (JDOMException ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		} catch (IOException ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}

	
	/**
	* 
	* @return le Document au format String
	*/
	@Override
	public String toString() {
		try {
			String res;
			XMLOutputter outputter = new XMLOutputter();
			Format format = Format.getPrettyFormat();
			format.setOmitDeclaration(true);
			outputter.setFormat(format);
			StringWriter writer = new StringWriter();
			outputter.output(document, writer);
			res = writer.toString();
			writer.flush();
			writer.close();

			return res;
		} catch (IOException ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return "";
		}
	}
   

	public Object getRoot() {
		return new ArbreXMLNode(document.getRootElement());
	}

	public Object getChild(Object parent, int index) {
		return  new ArbreXMLNode((Element)((ArbreXMLNode)parent).getElement().getChildren().get(index));
	}

	public int getChildCount(Object parent) {
		return ((ArbreXMLNode)parent).getElement().getChildren().size();
	}

	public boolean isLeaf(Object node) {
		return ((ArbreXMLNode)node).getElement().getChildren().isEmpty();
	}

	public int getIndexOfChild(Object parent, Object child) {
		if(parent == null ||child == null) {
			return -1;
		}
		@SuppressWarnings("unchecked")
		List<Element> liste = (List<Element>) ((ArbreXMLNode)parent).getElement().getChildren();
		for (Element temp : liste) {
			if(temp.equals(((ArbreXMLNode)child).getElement())) {
				return liste.indexOf(temp);
			}
		}
		return -1;
	}

	public void addTreeModelListener(TreeModelListener l) {
		
		listeners.add(l);
	}

	public void removeTreeModelListener(TreeModelListener l) {
		listeners.remove(l);
	}

	public void valueForPathChanged(TreePath path, Object newValue) {
		Liste<TreeModelListener> bob = new Liste<TreeModelListener>(listeners);
		if (((ArbreXMLNode) newValue).getElement() != ((ArbreXMLNode) path.getLastPathComponent()).getElement()) {
//			((ArbreXMLNode) path.getLastPathComponent()).setElement(((ArbreXMLNode) newValue).getElement());
			((ArbreXMLNode) path.getLastPathComponent()).getElement().setText(((ArbreXMLNode) newValue).getElement().getText());
//			System.out.println("Edition1" + ((ArbreXMLNode) newValue).getElement().getText());
//			System.out.println("Edition2" + ((ArbreXMLNode) path.getLastPathComponent()).getElement().getText());
			TreeModelEvent e = new TreeModelEvent(this, path);
			for (TreeModelListener ec : bob) {
				ec.treeNodesChanged(e);
			}
		}
	}
	
	public void treeStructureChanged() {
		TreeModelEvent e = new TreeModelEvent(this,new TreePath(this.getRoot()));
		Liste<TreeModelListener> bob = new Liste<TreeModelListener>(listeners);
		for (TreeModelListener ec : bob) {
				ec.treeStructureChanged(e);
		}
	}
	
	public void removeContent(TreePath chemin) {
//		Integer profondeur = chemin.getPathCount();
//		Element base = document.getRootElement();
//		Element temp = base;
//		for(Integer i = 0; i<profondeur;i++) {
//			System.out.println( chemin.getPathComponent(i).toString());
////			temp = (Element)temp.getChild(((Element)chemin.getPathComponent(i)).getName());
////			chemin.getPathComponent(i);
//			System.out.println("temp " +temp.toString());
//			System.out.println("chemini " +chemin.getPathComponent(i).toString());
//		}
//		((Element)chemin.getLastPathComponent()).removeContent();
		
		((ArbreXMLNode)chemin.getLastPathComponent()).removeFromParent();
//		valueForPathChanged(chemin, chemin.getLastPathComponent());
		TreeModelEvent e = new TreeModelEvent(this,new TreePath(this.getRoot()));
		Liste<TreeModelListener> bob = new Liste<TreeModelListener>(listeners);
		for (TreeModelListener ec : bob) {
				ec.treeNodesRemoved(e);
		}
				
	}

	public Element getRootElement() {
		return document.getRootElement();
	}

	public void removeNodeFromParent(ArbreXMLNode currentNode) {
		currentNode.getElement().getParentElement().removeContent(currentNode.getElement());
	}

  
}
	
	
