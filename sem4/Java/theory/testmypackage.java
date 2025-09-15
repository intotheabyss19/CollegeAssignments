import inputPack.inputPack;
public class testmypackage {
  public static void main(String [] args) {
    inputPack ip = new inputPack();
    int num = ip.readInt();
    System.out.println("The input number is: " + num);
  }
}
