#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>


void setup();
void welcomeMessage();
void printInGameScreen();
void gameEngine();
void setCursor(short x, short y);
void hideCursor();
void inGameInput();
void title();
void snakeMovement();
void scorePrint();
void levelChoose();
bool isGameOver();
void gameOverScreen();
void food();
void foodSetup();
bool overlapWithBody(int x, int y);
void pauseScreen();
void showCurrentHighScores();
void initializeFile();
void scoreSave();


//Coloring Text:- ANSCII Esacpe colors
const char *RESET = "\033[0m";
const char *PURPLE = "\033[1;36m";
const char *CYAN = "\033[1;36m";
const char *YELLOW = "\033[1;33m";
const char *GREEN = "\033[1;32m";
const char *RED = "\033[1;31m";
const char *BLUE = "\033[1;34m";
const char *WHITE = "\033[1;37m";

const int boundaryStartX = 0;
const int boundaryEndX = 40;
const int boundaryStartY = 0;
const int boundaryEndY = 20;

int snakeHeadX;
int snakeHeadY;

int snakeTailX[200];
int snakeTailY[200];

int foodPositionX;
int foodPositionY;

char boundaryChar = '#';
char snakeHeadChar = '@';
char snakeBodyChar =  '*';
char foodChar =  '&';
char spaceChar = ' ';

char keyInput = 'w';
int refreshRate = 500;
int score;
int currentLevelArrow = 1;
int gameOverArrow = 1;
int maxScore[5] = {0};
int snakeLength = 3;
bool isPause;
bool isNewHighScore;


//start of main function--------------------------------------------------------------------------
int main(){

    setup();

    return 0;
}

void setup(){ //----------------------------------------------------------------------------------

    hideCursor(); //for hiding the blinking cursor

    system("cls");
    printf("%s", RESET);

    initializeFile();

    Sleep(200);

    welcomeMessage();

    levelChoose();

    gameEngine();

}

void initializeFile(){

    FILE *fp;
    fp = fopen("do_not_delete.arghya", "r");

    if(fp == NULL){
        fp = fopen("do_not_delete.arghya", "w");
        for(int i = 0; i < 5; i++){
            fprintf(fp, "%d\n", maxScore[i]);
        }
        fclose(fp);
    }

    else{
        for(int i = 0; i < 5; i++){
            fscanf(fp, "%d", &maxScore[i]);
        }
        // fscanf(fp, "%d%d%d%d%d", &maxScore[0], &maxScore[1], &maxScore[2], &maxScore[3], &maxScore[4]);
        fclose(fp);

    }

}

void scoreSave(){

    FILE *fp;

    fp = fopen("do_not_delete.arghya", "w");
    for(int i = 0; i < 5; i++){
        fprintf(fp, "%d\n", maxScore[i]);
    }
    fclose(fp);
    
    // printf("Hello\n");
    // Sleep(1000);

}

void welcomeMessage(){ //--------------------------------------------------------------------------
    
    //to add any line in welcome message, add a string here;
    char welcome[35] = "Welcome";
    char name[35] = "Console-Based Snake Game";
    char start[35] = "Press any key to start";
    char scoreShow[35] = "Press 'h' to see high score";

    //to add any line in welcome message, add a XLine and XMargine variable to store line number and indentation;
    int firstLine = 7;
    int firstMargine = strlen(welcome) / 2 * -1;

    int secondLine = 8;
    int secondMargine = strlen(name) / 2 * -1;

    int thirdLine = 11;
    int thirdMargine = strlen(start) / 2 * -1;
    
    int forthLine = 13;
    int forthMargine = strlen(scoreShow) / 2 * -1;

    setCursor(boundaryStartX, boundaryStartY);

    //to add any line in welcome message, add a else if and print the string and increase the value of j;
    for(int i = boundaryStartY; i <= boundaryEndY; i++){
        for(int j = boundaryStartX; j <= boundaryEndX; j++){

            if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                if(!(j & 1)){
                    printf("%s", BLUE);
                    printf("%c", boundaryChar);
                }
                else printf("%c", spaceChar);
            }

            else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 + firstMargine){
                printf("%s", CYAN);
                printf("%s", welcome);
                j += strlen(welcome) - 1;
            }

            else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 + secondMargine){
                printf("%s", CYAN);
                printf("%s", name);
                j += strlen(name) - 1;
            }

            else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 + thirdMargine){
                printf("%s", CYAN);
                printf("%s", start);
                j += strlen(start) - 1;
            }

            else if(i == boundaryStartY + forthLine && j == boundaryEndX / 2 + forthMargine){
                printf("%s", CYAN);
                printf("%s", scoreShow);
                j += strlen(scoreShow) - 1;
            }

            else{
                printf("%c", spaceChar);
            }

        }
        printf("\n");
    }

    while(1){
        if(_kbhit()){
            int newInput = _getch();
            if(newInput == 0 || newInput == 224){
                newInput = _getch();
            }
            
            if(newInput == 'h' || newInput == 'H'){
                showCurrentHighScores();
            }else break;

            Sleep(50);
        }
    }

    

}

