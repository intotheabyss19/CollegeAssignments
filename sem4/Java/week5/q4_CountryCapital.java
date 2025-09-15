import java.util.HashMap;
import java.util.Map;

class NoMatchFoundException extends Exception {
    public NoMatchFoundException(String message) {
        super(message);
    }
}

public class q4_CountryCapital {
    private static final Map<String, String> countryCapitals = new HashMap<>();

    static {
        countryCapitals.put("India", "New Delhi");
        countryCapitals.put("USA", "Washington, D.C.");
        countryCapitals.put("Canada", "Ottawa");
        countryCapitals.put("France", "Paris");
        countryCapitals.put("Germany", "Berlin");
        countryCapitals.put("Italy", "Rome");
        countryCapitals.put("Japan", "Tokyo");
        countryCapitals.put("Australia", "Canberra");
        countryCapitals.put("India", "New Delhi");
        countryCapitals.put("Brazil", "Brasília");
        countryCapitals.put("Russia", "Moscow");
    }

    public static String getCapital(String country) throws NoMatchFoundException {
        String capital = countryCapitals.get(country);
        if (capital == null) {
            throw new NoMatchFoundException("No match found for country: " + country);
        }
        return capital;
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java CountryCapital <country_name>");
            return;
        }

        String country = args[0];

        try {
            String capital = getCapital(country);
            System.out.println("The capital of " + country + " is: " + capital);
        } catch (NoMatchFoundException e) {
            System.out.println(e.getMessage());
        }
    }
}
