package classes;
import org.junit.Assert;

import org.junit.Test;

public class TestSuite {
Ultrasonic u1 = new Ultrasonic (new int []{25,30,12,17});
Ultrasonic u2 = new Ultrasonic (new int []{27,22,34,23});

  
	  
	  private Car follow1; 	  
	  private Car lead1; 
	 
	@Test
	public void Scenario1(){
		 follow1 = new Car(new V2V(u2,lead1,null),"follower");
		 lead1= new Car(new V2V(u1,null,follow1),"leader");
		
	  lead1.ps4.goForward();

	  lead1.ps4.turn();
	
	  lead1.ps4.goForward();
	
	  lead1.ps4.goForward();
	
	  Assert.assertTrue(follow1.v2v.posX==2);
	  Assert.assertTrue(follow1.v2v.posY==1);
	}
	
}