void showCurrentHighScores(){

    //to add any line in welcome message, add a string here;
    char highScores[35] = "High Scores:";
    char easy[38] =      "Easy      :";
    char medium[38] =    "Medium    :";
    char hard[38] =      "Hard      :";
    char extreme[38] =   "Extreme   :";
    char legendary[38] = "Legendary :";
    char back[38] = "Press any key to back";

    //to add any line in welcome message, add a XLine and XMargine variable to store line number and indentation;
    int firstLine = 5;
    int firstMargine = strlen(highScores) / 2;

    int secondLine = 7;
    int secondMargine = strlen(easy) / 2 + 3;

    int thirdLine = 8;
    int thirdMargine = strlen(medium) / 2 + 3;
    
    int forthLine = 9;
    int forthMargine = strlen(hard) / 2 + 3;
    
    int fifthLine = 10;
    int fifthMargine = strlen(extreme) / 2 + 3;
    
    int sixthLine = 11;
    int sixthMargine = strlen(legendary) / 2 + 3;
    
    int seventhLine = 13;
    int seventhMargine = strlen(back) / 2;

    setCursor(boundaryStartX, boundaryStartY);

    //to add any line in welcome message, add a else if and print the string and increase the value of j;
    for(int i = boundaryStartY; i <= boundaryEndY; i++){
        for(int j = boundaryStartX; j <= boundaryEndX; j++){

            if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                if(!(j & 1)){
                    printf("%s", BLUE);
                    printf("%c", boundaryChar);
                }
                else printf("%c", spaceChar);
            }

            else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 - firstMargine){
                printf("%s", CYAN);
                printf("%s", highScores);
                j += strlen(highScores) - 1;
            }

            else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 - secondMargine){
                printf("%s", CYAN);
                printf("%s %4d", easy, maxScore[0]);
                j += strlen(easy) + 4;
            }

            else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 - thirdMargine){
                printf("%s", CYAN);
                printf("%s %4d", medium, maxScore[1]);
                j += strlen(medium) + 4;
            }

            else if(i == boundaryStartY + forthLine && j == boundaryEndX / 2 - forthMargine){
                printf("%s", CYAN);
                printf("%s %4d", hard, maxScore[2]);
                j += strlen(hard) + 4;
            }
            
            else if(i == boundaryStartY + fifthLine && j == boundaryEndX / 2 - fifthMargine){
                printf("%s", CYAN);
                printf("%s %4d", extreme, maxScore[3]);
                j += strlen(extreme) + 4;
            }
            
            else if(i == boundaryStartY + sixthLine && j == boundaryEndX / 2 - sixthMargine){
                printf("%s", CYAN);
                printf("%s %4d", legendary, maxScore[4]);
                j += strlen(legendary) + 4;
            }
            
            else if(i == boundaryStartY + seventhLine && j == boundaryEndX / 2 - seventhMargine){
                printf("%s", CYAN);
                printf("%s", back);
                j += strlen(back) - 1;
            }

            else{
                printf("%c", spaceChar);
            }

        }
        printf("\n");
    }

    getch();
    welcomeMessage();
}

