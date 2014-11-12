public class CTest {
	public static void main (String[] args) {
		CTest c = new CTest();
		//c.GetName2();
		//System.out.println(c.GetName1());
		System.out.println("Java Run success");
	}

	private char[] GetName() {
		String str = new String("Lester");
		System.out.println(str);
		return str.toCharArray();
	}
	void PutName(char[] name) {
		String str = new String(name);
		System.out.println("Received Name " + str);
		System.out.println(name);
	}
	private char[] Paco(char[] s_in){
		String str = new String(s_in);
		str = str + "esto esta way";
		return str.toCharArray();
	}

}
	