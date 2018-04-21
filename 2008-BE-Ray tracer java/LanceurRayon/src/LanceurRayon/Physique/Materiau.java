/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package LanceurRayon.Physique;

import LanceurRayon.Util.JDomIO;
import java.lang.reflect.Field;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;
import org.jdom.filter.Filter;


/**
 *
 * @author Lecrubier
 */
public class Materiau implements JDomIO{

	public static final Materiau vide = new Materiau();
	public static final Materiau defaut = vide;
		
	
//Proprietés volumiques > rayon actuel
	
	private Couleur Attenuation;
	private Couleur Ambiante;				//composante ambiante
	
	private Couleur Speculaire;				//composante speculaire
	private Couleur AntiSpeculaire;			//composante antispeculaire
	private Couleur IndiceSpeculaire;		//indices de reflexion speculaire
	
	
//Proprietes surfaciques > rayon actuel
	
	private Couleur Normale;				//composante normale
	private Couleur AntiNormale;			//composante tangentielle
	private Couleur IndiceNormale;			//indice de la composante normale
	
	private Couleur Diffuse;				//composante diffuse
	private Couleur AntiDiffuse;			//composante antidiffuse
	private Couleur IndiceDiffuse;			//indice diffuse
	
//Proprietes surfacique > rayon reflechi
	
	private Couleur Reflexion;				//composante de reflexion
	
//	Proprietes surfaciques > rayon refracte
	
	private Couleur Refraction;				//composante de refraction 
	private Couleur IndiceRefraction;		//indices de refraction 

	public Materiau(Couleur Attenuation, Couleur Speculaire, Couleur AntiSpeculaire, Couleur IndiceSpeculaire, Couleur Ambiante, Couleur Normale, Couleur AntiNormale, Couleur IndiceNormale, Couleur Diffuse, Couleur AntiDiffuse, Couleur IndiceDiffuse, Couleur Reflexion, Couleur Refraction, Couleur IndiceRefraction) {
		this.Attenuation = Attenuation;
		this.Speculaire = Speculaire;
		this.AntiSpeculaire = AntiSpeculaire;
		this.IndiceSpeculaire = IndiceSpeculaire;
		this.Ambiante = Ambiante;
		this.Normale = Normale;
		this.AntiNormale = AntiNormale;
		this.IndiceNormale = IndiceNormale;
		this.Diffuse = Diffuse;
		this.AntiDiffuse = AntiDiffuse;
		this.IndiceDiffuse = IndiceDiffuse;
		this.Reflexion = Reflexion;
		this.Refraction = Refraction;
		this.IndiceRefraction = IndiceRefraction;
	}
	
	public Materiau(Materiau a) {
		this.Attenuation = a.Attenuation;
		this.Speculaire = a.Speculaire;
		this.AntiSpeculaire = a.AntiSpeculaire;
		this.IndiceSpeculaire = a.IndiceSpeculaire;
		this.Ambiante = a.Ambiante;
		this.Normale = a.Normale;
		this.AntiNormale = a.AntiNormale;
		this.IndiceNormale = a.IndiceNormale;
		this.Diffuse = a.Diffuse;
		this.AntiDiffuse = a.AntiDiffuse;
		this.IndiceDiffuse = a.IndiceDiffuse;
		this.Reflexion = a.Reflexion;
		this.Refraction = a.Refraction;
		this.IndiceRefraction = a.IndiceRefraction;
	}
	
	public Materiau() {
		try {
			this.Attenuation = Couleur.blanc.multiplication(0.99);
			this.Speculaire = Couleur.blanc;
			this.AntiSpeculaire = Couleur.noir;
			this.IndiceSpeculaire = Couleur.blanc.multiplication(40.);
			this.Ambiante = Couleur.noir;
			this.Normale = Couleur.blanc;
			this.AntiNormale = Couleur.noir;
			this.IndiceNormale = Couleur.blanc.multiplication(40.);
			this.Diffuse = Couleur.magenta;
			this.AntiDiffuse = Couleur.noir;
			this.IndiceDiffuse = Couleur.blanc.multiplication(40.);
			this.Reflexion = Couleur.noir;
			this.Refraction = Couleur.blanc;
			this.IndiceRefraction = Couleur.blanc;
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
		}
	}
	
