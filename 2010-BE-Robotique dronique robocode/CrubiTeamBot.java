package CrubiBot;

import robocode.*;

import robocode.util.*;
import java.awt.geom.*;
import java.awt.image.*;

import java.awt.*;
import java.io.IOException;
import java.util.Vector;

public class CrubiTeamBot extends TeamRobot {

	private class Mode {

		public static final int EXPLORE = 1;
		public static final int ATTACK = 2;
		public static final int TRACK = 3;

		private int mode = EXPLORE;
		private int step = 0;
		private int nextmode = EXPLORE;
		private int nextstep = 0;

		private int prioritylast = 0;

		private Point2D.Double target;
		private Point2D.Double targetVelocity;
		private long timePosition = 0;

		private BufferedImage map;
		private Graphics2D paintsheet;
		private double res;

		// to draw radar marks
		private Point2D.Double exPos;
		private Point2D.Double exRad;
		private Point2D.Double newPos;
		private Point2D.Double newRad;
		private long timetick = 0;

		public BufferedImage getMap() {
			return map;
		}

		public Mode(double xx, double yy) {
			res = 100.;
			map = new BufferedImage((int) (xx / res), (int) (yy / res), BufferedImage.TYPE_INT_ARGB);
			paintsheet = map.createGraphics();
			paintsheet.setColor(Color.BLACK);
			paintsheet.fillRect(0, 0, (int) (xx / res), (int) (yy / res));
			exPos = new Point2D.Double(getX(), getY());
			exRad = new Point2D.Double(getX() + Rules.RADAR_SCAN_RADIUS * Math.sin(getRadarHeadingRadians()), getY() + Rules.RADAR_SCAN_RADIUS *Math.cos(getRadarHeadingRadians()));
			newPos = new Point2D.Double(getX(), getY());
			newRad = new Point2D.Double(getX() + Rules.RADAR_SCAN_RADIUS * Math.sin(getRadarHeadingRadians()), getY() + Rules.RADAR_SCAN_RADIUS *Math.cos(getRadarHeadingRadians()));

		}

