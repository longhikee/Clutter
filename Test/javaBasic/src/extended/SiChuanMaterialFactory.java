package extended;

public class SiChuanMaterialFactory extends MaterialFactory {
	@Override
	public RawNoodle supplyRawNoodle() {
		// TODO Auto-generated method stub
		return new ThinNoodle();
	}

	@Override
	public SauceNoodle supplySauceNoodle() {
		// TODO Auto-generated method stub
		return new SiChuanSauceNoodle();
	}
}
