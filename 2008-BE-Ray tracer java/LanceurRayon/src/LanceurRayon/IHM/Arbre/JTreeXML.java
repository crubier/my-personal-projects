/**
 * This class is used to display a XML document in a form of a
 * interactive visible tree. When the window is closed, the system
 * does not exit (it only release resource). If the client of this class
 * wants to quit the whole system, the client program need either
 * set the windowListener, or need to run System.exit(0) explictly.
 */

package LanceurRayon.IHM.Arbre;

import LanceurRayon.IHM.Arbre.ArbreXMLCellEditor;
import LanceurRayon.IHM.Arbre.ArbreXMLCellRenderer;
import LanceurRayon.IHM.Arbre.*;
import LanceurRayon.IHM.JSplitPaneXML;
import LanceurRayon.Util.JDomIO;
import java.awt.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.event.*;


import org.jdom.*;



public class JTreeXML extends JTree implements JDomIO{

		//The XML document to be output to the JTree
	private ArbreXMLModelListener ecouteur ;
	private JSplitPaneXML PaneXML;

	//	public JTreeXML() {
	//		super();
	//		super.setRootVisible(false);
	//		tn= new DefaultMutableTreeNode("XML");
	//		this.setName("XML Tree");
	//		xmlDoc = new Document( new Scene().toJdom());
	//		initialize();
	//	}
	

	
	public JTreeXML(ArbreXMLModel arbre,JSplitPaneXML parent) {
		super(arbre);
		super.setRootVisible(true);
		super.setShowsRootHandles(true);
		super.getSelectionModel().setSelectionMode(TreeSelectionModel.DISCONTIGUOUS_TREE_SELECTION);

		this.PaneXML=parent;
		this.setName("XML Tree");
		
		this.setSelectionModel(selectionModel);
		this.setModel(arbre);
		ecouteur = new ArbreXMLModelListener(this);
		this.getModel().addTreeModelListener(ecouteur);
		this.setCellRenderer(new ArbreXMLCellRenderer());
//		this.setCellEditor(new ArbreXMLCellEditor(this, this.getCellRenderer()));
		this.setCellEditor(new ArbreXMLCellEditor(this,(ArbreXMLCellRenderer)this.getCellRenderer(), new ArbreXMLCellEditorFenetre(this)));
		this.setComponentPopupMenu(new ArbreXMLPopupMenu());
		this.setEditable(true);
	}

	public JSplitPaneXML getPaneXML() {
		return PaneXML;
	}
	
	@Override
	public ArbreXMLModel getModel() {
		return (ArbreXMLModel) super.getModel();
	}
	
	public void add(ArbreXMLModel element) {
		if(element!=null){
			TreePath[] selections = super.getSelectionPaths();
			if(selections!=null) {
				for(Integer i=0; i<selections.length;i++) {
					TreePath currentSelection = selections[i];
					if (currentSelection != null) {
						ArbreXMLNode currentNode = (ArbreXMLNode) currentSelection.getLastPathComponent();
						currentNode.insert(new ArbreXMLNode((Element)element.getRootElement().clone()),0);
						getModel().valueForPathChanged(currentSelection, currentNode);
					} 
				}
			}
		}
		else {
			Logger.getLogger("Journal").log(Level.WARNING,"Objet a ajouter vide !");
		}
	}
	
	public void remove() {
		TreePath[] selections = super.getSelectionPaths();
		if(selections!=null) {
			for(Integer i=0; i<selections.length;i++) {
				TreePath currentSelection = selections[i];
				if (currentSelection != null) {
					ArbreXMLNode currentNode = (ArbreXMLNode) currentSelection.getLastPathComponent();
					currentNode.removeFromParent();
					getModel().valueForPathChanged(currentSelection, currentNode);
				} 
			}
		}
	}
	
	public void replace(ArbreXMLModel element) {
		if(element!=null){
			TreePath[] selections = super.getSelectionPaths();
			if(selections!=null) {
				for(Integer i=0; i<selections.length;i++) {
					TreePath currentSelection = selections[i];
					if (currentSelection != null) {
						ArbreXMLNode currentNode = (ArbreXMLNode) currentSelection.getLastPathComponent();
						ArbreXMLNode parentNode = (ArbreXMLNode) currentNode.getParent();
						
						int index = parentNode.getIndex(currentNode) <0 ? 0 : parentNode.getIndex(currentNode);
						String role = currentNode.getElement().getAttributeValue("Role","");
						Element nouveau = (Element)element.getRootElement().clone();
						nouveau.setAttribute("Role", role);
						parentNode.remove(currentNode);
						ArbreXMLNode newNode = new ArbreXMLNode(nouveau);
						parentNode.insert(newNode, index);
	
						getModel().valueForPathChanged(currentSelection, currentNode);
					} 
				}
			}
		}
		else {
			Logger.getLogger("Journal").log(Level.WARNING,"Objet a remplacer vide !");
		}
	}
	
	public Object fromJdom(Element element) {
		super.setModel(new ArbreXMLModel(element));		
		super.repaint();
		return new Boolean(true);
	}

	public Element toJdom(String Nom, String Role) {
		throw new UnsupportedOperationException("Not supported yet.");
	}
	

	public void editer() {
		this.startEditingAtPath(this.getSelectionPath());
	}
	
	public void refresh() {
		TreePath path = this.getSelectionPath();
		PaneXML.refresh();
		this.setSelectionPath(path);
	}



}