	public Couleur getAmbiante() {
		return Ambiante;
	}

	public void setAmbiante(Couleur Ambiante) {
		this.Ambiante = Ambiante;
	}

	public Couleur getAntiDiffuse() {
		return AntiDiffuse;
	}

	public void setAntiDiffuse(Couleur AntiDiffuse) {
		this.AntiDiffuse = AntiDiffuse;
	}

	public Couleur getAntiNormale() {
		return AntiNormale;
	}

	public void setAntiNormale(Couleur AntiNormale) {
		this.AntiNormale = AntiNormale;
	}

	public Couleur getAntiSpeculaire() {
		return AntiSpeculaire;
	}

	public void setAntiSpeculaire(Couleur AntiSpeculaire) {
		this.AntiSpeculaire = AntiSpeculaire;
	}

	public Couleur getAttenuation() {
		return Attenuation;
	}

	public void setAttenuation(Couleur Attenuation) {
		this.Attenuation = Attenuation;
	}

	public Couleur getDiffuse() {
		return Diffuse;
	}

	public void setDiffuse(Couleur Diffuse) {
		this.Diffuse = Diffuse;
	}

	public Couleur getIndiceDiffuse() {
		return IndiceDiffuse;
	}

	public void setIndiceDiffuse(Couleur IndiceDiffuse) {
		this.IndiceDiffuse = IndiceDiffuse;
	}

	public Couleur getIndiceNormale() {
		return IndiceNormale;
	}

	public void setIndiceNormale(Couleur IndiceNormale) {
		this.IndiceNormale = IndiceNormale;
	}

	public Couleur getIndiceRefraction() {
		return IndiceRefraction;
	}

	public void setIndiceRefraction(Couleur IndiceRefraction) {
		this.IndiceRefraction = IndiceRefraction;
	}

	public Couleur getIndiceSpeculaire() {
		return IndiceSpeculaire;
	}

	public void setIndiceSpeculaire(Couleur IndiceSpeculaire) {
		this.IndiceSpeculaire = IndiceSpeculaire;
	}

	public Couleur getNormale() {
		return Normale;
	}

	public void setNormale(Couleur Normale) {
		this.Normale = Normale;
	}

	public Couleur getReflexion() {
		return Reflexion;
	}

	public void setReflexion(Couleur Reflexion) {
		this.Reflexion = Reflexion;
	}

	public Couleur getRefraction() {
		return Refraction;
	}

	public void setRefraction(Couleur Refraction) {
		this.Refraction = Refraction;
	}

	public Couleur getSpeculaire() {
		return Speculaire;
	}

	public void setSpeculaire(Couleur Speculaire) {
		this.Speculaire = Speculaire;
	}
	

	public Element toJdom(String Nom, String Role) {
		Field[] champs = this.getClass().getDeclaredFields();
		Integer imax = champs.length;
		
		Element c = new Element("Materiau")	;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);
		
		for (Integer i = 0; i<imax ; i++) {
			if(champs[i].getType().getName().compareTo(Couleur.class.getName()) == 0) {
				try {
					String nom = champs[i].getName();
					c.addContent(((Couleur) champs[i].get(this)).toJdom("",nom));
				} catch (IllegalArgumentException ex) {
					Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				} catch (IllegalAccessException ex) {
					Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				}
			}
		}
		return c;
	}

	public Materiau fromJdom(Element element) {
		
		if (element != null) {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0 && !ref.isEmpty()) {
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Materiau"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				Field[] champs = this.getClass().getDeclaredFields();
				Integer imax = champs.length;
				Materiau res = new Materiau();
//				System.out.println("Materiau :");
				for (Element fils : (List<Element>) element.getChildren()) {
			
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					for (Integer i = 0; i<imax ; i++) {
						if (role.compareTo(champs[i].getName().toLowerCase(Locale.ENGLISH))==0) {
//							System.out.println("   " + role+" OK");
							champs[i].set(res, new Couleur().fromJdom(fils));	
						}
					}
				}
				return res;
			} catch (Exception ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				return null;
			}
		} else {
			return null;
		}
	}	
}
