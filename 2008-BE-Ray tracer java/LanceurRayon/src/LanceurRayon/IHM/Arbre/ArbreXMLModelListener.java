/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.IHM.Arbre;

import javax.swing.event.TreeModelEvent;
import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreePath;

/**
 *
 * @author Lecrubier
 */
public class ArbreXMLModelListener implements TreeModelListener {

	JTreeXML ecouteur;
	
	public ArbreXMLModelListener(JTreeXML ecouteur) {
		this.ecouteur = ecouteur;
	}
		
	public void treeNodesChanged(TreeModelEvent e) {
		System.out.println("treeNodesChanged");
		ecouteur.getPaneXML().refreshEditeurTexte();
//		ecouteur.repaint();
//		ecouteur.updateUI();
		ecouteur.refresh();
	}

	public void treeNodesInserted(TreeModelEvent e) {
		System.out.println("treeNodesInserted");
		ecouteur.getPaneXML().refreshEditeurTexte();
//		ecouteur.repaint();
//		ecouteur.updateUI();
		ecouteur.refresh();
	}

	public void treeNodesRemoved(TreeModelEvent e) {
		System.out.println("treeNodesRemoved");
		ecouteur.getPaneXML().refreshEditeurTexte();
//		ecouteur.repaint();
//		ecouteur.updateUI();
		ecouteur.refresh();
	}

	public void treeStructureChanged(TreeModelEvent e) {
		
		TreePath temp = ecouteur.getSelectionPath();
			System.out.println(temp);
		System.out.println("treeStructureChanged");
		ecouteur.getPaneXML().refreshEditeurTexte();
//		ecouteur.repaint();
//		ecouteur.updateUI();
		ecouteur.refresh();
		ecouteur.setSelectionPath(temp);
	}
}
