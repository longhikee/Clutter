package extended;

public class SiChuanNoodleStore extends NoodleStore {
	public SiChuanNoodleStore() {
		super(new SiChuanMaterialFactory());
		// TODO Auto-generated constructor stub
	}

	protected Noodle createNoodle(Noodle.NOODLE_TYPE type)
	{
		Noodle noodle = null;
		
		switch(type)
		{
		case SEAFOOD_NOODLE:	
			noodle = new SiChuanSeafoodNoodle();
			break;
			
		case EGG_NOODLE:	
			noodle = new SiChuanEggNoodle();
			break;
			
		case BEEF_NOODLE:
			noodle = new SiChuanBeefNoodle();
			break;
		}
		
		return noodle;
	}
}
