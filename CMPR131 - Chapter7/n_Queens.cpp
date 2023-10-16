#include "n_Queens.h"

//precondition:
//postcondition:
bool checkIfConflict(int boardSize, stack<BoardSpaces> filledSpaces, BoardSpaces currentSpace);

//precondition:
//postcondition:
n_Queens::n_Queens() {
	shiftDirection = 'R';
	firstColumnPermutaions = 0;
	boardSize = 0;
	filled = 0;
	gameWon = false;
}
//precondition:
//postcondition:
void n_Queens::setBoardSize(int newBoardSize) {
	boardSize = newBoardSize;
}
//precondition:
//postcondition:
void n_Queens::setFilled(int newFilledAmount) {
	filled = newFilledAmount;
}
//precondition:
//postcondition:
int n_Queens::getBoardSize() const {
	return boardSize;
}
//precondition:
//postcondition:
int n_Queens::getFilled() const {
	return filled;
}
//precondition:
//postcondition:
void n_Queens::fillBoard() {
	BoardSpaces currentSpace;
	boardSize = inputInteger("\n\tEnter a number(1..100) of queens: ", 1, 100);
	BoardSpaces userDefinedSpace;
	userDefinedSpace.setRow(1);
	userDefinedSpace.setColumn(inputInteger("\tEnter the column to place the first queen : ", 1, boardSize));
	filledSpaces.push(userDefinedSpace);

	// Move on to the next row after placing the first queen
	currentSpace.setRow(2);
	currentSpace.setColumn(1);

	while (currentSpace.getRow() <= boardSize) {
		if (checkIfConflict(boardSize, filledSpaces, currentSpace)) { // Conflict found
			if (currentSpace.getColumn() < boardSize) { // If not in the last column, try next column
				currentSpace.setColumn(currentSpace.getColumn() + 1);
			}
			else { // If in the last column, backtrack
				do {
					if (filledSpaces.empty()) {
						cout << "\n\tNo Solution Found. " << endl;
						return;
					}
					currentSpace = filledSpaces.top();
					filledSpaces.pop();
				} while (currentSpace.getColumn() == boardSize);

				// Try next column for the queen we backtracked to
				currentSpace.setColumn(currentSpace.getColumn() + 1);
			}
		}
		else { // No conflict
			filledSpaces.push(currentSpace);
			currentSpace.setRow(currentSpace.getRow() + 1);
			currentSpace.setColumn(1);
		}
	}

	displayBoard(filledSpaces);
}

//precondition:
//postcondition:
void n_Queens::displayBoard(stack<BoardSpaces> filledSpaces) const {
	stack<BoardSpaces> reversedStack;
	stack<BoardSpaces> auxStack;

	// Reverse the filledSpaces stack
	while (!filledSpaces.empty()) {
		reversedStack.push(filledSpaces.top());
		filledSpaces.pop();
	}

	cout << endl << "\t" << boardSize << "-Queens Soulution." << endl;

	// Top border
	cout << "\t" << std::string(1, char(201));
	cout << string(boardSize * 2 + 1, char(205));
	cout << string(1, char(187)) << endl;

	// Display the board
	for (int i = 1; i <= boardSize; i++) { // for each row
		cout << "\t" << string(1, char(186)) << " ";
		for (int j = 1; j <= boardSize; j++) { // for each column
			if (!reversedStack.empty() && reversedStack.top().getRow() == i) {
				if (reversedStack.top().getColumn() == j) {
					cout << 'Q';
					auxStack.push(reversedStack.top());
					reversedStack.pop();
				}
				else {
					cout << '-';
				}
				cout << string(1, char(179));
			}
			else {
				cout << '-';
				if (j < boardSize) {
					cout << string(1, char(179));
				}
			}
		}
		cout << " " << string(1, char(186)) << endl;
	}

	// Bottom border
	cout << "\t" << std::string(1, char(200));
	cout << string(boardSize * 2 + 1, char(205));
	cout << string(1, char(188)) << endl;

	// Restore filledSpaces using auxStack
	while (!auxStack.empty()) {
		filledSpaces.push(auxStack.top());
		auxStack.pop();
	}
}
//precondition:
//postcondition:
bool checkIfConflict(int boardSize, stack<BoardSpaces> filledSpaces, BoardSpaces currentSpace) {
	stack<BoardSpaces> copyStack = filledSpaces;

	while (!copyStack.empty()) {
		BoardSpaces placedSpace = copyStack.top();

		// Check for column conflict
		if (placedSpace.getColumn() == currentSpace.getColumn()) {
			return true;
		}

		// Check for diagonal conflict
		if (abs(placedSpace.getColumn() - currentSpace.getColumn()) ==
			abs(placedSpace.getRow() - currentSpace.getRow())) {
			return true;
		}

		copyStack.pop();
	}

	return false;
}
//precondition:
//postcondition:
void n_Queens::n_QueensMenu() {
	system("cls");
	cout << "\n\t3> n_Queens Problem";
	cout << "\n\t" << string(82, char(205)) << "\n";
	fillBoard();
}