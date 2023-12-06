#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

bool checkValidCommand(string command, int &commandType);

void printInvalidCommand(){cout << "Error: invalid command";}

void printNewDatabase(int value){cout << "New database: max shapes is " << value;}

void printError(int error, string name);

bool arrayFull(int max, int current);

bool invalidShapeName(string name);

bool invalidShapeNameAll(string name, bool &all);

bool findShapeName(string name, int num, Shape** p);

bool invalidShapeType(string type);

bool notEOF(stringstream &line);

void checkName(stringstream &line, string &name, int num, int &error, bool &oops, Shape** p);

void checkNameExists(stringstream &line, string &name, int num, int &error, bool &oops, Shape** p, int &open);

void checkAllExists(stringstream &line, string &name, int num, int &error, bool &oops, Shape** p, int &open, bool &all);

bool nameDNE(string name, int num, Shape** p, int &open);

void checkType(stringstream &line, string &type, int &error, bool &oops);

void checkValue(stringstream &line, int &num, int &error, bool &oops);

void checkAngle(stringstream &line, int &angle, int &error, bool &oops);   

//void checkValueLast(stringstream &line, int &num, int &error, bool &oops);

void createNewShape(Shape** p, string name, string type, int locX, int locY, int sizeX, int sizeY, int current);

void moveShape(Shape** p, string name, int locX, int locY, int open);

void rotateShape(Shape** p, string name, int angle, int open);

void drawOne(Shape** p, string name, int open);

void drawAll(Shape** p, int num);

void deleteOne(Shape** p, string name, int open);

void deleteAll(Shape** p, int num);

