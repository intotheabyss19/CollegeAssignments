import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


class GameLogic {
  private char[][] gameGrid;
  private char currentSymbol;

  public GameLogic() {
    gameGrid = new char[3][3];
    currentSymbol = 'X';
    initializeBoard();
  }

  private void initializeBoard() {
    for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    gameGrid[i][j] = '-';
  }

  public boolean move(int row, int col) {
    if (row < 0 || row > 3 || col < 0 || col > 3 || gameGrid[row][col] != '-')
    return false;

    gameGrid[row][col] = currentSymbol;
    return true;
  }

  public boolean checkWin() {
    boolean win = false;
    // Win logic for '---' rows
    for (int i = 0; i < 3; i++) {
      if (gameGrid[i][0] == currentSymbol && gameGrid[i][1] == currentSymbol && gameGrid[i][2] == currentSymbol) {
        return true; // Row win
      }
    }

    // Win logic for '|||' columns
    for (int i = 0; i < 3; i++) {
      if (gameGrid[0][i] == currentSymbol && gameGrid[1][i] == currentSymbol && gameGrid[2][i] == currentSymbol) {
        return true; // Column win
      }
    }

    // Win logic for '\' diagonal
    if (gameGrid[0][0] == currentSymbol && gameGrid[1][1] == currentSymbol && gameGrid[2][2] == currentSymbol) {
      return true; // Diagonal win
    }

    // Win logic for '/' diagonal
    if (gameGrid[0][2] == currentSymbol && gameGrid[1][1] == currentSymbol && gameGrid[2][0] == currentSymbol) {
      return true; // Diagonal win
    }
    return false; // No win
  }

  public boolean isGameGridFull() {
    for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    if (gameGrid[i][j] == '-')
      return false;
    return true;
  }

  public char getCurrentPlayer() {
    return currentSymbol;
  }

  public void switchPlayer() {
    currentSymbol = (currentSymbol == 'X') ? 'O' : 'X';
  }

  public void resetGame() {
    initializeBoard();
    currentSymbol = 'X';
  }
}

class GameGUI {
  private JFrame gameFrame;
  private JButton[][] Cells;
  private JLabel statusLabel;
  private GameLogic Game;

  public GameGUI() {
    Game = new GameLogic();
    createGUI();
  }

  private void createGUI() {
    gameFrame = new JFrame("TIC-TAC-TOE");
    gameFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    gameFrame.setSize(600, 600);
    gameFrame.setLocationRelativeTo(null);
    gameFrame.setResizable(false);

    // background color
    gameFrame.getContentPane().setBackground(new Color(200, 200, 200));

    JPanel gamePanel = new JPanel(new GridLayout(3, 3));
    Cells = new JButton[3][3];

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        Cells[i][j] = new JButton("");
        Cells[i][j].setFont(new Font("Arial", Font.BOLD, 60));
        Cells[i][j].addActionListener(new ButtonClickListener(i, j));
        Cells[i][j].setBackground(new Color(50, 50, 100));
        Cells[i][j].setForeground(new Color(0, 200, 200));
        Cells[i][j].setBorder(BorderFactory.createLineBorder(new Color(0, 0, 0), 1));
        gamePanel.add(Cells[i][j]);
      }
    }

    statusLabel = new JLabel("Player X's turn");

    gameFrame.add(gamePanel, BorderLayout.CENTER);
    gameFrame.add(statusLabel, BorderLayout.SOUTH);

    gameFrame.setVisible(true);
  }

  private class ButtonClickListener implements ActionListener {
    private int row, col;

    public ButtonClickListener(int row, int col) {
      this.row = row;
      this.col = col;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
      if (Game.move(row, col)) {
        Cells[row][col].setText(String.valueOf(Game.getCurrentPlayer()));
        if (Game.checkWin()) {
          statusLabel.setText("Player " + Game.getCurrentPlayer() + " wins!");
          showPopup("Player " + Game.getCurrentPlayer() + " wins!");
        } else if (Game.isGameGridFull()) {
          statusLabel.setText("It's a draw!");
          showPopup("Draw!!!");
        } else {
          Game.switchPlayer();
          statusLabel.setText("Player " + Game.getCurrentPlayer() + "'s turn");
        }
      }
    }
  }

  private void showPopup(String message) {
    int response = JOptionPane.showOptionDialog(gameFrame, message + "\nWould you like to play again?", "Game Over",
      JOptionPane.YES_NO_OPTION, JOptionPane.INFORMATION_MESSAGE, null, null, null);
    if (response == JOptionPane.YES_OPTION) {
      Game.resetGame();
      resetBoard();
      statusLabel.setText("Player X's turn");
    } else {
      System.exit(0);
    }
  }

  private void resetBoard() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        Cells[i][j].setText("");
      }
    }
  }
}


public class tictactoe {
  public static void main(String[] args) {
    GameGUI gui = new GameGUI();
  }
}
