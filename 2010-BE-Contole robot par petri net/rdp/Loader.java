package rdp;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Loader {
	//static FileReader lecteur;

	
	
	
	public static Player load(File file) throws IOException{
		PlayerLoader player = new PlayerLoader();
		TransitionLoader transition = new TransitionLoader();
		ConditionLoader condition = new ConditionLoader();
		ActionLoader action = new ActionLoader();
		List<Integer> Nombre= new ArrayList<Integer>();
		
		FileInputStream fis = new FileInputStream(file);
		BufferedInputStream lecteur = new BufferedInputStream(fis);
		
		
		char i;
		int nbplaces;
		int h=0;
		double entier;
		int a;
		double z=10;
		double l;
		int FlagEndOfFile=0;
		int c=0;
		
		//*******Marquage initial
		Nombre.clear();
		entier=0;
		h=lecteur.read();
		while (h>47 & h<58){
			Nombre.add(h-48);
			h=lecteur.read();
		}
		for(int k=0;k<Nombre.size();k++){
			l = (double) k;
			entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
		}
		nbplaces=(int) entier;
		int marquage[]=new int[nbplaces];
		
		
		while (h!=10){
			Nombre.clear();
			entier=0;
			h=lecteur.read();
			while (h>47 & h<58){
				Nombre.add(h-48);
				h=lecteur.read();
			}
			for(int k=0;k<Nombre.size();k++){
				l = (double) k;
				entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
			}
			marquage[c]=(int) entier;
			c++;
		}
		player.setMarking(marquage);
		
		/*entier=0;
		for (int k=0;k<marquage.length;k++){
			l = (double) k;
			entier=entier+(marquage[nbplaces-1-k]*Math.pow(z,l));
		}
		System.out.println("le marquage initial est: " + (int)entier);*/
		
		//*******fin Initialisation marquage
		
		
		
		//******* debut de la boucle de lecture des lignes de transitions**
		while (FlagEndOfFile!=-1) {
			h=lecteur.read();
			i= (char) h;
			Nombre.clear();
			entier=0;
			h=lecteur.read();
			while (h>47 & h<58){
				Nombre.add(h-48);
				h=lecteur.read();
			}
			for(int k=0;k<Nombre.size();k++){
				l = (double) k;
				entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
			}
			System.out.println("NumŽro de transition= " + i + (int)entier);
			i= ':';
			
			
			//********Lecture de l'etat pre-transition********/
			for (int s=0;s<marquage.length;s++)
				marquage[s]=0;
			while (i!=';'){
				
				h=lecteur.read();
				i= (char) h;
				if (i!='p')
					System.out.println("erreur fromat fichier");
				else {
					a=0;
					Nombre.clear();
					entier=0;
					h=lecteur.read();
					while (h>47 & h<58){
						Nombre.add(h-48);
						h=lecteur.read();
					}
					for(int k=0;k<Nombre.size();k++){
						l = (double) k;
						entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
					}
					a= (int) entier;
					i= (char) h;
					if (i!='*')
						System.out.println("erreur fromat fichier");
					else {
						Nombre.clear();
						entier=0;
						h=lecteur.read();
						while (h>47 & h<58){
							Nombre.add(h-48);
							h=lecteur.read();
						}
						for(int k=0;k<Nombre.size();k++){l = (double) k;
						entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
						}
						marquage[a]=(int)entier;
						//System.out.println(" pre place = p " + a + '*'+ (int)entier);
					}
				}
				i= (char) h;
			}
			transition.setInput(marquage);
			//System.out.println("Caractere courant= " + i );
			
			//**********Fin de lecture de l'etat pre-transition*********/
			
			
			
			//**************Lecture des conditions***************/
			i='/';
			while (i!=';' ){
				
				//**Lecture du numero de capteur**/
				int cap=0;
				int op=0;
				Nombre.clear();
				entier=0;
				h=lecteur.read();
				while (h>47 & h<58){
					Nombre.add(h-48);
					h=lecteur.read();
				}
				for(int k=0;k<Nombre.size();k++){
					l = (double) k;
					entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
				}
				cap=(int) entier;
				
				
				//**lecture de l'operateur**/
				op=lecteur.read()-48;
				h=lecteur.read(); /*parsage de la virgule*/
				//**lecture du seuil**/
				Nombre.clear();
				entier=0;
				h=lecteur.read();
				while (h>47 & h<58){
					Nombre.add(h-48);
					h=lecteur.read();
				}
				for(int k=0;k<Nombre.size();k++){
					l = (double) k;
					entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
				}
				if (op!=0){
					condition.setSensor(cap);
					//System.out.println("NumŽro de capteur= " + cap);
					condition.setOperator(op);
					//System.out.println("NumŽro d'operateur= " + op);
					condition.setThreshold((int)entier);
					//System.out.println("seuil= " + (int)entier);
					transition.getConditions().add(condition);
				}
				
				i=(char) h;
			}
			//System.out.println("Caractere courant= " + i );
			//**************Fin de lecture des conditions***************/
			
			
			
			//********Lecture de l'etat post-transition********/
			for (int s=0;s<marquage.length;s++)
				marquage[s]=0;
			i='/';
			while (i!=';'){
				
				h=lecteur.read();
				i= (char) h;
				if (i!='p')
					System.out.println("erreur fromat fichier");
				else {
					a=0;
					Nombre.clear();
					entier=0;
					h=lecteur.read();
					while (h>47 & h<58){
						Nombre.add(h-48);
						h=lecteur.read();
					}
					for(int k=0;k<Nombre.size();k++){
						l = (double) k;
						entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
					}
					a= (int)entier;
					i= (char) h;
					if (i!='*')
						System.out.println("erreur fromat fichier");
					else {
						Nombre.clear();
						entier=0;
						h=lecteur.read();
						while (h>47 & h<58){
							Nombre.add(h-48);
							h=lecteur.read();
						}
						for(int k=0;k<Nombre.size();k++){
							l = (double) k;
							entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
						}
						marquage[a]=(int)entier;
						//System.out.println(" post place = p " + a + '*'+ (int)entier);
					}
				}
				i= (char) h;
			}
			transition.setOutput(marquage);
			//System.out.println("Caractere courant= " + i );
			//**********Fin de lecture de l'etat post-transition*********
			
			
			
			
			
			//**************Lecture des actions*************** 
			i='/';
			while (i!=';' ){
				
				//**Lecture du numero de l'action
				int numAction=0;
				Nombre.clear();
				entier=0;
				h=lecteur.read();
				while (h>47 & h<58){
					Nombre.add(h-48);
					h=lecteur.read();
				}
				for(int k=0;k<Nombre.size();k++){
					l = (double) k;
					entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
				}
				numAction=(int) entier;
				
				
				//********lecture du parametre
				Nombre.clear();
				entier=0;
				h=lecteur.read();
				while (h>47 & h<58){
					Nombre.add(h-48);
					h=lecteur.read();
				}
				for(int k=0;k<Nombre.size();k++){
					l = (double) k;
					entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
				}
				if (numAction!=99){
					action.SetNumero(numAction);
					//System.out.println("numero action: "+ numAction);
					action.SetParametre((int)entier);
					//System.out.println("parametre action: "+ (int)entier);
					transition.getActions().add(action);
				}
				
				i=(char) h;
			}
			//**************Fin de lecture des actions***************
			
			
			
			//**************lecture Priorite****************************
			Nombre.clear();
			entier=0;
			h=lecteur.read();
			while (h>47 & h<58){
				Nombre.add(h-48);
				h=lecteur.read();
			}
			for(int k=0;k<Nombre.size();k++){
				l = (double) k;
				entier=entier+(Nombre.get(Nombre.size()-1-k)*Math.pow(z,l));
			}
			transition.setPriority((int)entier);
			//System.out.println(" priorite  " +(int)entier);
			//**************Fin lecture Priorite****************************
			
			
			player.getTransitions().add(transition);
			FlagEndOfFile=h;						
		}
		
		return player;
	}
}
