package runnable;

import extended.*;

public class Main {
	static void NoddleStoreTest() {
		Customer customer = new Customer();
		customer.order1();
		customer.order2();
		customer.order3();
	}
	
	public static void main(String[] args) {
		NoddleStoreTest();
	}
	
}