		public void tick() {
			if (this.mode != this.nextmode || this.step != this.nextstep) {
				this.prioritylast = 0;
				if (this.mode != this.nextmode)
					this.nextstep = 0;
				this.mode = this.nextmode;
				// ////////////////////////////////////////////
				// this.mode = EXPLORE;
				// ////////////////////////////////////////
				this.step = this.nextstep;
				switch (this.get()) {
				case Mode.ATTACK:
					paintsheet.setColor(new Color(255, 0, 0));
					System.out.println("ATTACK  " + this.step);
					break;
				case Mode.EXPLORE:
					paintsheet.setColor(new Color(0, 255, 0));
					System.out.println("EXPLORE " + this.step);
					break;
				case Mode.TRACK:
					paintsheet.setColor(new Color(0, 0, 255));
					System.out.println("TRACK   " + this.step);
					break;
				}

				// paintsheet.fillOval((int)(this.target.getX()/res)-4,
				// (int)(this.target.getY()/res)-4, 8,8);

				newPos = new Point2D.Double(getX(), getY());
				newRad = new Point2D.Double(getX() + Rules.RADAR_SCAN_RADIUS * Math.sin(getRadarHeadingRadians()), getY() + Rules.RADAR_SCAN_RADIUS * Math.cos(getRadarHeadingRadians()));

				paintsheet.setColor(new Color(0, 0, 0, (int) (255. * (1 - Math.exp(0.0001 * (double) (timetick - getTime()))))));
				paintsheet.fillRect(0, 0, (int) (getBattleFieldWidth() / res), (int) (getBattleFieldHeight() / res));

				paintsheet.setColor(Color.WHITE);

				double istep = 1. / (Math.max(newPos.distance(exPos), newRad.distance(exRad)) * res);

				for (double i = 0.; i <= 1.; i += istep) {
					paintsheet.drawLine((int) ((i * newPos.getX() + (1. - i) * exPos.getX()) / res), (int) ((i * newPos.getY() + (1. - i) * exPos.getY()) / res), (int) ((i * newRad.getX() + (1. - i) * exRad.getX()) / res), (int) ((i * newRad.getY() + (1. - i) * exRad.getY()) / res));
				}

				exPos = newPos;
				exRad = newRad;
				timetick = getTime();

				paquet pak = new paquet(map);
				try {
					broadcastMessage(pak);
				}
				catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}

		public void signalScan() {
			paintsheet.setColor(Color.WHITE);
			paintsheet.fillOval((int) ((getX() - Rules.RADAR_SCAN_RADIUS) / res), (int) ((getY() - Rules.RADAR_SCAN_RADIUS) / res), (int) ((2. * Rules.RADAR_SCAN_RADIUS) / res), (int) ((2. * Rules.RADAR_SCAN_RADIUS) / res));
			
			paquet pak = new paquet(map);
			try {
				broadcastMessage(pak);
			}
			catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		public void findTarget() {
			int nbcases = this.map.getWidth();
			int min = 256;
			int max = 0;

			Vector<Point2D> potentialtargets = new Vector<Point2D>();

			BufferedImage tempmap;
			Graphics2D temppaintsheet;
			tempmap = new BufferedImage(nbcases, nbcases, BufferedImage.TYPE_INT_ARGB);
			temppaintsheet = tempmap.createGraphics();
			temppaintsheet.drawImage(map, 0, 0, tempmap.getWidth(), tempmap.getHeight(), 0, 0, map.getWidth(), map.getHeight(), null);

			// //
			// paintsheet.drawImage(tempmap, 0, 0, map.getWidth(),
			// map.getHeight(), 0, 0, tempmap.getWidth(), tempmap.getHeight(),
			// null);

			for (int j = 0; j < nbcases; j++) {
				for (int i = 0; i < nbcases; i++) {
					Color c = new Color(map.getRGB(i, j));
					if (c.getRed() <= min) {
						if (c.getRed() < min) {
							min = c.getRed();
							potentialtargets = new Vector<Point2D>();
						}
						potentialtargets.add(new Point2D.Double(((double) (i) / (double) nbcases) * getBattleFieldWidth(), ((double) (j) / (double) nbcases) * getBattleFieldHeight()));
					}
					if (c.getRed() > max) {
						max = c.getRed();
					}
				}
			}

			int choix = Utils.getRandom().nextInt(potentialtargets.size());
			Point2D.Double nexttg = new Point2D.Double(potentialtargets.get(choix).getX() + Utils.getRandom().nextDouble() * (getBattleFieldWidth() / (double) nbcases), potentialtargets.get(choix).getY() + Utils.getRandom().nextDouble() * (getBattleFieldHeight() / (double) nbcases));

			System.out.println("STILL " + (100. * potentialtargets.size() / ((double) nbcases * nbcases)) + "% TO EXPLORE...");

			if (max <= 20 || this.target.distance(nexttg) <= 40) {
				// //System.out.println("RANDOMM");
				this.setTarget(new Point2D.Double(Utils.getRandom().nextDouble() * (getBattleFieldWidth() - 36.) + 18., Utils.getRandom().nextDouble() * (getBattleFieldHeight() - 36.) + 18.));
			}
			else {
				this.setTarget(nexttg);
			}

		}

		public Point2D.Double getTargetVelocity() {
			return targetVelocity;
		}

		public void setTargetVelocity(Point2D.Double targetVelocity) {
			this.targetVelocity = targetVelocity;
		}

		public void set(int nm, int prio) {
			if (prio >= this.prioritylast) {
				this.nextmode = nm;
				this.prioritylast = prio;
			}
		}

		public int get() {
			return this.mode;
		}

		public void nextStep() {
			this.nextstep = this.step + 1;
		}

		public void initStep() {
			this.nextstep = 0;
		}

		public void setStep(int st) {
			this.nextstep = st;
		}

		public int getStep() {
			return this.step;
		}

		public Point2D.Double getTarget() {
			if (this.targetVelocity == null) {
				return this.target;
			}
			else {
				return new Point2D.Double(this.target.x + (getTime() - this.timePosition) * this.targetVelocity.x, this.target.y + (getTime() - this.timePosition) * this.targetVelocity.y);
			}
		}

		public void setTarget(Point2D.Double tg) {

			this.target = tg;
			this.targetVelocity = null;
			this.timePosition = getTime();
		}
	}

	private Mode mode;

	double oldEnemyHeading = 0;

	public void run() {

		mode = new Mode(getBattleFieldWidth(), getBattleFieldHeight());
		mode.set(Mode.EXPLORE, 1000);
		mode.tick();
		mode.target = new Point2D.Double(getX(), getY());

		setBodyColor(Color.red);
		setGunColor(Color.red);
		setRadarColor(Color.red);
		setScanColor(Color.white);

		setAdjustRadarForGunTurn(true);
		setAdjustRadarForRobotTurn(true);
		setAdjustGunForRobotTurn(true);

		// turnRadarRightRadians(Double.POSITIVE_INFINITY);
		do {
			// //System.out.println("Run");

			mode.tick();

			switch (mode.get()) {
			case Mode.ATTACK:
				switch (mode.getStep()) {

				case 20:
					mode.set(Mode.TRACK, 10);
					break;

				default:

					stop(false);
					// //System.out.println("CALC");
					double bulletPower = Math.min(3.0, getEnergy());
					double myX = getX();
					double myY = getY();

					double enemyX = mode.getTarget().getX();
					double enemyY = mode.getTarget().getY();

					double absoluteBearing = Math.atan2(enemyX - getX(), enemyY - getY());

					double enemyVX;
					double enemyVY;
					if (mode.getTargetVelocity() != null) {
						enemyVX = mode.getTargetVelocity().getX();
						enemyVY = mode.getTargetVelocity().getY();
					}
					else {
						enemyVX = 0.;
						enemyVY = 0.;
					}
					double enemyHeading = Math.atan2(enemyVX, enemyVY);
					double enemyHeadingChange = enemyHeading - oldEnemyHeading;
					double enemyVelocity = Point2D.distance(0, 0, enemyVX, enemyVY);
					oldEnemyHeading = enemyHeading;

					double deltaTime = 0;
					double battleFieldHeight = getBattleFieldHeight();
					double battleFieldWidth = getBattleFieldWidth();
					double predictedX = enemyX;
					double predictedY = enemyY;

					int fire = 1;

					while ((++deltaTime) * (20.0 - 3.0 * bulletPower) < Point2D.Double.distance(myX, myY, predictedX, predictedY)) {
						predictedX += Math.sin(enemyHeading) * enemyVelocity;
						predictedY += Math.cos(enemyHeading) * enemyVelocity;
						enemyHeading += enemyHeadingChange;
						if (predictedX < 17.0 || predictedY < 17.0 || predictedX > battleFieldWidth - 17.0 || predictedY > battleFieldHeight - 17.0) {

							predictedX = Math.min(Math.max(18.0, predictedX), battleFieldWidth - 18.0);
							predictedY = Math.min(Math.max(18.0, predictedY), battleFieldHeight - 18.0);
							mode.set(Mode.TRACK, 10);
							fire = 0;
							// On ne tire pas si la position predite sors du
							// champ
							break;
						}
					}
					double theta = Utils.normalAbsoluteAngle(Math.atan2(predictedX - getX(), predictedY - getY()));
					// //System.out.println("AIM");
					turnRadarRightRadians(Utils.normalRelativeAngle(absoluteBearing - getRadarHeadingRadians()));
					turnGunRightRadians(Utils.normalRelativeAngle(theta - getGunHeadingRadians()));

					if (getGunHeat() > 0)
						fire = 0; // On ne tire pas si le gun est chaud
					if (mode.getStep() < 3)
						fire = 0; // On ne tire que lorsqu'on a bien ajusté la
									// cible a plusieurs reprises

					if (fire != 0) {
						// //System.out.println("FIRE");
						fire(3);
						mode.nextStep();
					}
					else {
						scan();
						mode.nextStep();
					}
					break;

				}
				break;

			case Mode.EXPLORE:

				switch (mode.getStep()) {
				case 0:
					stop(false);
					turnRadarRightRadians(((double) (Utils.getRandom().nextInt(2) * 2 - 1)) * 2. * Math.PI);
					mode.signalScan();
					mode.findTarget();

					mode.nextStep();
					break;
				case 1:
					turnRightRadians(Utils.normalRelativeAngle(Math.atan2(mode.getTarget().getX() - getX(), mode.getTarget().getY() - getY()) - getHeadingRadians()));
					turnRadarRightRadians(Utils.normalRelativeAngle((Math.PI * Utils.getRandom().nextInt(2) + Math.PI / 2.) + Math.atan2(mode.getTarget().getX() - getX(), mode.getTarget().getY() - getY()) - getRadarHeadingRadians()));
					mode.nextStep();
					break;
				case 2:
					ahead(mode.getTarget().distance(getX(), getY()));
					mode.nextStep();
					break;
				case 3:
					if (mode.getTarget().distance(getX(), getY()) < 30) {

						mode.initStep();
					}
					else {
						execute();
					}
					break;

				default:
					break;
				}

				break;

			case Mode.TRACK:
				switch (mode.getStep()) {
				case 0:
					stop(false);
					turnRightRadians(1 * Utils.normalRelativeAngle((Math.PI * Utils.getRandom().nextInt(2) + Math.PI / 2.) + Math.atan2(mode.getTarget().getX() - getX(), mode.getTarget().getY() - getY()) - getRadarHeadingRadians()));

					double strafe = 200. * (Utils.getRandom().nextDouble() + 0.8) * (double) (Utils.getRandom().nextInt(2) * 2 - 1);
					double predictedX = getX() + strafe * Math.sin(getHeadingRadians());
					double predictedY = getY() + strafe * Math.cos(getHeadingRadians());
					if (!(predictedX < 19.0 || predictedY < 19.0 || predictedX > getBattleFieldWidth() - 19.0 || predictedY > getBattleFieldHeight() - 19.0)) {
						ahead(strafe);
					}

					turnRadarRightRadians(1 * Utils.normalRelativeAngle(Math.atan2(mode.getTarget().getX() - getX(), mode.getTarget().getY() - getY()) - getRadarHeadingRadians()));

					mode.nextStep();
					break;
				case 1:
					if (Math.abs(getRadarTurnRemainingRadians()) > 0.005) {
						execute();
					}
					else {
						mode.nextStep();
					}
					break;
				case 2:
					turnRadarRightRadians(((double) (Utils.getRandom().nextInt(2) * 2 - 1)) * 2. * Math.PI);
					mode.signalScan();
					mode.nextStep();
					break;
				case 3:
					mode.set(Mode.EXPLORE, 10);
					scan();
					break;

				default:
					break;
				}

				break;

			default:
				break;

			}
			// scan();
			execute();

		}
		while (true);
	}

	public void onScannedRobot(ScannedRobotEvent e) {
		System.out.println("ScannedRobot");

		if (!isTeammate(e.getName())) {

			double absoluteBearing = getHeadingRadians() + e.getBearingRadians();
			double enemyX = getX() + e.getDistance() * Math.sin(absoluteBearing);
			double enemyY = getY() + e.getDistance() * Math.cos(absoluteBearing);

			double enemyHeading = e.getHeadingRadians();
			double enemyVX = e.getVelocity() * Math.sin(enemyHeading);
			double enemyVY = e.getVelocity() * Math.cos(enemyHeading);

			switch (mode.get()) {
			case Mode.EXPLORE:
				mode.setTarget(new Point2D.Double(enemyX, enemyY));
				mode.setTargetVelocity(new Point2D.Double(enemyVX, enemyVY));
				mode.set(Mode.ATTACK, 5);
				stop(false);
				break;
			case Mode.ATTACK:
				mode.setTarget(new Point2D.Double(enemyX, enemyY));
				mode.setTargetVelocity(new Point2D.Double(enemyVX, enemyVY));
				// mode.initStep();
				break;
			case Mode.TRACK:
				mode.setTarget(new Point2D.Double(enemyX, enemyY));
				mode.setTargetVelocity(new Point2D.Double(enemyVX, enemyVY));
				mode.set(Mode.ATTACK, 5);
				break;

			default:
				break;
			}
		}
	}

	public void onHitByBullet(HitByBulletEvent e) {
		System.out.println("HitByBullet");

		double absoluteBearing = e.getHeadingRadians() + Math.PI;
		double enemyX = getX() + 2000 * Math.sin(absoluteBearing);
		double enemyY = getY() + 2000 * Math.cos(absoluteBearing);

		switch (mode.get()) {
		case Mode.EXPLORE:
		case Mode.ATTACK:
			mode.setTarget(new Point2D.Double(enemyX, enemyY));
			mode.setTargetVelocity(null);
			mode.set(Mode.TRACK, 20);
			stop(false);
			break;

		case Mode.TRACK:
			break;
		}
	}

	public void onBulletHit(BulletHitEvent e) {
		System.out.println("BulletHit");
		switch (mode.get()) {
		case Mode.EXPLORE:
		case Mode.ATTACK:
		case Mode.TRACK:
			if (e.getEnergy() <= 0)
				mode.set(Mode.EXPLORE, 5);
			break;
		}
	}

	public void onHitRobot(HitRobotEvent e) {
		System.out.println("HitRobot");
		if (!isTeammate(e.getName())) {
			double absoluteBearing = e.getBearingRadians() + getHeadingRadians();
			double enemyX = getX() + 2000 * Math.sin(absoluteBearing);
			double enemyY = getY() + 2000 * Math.cos(absoluteBearing);

			double enemyVX = 0;
			double enemyVY = 0;

			switch (mode.get()) {
			case Mode.EXPLORE:
				mode.setTarget(new Point2D.Double(enemyX, enemyY));
				mode.setTargetVelocity(new Point2D.Double(enemyVX, enemyVY));
				mode.set(Mode.TRACK, 20);
				break;
			case Mode.ATTACK:
			case Mode.TRACK:
				break;
			}
		}
		else {
			mode.set(Mode.TRACK, 20);
		}
	}

	public void onRobotHitWall(HitWallEvent e) {
		System.out.println("HitWall");
		switch (mode.get()) {
		case Mode.EXPLORE:
		case Mode.ATTACK:
		case Mode.TRACK:
			// mode.setMode(Mode.EXPLORE);
			break;
		}
	}

	public void onPaint(Graphics2D g) {

		int res = (int) mode.res;
		for (int i = 0; i < mode.getMap().getWidth(); i++) {
			for (int j = 0; j < mode.getMap().getHeight(); j++) {
				Color dupix = new Color(mode.map.getRGB(i, j));
				Color bobix = new Color(0, 0, 0, 255 - dupix.getRed());
				g.setColor(bobix);
				g.fillRect(i * res, j * res, res, res);
			}
		}

		switch (mode.get()) {
		case Mode.EXPLORE:
			g.setColor(new Color(0, 255, 0, 191));
			g.setStroke(new BasicStroke(20));
			g.drawOval((int) mode.getTarget().getX() - 40, (int) mode.getTarget().getY() - 40, 80, 80);
			break;
		case Mode.ATTACK:
			g.setColor(new Color(255, 0, 0, 191));
			g.setStroke(new BasicStroke(20));
			double taille = mode.getStep() / 5. + 1.;
			g.drawOval((int) (mode.getTarget().getX() - 40. * taille), (int) (mode.getTarget().getY() - 40. * taille), (int) (80. * taille), (int) (80. * taille));
			g.drawLine((int) (mode.getTarget().getX()), (int) (mode.getTarget().getY() - 60. * taille), (int) (mode.getTarget().getX()), (int) (mode.getTarget().getY() + 60. * taille));
			g.drawLine((int) (mode.getTarget().getX() - 60. * taille), (int) (mode.getTarget().getY()), (int) (mode.getTarget().getX() + 60. * taille), (int) (mode.getTarget().getY()));
			break;
		case Mode.TRACK:
			g.setColor(new Color(0, 0, 255, 191));
			g.setStroke(new BasicStroke(20));
			g.drawOval((int) mode.getTarget().getX() - 40, (int) mode.getTarget().getY() - 40, 80, 80);
			// g.drawLine((int) mode.getTarget().getX(), (int)
			// mode.getTarget().getY() - 60, (int) mode.getTarget().getX(),
			// (int) mode.getTarget().getY() + 60);
			// g.drawLine((int) mode.getTarget().getX() - 60, (int)
			// mode.getTarget().getY(), (int) mode.getTarget().getX() + 60,
			// (int) mode.getTarget().getY());
			break;
		}
	}

	public void onMessageReceived(MessageEvent e) {
		if (e.getMessage() instanceof paquet) {
			BufferedImage receivedimage = ((paquet) e.getMessage()).decode();
			mode.paintsheet.drawImage(receivedimage, 0, 0, mode.getMap().getWidth(), mode.getMap().getHeight(), 0, 0, receivedimage.getWidth(), receivedimage.getHeight(), null);
		}
	}
}
