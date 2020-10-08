//SE 185: Final Project Template//
/////////////////////////
/*
Team xx (please insert your team number instead of xx)
Team member 1 Dylan Hampton |
Team member 2 "Selma Saric" |
*/

////////////////////
#include<stdio.h>//

#include <stdlib.h>//

#include <unistd.h>//

#include <time.h>//

#include <string.h>//
 //add more here////

//////////////////////
//Struct Definition//
////////////////////

/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//tehm below the main function////
/////////////////////////////////
void start();
void drawBoard(int random);
int printHighscore();
void countDown();
void addHighscore(int score);

int main() {
  char check = 'f';
  int stillPlaying = 1;
  int score = 0;
  int turns = 1;
  int arrCount = 0;
  char input = 'z';
  char * outputs = (char * ) malloc((arrCount + 1) * sizeof(char));
  srand(time(NULL));

  start();
  int lowestHS = printHighscore();
  //if leaderboard is empty
  if (lowestHS == -1) {
    printf("\n");
  }

  printf("What would you like to do?\n");
  while (check != 'g') {
    printf("Enter \"g\" to start: ");
    scanf(" %c", & check);
  }

  //main game loop
  while (stillPlaying == 1) {
    printf("Get ready for the round!\n");
    countDown();
    int random = rand() % 4;
    //Choose random answer and store it in the array
    switch (random) {
    case 0:
      *
      (outputs + arrCount) = 'w';
      break;
    case 1:
      *
      (outputs + arrCount) = 'a';
      break;
    case 2:
      *
      (outputs + arrCount) = 's';
      break;
    case 3:
      *
      (outputs + arrCount) = 'd';
      break;
    }
    //draw the board and circle the random symbol
    drawBoard(random);
    //printf("%c\n", *(outputs + arrCount));

    printf("Okay, what was the order? (Use w,a,s,d)\n");
    //quiz the player on their knowledge and compare it to the past rounds
    for (int i = 0; i < turns; i++) {
      printf("%d time: ", i + 1);
      scanf(" %c", & input);
      //check against the previous random chars
      if (input == * (outputs + i)) {
        score++;
        printf("Score: %d\n", score);
      } else {
        stillPlaying = -1;
        printf("Sorry, you lose, at least you got to turn %d.\n", turns);
        printf("Your final score was %d, try again and get an even higher score!\n\n", score);
        break;
      }
    }
    //if they got all of the turns right
    if (stillPlaying == 1) {
      turns++;
      arrCount++;
    }
  }
  free(outputs);

  //if they got on the highscore board, update and print it
  if (score >= lowestHS) {
    addHighscore(score);
    printf("\n");
    printHighscore();
  }

  return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////

//Prints out the start messages and waits for user input
void start() {
  char check = 'f';
  printf("Welcome to the memory game.\n");
  while (check != 'g') {
    printf("Enter \"g\" to start: ");
    scanf(" %c", & check);
  }
  printf("In the game various shapes will appear with a circle around it\n");
  printf("You must remember the shapes that are circled and repeat the order\n");
  printf("Use W for up, S for down, D for right, A for left\n\n");
}

//prints out the highscore table stored in highscores.txt,
//with proper spacing
int printHighscore() {
  FILE * f = fopen("highscores.txt", "r");
  //maximum row length for chars is 9, for this method of searching
  char arr[9][6];
  int row = 0;
  int col = 0;
  char * lowest = (char * ) malloc(2 * sizeof(char));

  if (f == NULL) {
    printf("Error: Could not find \"highscores.txt\"");
    exit(0);
  }

  printf("Highscore Table: \nRank Score  Name\n");

  //checks if the file is empty, if so, return -1
  fseek(f, 0, SEEK_END);
  if (ftell(f) == 0) {
    return -1;
  }

  rewind(f);
  //reads the file and stores its input in a 2d char array
  while (!feof(f)) {
    char current;
    //add current char to array
    fscanf(f, "%c ", & current);
    //if the column reached the end reset and increment row
    if (col == 5) {
      arr[row][col] = current;
      row++;
      col = 0;
    } else {
      arr[row][col] = current;
      col++;
    }
  }
  fclose(f);

  //traverses the 2d array and prints out the highscores with proper spacing
  for (int r = 0; r < row; r++) {
    for (int c = 0; c < 6; c++) {
      switch (c) {
      case 0:
        printf("%c     ", arr[r][c]);
        break;
      case 1:
      case 3:
      case 4:
      case 5:
        printf("%c ", arr[r][c]);
        break;
      case 2:
        printf("%c   ", arr[r][c]);
        break;
      default:
        printf("%c ", arr[r][c]);
      }
    }
    printf("\n");
  }

  //gets the lowest score on the leaderboard and returns it as an int
  *(lowest) = arr[row][1];
  *(lowest + 1) = arr[row][2];
  return atoi(lowest);
}

//counts down from 3
void countDown() {
  int count = 3;
  while (count > 0) {
    printf("%d...\n", count);
    sleep(1);
    count--;
  }
}

//draws out the 4 symbols,
//circling one of them based on the given random
void drawBoard(int random) {

  if (random == 0) {
    printf(" - - - - - -\n");

  }
    
  //drawing triangle
  int spaceOut = 20;
  int rowLength = 4;
  for (int i = 1; i <= rowLength; i++) {
    if (random == 0) {
      printf("|");
    }

    for (int j = i; j < rowLength; j++) {
      printf(" ");

    }

    if (i > 0) //spacing for the triangle, keeps it away from the edge of the screen.
    {
      printf(" ");
      printf(" ");
    }

    for (int j = 1; j <= (2 * i - 1); j++) {
      printf("^");
    }

    if (random == 0) {

      for (int z = i; z < rowLength; z++) {
        printf(" ");
      }
      printf("  |");
    }
    printf("\n");

  }

  if (random == 0) {
    printf(" - - - - - -\n");

  }
  printf("\n");
  if (random == 3) {
    printf("         - - - - -");
  }

  //drawing square
  int hLength = 5;
  int rLength = 2;
  int sideLength = 3;
  int heightL = 3;
  int rowL = 0;
  printf("\n");

  if (random == 1) {
    printf(" - - - - - ");
    printf("\n");
   
  }

  for (int l = 1; l < rLength; l++) {
    for (int h = 1; h <= hLength; h++) {
      if (h == 1) //spacing for the top line of the square.
      {
          if (random == 1){
                       printf("|");
                   }
          if (l > 0) {
                  printf(" ");
                }
        printf(" ");
          
      }
      printf("@");
      if (h == 5) {
        printf(" ");
      }
    }
  }

  //drawing diamond
  for (int k = 1; k <= sideLength; k++) {
      if (random == 1 || random == 3){
          printf("|");
      }
    for (int m = k; m <= sideLength; m++) {
      printf(" ");
    }

    for (int m = 1; m <= (2 * k - 1); m++) {
      printf("^");
      if (m >= (2 * k - 1)) {
          if (random == 3 && m == 1){
              printf("    |");
          }
          if (random == 3 && m == 3){
              printf("   |");
          }
          if (random == 3 && m == 5){
              printf("  |");
          }
        printf("\n");
        for (int h = 1; h <= hLength; h++) {
          if (h == 1) //this is spacing before the shape is printed. For the 3 middle parts of the sqare
          {
              if (random == 1){
                           printf("|");
                       }
            printf(" ");
            printf(" ");
          }
          printf("@");
          if (h == 5) {
            printf(" ");
          }
        }
      }
    }
      if (random == 1 || random == 3) {
        for (int z = k; z >= sideLength; z--) {
          printf("|");
        }
      }
  }

  for (int l = 2; l >= rowL; l--) {

    for (int h = l; h <= heightL; h++) {
      printf(" ");
    }
    for (int h = 3; h <= (2 * l + 1); h++) {
      printf("^");
      if (h > (4)) {
          if (random == 3){
              printf("   |");
          }
        printf("\n");
        for (int h = 1; h <= hLength; h++) {
          if (h == 1) {
              if (random == 1){
                  printf("|");
              }
            printf(" ");
            printf(" ");
          }
          printf("@");
          if (h >= 5) {
            printf(" ");
              if (random == 1 || random == 3){
                  printf("|");
              }
          }
        }
      }
      }
      if (random == 3 && l == 0){
                 printf("|");
        }
    }
  printf(" \n");
  if (random == 1) {
    printf(" - - - - - ");
  }

  if (random == 3) {
    printf("         - - - - -");
  }

  if (random == 2) {
    printf(" - - - - -");
  }

  //drawing X
  printf("\n");
  int t, r;
  int size = 5;

  for (t = 1; t <= size; t++) {
    if (random == 2) {
      printf("|");
    }
    for (r = 1; r <= size; r++) {
      if (r == 1) //spacing for the x, to keep away from edge of screen.
      {
        printf(" ");
        printf(" ");
      }
      if (r == t || (r == size - t + 1)) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    if (random == 2) {
         for (int z = t; z > size; z++) {
           printf(" ");
         }
         printf("  |");
       }
      
    printf("\n");
   
  }
    
  if (random == 2) {
    printf(" - - - - -\n");
  }

}

//takes the players score and name
//then inserts it into the correct position and
//moves the rest of the leaderboard into its new order
void addHighscore(int score) {
  //max score is 99
  if (score > 99) {
    score = 99;
  }

  //get the players name
  char name[3];
  printf("Congratulations, you made it on the highscore table!\n");
  printf("Please enter your name (only 3 capital letters): ");
  scanf("%s", name);

  FILE * f = fopen("highscores.txt", "r");
  char arr[9][6];
  int row = 0;
  int col = 0;
  char * currentValue = (char * ) malloc(2 * sizeof(char));
  int replacementRow = -1;

  //checks if the file is empty, if so, set replacementRow to 0
  fseek(f, 0, SEEK_END);
  if (ftell(f) == 0) {
    replacementRow = 0;
  }
  rewind(f);

  //scan current highscore table into 2d char array
  while (!feof(f)) {
    char current;
    //add current char to array
    fscanf(f, "%c ", & current);
    //if the column reached the end reset and increment row
    if (col == 5) {
      arr[row][col] = current;
      row++;
      col = 0;
    } else {
      arr[row][col] = current;
      col++;
    }
  }
  fclose(f);

  //find row to put new highscore in
  //by comparing this players score vs the leaderboards
  for (int r = 0; r < row; r++) {
    *(currentValue) = arr[r][1];
    *(currentValue + 1) = arr[r][2];
    *(currentValue + 2) = '\0';
    if (score >= atoi(currentValue)) {
      replacementRow = r;
      break;
    }
  }

  char newTable[9][6];
  //move all the old highscores downwards
  if (replacementRow != 0) {
    for (int r = 0; r < row; r++) {
      if (r == replacementRow) {
        newTable[replacementRow][0] = '0' + (replacementRow + 1);
        newTable[replacementRow][1] = '0' + (score / 10) % 10;
        newTable[replacementRow][2] = '0' + score % 10;
        newTable[replacementRow][3] = name[0];
        newTable[replacementRow][4] = name[1];
        newTable[replacementRow][5] = name[2];
      }
      for (int c = 0; c < 6; c++) {
        if (r < replacementRow) {
          newTable[r][c] = arr[r][c];
        } else if (r > replacementRow) {
          if (c == 0) {
            int orig = arr[r - 1][c] - '0';
            orig++;
            newTable[r][c] = orig + '0';
          } else {
            newTable[r][c] = arr[r - 1][c];
          }
        }
      }
    }
  } else {
    newTable[replacementRow][0] = '0' + (replacementRow + 1);
    newTable[replacementRow][1] = '0' + (score / 10) % 10;
    newTable[replacementRow][2] = '0' + score % 10;
    newTable[replacementRow][3] = name[0];
    newTable[replacementRow][4] = name[1];
    newTable[replacementRow][5] = name[2];
    for (int r = 1; r <= row; r++) {
      for (int c = 0; c < 6; c++) {
        if (c == 0) {
          int orig = arr[r - 1][c] - '0';
          orig++;
          newTable[r][c] = orig + '0';
        } else {
          newTable[r][c] = arr[r - 1][c];
        }
      }
    }
  }

  //write new leaderboard to file
  f = fopen("highscores.txt", "w");
  for (int r = 0; r < row; r++) {
    for (int c = 0; c < 6; c++) {
      fprintf(f, "%c ", newTable[r][c]);
    }
    if (row > 1) {
      fprintf(f, "\n");
    }
  }
  fclose(f);
}
