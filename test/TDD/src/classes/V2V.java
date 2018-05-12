package classes;

public class V2V {
public boolean obstacle=false;

public Ultrasonic sensor;

public int posX;
public int posY;

public Car leader;
public Car follower;

	public V2V (Ultrasonic u,Car leader,Car follower){
		this.sensor=u;
		this.leader=leader;	
		this.follower=follower;
	}

    public int measure(){
    	return sensor.getDistance();
    }
    
	public void move (){
		int check=measure();
		if (check>=20 && obstacle==false){
			posX++;
			leaderStatus("move");
		}
		leaderStatus("stop");
	}
	
	public void turn (){
		int check=measure();
		if (check>=20){
			posX++;
			posY++;
			leaderStatus("turn");
		}
		leaderStatus("stop");
	}
	
	public void receiveMsg(String msg){
		if (msg.equals("turn")){
			turn();
		}
		if (msg.equals("stop")){
			obstacle=true;
		}
		if (msg.equals("move")){
			move();
		}
	}
	
	public void leaderStatus(String msg){
		if (follower!=null)
		follower.v2v.receiveMsg(msg);		
	}
}
