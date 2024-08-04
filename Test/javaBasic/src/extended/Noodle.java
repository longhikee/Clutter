package extended;

public abstract class Noodle {
	private float price = 10.0f;
	
	public enum NOODLE_TYPE {
		EGG_NOODLE,
		SEAFOOD_NOODLE,
		BEEF_NOODLE
	};
	
//	public Noodle() {};
	
	public void prepare(MaterialFactory materialFactory)
	{
		System.out.println("Prepare with " + 
				materialFactory.supplyRawNoodle().toString() + ", " +
				materialFactory.supplySauceNoodle().toString());
	}
	
	public void boil()
	{
		System.out.println("Cooking with noodle with 8 mins ...");
	}
	
	public float getPrice()
	{
		return price;
	}
	
	public void pack(boolean here)
	{
		if (here)	
		{
			System.out.println("Pack the noodle with a bowl");
		}
		else
		{
			System.out.println("Pack the noodle with a box");
		}
	}

}
