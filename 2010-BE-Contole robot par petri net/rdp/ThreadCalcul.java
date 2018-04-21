package rdp;

import java.io.File;
import java.io.IOException;
import java.util.List;

import lejos.nxt.Button;
import lejos.nxt.Sound;
import lejos.util.TextMenu;
import rdp.debug.PlayerSimpleDebug;

/**
 * Thread principal assurant le déroulement du graphe de Petri.
 * 
 * @author Yannick BISIAUX
 *
 */
public class ThreadCalcul extends Thread {
	
	private static int PULSATION = 500;
	private static int LA = 440;
	
	public ThreadCalcul(){
		this.setPriority(2);
	}

	public void run(){
		Tribot tribot = new Tribot();
		tribot.init();
		
		File[] files = File.listFiles();
		String[] viewItems = new String[File.totalFiles];
		System.out.println(File.totalFiles);
		if (File.totalFiles>0){
			for (int i=0; i<File.totalFiles; i++){
				viewItems[i] = files[i].getName();
			}
		}
		
		TextMenu main = new TextMenu(viewItems, 1, "Fichier RDP :");
		int selection = main.select();
		File fs = files[selection];
		System.out.println(fs.getName());
		
		Player player;
		//player = PlayerSimpleDebug.load();
		try {
			player = Loader.load(fs);
		} catch (IOException e1) {
			System.out.println("Erreur de lecture");
			System.out.println("Utilisation player debug");
			player = PlayerSimpleDebug.load();
		}
		player.setRobot(tribot);
		tribot.refreshCapteurs();
		
		System.out.println("Fin Init");
		
		//Marche Imp
		jouerNote(392, 1.0f);
		jouerNote(392, 1.0f);
		jouerNote(392, 1.0f);
		jouerNote(311, 0.75f);
		jouerNote((int)(1.0595*LA), 0.25f);
		jouerNote(392, 1.0f);
		jouerNote(311, 0.75f);
		jouerNote((int)(1.0595*LA), 0.25f);
		jouerNote(392, 2.0f);
		
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
		}
		
		boolean arret = false;
		boolean joueurActif = true;
		while(!arret){
			arret = Button.ESCAPE.isPressed();
			
			if(joueurActif){
				List<Transition> trans = player.play();
				
				if(trans.size()!=0){
					System.out.println(player.markingToString());
					tribot.getAbonnements().abonnerTransitions(trans);
					joueurActif = false;
					System.out.println("Joueur Inactif");
				}
				
			} else {
				tribot.refreshCapteurs();
				Transition trans = tribot.getAbonnements().verifierAbonnements();
				if(trans != null){
					if(!player.tryToCross(trans)){
						arret = true;
						System.out.println("Erreur!!!");
					} else {
						joueurActif = true;
						System.out.println("Joueur Actif");
					}
				}
			}
			
		}
		System.out.println("Arret");
		try {
			Thread.sleep(5000);
		} catch (InterruptedException e) {
		}
	}
	
	public void jouerNote(int freq, float ratio){
		Sound.playTone(freq, (int)(ratio*PULSATION));
		try {
			Thread.sleep((int)(1.1*ratio*PULSATION));
		} catch (InterruptedException e) {
			
		}
	}
	
	public static void main(String[] args) {
		ThreadCalcul tc = new ThreadCalcul();
		tc.start();
	}
}
