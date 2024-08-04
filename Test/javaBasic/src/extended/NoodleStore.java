package extended;

import extended.Noodle.NOODLE_TYPE;

public class NoodleStore {
	private MaterialFactory materialFactory = null;

	public NoodleStore(MaterialFactory materialFactory) {
		this.materialFactory = materialFactory;
	}
	
	public NoodleStore() {
		this.materialFactory = new MaterialFactory();
	}
	
	public void setMaterialFactory(MaterialFactory materialFactory) {
		this.materialFactory = materialFactory;
	}
	
	public Noodle orderNoodle(Noodle.NOODLE_TYPE type, boolean here) {
		Noodle noodle = createNoodle(type);
		noodle.prepare(materialFactory);
		noodle.boil();
		noodle.pack(here);
		
		return noodle;
	}

	protected Noodle createNoodle(NOODLE_TYPE type) {
		Noodle noodle = null;		
		switch(type)
		{
		case SEAFOOD_NOODLE:	
			noodle = new SeafoodNoodle();
		
		case EGG_NOODLE:	
			noodle = new EggNoodle();
		
		case BEEF_NOODLE:
			noodle = new BeefNoodle();
		}
			
		return noodle;
	}
}
