package extended;
import org.junit.*;

public class Customer {
	public void order1() {
		NoodleStore store = new ShanXiNoodleStore();
		store.orderNoodle(Noodle.NOODLE_TYPE.EGG_NOODLE, false);
    }
	public void order2() {
		NoodleStore store = new SiChuanNoodleStore();
		store.orderNoodle(Noodle.NOODLE_TYPE.SEAFOOD_NOODLE, true);		
	}
	public void order3() {
		DependencyNoodleStore store = new DependencyNoodleStore();
		store.orderNoodle("ShanXi", Noodle.NOODLE_TYPE.SEAFOOD_NOODLE, true);		
	}
	
//	public static void main(String[] args) {
//		Customer customer = new Customer();
//		customer.order1();
//		customer.order2();
//		customer.order3();
//	}
	
	@Before
	public void setup() {

	}
	
	@Test
	public void ShanXiEggNoodle() {
		NoodleStore store = new ShanXiNoodleStore();
		store.orderNoodle(Noodle.NOODLE_TYPE.EGG_NOODLE, false);
	}
	
	@Test 
	public void SiChuanSeafoodNoodle() {
		NoodleStore store = new SiChuanNoodleStore();
		store.orderNoodle(Noodle.NOODLE_TYPE.SEAFOOD_NOODLE, true);	
	}
	
}