int main() {

    string line;
    string command;
    shapesArray = NULL;

    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {

        stringstream lineStream (line);
        int commandType = 7;
        bool faxNoKizzy = true;
        


        

        lineStream >> command;
        string name, type;

        int locX = 0;
        int locY = 0;
        int sizeX = 0;
        int sizeY = 0;
        int value = 0;
        int angle = 0;

        int error = 10;
        int openSlot = -1;

        bool alreadyOopsies = false;
        bool all = false;

        if (lineStream.fail()){

            faxNoKizzy = false;

            printInvalidCommand();
        }

       if (checkValidCommand(command, commandType) && faxNoKizzy){ //check command is valid and returns number in array

            switch (commandType){

                case 1:                                         //case 1 maxShapes

                    if (lineStream.eof()){                      // too few args
                        error = 8;
                    } else {

                       // lineStream >> value;
                        /*if (lineStream >> value){
                            cout << "good" << endl;
                        } else {
                            cout << "bad" << endl;
                        }*/

                        if ((!(lineStream >> value) || lineStream.peek() == '.')){                        //invalid arg
                            error = 1;
                            alreadyOopsies = true;
                        } else if (value < 0) {                         //invalid value           
                            error = 6;
                            alreadyOopsies = true;
                        }  
                                                             // all good make array
                        if (notEOF(lineStream) && !alreadyOopsies){                   // too many args
                            error = 7;
                            alreadyOopsies = true;
                            //newError = 7;
                            //if (newError < error){error = newError;}
                        }

                        if (!alreadyOopsies){
                            if (shapesArray == NULL){
                                //uint64_t bla = (uint64_t)shapesArray;
                                //cout << bla << " 1111\n";
                                shapesArray = new Shape* [value]();
                                //bla = (uint64_t)shapesArray;
                                //cout << bla << "\n";
                                max_shapes = value;
                                printNewDatabase(value);

                            } else {
                                //uint64_t bla = (uint64_t)shapesArray;
                                //cout << bla << "\n";
                                for (int i = 0; i < max_shapes; i++){
                                    if (shapesArray[i] != NULL){

                                        delete shapesArray[i];
                                        shapesArray[i] = NULL;

                                    }
                                }

                                delete [] shapesArray;

                                shapesArray = new Shape* [value]();
                                //bla = (uint64_t)shapesArray;
                                //cout << bla << "\n";
                                max_shapes = value;
                                shapeCount = 0;
                                printNewDatabase(value);

                            }
                        }
                        

                    }
                printError(error, "");
                break;

                case 2:                                                 // case 2 Create name, type, locX, locY, sizeX, sizeY 

                    if (arrayFull(max_shapes, shapeCount)){              // check if array is full
                        error = 9;
                        //newError = 9;
                        //if (newError < error){error = newError;}
                    }

                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkName(lineStream, name, max_shapes, error, alreadyOopsies, shapesArray);          //check name valid
                    }
                                                                                                    
                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkType(lineStream, type, error, alreadyOopsies);                                 //check type
                    }
                    
                    //lineStream >> locX;
                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkValue(lineStream, locX, error, alreadyOopsies);                                            //check value 1
                    } 

                    //locY
                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkValue(lineStream, locY, error, alreadyOopsies);                                        //check value 2
                    } 

                    //lineStream >> sizeX;
                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkValue(lineStream, sizeX, error, alreadyOopsies);                                               //check value 3
                    }

                    //lineStream >> sizeY;
                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                        alreadyOopsies = true;
                    } else {
                        checkValue(lineStream, sizeY, error, alreadyOopsies);                                                //check value 4
                    }

                    if ((type == "circle") && (sizeX != sizeY) && !alreadyOopsies) {
                        error = 6;
                        alreadyOopsies = true;                                                //check value 4
                    }

                    /*if ((type == "circle") && (sizeX == sizeY) && !alreadyOopsies){
                        error = 6;
                        alreadyOopsies = true;
                    }*/

                    if (notEOF(lineStream) && !alreadyOopsies){                                                      //checks eof
                        error = 7;
                        alreadyOopsies = true;
                    }        

                    if (error == 9){
                        alreadyOopsies = true;
                    }                                                                                

                    if (!alreadyOopsies && error == 10){
                        
                        createNewShape(shapesArray, name, type, locX, locY, sizeX, sizeY, shapeCount);
                        shapeCount++;

                    } else {
                        printError(error, name);
                    }

                break;

                case 3:

                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkNameExists(lineStream, name, max_shapes, error, alreadyOopsies, shapesArray, openSlot);          //check name valid && exists
                    }

                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkValue(lineStream, locX, error, alreadyOopsies);                                            //check locX
                    }

                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkValue(lineStream, locY, error, alreadyOopsies);                                        //check locY
                    } 

                    if (notEOF(lineStream) && !alreadyOopsies){                                                      //checks eof
                        error = 7;
                        alreadyOopsies = true;
                    }

                    if (!alreadyOopsies && error == 10){

                        moveShape(shapesArray, name, locX, locY, openSlot);
                                                
                    } else {
                        printError(error, name);
                    }

                break;

                case 4:

                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkNameExists(lineStream, name, max_shapes, error, alreadyOopsies, shapesArray, openSlot);          //check name valid && exists
                    }

                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkAngle(lineStream, angle, error, alreadyOopsies);                                            //check angle
                    }

                    if (notEOF(lineStream) && !alreadyOopsies){                                                      //checks eof
                        error = 7;
                        alreadyOopsies = true;
                    }

                    if (!alreadyOopsies && error == 10){

                        rotateShape(shapesArray, name, angle, openSlot);
                                                 
                    } else {
                        printError(error, name);
                    }

                break;

                case 5:

                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkAllExists(lineStream, name, max_shapes, error, alreadyOopsies, shapesArray, openSlot, all);          //check name valid && exists
                    }

                    if (notEOF(lineStream) && !alreadyOopsies){                                                      //checks eof
                        error = 7;
                        alreadyOopsies = true;
                    }

                    if (!alreadyOopsies && error == 10){

                        if (all){
                            drawAll(shapesArray, max_shapes);
                        } else {
                            drawOne(shapesArray, name, openSlot);
                        }
                        
                    } else {
                        printError(error, name);
                    }


                break;

                case 6:

                    if (lineStream.eof() && !alreadyOopsies){
                        error = 8;
                    } else {
                        checkAllExists(lineStream, name, max_shapes, error, alreadyOopsies, shapesArray, openSlot, all);          //check name valid && exists
                    }

                    if (notEOF(lineStream) && !alreadyOopsies){                                                      //checks eof
                        error = 7;
                        alreadyOopsies = true;
                    }

                    if (!alreadyOopsies && error == 10){

                        if (all){
                            deleteAll(shapesArray, max_shapes);
                            shapeCount = 0;
                        } else {
                            deleteOne(shapesArray, name, openSlot);
                        }
                                                 
                    } else {
                        printError(error, name);
                    }

                break;

            }

       } else if (faxNoKizzy){

            printInvalidCommand();

       } 

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        
        
        
        // Once the command has been processed, prompt for the
        // next command
        cout << endl;
        lineStream.clear();
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.

    if (shapesArray != NULL){
        
        for (int i = 0; i < max_shapes; i++){

            if (shapesArray[i] != NULL){

                delete shapesArray[i];
                shapesArray[i] = NULL;

            }
        }

        delete [] shapesArray;
        shapesArray = NULL;
    }

    return 0;
}

