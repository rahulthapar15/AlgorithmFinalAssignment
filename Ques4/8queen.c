#include <stdio.h>

//function prototypes
void populateBlankBoard();
void printBoard();
void printBoardAndExit();
void placeQueens(int location);
void solveProblem();
void printBoardPlusLocations();
int checkRow(int queen_loc);
int checkColumn(int queen_loc);
int checkAscendingDiagnol(int queen_loc);
int checkDescendingDiagnol(int queen_loc);
int validateLocation(int queen_loc);


//declare the board
char board[64];
//declare the solution count
int solution_count = 0;

int main(){

    populateBlankBoard();
    printBoard();
    solveProblem();
    return 0;
}

void populateBlankBoard(){
  int count = 0;

      while(count < 64){
          board[count] = 'X';

        count++;
      }

}

void printBoard(){
      int count = 0;

  while(count < 64){


      printf("%c", board[count]);

      count++;

      if(count % 8 == 0){
        printf("\n");
      }
  }

  printf("\n\n");
}



void solveProblem(){
  //loop through all of the possible locations for the first queen
  //on the first row
  int count = 0;
  while(count < 8){
      placeQueens(count);
      count++;

    }
    //  printBoard();
}


void placeQueens(int location){
      //  printf("Lccation Value %d  \n", location);
      //place queen on the board
      if(validateLocation(location) == 0){


          board[location] = 'Q';


          //increment the new location to put a new queen 1 step ahead
          int newLocation = location + 1;

          placeQueens(newLocation);
        //  printBoard();
          //if this queen is in the old location and the recursion is broken
          //remove the queen from the board
          board[location] = 'X';
        }
      else{
          //loop through the board until a valid spot is found
          int temp_location = location + 1;
              while(temp_location < 64){
                    if(validateLocation(temp_location) == 0){
                      board[temp_location] = 'Q';




                      //increment the new location to put a new queen 1 step ahead
                      int newLocation = temp_location + 1;

                      placeQueens(newLocation);
                    //  printBoard();
                      //if this queen is in the old location and the recursion is broken
                      //remove the queen from the board
                      board[temp_location] = 'X';

                    }
                    temp_location++;

          }

      }




//in the case where you get all 8 queens on the board before the end
if(queenCount() == 8){
        printf("queencountreached\n");
        solution_count++;
        printf("\nSolution #%d\n\n",solution_count);
        printBoardPlusLocations();
}

}



//this function returns 1 if a queen is
//found on the row and a 0 if not
int checkRow(int queen_loc){
      int temp_loc = queen_loc;
      //printf("Queen Loc\n%d",queen_loc);
      //check current location
      //if it mod 8 = 0 only move forward
      if(temp_loc % 8 == 0){
          temp_loc++;

          while(temp_loc % 8 != 0){
                if(board[temp_loc] == 'Q'){
                        return 1;
                }

            temp_loc++;
          }

          return 0;
      }


      //for the case whenever you are in themiddle of the line
      int count_up = queen_loc + 1;
      int count_down = queen_loc - 1;

      //loop to count your way up from the queen location
      while(count_down % 8 != 0 && count_down >= 0){
          if(board[count_down] == 'Q'){
            return 1;
          }

        count_down--;
      }
      if(board[count_down] == 'Q'){
        return 1;
      }


      //loop up to find check locations ahead
      while(count_up % 8 != 0){
          if(board[count_up] == 'Q'){
            return 1;
          }

        count_up++;
      }

      //in the case where all of these fail
      //return 0
      if(queen_loc == 7){
        printf("Returned0row\n");
      }

      return 0;




}


int checkColumn(int queen_loc){
      int temp_loc = queen_loc;

      //check locations above
      temp_loc = temp_loc - 8;
      while(temp_loc >=  0){
        if(board[temp_loc] == 'Q'){
            return 1;
        }

        temp_loc = temp_loc -8;
      }

      //check locations below
      temp_loc = queen_loc + 8;
      while(temp_loc < 64){
          if(board[temp_loc] == 'Q'){
                return 1;
          }
          temp_loc = temp_loc + 8;
      }

//testing for error at value 7
      if(queen_loc == 7){
        printf("Returned0col\n");
      }

      //if both tests fail return 0
      return 0;

}

int checkAscendingDiagnol(int queen_loc){
  int temp_loc = queen_loc;

  //check locations above
  temp_loc = temp_loc - 7;
  while(temp_loc >  0){
    if(board[temp_loc] == 'Q'){
        return 1;
    }

    //break out once a place at the edge of the board is hit
    if(temp_loc % 8 == 0 || temp_loc < 8 || temp_loc % 8 == 7 || (temp_loc > 57 && temp_loc < 64)){
        break;
    }

    temp_loc = temp_loc -7;
  }

  //check locations below
  temp_loc = queen_loc + 7;
  while(temp_loc < 64){
      if(board[temp_loc] == 'Q' && temp_loc % 8 != 0){
            return 1;
      }

      //break out once a place at the edge of the board is hit
      if(temp_loc % 8 == 0 || temp_loc < 8 || temp_loc % 8 == 7 || (temp_loc > 57 && temp_loc < 64)){
          break;
      }


      temp_loc = temp_loc + 7;
  }

  //testing for error at value 7
        if(queen_loc == 7){
          printf("ReturneddiagA0\n");
        }


  //if both tests fail return 0
  return 0;

}



int checkDescendingDiagnol(int queen_loc){
  int temp_loc = queen_loc;

  //check locations above
  temp_loc = temp_loc - 9;
  while(temp_loc >=  0){
    if(board[temp_loc] == 'Q'){
        return 1;
    }

    //break out once a place at the edge of the board is hit
    if(temp_loc % 8 == 0 || temp_loc < 8 || temp_loc % 8 == 7 || (temp_loc > 57 && temp_loc < 64)){
        break;
    }

    temp_loc = temp_loc -9;
  }

  //check locations below
  temp_loc = queen_loc + 9;
  while(temp_loc < 64){
      if(board[temp_loc] == 'Q' && temp_loc % 8 != 0){
            return 1;
      }

      //break out once a place at the edge of the board is hit
      if(temp_loc % 8 == 0 || temp_loc < 8 || temp_loc % 8 == 7 || (temp_loc > 57 && temp_loc < 64)){
          break;
      }


      temp_loc = temp_loc + 9;
  }

  //testing for error at value 7
        if(queen_loc == 7){
          printf("Returned0Diagd\n");
        }



  //if both tests fail return 0
  return 0;

}



//this function returns 0 if the queen placement is valid and a 1 if invalid
int validateLocation(int queen_loc){
//  printf("Queen Locatiion: %d\n",queen_loc);
  if(checkRow(queen_loc) == 1 || checkColumn(queen_loc) == 1 || checkAscendingDiagnol(queen_loc) == 1  || checkDescendingDiagnol(queen_loc) == 1){
   //printf("invalid\n");
  //  printBoard();
    return 1;

  }
  //printf("valid\n");
// printBoard();
  return 0;
}

//a function that obviously takes count of the queens on the table
int queenCount(){
  int count = 0;
  int queen_count = 0;
    while(count < 64){
      if(board[count] == 'Q'){
        queen_count++;
      }
      count++;
    }

    return queen_count;

}

void printQueenLocations(){
      int count = 0;
      while(count < 64){
          if(board[count] == 'Q'){
              printf("Queen Location: %d\n",count);
          }

          count++;

      }

}

void printBoardPlusLocations(){
      printBoard();
      printQueenLocations();
}


void printBoardAndExit(){
      printBoard();
      printQueenLocations();
      exit(0);
}
