package LanceurRayon.Objets;

import LanceurRayon.Util.Angle;
import LanceurRayon.Util.Geometrie.Vecteur;
import LanceurRayon.Util.JDomIO;


public interface ObjetDeScene extends JDomIO{
	
	public void translation(Vecteur direction) ;
		
	public void rotation(Vecteur origine , Angle a, Vecteur axe) ;
		
}
