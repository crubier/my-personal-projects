/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.IHM.Arbre;

import LanceurRayon.Util.Liste;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.tree.*;
import org.jdom.Content;
import org.jdom.Element;

/**
 *
 * @author Lecrubier
 */


// IMPOSSIBLE DE FAIRE extends Element implements MutableTreeNode, TreeNode  a CAUSE DE LA METHODE
// getParent() Present dans Element et TreeNode, c'est scandaleux aucune solution existe
public class ArbreXMLNode implements MutableTreeNode, TreeNode {
	
	private Element element;


	public ArbreXMLNode(Element element) {
		this.element = element;
	}
	
	public Element getElement() {
		return element;
	}

	public void setElement(Element element) {
		ArbreXMLNode parent = (ArbreXMLNode) this.getParent();
		this.element = element;
		this.setParent(parent);
	}
	
	public void insert(MutableTreeNode child, int index) {
		element.addContent(index,((ArbreXMLNode)child).getElement());
	}

	public void remove(int index) {
		element.removeContent(index);
	}

	public void remove(MutableTreeNode node) {
		((ArbreXMLNode)node).getElement().detach();
	}

	public void setUserObject(Object object) {
		element = (Element)object;
	}

	public void removeFromParent() {
		if( ! element.isRootElement()){
			element.getParentElement().removeContent(element);
		}
		else {
			Logger.getLogger("Journal").log(Level.WARNING,"Impossible de supprimer l'objet racine !");
		}
	}

	public void setParent(MutableTreeNode newParent) {
		if(this.element.getParentElement()!=null) {
			this.element.getParentElement().removeContent(this.element);
		}
		((ArbreXMLNode)newParent).getElement().addContent(this.element);
		
	}

	public TreeNode getChildAt(int childIndex) {
		return new ArbreXMLNode( (Element) element.getChildren().get(childIndex));
	}

	public int getChildCount() {
		return element.getChildren().size();
	}

	public int getIndex(TreeNode node) {
		Element elem = ((ArbreXMLNode) node).getElement();

//		List<Element> liste = element.getChildren();
//		for(Integer i = 0; i < liste.size(); i++) {
//			if(liste.get(i).equals(elem)) {
//				return i;
//			}
//		}
//		return -1;
		return element.getChildren().indexOf(elem);
	}

	public boolean getAllowsChildren() {
		return true;
	}

	public boolean isLeaf() {
		return element.getChildren().isEmpty();
	}

	public Enumeration children() {
		
// Scandale : on est ici obligé d'utiliser l interface Enumeration, qui est deprecated
// on doit creer un adaptateur
		
		List<Element> res =  element.getChildren();
		List<ArbreXMLNode> result = new Vector<ArbreXMLNode>();
		for(Integer i = 0; i<res.size();i++) {
			result.add(i,new ArbreXMLNode(res.get(i)));
		}
		
		class EnumerationNode implements Enumeration {

			private Iterator<ArbreXMLNode> nodes ;
				
			private EnumerationNode(List<ArbreXMLNode> result) {
				nodes = result.iterator();
			}

			public boolean hasMoreElements() {
				return nodes.hasNext();
			}

			public Object nextElement() {
				return nodes.next();
			}
			
		}
		return new EnumerationNode(result);
	}

	public TreeNode getParent() {
		return new ArbreXMLNode(element.getParentElement());
	}

	
	
}
