//
//  Maize.h
//  Assignment2
//  This file has the classes for solving maize
//  Maize class represents maize.
//  Point class represents a point in maize
//  Path represents a path segment of continues move points in one direction
//  MaizeRunner class runs the maize to find the exit

//  Created by Om Soni on 6/09/18.
//  Copyright © 2018 Om Soni. All rights reserved.


#include <string>
#include <stdexcept>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

enum Direction { NORTH, SOUTH, EAST, WEST} ;
std::string enumArr[4] = {"NORTH", "SOUTH", "EAST", "WEST"};
//Point class represents a point in maize
//MaizeRunner class tracks the position by flagging points

class Point {
public:
    int x, y;
    explicit Point(int _x,int _y){
        x=_x; y=_y;
    }

    Point(){}
    
    //Is this point on Path
    bool isOnPath() {
        return onPath;
    }
    //set true if this point is on path
    void setOnPath(bool _onPath){
        onPath = _onPath;
    }
    // flag if the Path with this Point is already traversed by MaizeRunner
    // So that is does not loop
    void flag() {
        flagged = true;
    }
    
    const std::string to_string(){
        return '(' + std::to_string(x) + "," + std::to_string(y) + ')';
    }

    friend std::ostream& operator << (std::ostream &strm, Point &p) {
        return   strm << p.to_string() ;
    }
    
private:
    bool flagged = false ;
    bool onPath = false;
};

//Path connects a line segment between two points that can be
// run continuously by MaizeRunner

class Path {
public:
    explicit Path(Point p): beginPoint(p){
    }
    Path(){}
    void setBeginPoint(Point p) {
        beginPoint = p ;
    }
    Point getBeginPoint() {
        return beginPoint;
    }
    void setEndPoint(Point p) {
        endPoint = p ;
    }
    Point getEndPoint() {
        return endPoint;
    }
    Direction getPathDirection() {
        return pathDirection;
    }
    void setPathDirection(Direction d){
        pathDirection = d ;
    }
    
    const std::string to_string(){
        return "Path:" + beginPoint.to_string() + " to " + endPoint.to_string() + " in direction "  + enumArr[pathDirection];
    }
    
    friend std::ostream& operator << (std::ostream &strm, Path &p) {
        return   strm << p.to_string() ;
    }
    
private:
    bool traversed = false ;
    Point beginPoint ;
    Point endPoint;
    Direction pathDirection ;
};

//Maize class represents the maize to be solved
// The builder pattern is used to build this class
class Maize {
public:
    explicit Maize(char **_maize, long l, long w) {
        length = l;
        width = w;
        maizepoints = buildMaize(_maize,l,w);
        std::cout << "Maize object is built !!\n"  ;
    }
    
    Point getPoint(int i, int j){
        return maizepoints[i][j];
    }
 
    Point getEntrance() {
        return entrance;
    }
    
    Point getExit() {
        return exit ;
    }
    
    Direction getEntranceSide() {
        return entranceSide;
    }
    
    Point** getMaizePoints(){
        return maizepoints;
    }
    
    long getMaizeLength(){
        return length ;
    }
    long getMaizeWidth(){
        return width;
    }
    char** getRawMaize() {
        return rawmaize;
    }
    
private:
    Point **maizepoints;
    Direction entranceSide ;
    Point entrance ;
    Point exit ;
    long length=0, width=0;
    char** rawmaize ;
    
    // uses builder pattern to build the object
    Point**  buildMaize(char *maize[], long l, long w) {
        maizepoints = new Point*[w];
        rawmaize = maize;
        for (int i=0; i < l; i++)
            maizepoints[i] = new Point[w];
        
        for (int i=0; i<l; i++) {
            for (int j=0;j<w; j++){
                Point p =  Point(i,j);
                
                if (maize[i][j] == '.'){
                    p.setOnPath(true);
                    if (i==0 || j==0) {
                        entrance=p;
                        i==0?entranceSide=SOUTH:i==(l-1)?entranceSide=NORTH:j==0?entranceSide=EAST:entranceSide=WEST;
                    }
                    else if ( i==(l-1) || j==(w-1)) {
                        exit=p;
                    }
                }
                maizepoints[i][j] = p ;
            }

        }
        /*
        for (int i=0; i<l; i++) {
            for (int j=0;j<w; j++){
                std::cout << "maize point is " << maizepoints[i][j].x << "  " << maizepoints[i][j].y;
            }
        }
         */
        return maizepoints;
    }
};


// MaizeRunner class runs the maize
// It is a singlton but can be multiple runners competing
// Clsas is not tested for multiple runners
class MaizeRunner {
    
public:
    explicit MaizeRunner(Maize mz): maize(mz){
        currentDirection = maize.getEntranceSide();
    }
    
    void enterMaize() {
        //look for entrance on perimeter of maize
        currentPos = maize.getEntrance();
       
        Point exit = maize.getExit();
        
//        if (currentPos == nullptr)
//            throw "No entrance found to Maize. Not entering..";
    }
    
    void goback() {
        //look for entrance on perimeter of maize
    }
    
    void moveTo(Point pos) {
        currentPos = pos;
    }
    