bool checkValidCommand(string command, int &commandType){

    if (command == keyWordsList[1]){                //maxShapes     
        commandType = 1;
        return true;
    } else if (command == keyWordsList[2]){        //create
        commandType = 2;
        return true;
    } else if (command == keyWordsList[3]){         //move
        commandType = 3;
        return true;
    } else if (command == keyWordsList[4]){         //rotate
        commandType = 4;
        return true;
    } else if (command == keyWordsList[5]){         //draw
        commandType = 5;
        return true;
    } else if (command == keyWordsList[6]){         //delete
        commandType = 6;
        return true;
    }

    return false;
}

void printError(int error, string name){

    switch (error){

        case 1:                         //Invalid Arg
            cout << "Error: invalid argument";
        break;
        case 2:
            cout << "Error: invalid shape name";
        break;
        case 3:
            cout << "Error: shape " << name << " exists";
        break;
        case 4:
            cout << "Error: shape " << name << " not found";
        break;
        case 5:
            cout << "Error: invalid shape type";
        break;
        case 6:
            cout << "Error: invalid value";
        break;
        case 7:
            cout << "Error: too many arguments";
        break;
        case 8:
            cout << "Error: too few arguments";
        break;
        case 9:
            cout << "Error: shape array is full";
        break;
        case 10:                           //nothing wrong dont do anything

        break;
    }
}

bool arrayFull(int max, int current){           // true = array full
    
    if (current == max){
        return true;
    } else {
        return false;
    }

    /*for (int i = 0; i < num; i++){
        if (p[i] == NULL){
            return false;
        }
    }
    
    return true;*/
}

bool invalidShapeName(string name){                                   // true = shape name invalid

    for (int i = 0; i < NUM_KEYWORDS; i++){
        if (name == keyWordsList[i]){
            return true;
        }
    }

    for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i]){
            return true;
        }
    }

    return false;
}

bool invalidShapeNameAll(string name, bool &all){                                   // true = shape name invalid except all

    for (int i = 0; i < NUM_KEYWORDS; i++){
        if (name == keyWordsList[i]){
            if (i == 0){
                all = true;
                return false;
            } else {
                return true;
            }
        }
    }

    for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i]){
            return true;
        }
    }

    return false;
}

bool findShapeName(string name, int num, Shape** p){               // true = shape name already exists

    for (int i = 0; i < num; i++){
        if (p[i] != NULL){
            if (((p[i]) -> getName()) == name){
                return true;
            }
        }
    }

    return false;
}

bool invalidShapeType(string type){                                    // true if shape type invalid

    for (int i = 0; i < NUM_TYPES; i++){
        if (shapeTypesList[i] == type){
            return false;
        }
    }

    return true;
}

bool notEOF(stringstream &line){

    string test;

    if (line.peek() == ' ' && line >> test){
        return true;
    } else{
        return false;
    }
}

void checkName(stringstream &line, string &name, int num, int &error, bool &oops, Shape** p){          // check name valid and if already exists

    line >> name;
    
    if (invalidShapeName(name)){
        error = 2;
        oops = true;
    } else if (findShapeName(name, num, p)){
        error = 3;
        oops = true;
    }   

    return;
}

void checkNameExists(stringstream &line, string &name, int num, int &error, bool &oops, Shape** p, int &open){      // check name valid and found

    line >> name;
    bool notOk = true;

    if(invalidShapeName(name)){
        error = 2;
        oops = true;
    } else {

        for (int i = 0; i < num; i++){
            if (p[i] != NULL){
                if (name == (p[i]) -> getName()){
                    open = i;
                    notOk = false;
                }
            }
        }

        if (line.fail()){
            if (line.eof()){
                notOk = false;
                error = 8;
                oops = true;
            } else {
                notOk = true;
            }
        }

        if (notOk){
            error = 4;
            oops = true;
        }
    }
    
    /*else if (nameDNE(name, num, p, open)){
        error = 4;
        oops = true;
    }*/
}

