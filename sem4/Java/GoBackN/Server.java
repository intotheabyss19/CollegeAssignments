import java.io.*;
import java.net.*;

public class Server {
    private static final int PORT = 9876;
    private static final int WINDOW_SIZE = 4;

    public static void main(String[] args) {
        int totalFrames = 0;

	if (args.length != 1) {
		System.out.println("This program utilises command line arguments\nUsage: Server.java <Num_of_packets_to_send>"); 
		return;
	}
	
        if (args.length > 0) {
            try {
                totalFrames = Integer.parseInt(args[0]);
                if (totalFrames <= 0) {
                    System.out.println("Number of packets must be positive. Using default value of 10.");
                    totalFrames = 10;
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid number format. Using default value of 10.");
            }
        }

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server is listening on port " + PORT);
            Socket socket = serverSocket.accept();
            System.out.println("Client connected!");

            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            DataInputStream in = new DataInputStream(socket.getInputStream());

            int nextFrameToSend = 0;

            while (nextFrameToSend < totalFrames) {
                int framesSent = 0;

                // Send frames in the window
                while (framesSent < WINDOW_SIZE && nextFrameToSend < totalFrames) {
                    System.out.println("Sending frame: " + nextFrameToSend);
                    out.writeInt(nextFrameToSend);
                    nextFrameToSend++;
                    framesSent++;
                }

                // Wait for acknowledgments
                for (int i = 0; i < framesSent; i++) {
                    int ack = in.readInt();
                    System.out.println("Received ACK for frame: " + ack);
                    if (ack != (nextFrameToSend - framesSent + i)) {
                        System.out.println("ACK mismatch, resending frames from " + (nextFrameToSend - framesSent + i));
			// Go back to the last acknowledged frame
                        nextFrameToSend = ack; 
                        break;
                    }
                }
            }
	// end of transmission
            out.writeInt(-1); 
            System.out.println("All frames sent. Ending transmission.");
            socket.close();
        } catch (IOException e) {
            System.err.println("Server error: " + e.getMessage());
        }
    }
}
