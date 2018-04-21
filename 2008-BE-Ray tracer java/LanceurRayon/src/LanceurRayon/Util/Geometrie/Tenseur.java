/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LanceurRayon.Util.Geometrie;

import LanceurRayon.Util.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdom.Element;
import org.jdom.filter.ElementFilter;

/**
 *
 * @author Lecrubier
 */
public class Tenseur implements JDomIO{
    private Liste<Integer> dimensions;
    private Liste<Double> coefficients;

    /**
     *
     */
    public Tenseur() {
        this.dimensions = new Liste<Integer>();
		this.dimensions.add(1);
        this.coefficients = new Liste<Double>(this.longueur(),new Double(0.));
    }

    /**
     *
	 * @param dimensions
     */
    public Tenseur(Liste<Integer> dimensions) {
        this.dimensions = new Liste<Integer>(dimensions);
        this.coefficients = new Liste<Double>(this.longueur(),new Double(0.));
    }

	/**
	 *
	 * @param dimensions
	 * @param coefficients
	 */
	public Tenseur(Liste<Integer> dimensions, Liste<Double> coefficients) {
		this.dimensions = new Liste<Integer>(dimensions);
		this.coefficients = new Liste<Double>(coefficients);
	}

	/**
	 * 
	 * @param a
	 */
	public Tenseur(Tenseur a) {
		this.dimensions = new Liste<Integer>(a.dimensions);
		this.coefficients = new Liste<Double>(a.coefficients);
	}
	
    /**
     *
     */
    public void initialiseCoefficients() {
        Integer a = this.longueur();
		this.coefficients.clear();
        for(int i=0; i<a ; i++) {
            this.coefficients.add(0.0);
        }
    }

    /**
     *
     * @return
     */
    public Integer ordre() {
        return this.dimensions.size();
    }

    /**
     *
     * @return
     */
    public Integer longueur() {
        Integer res = 1;
        for(Integer a : this.dimensions) {
            res *= a ;
        }
        return res;
    }

    /**
     *
     * @param element
     * @return
     * @throws java.lang.Exception
     */
    public Double getDouble(Liste<Integer> element) throws Exception {
		return this.coefficients.get(this.getPosition(element));
	}

    /**
     *
     * @param element
     * @param val
     * @throws java.lang.Exception
     */
    public void setDouble(Liste<Integer> element, double val) throws Exception {
		this.coefficients.set(this.getPosition(element), val);
    }

	/**
	 *
	 * @param element
	 * @return
	 * @throws java.lang.Exception
	 */
    public Integer getPosition(Liste<Integer> element) throws Exception {
		Integer ordre = this.ordre();
		if(element.size() != ordre) {
            throw new Exception("Index incompatible");
        }
        else {
	    Integer i = 0;
            Integer k = this.longueur();
			Integer temp = null;
            for(Integer a = 0 ;  a < ordre ; a ++) {
				temp = this.dimensions.get(a);
                if(element.get(a) >=  temp || element.get(a) < 0) {
                    throw new Exception("Index incompatible");
                }
				k /= temp;
                if(element.get(a) < temp) {

                    i += element.get(a) * k;
                }
            }
            return i;
        }
    }

	/**
	 *
	 * @param i
	 * @return
	 * @throws java.lang.Exception
	 */
	public Liste<Integer> getIndice(Integer i) throws Exception {
		Liste<Integer> res = new Liste<Integer>();
		Integer a = i;
		for(Integer b=0; b < this.dimensions.size();b++) {
			res.add( a % (this.dimensions.get(b)));
			a = a / (this.dimensions.get(b));
		}
		return res;

	}

	public Boolean isValide() {
		if(this.coefficients.size() != this.longueur()) {
			return false;
		}
		return true;
    }
	
