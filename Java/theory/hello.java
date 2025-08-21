import hellopack.hellofn;

public class hello {
  public static void main(String [] args) {
    System.out.println("Hello");
    hellofn obj = new hellofn();
    obj.hellofn();

    Runtime r = Runtime.getRuntime();
    System.out.println(r.totalMemory());

    inter i = new inter();
    i.I();
    //i.L();
    I.L();
  }
}

interface I {
  void I ();
   static void L () {
    System.out.println("inside interface");
  }
}

class inter implements I {
  public void I () { 
    System.out.println("inside I");
  }
  //public void L () { 
  //  System.out.println("inside L");
  //}
}
