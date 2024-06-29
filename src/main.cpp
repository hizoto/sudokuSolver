#include <Arduino.h>

void printField();
bool validRow(int row);
bool validRows();
bool validCol(int col);
bool validCols();
bool validBox(int startRow, int startCol);
bool validBoxes();
bool validField();
bool validPlacement(int row, int col, int num);
bool solve(int i, int j);

int field[9][9] = { {2, 0, 0, 9, 0, 0, 0, 0, 0},
                    {0, 0, 0, 6, 0, 7, 3, 4, 0},
                    {0, 0, 0, 0, 5, 4, 1, 0, 0},
                    {0, 0, 0, 0, 0, 1, 0, 0, 0},
                    {0, 0, 3, 0, 2, 6, 8, 0, 0},
                    {7, 0, 8, 0, 0, 0, 9, 0, 0},
                    {0, 2, 1, 4, 0, 0, 6, 0, 0},
                    {9, 8, 5, 0, 6, 2, 0, 0, 4},
                    {0, 4, 0, 5, 0, 0, 0, 1, 0},
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  printField();
  Serial.println("Solving Sudoku...");
  unsigned long startingTime = millis();
  solve(0, 0);
  float solvingTime = (millis() - startingTime) / 1000;
  /*if(validField()){
    printField();
  }*/
  printField();
  Serial.print("Sudoku solved in ");
  Serial.print(solvingTime);
  Serial.println(" seconds!");
}

void loop(){

}

void printField() {
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (j % 3 == 0 && j != 0){
        Serial.print("|");
      }
      Serial.print(field[i][j]);
      Serial.print(' ');
    }
    if ((i + 1) % 3 == 0 && i != 0 && i != 8){
      Serial.print('\n');
      Serial.print("-------------------");
    }
    Serial.print('\n');
  }
}

bool validRow(int row){
  bool present[10] = {false};
  for (int i = 0; i < 9; i++){
    int current = field[row][i];
    if (current != 0){
      if (present[current]){
        return false;
      }
    }
    present[current] = true;
  }
  return true;
}

bool validRows(){
  for (int i = 0; i < 9; i++){
    if (!validRow(i)){
      return false;
    }
  }
  return true;
}

bool validCol(int col){
  bool present[10] = {false};
  for (int i = 0; i < 9; i++){
    if (field[i][col] != 0){
      int current = field[i][col];
      if (present[current]){
        return false;
      }
      present[current] = true;
    }
  }  
  return true;
}

bool validCols(){
  for (int i = 0; i < 9; i++){
    if (!validCol(i)){
      return false;
    }
  }
  return true;
}

bool validBox(int startRow, int startCol) {
  bool present[10] = {false};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int current = field[startRow + i][startCol + j];
      if (current != 0) {
        if (present[current]) {
          return false;
        }
        present[current] = true;
      }
    }
  }
  return true;
}

bool validBoxes() {
  for (int i = 0; i < 9; i += 3) {
    for (int j = 0; j < 9; j += 3) {
      if (!validBox(i, j)) {
        return false;
      }
    }
  }
  return true;
}

bool validField(){
  if(validCols() && validRows() && validBoxes()){
    return true;
  }
  return false;
}

bool validPlacement(int row, int col, int num) {
  for (int x = 0; x < 9; x++) {
    if (field[row][x] == num || field[x][col] == num || 
        field[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
      return false;
    }
  }
  return true;
}


bool solve(int i, int j){
  if (j == 9){
    i++;
    j = 0;
  }
  if (i == 9){
    return true;
  }
    
  if (field[i][j] != 0){
    return solve(i, j + 1);
  }
  for (int num = 1; num <= 9; num++){
    if (validPlacement(i, j, num)){
      field[i][j] = num;
      if (solve(i, j + 1)){
        return true;
      }
    }
  
    field[i][j] = 0;
  }
  return false;
}