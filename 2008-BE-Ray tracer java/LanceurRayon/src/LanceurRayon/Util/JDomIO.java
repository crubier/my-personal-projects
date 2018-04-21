/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util;

import org.jdom.Element;

/**
 *
 * @author Lecrubier
 */
public interface JDomIO {
	public Element toJdom(String Nom, String Role) ;
	public Object fromJdom(Element element) ;
}