    /**
	 *
	 * @param element
	 * @return
	 * @throws java.lang.Exception
	 */
    public Tenseur getTenseur(Integer element) throws Exception {
		if(this.ordre() < 1 ) {
			if(element != 0) {
				throw new Exception("Index incompatible");
			}
			else {
				return this;
			}
		}

		if(element >= this.dimensions.get(0) || element <0) {
			throw new Exception("Index incompatible");
		}

//		System.out.println("==============================");
//		System.out.println("a = " + element * this.longueur()/this.dimensions.get(0));
//		System.out.println("b = " + ((element+1) * this.longueur()/this.dimensions.get(0) ));
//		System.out.println("element = " + element);
//		System.out.println("this.longueur() = " + this.longueur());
//		System.out.println("this.dimensions.get(0) = " + this.dimensions.get(0));
//		System.out.println("Q = " + (this.longueur()/this.dimensions.get(0)));
//		System.out.println("==============================");
	

		Liste<Integer> dim = new Liste<Integer>(this.dimensions);
		dim.remove(0);
		Tenseur res = new Tenseur( dim );

		for(Integer i = 0; i<res.longueur(); i++) {
			res.coefficients.ajouter(i, this.coefficients.get(element * this.longueur()/this.dimensions.get(0) + i));
		}

		//res.setCoefficients( (Liste<Double>) this.coefficients.subList(element * this.longueur()/this.dimensions.get(0),(element+1) * this.longueur()/this.dimensions.get(0)/*-1 ?*/));

		return res;
    }

    public Tenseur getTenseur(Liste<Integer> elements) throws Exception {
        Tenseur res = new Tenseur(this.dimensions, this.coefficients);
		for(Integer i : elements) {
			res = res.getTenseur(i);
		}
		return res;
    }

    public Liste<Integer> getDimensions() {
        return dimensions;
    }

    public void setDimensions(Liste<Integer> dimensions) {
        this.dimensions = new Liste<Integer>(dimensions);
        this.initialiseCoefficients();
    }

    public Liste<Double> getCoefficients() {
        return coefficients;
    }

