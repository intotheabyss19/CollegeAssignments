import java.io.*;
import java.net.*;

public class Client {
    private static final String SERVER_ADDRESS = "localhost";
    private static final int PORT = 9876;

    public static void main(String[] args) {
        while (true) {
            try (Socket socket = new Socket(SERVER_ADDRESS, PORT)) {
                System.out.println("Connected to server!");

                DataOutputStream out = new DataOutputStream(socket.getOutputStream());
                DataInputStream in = new DataInputStream(socket.getInputStream());

                int expectedFrame = 0;

                while (true) {
                    int frame = in.readInt();
                    if (frame == -1) {
                        System.out.println("Server has ended transmission.");
                        break;
                    }

                    System.out.println("Received frame: " + frame);
                    if (frame == expectedFrame) {
                        // Acknowledge the received frame
                        out.writeInt(expectedFrame);
                        System.out.println("Acknowledged frame: " + expectedFrame);
                        expectedFrame++;
                    } else {
                        // Acknowledge the last correctly received frame
                        out.writeInt(expectedFrame - 1);
                        System.out.println("ACK for frame " + (expectedFrame - 1) + " sent (frame out of order).");
                    }
                }

                socket.close();
                break;
            } catch (IOException e) {
                System.err.println("Connection failed: " + e.getMessage());
                System.out.println("Retrying connection...");
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException interruptedException) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }
}
