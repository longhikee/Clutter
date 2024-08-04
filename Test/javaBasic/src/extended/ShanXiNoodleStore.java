package extended;

public class ShanXiNoodleStore extends NoodleStore {
	public ShanXiNoodleStore() {
		super(new ShanXiMaterialFactory());
	}

	protected Noodle createNoodle(Noodle.NOODLE_TYPE type) {
		Noodle noodle = null;
		switch(type)
		{
		case SEAFOOD_NOODLE:	
			noodle = new ShanXiSeafoodNoodle();
			break;
		case EGG_NOODLE:	
			noodle = new ShanXiEggNoodle();
			break;
		case BEEF_NOODLE:
			noodle = new ShanXiBeefNoodle();
			break;
		}
		return noodle;
	}
}
