package extended;

import extended.Noodle.NOODLE_TYPE;

public class DependencyNoodleStore {
	public Noodle orderNoodle(String style, NOODLE_TYPE type, boolean here)
	{
		Noodle noodle = null;

		if (style.equals("SiChuan"))
		{
			if (type == Noodle.NOODLE_TYPE.SEAFOOD_NOODLE)
				noodle = new SiChuanSeafoodNoodle();
			
			else if (type == Noodle.NOODLE_TYPE.EGG_NOODLE)
				noodle = new SiChuanEggNoodle();
			
			else if (type == Noodle.NOODLE_TYPE.BEEF_NOODLE)
				noodle = new SiChuanBeefNoodle();
		}
		else if (style == ("ShanXi"))
		{
			if (type == Noodle.NOODLE_TYPE.SEAFOOD_NOODLE)
				noodle = new ShanXiSeafoodNoodle();
			
			else if (type == Noodle.NOODLE_TYPE.EGG_NOODLE)
				noodle = new ShanXiEggNoodle();
			
			else if (type == Noodle.NOODLE_TYPE.BEEF_NOODLE)
				noodle = new ShanXiBeefNoodle();
		}
		
		noodle.prepare(null);
		noodle.boil();
		noodle.pack(here);
		
		return noodle;
	}
}
