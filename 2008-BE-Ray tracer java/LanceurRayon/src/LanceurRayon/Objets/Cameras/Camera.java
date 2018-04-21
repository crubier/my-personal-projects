/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Objets.Cameras;

import LanceurRayon.Objets.Lumieres.*;
import LanceurRayon.Objets.*;
import LanceurRayon.Physique.Rayon;
import LanceurRayon.Util.JDomIO;
import LanceurRayon.Util.Rectangle;
import java.util.Iterator;
import java.util.Locale;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @author Lecrubier
 */
public abstract class Camera implements ObjetDeScene, JDomIO {
	
	private Rectangle<Integer> dimensions;
	private Integer recursivite;

	public Camera(Rectangle<Integer> dimensions, Integer recursivite) {
		this.dimensions = dimensions;
		this.recursivite = recursivite;
	}

	public Camera() {
		this.dimensions = new Rectangle<Integer>(0,0,400,300);
		this.recursivite = 3;
	}

	public Rectangle<Integer> getDimensions() {
		return dimensions;
	}

	public void setDimensions(Rectangle<Integer> dimensions) {
		this.dimensions = dimensions;
	}

	public Integer getRecursivite() {
		return recursivite;
	}

	public void setRecursivite(Integer recursivite) {
		this.recursivite = recursivite;
	}
	
	public abstract Rayon rayonLance(Double x, Double y);
	
	@Override
	public Camera fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Camera"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
			
			String type = element.getAttributeValue("Type","Inconnu").toLowerCase(Locale.ENGLISH);
			if(type.contains("ponctuelle")) {
				return new CameraSimple().fromJdom(element);
			} else {
				return new CameraSimple().fromJdom(element);
			}
			
		}
	}
	
}
