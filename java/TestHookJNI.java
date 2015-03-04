
public class TestHookJNI {
	private native void mousePosition();
	
	static{
		System.loadLibrary("TestHookJNI"); 
	}
	
	public static void main(String[] args){
		new TestHookJNI().mousePosition();
	}
}
