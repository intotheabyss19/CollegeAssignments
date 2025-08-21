public class q14_AssetClass {
    public static void main(String [] args) {
        Stock S = new Stock();
        System.out.println("Contents of Stock: ");
        S.displayDetails();
        Bond B = new Bond();
        System.out.println("Contents of Bond: ");
        B.displayDetails();
        Savings Sa = new Savings();
        System.out.println("Contents of Savings: ");
        Sa.displayDetails();
    }
}

abstract class Assets {
    String descriptor = "";
    String date = "";
    double current_value;
    public abstract void displayDetails();
}

class Stock extends Assets {
    int num_shares;
    double share_price;
    String asset = "";

    public void displayDetails() {
        System.out.println("\tdescriptor: " + descriptor);
        System.out.println("\tdate: " + date);
        System.out.println("\tcurrent_value: " + current_value);
        System.out.println("\tnum_shares: " + num_shares);
        System.out.println("\tshare_price: " + share_price);
        System.out.println("\tasset: " + asset);
    }
}

class Bond extends Assets {
    double interest_rate;
    String asset = "";

    public void displayDetails() {
        System.out.println("\tdescriptor: " + descriptor);
        System.out.println("\tdate: " + date);
        System.out.println("\tcurrent_value: " + current_value);
        System.out.println("\tinterest_rate: " + interest_rate);
        System.out.println("\tasset: " + asset);
    }
}

class Savings extends Assets{
    double interest_rate;
    String asset = "";

    public void displayDetails() {
        System.out.println("\tdescriptor: " + descriptor);
        System.out.println("\tdate: " + date);
        System.out.println("\tcurrent_value: " + current_value);
        System.out.println("\tinterest_rate: " + interest_rate);
        System.out.println("\tasset: " + asset);
    }
}