void gameEngine(){ //-------------------------------------------------------------------------------------
    
    snakeHeadX = boundaryEndX / 2; //if(snakeHeadX & 1) snakeHeadX++;
    snakeHeadY = boundaryEndY / 2;
    keyInput = 'w';
    score = 0;
    snakeLength = 3;
    isPause = false;
    isNewHighScore = false;

    for(int i = 0; i < snakeLength - 1; i++){
        snakeTailX[i] = snakeHeadX;
        snakeTailY[i] = snakeHeadY;
    }

    foodSetup();
    printInGameScreen();

    while(1){
        food();
        inGameInput();
        if(isPause) pauseScreen();
        snakeMovement();
        printInGameScreen();
        if(isGameOver()){
            scoreSave();
            gameOverScreen();
            if(gameOverArrow == 1){
                setup();
            } 
            else if(gameOverArrow == 2){
                exit(0);
            } 
        } 

        Sleep(refreshRate);
    }
}

void pauseScreen(){

    char gamePausedString[35] = "Game Paused";
    char restart[38] = "Restart";
    char resume[38] = "Resume";

    int firstLine = 7;
    int firstMargine = strlen(gamePausedString) / 2 * -1;

    int secondLine = 10;
    int secondMargine = strlen(restart) / 2 * -1;

    int thirdLine = 9;
    int thirdMargine = strlen(resume) / 2 * -1;


    // system("cls");

    setCursor(boundaryStartX, boundaryStartY);

    while(1){

        int currentInput = 0;

        if(_kbhit()){
            currentInput = _getch();

            if(currentInput == 'p' || currentInput == 'P'){
                system("cls");
                isPause = false;
                return;
            }else if(currentInput == 'r' || currentInput == 'R'){
                setup();
            }

        }
        setCursor(boundaryStartX, boundaryStartY);

        title();

        for(int i = boundaryStartY; i <= boundaryEndY; i++){
            for(int j = boundaryStartX; j <= boundaryEndX; j++){

                if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                    if(!(j & 1)){
                        printf("%s", BLUE);
                        printf("%c", boundaryChar);
                    }
                    else printf("%c", spaceChar);
                }

                else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 + firstMargine){
                    printf("%s", CYAN);
                    printf("%s", gamePausedString);
                    j += strlen(gamePausedString) - 1;
                }

                else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 + secondMargine){
                    printf("%s", CYAN);
                    printf("%s", restart);
                    j += strlen(restart) - 1;
                }

                else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 + thirdMargine){
                    printf("%s", CYAN);
                    printf("%s", resume);
                    j += strlen(resume) - 1;
                }

                else{
                    printf("%c", spaceChar);
                }
            }

            printf("\n");
        }

    }
}

void inGameInput(){
    if(_kbhit()){
        int newInput = _getch();
        if(newInput == 0 || newInput == 224){
            newInput = _getch();
        }
        
        if(newInput == 'w' || newInput == 72 || newInput == 'a' || newInput == 75 || newInput == 's' || newInput == 80 || newInput == 'd' || newInput == 77){
            if((newInput == 'w' || newInput == 72) && (keyInput == 's' || keyInput == 80)) return;
            if((newInput == 's' || newInput == 80) && (keyInput == 'w' || keyInput == 72)) return;
            if((newInput == 'a' || newInput == 75) && (keyInput == 'd' || keyInput == 77)) return;
            if((newInput == 'd' || newInput == 77) && (keyInput == 'a' || keyInput == 75)) return;
            
            keyInput = newInput;
        }

        else if(newInput == 'p' || newInput == 'P') isPause = true;
    }
}

void snakeMovement(){  //-------------------------------------------------------------------------------------
    
    //shohan start
    for(int i = snakeLength - 1; i > 0; i--){
        snakeTailX[i] = snakeTailX[i - 1];
        snakeTailY[i] = snakeTailY[i - 1];
    }

    snakeTailX[0] = snakeHeadX;
    snakeTailY[0] = snakeHeadY;
    //shohan end

    
    //gameOverArrow key ascii value. up = 72; down = 80; left = 75; right = 77; enter 13;
    if(keyInput == 'w' || keyInput == 72){
        snakeHeadY--;
    }else if(keyInput == 'a' || keyInput == 75){
        snakeHeadX--;
        snakeHeadX--;
    }else if(keyInput == 's' || keyInput == 80){
        snakeHeadY++;
    }else if(keyInput == 'd' || keyInput == 77){
        snakeHeadX++;
        snakeHeadX++;
    }


    
}

