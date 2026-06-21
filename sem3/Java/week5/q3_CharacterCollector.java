import java.util.Scanner;

class InvalidCharacterException extends Exception {
    public InvalidCharacterException(String message) {
        super(message);
    }
}

class CharacterCollector {
    private int validCharacterCount;

    public CharacterCollector() {
        this.validCharacterCount = 0;
    }

    public void addCharacter(char c) throws InvalidCharacterException {
        if (Character.isAlphabetic(c)) {
            validCharacterCount++;
        } else {
            throw new InvalidCharacterException("Invalid character: " + c);
        }
    }

    public int getValidCharacterCount() {
        return validCharacterCount;
    }
}


public class q3_CharacterCollector {
    public static void main(String[] args) {
        CharacterCollector collector = new CharacterCollector();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter characters (type 'exit' to finish):");

        while (true) {
            String input = scanner.nextLine();
            if (input.equalsIgnoreCase("exit")) {
                break;
            }

            for (char c : input.toCharArray()) {
                try {
                    collector.addCharacter(c);
                    System.out.println("Added valid character: " + c);
                } catch (InvalidCharacterException e) {
                    System.out.println(e.getMessage());
                }
            }
        }

        System.out.println("Total valid characters collected: " + collector.getValidCharacterCount());
        scanner.close();
    }
}
