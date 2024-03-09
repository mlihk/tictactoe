#include <stdio.h>

char board[3][3];

//place all values in the board with empty string
void initialize_board() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

//just display the board state
void display_board() {
    int i, j;
    printf("\n");
    printf("  0 1 2\n");
    for (i = 0; i < 3; i++) {
        printf("%d ", i);
        for (j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
            if (j < 2)
                printf("|");
        }
        printf("\n");
        if (i < 2)
            printf("  -----\n");
    }
}

//check if either side got a connect-3
char check_winner() {
    int i;
    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];
    return ' '; // No winner yet
}

//check if the 9 spaces in 3 arrays are full if so, end the game with tie
int is_board_full() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

//allow player to choose a row/col and replace it with relative symbol X/O
int player_move(int row, int col, char symbol) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = symbol;
        return 1;
    } else {
        printf("Invalid move. Try again.\n");
        return 0;
    }
}

//randomly placing their symbol on an empty space
void ai_move(char symbol) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    printf("Opponent's move: %d %d\n", row, col);
    board[row][col] = symbol;
}

//runs everything lol
int main() {
    int row, col;
    int mode;
    char player1 = 'X', player2 = 'O';
    char current_player = player1;
    char winner;

    initialize_board();
    
    printf("Choose a mode:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs AI\n");
    scanf("%d", &mode);
    
    if (mode == 2) {
            printf("Enter symbol for Player (X or O): ");
            scanf(" %c", &player1);
            player2 = (player1 == 'X') ? 'O' : 'X';
            current_player = (rand() % 2 == 0) ? player1 : player2;
        } else {
            printf("Invalid mode. Exiting.\n");
            return 1;
        }

    printf("Player 1: X, Player 2: O\n");

    while (1) {
        display_board();
        if (mode == 1 || current_player == player1){
            printf("Player %c's turn. Enter row and column (e.g., 1 2): ", current_player);
            scanf("%d %d", &row, &col);

            //Check if player input a valid move, if not prompt them to re-enter their choice
            if (player_move(row, col, current_player) != 1){
                printf("Player %c's turn. Enter row and column (e.g., 1 2): ", current_player);
                scanf("%d %d", &row, &col);
                player_move(row, col, current_player);
            };
        } else {
            ai_move(current_player);
        }
        
        winner = check_winner();
        
        if (winner != ' ') {
            display_board();
            printf("Player %c wins!\n", winner);
            break;
        }
        if (is_board_full()) {
            display_board();
            printf("It's a draw!\n");
            break;
        }
        
        current_player = (current_player == player1) ? player2 : player1;
        
    }

    return 0;
}
