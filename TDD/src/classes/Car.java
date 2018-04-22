package classes;

public class Car {

public String type; //follower, leader, mid

public PS4Service ps4;
public V2V v2v;

public Car (V2V v2v,String type){
	this.type=type;
	this.v2v=v2v;
	this.ps4=new PS4Service(this);
}

}