    void run() {
        Path path = Path(currentPos);
        path.setPathDirection(currentDirection);
        bool solved = false;
        do {
            solved = mazeTraverse(path);
            if (solved) {
                std::cout << "MaizeRunner has successfully solved the maize !! \n\n";
                printSolve();
                exit(0);
            }
            if(junctions.empty())
               break;
            path = junctions.back(); //get next path
            junctions.pop_back();
            Point point = path.getBeginPoint();
            currentPos = point;
        } while (true);
    }

    //function that Traverses the maize
    bool mazeTraverse(Path path) {
        Point currentPoint = path.getBeginPoint();
        currentDirection = path.getPathDirection();
        Direction pathDirection ;
        currentPoint.flag();
        bool hasPath = true;
        int i = currentPoint.x; int j = currentPoint.y ;
        Point nextPoint;
        Path nextPath = Path();
        do {
            Point leftpoint = getLeftPoint(currentPoint);
            if (leftpoint.isOnPath()) {
                hasPath =true;
                currentDirection==NORTH?pathDirection=WEST:currentDirection==SOUTH?pathDirection=EAST:currentDirection==EAST?pathDirection=NORTH:pathDirection=SOUTH;
                nextPath = Path(leftpoint);
                nextPath.setPathDirection(pathDirection);
                junctions.push_back(nextPath);
                if (isPointOnExit(leftpoint)) {
                    moveTo(leftpoint);
                    this->reachedExit();
                    path.setEndPoint(currentPoint);
                    solve.push_back(path);
                    currentPoint = leftpoint;
                    nextPath.setEndPoint(maize.getExit());
                    solve.push_back(nextPath);
                    return true; //solved
                }
            }
            //found segment, path ends at current point
            Point rightpoint = getRightPoint(currentPoint);
            if (rightpoint.isOnPath()) {
                hasPath =true;
                currentDirection==NORTH?pathDirection=EAST:currentDirection==SOUTH?pathDirection=WEST:currentDirection==EAST?pathDirection=SOUTH:pathDirection=NORTH;
                nextPath = Path(rightpoint);
                nextPath.setPathDirection(pathDirection);
                junctions.push_back(nextPath);
                if (isPointOnExit(rightpoint)) {
                    moveTo(rightpoint);
                    path.setEndPoint(currentPoint);
                    solve.push_back(path);
                    currentPoint = rightpoint;
                    nextPath.setEndPoint(maize.getExit());
                    solve.push_back(nextPath);
                    this->reachedExit();
                    return true; //solved
                }
            }
            
            //from current point get the next point in current direction
            currentDirection==NORTH?i--:currentDirection==SOUTH?i++:currentDirection==EAST?j++:j--;
            nextPoint =  maize.getPoint(i,j);
            if (isPointOnExit(nextPoint)) {
                
                moveTo(nextPoint);
                this->reachedExit();
                return true; //solved
            }
            //check what is on left of it
            if(nextPoint.isOnPath()) {
                moveTo(nextPoint);
                currentPoint = nextPoint;
            }
            //Follow the path as long as it is there
            else {
                currentPos.flag(); //flag that current path ended here
                path.setEndPoint(currentPoint); //set the endpoint to indicate Path is complete
                solve.push_back(path);
                break; //this path is complete
            }
        } while (true);
        //std::cout << path << "\n";
        return false ; //Not solved yet
    }
    
        Point getLeftPoint(Point p){
            int i = p.x; int j = p.y ;
            currentDirection==NORTH?j--:currentDirection==SOUTH?j++:currentDirection==EAST?i--:i++;
            return maize.getPoint(i, j);
        }
        Point getRightPoint(Point p) {
            int i = p.x; int j = p.y ;
            currentDirection==NORTH?j++:currentDirection==SOUTH?j--:currentDirection==EAST?i++:i--;
            return maize.getPoint(i, j);
        }
    
    bool isPointOnExit(Point p) {
        Point exit = maize.getExit();
        if (p.x ==exit.x && p.y == exit.y)
            return true ;
        return false;
    }
    
    void reachedExit(){
        success= true;
    }
    
    void printSolve() {
        Path previousPath ;
        bool firstpath= true;
        char** rawmaize= maize.getRawMaize();
        for(Path path: solve){
            if (!firstpath)
                path.setBeginPoint(previousPath.getEndPoint()); //Connect previous path end point to next to tell connected story
            std::cout << "Runner ran " << path << "\n";
            previousPath = path;
            Point p1 = path.getBeginPoint();
            Point p2 = path.getEndPoint();
            auto result = std::minmax(p1.x, p2.x);
            if (p1.x != p2.x) {
                for (int i=result.first; i <= result.second; i++){
                     rawmaize[i][p1.y] = 'X';
                }
            }
            else if (p1.y != p2.y) {
                auto result = std::minmax(p1.y, p2.y);
                for (int j=result.first; j <= result.second; j++) {
                    rawmaize[p2.x][j] = 'X';
            }
            firstpath =false;
        }
    }
        Point exit = maize.getExit();
        std::cout << "\nRunner successfully exited the maize at " << exit << " !!!\n\n";
        long l = maize.getMaizeLength();
         long w = maize.getMaizeWidth();
        
        for (int i=0; i<l; i++) {
            for (int j=0;j<w; j++){
                std::cout << rawmaize[i][j] << ' ';
            }
            std::cout << '\n';
        }
        
}
    

    
private:
    std::vector <Path> junctions ;
    std::vector <Path> solve ;
    Point currentPos ;
    Direction currentDirection;
    Maize maize ;
    bool success = false;
    
};