bool isGameOver(){
    if(snakeHeadY == boundaryStartY || snakeHeadY == boundaryEndY || snakeHeadX == boundaryStartX || snakeHeadX == boundaryEndX){
        return true;
    }
    
    for(int i = 0; i < snakeLength - 1; i++){
        if(snakeHeadX == snakeTailX[i] && snakeHeadY == snakeTailY[i]){
            return true;
        }
    }
    
    return false;
}

void gameOverScreen(){

    int inputArrow = 1;
    gameOverArrow = 1;

    char congo[36] = "Congratulation";
    char newHigh[36] = "New high score:";
    char gameOverString[35] = "Game Over";
    char restart[38] = "Restart";
    char exit[38] = "Exit";

    int firstLine = 7;
    int firstMargine = strlen(congo) / 2 * -1;

    int secondLine = 8;
    int secondMargine = strlen(newHigh) / 2 * -1 - 2;

    int thirdLine = 10;
    int thirdMargine = strlen(gameOverString) / 2 * -1;

    int forthLine = 12;
    int forthMargine = strlen(restart) / 2 * -1;

    int fifthLine = 13;
    int fifthMargine = strlen(exit) / 2 * -1;

    Sleep(100);
    system("cls");

    while(1){

        if(_kbhit()){
            inputArrow = _getch();

            if(inputArrow == 0 || inputArrow == 224){
                inputArrow = _getch();
                //gameOverArrow key ascii value. up = 72; down = 80; left = 75; right = 77; enter 13;
                if(inputArrow == 80 || inputArrow == 77) gameOverArrow++;
                else if(inputArrow == 72 || inputArrow == 75) gameOverArrow--;

                if(gameOverArrow == 0) gameOverArrow = 2;
                else if(gameOverArrow == 3) gameOverArrow = 1;
            }

            else if(inputArrow == 13){
                break;
            }
        }
        setCursor(boundaryStartX, boundaryStartY);

        for(int i = boundaryStartY; i <= boundaryEndY; i++){
            for(int j = boundaryStartX; j <= boundaryEndX; j++){

                if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                    if(!(j & 1)){
                        printf("%s", BLUE);
                        printf("%c", boundaryChar);
                    }
                    else printf("%c", spaceChar);
                }

                else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 + firstMargine && isNewHighScore){
                    printf("%s", CYAN);
                    printf("%s", congo);
                    j += strlen(congo) - 1;
                }
                
                else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 + secondMargine && isNewHighScore){
                    printf("%s", CYAN);
                    printf("%s %4d", newHigh, maxScore[currentLevelArrow - 1]);
                    j += strlen(newHigh) + 4;
                }
                
                else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 + thirdMargine){
                    printf("%s", CYAN);
                    printf("%s", gameOverString);
                    j += strlen(gameOverString) - 1;
                }

                else if(i == boundaryStartY + forthLine && j == boundaryEndX / 2 + forthMargine){
                    if(gameOverArrow == 1){
                        printf("%s", GREEN);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", CYAN);
                    printf("%s", restart);
                    j += strlen(restart) - 1;
                }

                else if(i == boundaryStartY + fifthLine && j == boundaryEndX / 2 + fifthMargine){
                    if(gameOverArrow == 2){
                        printf("%s", GREEN);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", CYAN);
                    printf("%s", exit);
                    j += strlen(exit) - 1;
                }

                else{
                    printf("%c", spaceChar);
                }
            }

            printf("\n");
        }

    }
}

