package classes;

public class PS4Service {
	Car car;
	public PS4Service(Car c){
		this.car=c;
	}
	public void turn (){
		car.v2v.turn();
	}

	public void goForward(){
		car.v2v.move();
	}
}
