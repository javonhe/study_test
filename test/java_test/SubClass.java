public class SubClass extends SuperClass {	
	public SubClass() {  
		System.out.println("sub class constructed.");  
	}  
	public SubClass(String name) {	
		//super(name);  
		System.out.println("sub class constructed with name: " + name);  
	}  
	public static void main(String[] args) {  
		new SubClass();  
		new SubClass("world");	
	}  
}  

