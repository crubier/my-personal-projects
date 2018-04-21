/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util;

import java.util.Iterator;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @author Lecrubier
 */
public class Nombre implements JDomIO{

	private Number contenu;

	public Nombre(Number contenu) {
		this.contenu = contenu;
	}
	
	public Number getContenu() {
		return contenu;
	}

	public void setContenu(Number contenu) {
		this.contenu = contenu;
	}
	
	public short shortValue() {
		return contenu.shortValue();
	}

	public long longValue() {
		return contenu.longValue();
	}

	public int intValue() {
		return contenu.intValue();
	}

	public float floatValue() {
		return contenu.floatValue();
	}

	public double doubleValue() {
		return contenu.doubleValue();
	}

	public byte byteValue() {
		return contenu.byteValue();
	}

	public static Number convertir(Object a,String b) {
		if (a instanceof Short) {
			return new Short(b);
		} 
		else if (a instanceof Long) {
			return new Long(b);
		} 
		else if (a instanceof Integer) {
			return new Integer(b);
		} 
		else if (a instanceof Float) {
			return new Float(b);
		} 
		else if (a instanceof Double) {
			return new Double(b);
		} 
		else if (a instanceof Byte) {
			return new Byte(b);
		} 
		else {
			return new Double(b);
		}
	}
	
	public Element toJdom(String Nom, String Role) {
		Element c = new Element(contenu.getClass().getSimpleName());
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		c.setText(contenu.toString());	
		return c;
	}

	public Object fromJdom(Element element) {
		String ref = element.getAttributeValue("Reference","Inconnu");
		if(ref.compareTo("Inconnu")!=0) {
			System.out.println("reference");
			Iterator el = element.getDocument().getDescendants(new ElementFilter("Materiau"));
			while(el.hasNext()) {
				Element actuel = (Element)el.next();
				String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
				if(nomEl.compareTo(ref)==0) {
					return this.fromJdom(actuel);
				}
			}
		}
		if(element.getName().contains(Short.class.getSimpleName())) {
			return new Short(element.getText());
		}
		else if(element.getName().contains(Long.class.getSimpleName()) ) {
			return new Long(element.getText());
		}
		else if(element.getName().contains(Integer.class.getSimpleName())) {
			return new Integer(element.getText());
		}
		else if(element.getName().contains(Float.class.getSimpleName()) ) {
			return new Float(element.getText());
		}
		else if(element.getName().contains(Double.class.getSimpleName()) ) {
			return new Double(element.getText());
		}
		else if(element.getName().contains(Byte.class.getSimpleName())) {
			return new Byte(element.getText());
		}
		else {
			return new Double(element.getText());
		}
	}

}
