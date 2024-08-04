package extended;

public class MaterialFactory {
	
	public RawNoodle supplyRawNoodle()
	{
		return new RawNoodle();
	}

	public SauceNoodle supplySauceNoodle()
	{
		return new SauceNoodle();
	}

}
