package inputPack;

import java.util.Scanner;
public class inputPack {
  public Scanner scanner;
  public void Input() { scanner = new Scanner(System.in); }
  public int readInt() { return scanner.nextInt(); }
  public String readString() { return scanner.next(); }
}