void checkAllExists(stringstream &line, string &name, int num, int &error, bool &oops, Shape** p, int &open, bool &all){

    line >> name;
    bool notOk = true;

    if(invalidShapeNameAll(name, all)){
        error = 2;
        oops = true;
    } else if (!all){

        for (int i = 0; i < num; i++){
            if (p[i] != NULL){
                if (name == (p[i]) -> getName()){
                    open = i;
                    notOk = false;
                }
            }
        }

        if (line.fail()){
            if (line.eof()){
                notOk = false;
                error = 8;
                oops = true;
            } else {
                notOk = true;
            }
        }

        if (notOk){
            error = 4;
            oops = true;
        }
    }
    
    /*else if (nameDNE(name, num, p, open) && !all){
        error = 4;
        oops = true;
    }*/
}

bool nameDNE(string name, int num, Shape** p, int &open){

    for (int i = 0; i < num; i++){
        if (p[i] != NULL){
            if (name == (p[i]) -> getName()){
                open = i;
                return false;
            }
        }
    }

    return true;
}

void checkType(stringstream &line, string &type, int &error, bool &oops){

    line >> type;

    if (line.peek() == -1 && !oops){
        error = 8;
        oops = true;
    }

    if (invalidShapeType(type) && !oops){
        error = 5;
        oops = true;
    }

    return;
}

void checkValue(stringstream &line, int &num, int &error, bool &oops){

    line >> num;

    if (line.fail() && line.eof() && !oops){
        error = 8;
        oops = true;
    }

    if ((line.fail() || line.peek() == '.' || ((line.peek() != ' ') && (line.peek() != -1))) && !oops){
        error = 1;
        oops = true;
    } else if (num < 0 && !oops){
        error = 6;
        oops = true;
    }

    return;
}

void checkAngle(stringstream &line, int &angle, int &error, bool &oops){

    line >> angle;

     if (line.fail() && line.eof() && !oops){
        error = 8;
        oops = true;
    }

    if ((line.fail() || line.peek() == '.' || ((line.peek() != ' ') && (line.peek() != -1))) && !oops){
        error = 1;
        oops = true;
    } else if ((angle < 0 || angle > 360) && !oops){
        error = 6;
        oops = true;
    }

    return;
}

void createNewShape(Shape** p, string name, string type, int locX, int locY, int sizeX, int sizeY, int current){

    Shape *n; 
    n = new Shape(name, type, locX, sizeX, locY, sizeY);
    
    p[current] = n;
    n = NULL;

    cout << "Created " << name << ": " << type << " " << locX << " " << locY << " " << sizeX << " " << sizeY;

    /*for (int i = 0; i < max; i++){
        
        if (p[i] == NULL){

            p[i] = n;
            n = NULL;

            cout << "Created " << name << ": " << type << " " << locX << " " << locY << " " << sizeX << " " << sizeY;                               //Created my_circle: ellipse 30 40 10 10
            return;
        }
    }*/
}

void moveShape(Shape** p, string name, int locX, int locY, int open){                                   // move Shape

    (p[open]) -> setXlocation(locX);
    (p[open]) -> setYlocation(locY);

    cout << "Moved " << name << " to " << locX << " " << locY;  

}

void rotateShape(Shape** p, string name, int angle, int open){

    (p[open] -> setRotate(angle));

    cout << "Rotated " << name << " by " << angle << " degrees";                                                      //Rotated my_rectangle by 100 degrees

}

void drawOne(Shape** p, string name, int open){

    cout << "Drew " << name << ": " << (p[open]) -> getType() << " " << (p[open]) -> getXlocation() << " " << (p[open]) -> getYlocation() << " " << (p[open]) -> getXsize() << " " << (p[open]) -> getYsize();                                     

}

void drawAll(Shape** p, int num){

    cout << "Drew all shapes";

    for (int i = 0; i < num; i++){
        
        if ((p[i]) != NULL){
            cout << " " << (p[i]) -> getName() << ": " << (p[i]) -> getType() << " " << (p[i]) -> getXlocation() << " " << (p[i]) -> getYlocation() << " " << (p[i]) -> getXsize() << " " << (p[i]) -> getYsize();
        }
    }
}

void deleteOne(Shape** p, string name, int open){

    delete p[open];
    p[open] = NULL;

    cout << "Deleted shape " << name;                                   //Deleted shape my_square
}

void deleteAll(Shape** p, int num){

    for (int i = 0; i < num; i++){

        if (p[i] != NULL){

            delete p[i];
            p[i] = NULL;

        }
    }

    cout << "Deleted: all shapes";                                   //Deleted: all shapes
}
