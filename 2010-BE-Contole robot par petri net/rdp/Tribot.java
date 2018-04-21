package rdp;

import lejos.nxt.LightSensor;
import lejos.nxt.Motor;
import lejos.nxt.SensorPort;
import lejos.nxt.Sound;
import lejos.nxt.SoundSensor;
import lejos.nxt.TouchSensor;
import lejos.nxt.UltrasonicSensor;

/**
 * Cette classe représente le robot modèle Tribot. Elle décrit les actions réalisables par le robot.
 * 
 * @author Yannick BISIAUX
 *
 */
public class Tribot {
	
	//private static Tribot INSTANCE;
	private static int ROTATION_DEMI_TOUR = 370;
	private static int ANGLE_PINCE = 80;
	private static int VITESSE_ROTATION = 250;
	private static int VITESSE_PINCE = 50;
	
	//private Monitoring monitoring;
	//private MajCapteur majCapteur;
	private GestionnaireAbonnement abonnements;
	
	private TouchSensor touchSensor;
	private SoundSensor soundSensor;
	private LightSensor lightSensor;
	private UltrasonicSensor ultrasonicSensor;
	
	protected volatile int[] valeurCapteur;
	
	private int n = -1;
	
	public Tribot(){
		//majCapteur = new MajCapteur(this);
		abonnements = new GestionnaireAbonnement(this);
	}
	
	public void init(){
		valeurCapteur = new int[4];
		touchSensor = new TouchSensor(SensorPort.S4);
		soundSensor = new SoundSensor(SensorPort.S2);
		lightSensor = new LightSensor(SensorPort.S3);
		ultrasonicSensor = new UltrasonicSensor(SensorPort.S1);
		
		//majCapteur.start();
	}
	
	public void refreshCapteurs(){
		valeurCapteur[0] = (touchSensor.isPressed()) ? 1 : 0;
		valeurCapteur[1] = soundSensor.readValue();
		valeurCapteur[2] = lightSensor.readValue();
		valeurCapteur[3] = ultrasonicSensor.getDistance();
	}
	
	/*public void arreterMaj(){
		this.majCapteur.arreter();
	}*/
	
	public int getValeur(int indexCapteur){
		return valeurCapteur[indexCapteur];
	}
	
	public int[] getValeurs(){
		return valeurCapteur;
	}
	
	public GestionnaireAbonnement getAbonnements(){
		return this.abonnements;
	}
	
	public void executerAction(int action, int parametre){
		if (action == NomAction.AVANCER.ordinal()){
			avancer(parametre);
		} else if (action == NomAction.RECULER.ordinal()){
			reculer(parametre);
		} else if (action == NomAction.TOURNER_GAUCHE.ordinal()){
			tournerGauche(parametre);
		} else if (action == NomAction.TOURNER_DROITE.ordinal()){
			tournerDroite(parametre);
		} else if (action == NomAction.STOP.ordinal()){
			freiner();
		} else if (action == NomAction.OUVRIR_PINCE.ordinal()){
			ouvrirPince();
		} else if (action == NomAction.FERMER_PINCE.ordinal()){
			fermerPince();
		} else if (action == NomAction.JOUER_TON.ordinal()){
			jouerSon(parametre);
		}  else if (action == NomAction.BIPER.ordinal()){
			biper();
		} else {
			System.out.println("Action non prise en compte");
		}
	}
	
	public void avancer(int n){
		System.out.println("Avancer");
		Motor.B.setSpeed(n);
		Motor.C.setSpeed(n);
		Motor.B.forward();
		Motor.C.forward();
	}
	
	public void reculer(int n){
		System.out.println("Reculer");
		Motor.B.setSpeed(n);
		Motor.C.setSpeed(n);
		Motor.B.backward();
		Motor.C.backward();
	}
	
	public void tournerGauche(){
		System.out.println("Tour gauche");
		Motor.B.setSpeed(VITESSE_ROTATION);
		Motor.C.setSpeed(VITESSE_ROTATION);
		Motor.B.forward();
		Motor.C.backward();
	}
	
	public void tournerDroite(){
		System.out.println("Tour droite");
		Motor.B.setSpeed(VITESSE_ROTATION);
		Motor.C.setSpeed(VITESSE_ROTATION);
		Motor.B.backward();
		Motor.C.forward();
	}
	
	public void tournerGauche(int degres){
		System.out.println("Tour gauche");
		Motor.B.setSpeed(VITESSE_ROTATION);
		Motor.C.setSpeed(VITESSE_ROTATION);
		Motor.B.rotate((degres*ROTATION_DEMI_TOUR)/360, true);
		Motor.C.rotate((-degres*ROTATION_DEMI_TOUR)/360, true);
	}
	
	public void tournerDroite(int degres){
		System.out.println("Demi tour droite");
		Motor.B.setSpeed(VITESSE_ROTATION);
		Motor.C.setSpeed(VITESSE_ROTATION);
		Motor.B.rotate((-degres*ROTATION_DEMI_TOUR)/360, true);
		Motor.C.rotate((degres*ROTATION_DEMI_TOUR)/360, true);
	}
	
	public void demiTourGauche(){
		System.out.println("Demi tour gauche");
		Motor.B.setSpeed(VITESSE_ROTATION);
		Motor.C.setSpeed(VITESSE_ROTATION);
		Motor.B.rotate(ROTATION_DEMI_TOUR, true);
		Motor.C.rotate(-ROTATION_DEMI_TOUR, true);
	}
	
	public void demiTourDroite(){
		System.out.println("Demi tour droite");
		Motor.B.setSpeed(VITESSE_ROTATION);
		Motor.C.setSpeed(VITESSE_ROTATION);
		Motor.B.rotate(-ROTATION_DEMI_TOUR, true);
		Motor.C.rotate(ROTATION_DEMI_TOUR, true);
	}
	
	public void freiner(){
		System.out.println("Freiner");
		Motor.B.stop();
		Motor.C.stop();
	}
	
	public void ouvrirPince(){
		System.out.println("Ouvrir pince");
		Motor.A.setSpeed(VITESSE_PINCE);
		Motor.A.rotateTo(ANGLE_PINCE);
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {

		}
	}
	
	public void fermerPince(){
		System.out.println("Fermer pince");
		Motor.A.setSpeed(VITESSE_PINCE);
		Motor.A.rotateTo(-1);
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {

		}
	}
	
	public void jouerSon(int freq){
		System.out.println("Jouer son");
		Sound.playTone(freq, 1000);
	}
	
	public void biper(){
		System.out.println("Bipper");
		Sound.beep();
	}
	
	public void afficher(String str){
		System.out.println(str);
	}
	
	@Deprecated
	public void prendreDecision(){
		int sound = this.soundSensor.readValue();
		System.out.println(sound);
		if (touchSensor.isPressed()){
			n=50;
			freiner();
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {

			}
		}
		if (n==0){
			if (sound>30){
				this.ouvrirPince();
			} else {
				n = -1;
			}
		}
		if(n>0){
			if (n<50){
				this.avancer(360);
			} else if (n<60){
				this.reculer(200);
			} else if (n==60){
				this.freiner();
				this.fermerPince();
				this.demiTourGauche();
				try {
					Thread.sleep(2000);
				} catch (InterruptedException e) {

				}
			} else if (n<70){
				this.avancer(700);
			} else {
				//monitoring.setFinProgramme();
			}
		}
		n++;
	}
	
	public static void main(String[] args) {
		//Tribot.initStatic();
		//Tribot.getInstance().init();
		//Tribot tribot = new Tribot();
		//tribot.init();
	}
}
