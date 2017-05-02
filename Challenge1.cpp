/*
 * Adaptrum Coding Challenge 1
 * Programmer: Lawrence Jacobs
 *
 * This program prints a 10 x 7 picture and allows the user to
 * (1) insert a row of a certain character, (2) insert a column of a
 * certain character, (3) specify a certain character to be changed to
 * another.
 *
 * If the user inserts a new row, inserts a new column and then changes the
 * value of a particular character in the picture, printing after the
 * last of these changes has been made, the program runs in O(N^2) time.
 *
 */

#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
using namespace std;

/*Constants*/
const int WIDTH  = 7;
const int HEIGHT = 10;
const char CHAR = '.';

/*Function prototypes*/
void planPic(Grid<char>&);
void printPic(Grid<char>);
void insertRow(Grid<char>&, string, int);
void insertCol(Grid<char>&, string, int);
void copy_for_row(Grid<char>, Grid<char>&, string, int);
void copy_for_col(Grid<char>, Grid<char>&, string, int);
void printOptions();
void interact(Grid<char>&);

int main() {
    /*Set up original image*/
    Grid<char> pic(HEIGHT, WIDTH);
    planPic(pic);
    printPic(pic);

    /*Allow user to draw*/
    interact(pic);
    return 0;
}

/*
 *This function handles the user interaction with the program.
 */
void interact(Grid<char>& pic){
    string input = "";
    while (input != "quit"){
        printOptions();
        int insert_option = getInteger("Your choice: ");
        input = getLine("Choose character to add: ");
        int row;
        int col;
        switch(insert_option){
        case 1:
            row = getInteger("Choose a row: ");
            insertRow(pic, input, row);
            printPic(pic);
            break;
        case 2:
            col = getInteger("Choose a column: ");
            insertCol(pic, input, col);
            printPic(pic);
            break;
        case 3:
            row = getInteger("Specify row: ") - 1;
            col = getInteger("Specify column: ") - 1;
            if ((row, col >= 0) && row < pic.nRows && col < pic.nCols){
                pic[row][col] = input[0];
                printPic(pic);
            }
            break;
        }
    }
}

/*
 * Print the user's options
 */
void printOptions(){
    cout << "1 : Insert new row" << endl;
    cout << "2 : Insert new column" << endl;
    cout << "3 : Change existing character" << endl;
}

/*
 * Function for populating the array that
 * represents the picture
 *
 * Runs on O(N^2) time
 */
void planPic(Grid<char>& original_pic){
    for(int row = 0; row < HEIGHT; row++){
        for(int col = 0; col < WIDTH; col++){
            original_pic[row][col] = CHAR;
        }
    }
}

/*
 * Function for printing the current picture
 *
 * Runs on O(N^2) time
 */
void printPic(Grid<char> pic){
    for(int row = 0; row < pic.numRows(); row++){
        for(int col = 0; col < pic.numCols(); col++){
            cout << pic[row][col];
        }
        cout << endl;
    }
}

/*
 * Administrative function for inserting a new row into picture
 */
void insertRow(Grid<char>& original, string input, int newRow){
    Grid<char> newPic(original.numRows()+1, original.numCols());
    copy_for_row(original, newPic, input, newRow);
    original = newPic;
}

/*
 * Function for copying original picture values into new picture
 * along with new row
 *
 * Runs on O(N^2) time
 *
 */
void copy_for_row(Grid<char> original, Grid<char>& newPic, string input, int newRow){
    int expansion = 0;
    for(int row = 0; row < original.numRows(); row++){
        if(row == newRow - 1){  //insert new row
            for(int col = 0; col < original.numCols(); col++)
                newPic[row][col] = input[0];
            expansion = 1;
        }
        for(int col = 0; col < original.numCols(); col++)
            newPic[row + expansion][col] = original[row][col];
    }
}

/*
 * Administrative function for inserting a new column into picture
 */
void insertCol(Grid<char>& original, string input, int newCol){
    Grid<char> newPic(original.numRows(), original.numCols() + 1);
    copy_for_col(original, newPic, input, newCol);
    original = newPic;
}

/*
 * Function for copying original picture values into new picture
 * along with new column
 *
 * Runs on O(N^2) time
 *
 */
void copy_for_col(Grid<char> original, Grid<char>& newPic, string input, int newCol){
    int expansion = 0;
    for(int col = 0; col < original.numCols(); col++){
        if(col == newCol - 1){  //insert new column
            for(int row = 0; row < original.numRows(); row++)
                newPic[row][col] = input[0];
            expansion = 1;
        }
        for(int row = 0; row < original.numRows(); row++)
            newPic[row][col + expansion] = original[row][col];
    }
}


