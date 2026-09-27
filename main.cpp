#include <iostream>
#include <random>

void game(char gameBoard[3][3], char &moveChar, char &gameWinner, int gameMode);
void computerMode(char gameBoard[3][3], char moveSymbol);
void initBoard(char gameBoard[3][3]);
void showBoard(char gameBoard[3][3]);
void changeBoard(char gameBoard[3][3], int moveX, int moveY, char moveChar);
void switchMove(char &moveChar);
void checkGameWinner(char gameBoard[3][3], char &gameWinner);
bool isLegalInput(int xInput, int yInput);
bool isOccupied(char gameBoard[3][3], int x, int y);
 
int main() {
    std::cout << "Hello! Welcome to tic-tac-toe." << std::endl;
    std::cout << "Before you begin, select a game mode." << std::endl;
    std::cout << "\tEnter 0 to play against a human." << "\n\tEnter 1 to play against the computer." << std::endl;

    int inputGameMode;
    std::cin >> inputGameMode;

    char gameBoard[3][3];

    initBoard(gameBoard);

    char moveChar = 'X';
    char gameWinner = 'N';

    while (true) {
        game(gameBoard, moveChar, gameWinner, inputGameMode);

        if (gameWinner == 'D') {
            std::cout << "\nIt seems like nobody won..." << std::endl;
            break;
        } else if (gameWinner != 'N') {
            std::cout << "\nGame ended. Winner is... " << gameWinner << std::endl;
            break;
        }
    }

    std::cin.get();
}

void game(char gameBoard[3][3], char &moveChar, char &gameWinner, int gameMode) {
    int inputMoveX;
    int inputMoveY;

    std::cout << "\033[2J\033[1;1H";
    
    showBoard(gameBoard);

    checkGameWinner(gameBoard, gameWinner);
    
    if (gameWinner != 'N') return;
    
    std::cout << "\n" << moveChar << 
    ", enter your move!\n\tExample: 1 2 (He will place it on the second square of the first row.)" 
    << std::endl;
    
    do {
        std::cin >> inputMoveX >> inputMoveY;
        
        if (isOccupied(gameBoard, inputMoveX - 1, inputMoveY - 1)) {
            std::cout << "The cell is occupied by another player. Enter again:" << std::endl;
        }
    } while ( !isLegalInput(inputMoveX, inputMoveY) || isOccupied(gameBoard, inputMoveX - 1, inputMoveY - 1));
    
    changeBoard(gameBoard, inputMoveX - 1, inputMoveY - 1, moveChar);

    if (gameMode == 1) {
        computerMode(gameBoard, 'O');
    } else {
        switchMove(moveChar);
    }
}

// i'm aware of minimax, it just seemed too complicated for me right now
void computerMode(char gameBoard[3][3], char moveSymbol) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distrib(0, 2);

    while (true) {
        int x = distrib(gen);
        int y = distrib(gen);

        if (isOccupied(gameBoard, x, y)) {
            continue;
        }

        gameBoard[x][y] = moveSymbol;

        break;
    }
} 

void initBoard(char gameBoard[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j] = '-';
        }
    }
}

void showBoard(char gameBoard[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << " " << gameBoard[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void changeBoard(char gameBoard[3][3], int moveX, int moveY, char moveChar) {
    if (gameBoard[moveX][moveY] == '-') {
        gameBoard[moveX][moveY] = moveChar;
    } else if (gameBoard[moveX][moveY] != '-') {
        return;
    }
}

void switchMove(char &moveChar) {
    if (moveChar == 'X') {
        moveChar = 'O';
    } else if (moveChar == 'O') {
        moveChar = 'X';
    }
}

void checkGameWinner(char gameBoard[3][3], char &gameWinner) {
    for (int i = 0; i < 3; i++) {
        if (gameBoard[i][0] != '-' && gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2]) {
            gameWinner = gameBoard[i][0];
            return; 
        }
    }

    for (int j = 0; j < 3; j++) {
        if (gameBoard[0][j] != '-' && gameBoard[0][j] == gameBoard[1][j] && gameBoard[1][j] == gameBoard[2][j]) {
            gameWinner = gameBoard[0][j];
            return;
        }
    }

    if (gameBoard[0][0] != '-' && gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2]) {
        gameWinner = gameBoard[0][0];
        return;
    }

    if (gameBoard[0][2] != '-' && gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0]) {
        gameWinner = gameBoard[0][2];
        return;
    }

    bool hasEmptySpace = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameBoard[i][j] == '-') {
                hasEmptySpace = true;
            }
        }
    }

    if (hasEmptySpace) {
        gameWinner = 'N';
    } else {
        gameWinner = 'D';
    }
}

bool isLegalInput(int xInput, int yInput) {
    if (xInput > 3 || yInput > 3 || xInput < 1 || yInput < 1) {
        return false;
    }

    return true;
}

bool isOccupied(char gameBoard[3][3], int x, int y) {
    if (gameBoard[x][y] == 'X' || gameBoard[x][y] == 'O') {
        return true;
    }

    return false;
}