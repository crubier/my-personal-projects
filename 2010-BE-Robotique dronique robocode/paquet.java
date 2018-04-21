package CrubiBot;

import java.awt.image.BufferedImage;
import java.io.Serializable;

public class paquet implements Serializable{
	private static final long serialVersionUID = 1L;
	public int[][] map;
	
	public paquet(BufferedImage bi) {
		map = new int [bi.getWidth()][bi.getHeight()];
		for(int j=0;j<bi.getHeight();j++) {
			for(int i=0;i<bi.getWidth();i++) {
				map[i][j]=bi.getRGB(i, j);
			}
		}
	}
	
	public BufferedImage decode() {
		BufferedImage res = new BufferedImage(map[0].length,map.length,BufferedImage.TYPE_INT_ARGB);
		for(int j=0;j<map.length;j++) {
			for(int i=0;i<map[0].length;i++) {
				res.setRGB(i, j, map[i][j]);
			}
		}
		return res;
	}
	
}
