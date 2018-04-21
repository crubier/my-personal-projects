/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.IHM.Annulation;

import LanceurRayon.IHM.Arbre.ArbreXMLModel;
import LanceurRayon.IHM.JSplitPaneXML;
import javax.swing.undo.AbstractUndoableEdit;
import javax.swing.undo.*;
import org.jdom.Element;

/**
 *
 * @author Lecrubier
 */
public class UndoableEditXML extends AbstractUndoableEdit {
	
	private JSplitPaneXML ihm;
	private ArbreXMLModel avant;
	private ArbreXMLModel apres;
	private String definition;

	public UndoableEditXML(JSplitPaneXML ihm, ArbreXMLModel avant, ArbreXMLModel apres, String def) {
		this.ihm = ihm;
		this.avant = avant.clone();
		this.apres = apres.clone();
		this.definition = def;
	}
	
	@Override
	public void undo() throws CannotUndoException {
      super.undo();
      ihm.setArbre(avant);
	  ihm.refresh();
    }

	@Override
    public void redo() throws CannotRedoException {
      super.redo();
      ihm.setArbre(apres);
	  ihm.refresh();
    }

	@Override
    public String getPresentationName() {
      return this.definition;
    }
	
	public String toString()
    {
		return super.toString();
    }
   
}