    public void setCoefficients(Liste<Double> coefficients) throws Exception {
        if(coefficients.size() != this.longueur()) {
            throw new Exception("Taille incompatible");
        }
        else {
            this.coefficients = new Liste<Double>(coefficients);
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Tenseur other = (Tenseur) obj;
        if (this.dimensions != other.dimensions && (this.dimensions == null || !this.dimensions.equals(other.dimensions))) {
            return false;
        }
        if (this.coefficients != other.coefficients && (this.coefficients == null || !this.coefficients.equals(other.coefficients))) {
            return false;
        }
        return true;
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 89 * hash + (this.dimensions != null ? this.dimensions.hashCode() : 0);
        hash = 89 * hash + (this.coefficients != null ? this.coefficients.hashCode() : 0);
        return hash;
    }

    @Override
    public String toString() {
 String res = "";
        if(this.ordre() == 0) {
			res = this.coefficients.get(0).toString();
		}
		else {
			res = "[ ";
			for(Integer i = 0; i < this.dimensions.get(0) ; i++ ) {
				try {
					res = res + this.getTenseur(i).toString() + " ";
				} catch (Exception ex) {
					Logger.getLogger(Tenseur.class.getName()).log(Level.SEVERE, null, ex);
				}
			}
			res = res + "]";
		}
		return res;
    }

    public Tenseur produitcontracte(Tenseur other, Integer contraction) throws Exception{
		if(contraction>this.ordre() || contraction >other.ordre() || 2 * contraction > this.ordre() + other.ordre()) {
			throw new Exception("Produit tensoriel contracte invalide");
		}

		for(Integer i = 0; i< contraction ; i++){
			if(this.dimensions.lire(-1-i) != other.dimensions.lire(i)) {
				throw new Exception("Produit tensoriel contracte invalide");
			}
		}
		
		Tenseur resa = this.produit(other);
		Tenseur res = resa.contraction( this.ordre()-1 ,contraction);
		
		return res;

    }

	@Override
	@SuppressWarnings("unchecked")
	protected Object clone() throws CloneNotSupportedException {
		Tenseur res= new Tenseur() ;
		res.coefficients = (Liste<Double>) this.coefficients.clone();
		res.dimensions = (Liste<Integer>) this.dimensions.clone();
		return res;
	}
	
	
	 public Tenseur produit(Tenseur other) throws Exception{

		Liste<Integer> dim = new Liste<Integer>();
		dim.addAll(this.dimensions);
		dim.addAll(other.dimensions);
		Tenseur res = new Tenseur(dim);

		/*
		 * RES i j k p q  =  THIS i j k * OTHER p q
		 *
		 * */

		for(Integer i = 0; i<res.longueur();  i++) {
			Liste<Integer> pos = res.getIndice(i);
			Liste<Integer> thispos = pos.getTo(this.ordre());
			Liste<Integer> otherpos = pos.getFrom(this.ordre());
			Double temp = this.getDouble(thispos) * other.getDouble(otherpos);
			res.setDouble(pos, temp);
		}

		return res;

    }
	 
	/**
	 * Contraction
	 * Transforme le tenseur Aijklmn en Ailmn = Aijjlmn
	 * si position = 1 (j)
	 * @param position
	 * @return
	 * @throws java.lang.Exception
	 */
	public Tenseur contraction(Integer position) throws Exception{
		if(position < 0 || position + 2 > this.ordre()) {
			throw new Exception("Contraction invalide : Position de la contraction " + position + " Ordre " + this.ordre());
		}

		if(this.dimensions.get(position) != this.dimensions.get(position+1)) {
			throw new Exception("Contraction invalide : Dimensions " + this.dimensions.get(position) + " et " + this.dimensions.get(position+1));
		}

		Integer longcontract = this.dimensions.get(position);
		Liste<Integer> dim = new Liste<Integer>();
		dim.addAll(this.dimensions);
		dim.removeElementAt(position);
		dim.removeElementAt(position);
		Tenseur res = new Tenseur(dim);

		for(Integer i = 0; i<res.longueur();  i++) {
			Liste<Integer> pos = res.getIndice(i);
			Liste<Integer> thispos = pos.getTo(position);
			Liste<Integer> otherpos = pos.getFrom(position);
			
			Double temp = 0.;
			for(Integer j=0;j<longcontract;j++ ) {
				Liste<Integer> prevpos = new Liste<Integer>();
				prevpos.addAll(thispos);
				prevpos.add(j);
				prevpos.add(j);
				prevpos.addAll(otherpos);
				
				temp += this.getDouble(prevpos);
			}
			res.setDouble(pos,temp);
			
		}

		return res;
    }
	
	public Tenseur contraction(Integer position, Integer contraction) throws Exception{

		if(contraction < 0 ) {
			throw new Exception("Contraction invalide : Ordre " + contraction);
		}
		
		Tenseur res = new Tenseur();
		res = (Tenseur) this.clone();
		
		for(Integer i=0; i<contraction; i++) {
			res= res.contraction(position-i);
		}
		return res;
    }
	
	/**
	 * 
	 * @param indicea
	 * @param indiceb
	 * @return
	 * @throws java.lang.Exception
	 */
	public Tenseur transposition(Integer indicea, Integer indiceb) throws Exception {
		if(indicea <0 || indicea >= this.ordre() || indiceb <0 || indiceb >= this.ordre() ) {
			throw new Exception("Transposition invalide ");
		}
		
		if(indicea == indiceb ) {
			return new Tenseur(this);
		}
		
		Liste<Integer> dim = new Liste<Integer>();
		dim.addAll(this.dimensions);
		dim.set(indicea, this.dimensions.get(indiceb));
		dim.set(indiceb, this.dimensions.get(indicea));
		Tenseur res = new Tenseur(dim);
		
		for(Integer i = 0; i<res.longueur();  i++) {
			Liste<Integer> pos = res.getIndice(i);
			Liste<Integer> thispos = res.getIndice(i);
			thispos.set(indicea, pos.get(indiceb));
			thispos.set(indiceb, pos.get(indicea));
			
			res.setDouble(pos,this.getDouble(thispos));
		}
		return res;
		
	}
	
	/**
	 * Multiplication terme a terme de tenseurs de meme ordre et meme dimensions
	 * @param other
	 * @return
	 * @throws java.lang.Exception
	 */
	public Tenseur multiplication(Tenseur other) throws Exception {
		if(other.dimensions.equals(this.dimensions)==false) {
			throw new Exception("Multiplication invalide ");
		}
		else {
			Tenseur res=new Tenseur(this.getDimensions());
			for(Integer i=0; i<res.longueur(); i++) {
				res.coefficients.set(i, this.coefficients.get(i) * other.coefficients.get(i) );
			}		
			return res;	
		}
	}
	
		/**
	 * Multiplication par un reel
	 * @param other
	 * @return
	 */
	public Tenseur multiplication(Double other)  {

		Tenseur res=new Tenseur(this.getDimensions());
		for(Integer i=0; i<res.longueur(); i++) {
			res.coefficients.set(i, this.coefficients.get(i) * other );
		}		
		return res;	

	}
	
	public Tenseur somme(Tenseur other) throws Exception {
		if(other.dimensions.equals(this.dimensions)==false) {
			throw new Exception("Somme invalide ");
		}
		else {
			Tenseur res=new Tenseur(this.getDimensions());
			for(Integer i=0; i<res.longueur(); i++) {
				res.coefficients.set(i, this.coefficients.get(i) + other.coefficients.get(i) );
			}		
			return res;	
		}
	}
	
	public Tenseur difference(Tenseur other) throws Exception {
		if(other.dimensions.equals(this.dimensions)==false) {
			throw new Exception("Difference invalide ");
		}
		else {
			Tenseur res=new Tenseur(this.getDimensions());
			for(Integer i=0; i<res.longueur(); i++) {
				res.coefficients.set(i, this.coefficients.get(i) - other.coefficients.get(i) );
			}		
			return res;	
		}
	}
	
	public Tenseur oppose() throws Exception {
		Tenseur res=new Tenseur(this.getDimensions());
		for(Integer i=0; i<res.longueur(); i++) {
			res.coefficients.set(i, -this.coefficients.get(i) );
		}		
		return res;	
	}
	
	public Double norme() {
		try {
			Tenseur res = this.produitcontracte(this, this.ordre());
			return Math.sqrt(res.getDouble(Scalaire.i));
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	public Tenseur normaliser() {
		try {
			Double norme = this.norme();
			return this.multiplication(1./norme);
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	public Double distance(Tenseur other) {
		try {
			
			return this.difference(other).norme();
		} catch (Exception ex) {
			Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
			return null;
		}
	}
	
	public Scalaire scalaireValue() {
		return new Scalaire(this);
	}
	
	public Vecteur vecteurValue() {
		return new Vecteur(this);
	}
	
	public Matrice matriceValue() {
		return new Matrice(this);
	}

	public Element toJdom(String Nom, String Role) {
		Element c = new Element("Tenseur") ;
		c.setAttribute("Role", Role);
		c.setAttribute("Nom", Nom);

		c.addContent(this.dimensions.toJdom("","Dimensions"));
		c.addContent(this.coefficients.toJdom("","Coefficients"));

		return c;
	}


	public Tenseur fromJdom(Element element) {
		if(element == null) {
			return null;
		}
		else {
			try {
				String ref = element.getAttributeValue("Reference","Inconnu");
				if(ref.compareTo("Inconnu")!=0) {
					System.out.println("reference");
					Iterator el = element.getDocument().getDescendants(new ElementFilter("Tenseur"));
					while(el.hasNext()) {
						Element actuel = (Element)el.next();
						String nomEl = actuel.getAttributeValue("Nom", "Inconnu");
						if(nomEl.compareTo(ref)==0) {
							return this.fromJdom(actuel);
						}
					}
				}
				
				Tenseur res = new Tenseur();
				for (Element fils : (List<Element>) element.getChildren()) {
					String role = fils.getAttributeValue("Role", "Inconnu").toLowerCase(Locale.ENGLISH);
					if (role.contains("dimensions")) {
						res.setDimensions(res.getDimensions().fromJdom(fils));
					}
					if (role.contains("coefficients")) {
						res.setCoefficients(res.getCoefficients().fromJdom(fils));
					}
				}
				return res;

			} catch (Exception ex) {
				Logger.getLogger("Journal").log(Level.SEVERE, null, ex);
				return null;
			}
		}
	}
	

	
}