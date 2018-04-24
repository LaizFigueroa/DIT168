package classes;

public class Ultrasonic {
private int [] dists;
private int i=0;

	public Ultrasonic (int [] dists){
		this.dists=dists;
	}
	
	public int getDistance(){
		int temp = dists[i];	
		i++;
		return temp;
	}
	
}