void title(){  //-------------------------------------------------------------------------------------

    printf("%s", RESET);
    printf("Snake Game"); 

    if(currentLevelArrow == 1){
        printf("%s", WHITE);
        char dificultyString[10] = "Easy";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 
    else if(currentLevelArrow == 2){
        printf("%s", CYAN);
        char dificultyString[10] = "Medium";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 
    else if(currentLevelArrow == 3){
        printf("%s", GREEN);
        char dificultyString[10] = "Hard";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 
    else if(currentLevelArrow == 4){
        printf("%s", BLUE);
        char dificultyString[10] = "Extreme";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 
    else if(currentLevelArrow == 5){
        printf("%s", RED);
        char dificultyString[10] = "Legendary";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 

    
    
}

void scorePrint(){  //-------------------------------------------------------------------------------------
    printf("%s", RESET);
    printf("Max Score: %3d", maxScore[currentLevelArrow - 1]);
    for(int i = 0; i < boundaryEndX - 31; i++) printf(" ");
    printf("Current Score: %3d\n", score);
    printf("Press 'p' for pause and resume\n" );
    
}

void levelChoose(){  //-------------------------------------------------------------------------------------

    int pressedKey;
    currentLevelArrow = 1;
    refreshRate = 500;

    //to add any line in welcome message, add a string here;
    char level[38] = "Please choose a level";
    char level2nd[38] = "and press enter";
    char easy[38] = "Easy";
    char medium[38] = "Medium";
    char hard[38] = "Hard";
    char extreme[38] = "Extreme";
    char legendary[38] = "Legendary";

    //to add any line in welcome message, add a XLine and XMargine variable to store line number and indentation;
    int firstLine = 5;
    int firstMargine = strlen(level) / 2 * -1;
    
    int first2Line = 6;
    int first2Margine = strlen(level2nd) / 2 * -1;

    int secondLine = 8;
    int secondMargine = strlen(easy) / 2 * -1;

    int thirdLine = 9;
    int thirdMargine = strlen(medium) / 2 * -1;

    int forthLine = 10;
    int forthMargine = strlen(hard) / 2 * -1;

    int fifthLine = 11;
    int fifthMargine = strlen(extreme) / 2 * -1;
    
    int sixthLine = 12;
    int sixthMargine = strlen(legendary) / 2 * -1;

    setCursor(boundaryStartX, boundaryStartY);

    while(1){

        // Sleep(200);

        if(_kbhit()){

            pressedKey = _getch();

            if(pressedKey == 0 || pressedKey == 224){

                pressedKey = _getch();

                //gameOverArrow key ascii value. up = 72; down = 80; left = 75; right = 77; enter 13;
                if(pressedKey == 80 || pressedKey == 77) currentLevelArrow++;
                else if(pressedKey == 72 || pressedKey == 75) currentLevelArrow--;

                if(currentLevelArrow == 0) currentLevelArrow = 5;
                else if(currentLevelArrow == 6) currentLevelArrow = 1;

                switch(currentLevelArrow){
                    case 1:
                        refreshRate = 500;
                        break;
                    case 2:
                        refreshRate = 250;
                        break;
                    case 3:
                        refreshRate = 125;
                        break;
                    case 4:
                        refreshRate = 62;
                        break;
                    case 5:
                        refreshRate = 20;
                        break;
                }
            }
            
            else if(pressedKey == 13){
                break;
            }
        }

        setCursor(boundaryStartX, boundaryStartY);
        //to add any line in welcome message, add a else if and print the string and increase the value of j;
        for(int i = boundaryStartY; i <= boundaryEndY; i++){
            for(int j = boundaryStartX; j <= boundaryEndX; j++){

                if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                    if(!(j & 1)){
                        printf("%s", BLUE);
                        printf("%c", boundaryChar);
                    }
                    else printf("%c", spaceChar);
                }

                else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 + firstMargine){
                    printf("%s", CYAN);
                    printf("%s", level);
                    j += strlen(level) - 1;
                }

                else if(i == boundaryStartY + first2Line && j == boundaryEndX / 2 + first2Margine){
                    printf("%s", CYAN);
                    printf("%s", level2nd);
                    j += strlen(level2nd) - 1;
                }

                else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 + secondMargine){
                    if(currentLevelArrow == 1){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", WHITE);
                    printf("%s", easy);
                    j += strlen(easy) - 1;
                }

                else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 + thirdMargine){
                    if(currentLevelArrow == 2){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", CYAN);
                    printf("%s", medium);
                    j += strlen(medium) - 1;
                }

                else if(i == boundaryStartY + forthLine && j == boundaryEndX / 2 + forthMargine){
                    if(currentLevelArrow == 3){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", GREEN);
                    printf("%s", hard);
                    j += strlen(hard) - 1;
                }

                else if(i == boundaryStartY + fifthLine && j == boundaryEndX / 2 + fifthMargine){
                    if(currentLevelArrow == 4){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", BLUE);
                    printf("%s", extreme);
                    j += strlen(extreme) - 1;
                }

                else if(i == boundaryStartY + sixthLine && j == boundaryEndX / 2 + sixthMargine){
                    if(currentLevelArrow == 5){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", RED);
                    printf("%s", legendary);
                    j += strlen(legendary) - 1;
                }

                else{
                    printf("%c", spaceChar);
                }

            }
            printf("\n");
        }
    }
}

void printInGameScreen(){ //print every frame --------------------------------------------------------------

    setCursor(boundaryStartX, boundaryStartY);

    title();

    for(int i = boundaryStartY; i <= boundaryEndY; i++){
        for(int j = boundaryStartX; j <= boundaryEndX; j++){

            if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                if(!(j & 1)){
                    printf("%s", BLUE);
                    printf("%c", boundaryChar);
                }
                else printf("%c", spaceChar);
            }

            else if(i == snakeHeadY && j == snakeHeadX){
                printf("%s", CYAN);
                printf("%c", snakeHeadChar);
            }
            
            else if(i == foodPositionY && j == foodPositionX){
                printf("%s", RED);
                printf("%c", foodChar);
            }

            else{
                bool isPrinted = false;
                for(int k = 0; k < snakeLength - 1; k++){
                    if(snakeTailY[k] == i && snakeTailX[k] == j){
                        printf("%s", GREEN);
                        printf("%c", snakeBodyChar);
                        isPrinted = true;
                        break;
                    }
                }
                if(!isPrinted) printf("%c", spaceChar);
            }
        }

        printf("\n");
    }
    scorePrint();
    // snakeHeadY++;
}

void foodSetup(){

    foodPositionX = 0;
    foodPositionY = 0;

    while(1){

        srand(time(NULL));
        foodPositionX = (rand() % (boundaryEndX - boundaryStartX - 3)) + 2;
        if(foodPositionX & 1) foodPositionX++;

        // srand(time(NULL));
        foodPositionY = (rand() % (boundaryEndY - boundaryStartY - 3)) + 2;


        if(!((foodPositionX == snakeHeadX) && (foodPositionY == snakeHeadY || foodPositionY == snakeHeadY + 1 || foodPositionY == snakeHeadY + 2))) break;
    }
}

void food(){

    if(!(snakeHeadX == foodPositionX && snakeHeadY == foodPositionY) && currentLevelArrow != 5){
        return;
    }
    else if((snakeHeadX == foodPositionX && snakeHeadY == foodPositionY) && currentLevelArrow == 5){
        score += 10;
        if(score > maxScore[currentLevelArrow - 1]){
            maxScore[currentLevelArrow - 1] = score;
            isNewHighScore = true;
        } 
        snakeLength++;
        Beep(750, 100);
    }

    if(currentLevelArrow == 5){
        foodPositionX = 0;
        foodPositionY = 0;
        while(1){
            srand(time(NULL));
            foodPositionX = (rand() % (boundaryEndX - boundaryStartX - 3)) + 2;
            if(foodPositionX & 1) foodPositionX++;
            // Sleep(3);
            srand(time(NULL));
            foodPositionY = (rand() % (boundaryEndY - boundaryStartY - 3)) + 2;
            if(!(foodPositionX == snakeHeadX && foodPositionY == snakeHeadY) && !(overlapWithBody(foodPositionX, foodPositionY))) break;
        }
        return;
    }

    score += 10;
    if(score > maxScore[currentLevelArrow - 1]){
        maxScore[currentLevelArrow - 1] = score;
        isNewHighScore = true;
    } 
    snakeLength++;
    Beep(750, 100);

    

    while(1){

        srand(time(NULL));
        foodPositionX = (rand() % (boundaryEndX - boundaryStartX - 3)) + 2;
        if(foodPositionX & 1) foodPositionX++;

        Sleep(3);
        srand(time(NULL));
        foodPositionY = (rand() % (boundaryEndY - boundaryStartY - 3)) + 2;

        if(!(foodPositionX == snakeHeadX && foodPositionY == snakeHeadY) && !(overlapWithBody(foodPositionX, foodPositionY))) break;
    }
}

bool overlapWithBody(int x, int y){

    //shohan start
    for(int i = 0; i < snakeLength; i++){
        if(snakeTailX[i] == x && snakeTailY[i] == y){
            return true;
        }
    }
    return false;
    //shohan end

}

void hideCursor(){ //ChatGPT generated ----------------------------------------------------------------
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(out, &cursor);
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(out, &cursor);
}

void setCursor(short x, short y){ //ChatGPT generated -------------------------------------------------------
    COORD position = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}