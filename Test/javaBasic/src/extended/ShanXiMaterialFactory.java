package extended;

public class ShanXiMaterialFactory extends MaterialFactory {
	@Override
	public RawNoodle supplyRawNoodle() {
		// TODO Auto-generated method stub
		return new ThickNoodle();
	}

	@Override
	public SauceNoodle supplySauceNoodle() {
		// TODO Auto-generated method stub
		return new ShanXiSauceNoodle();
	}
}
