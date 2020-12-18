//Sources for BAM:
//https://www.globalspec.com/reference/14722/160210/Chapter-7-5-3-Binary-Angular-Measure
//https://en.wikipedia.org/wiki/Binary_scaling#:~:text=The%20terms%20binary%20angular%20measurement,computer%20games%2C%20and%20digital%20sensors.
//https://stackoverflow.com/questions/15691027/hex-to-binary-angle-measurement-bams-in-any-language
//https://stackoverflow.com/questions/1048945/getting-the-computer-to-realise-360-degrees-0-degrees-rotating-a-gun-turret
#include <vector>
#include <unordered_map>
#include <deque>
#include <set>
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <sstream>
#include <regex>

using namespace std;
using std::cout;

class boat{
   private:
      int positionEW{0};
      int positionNS{0};
      int8_t rotation{0x40};
      bool flippedNS{false};
      bool flippedEW{false};
      char facing{'E'};
      void changeDirection(char turn, int degrees);
      void rotate(int degrees);
      double toBam(int degrees);
      int toDegrees(uint8_t bams);
   public:
      boat(){};
      boat(int positionEW, int positionNS): positionEW(positionEW), positionNS(positionNS) {};
      void moveBoat(char instruction, int distance, bool isWaypoint=false);
      int getManhattanDistance();
      void moveToWaypoint(boat wp, int value);
};

template<typename T>
void swapVariables(T &a, T &b){
      T temp = a;
      a = b;
      b = temp;
}

void boat::moveToWaypoint(boat wp, int value){
   
   cout<<endl;
   cout<<boolalpha<<"flipped bits: "<<wp.flippedEW<<" "<<wp.flippedNS<<endl;
   cout<<"Waypoint facing: "<<wp.facing<<" ";
   cout<<"Degrees: "<<toDegrees(wp.rotation)<<endl;
   cout<<"Position wp: "<<wp.positionEW<<", "<<wp.positionNS<<endl;
   cout<<"Position boat: "<<positionEW<<", "<<positionNS<<endl;
   positionEW=positionEW+value*wp.positionEW;
   positionNS=positionNS+value*wp.positionNS;
   cout<<"After Position wp: "<<wp.positionEW<<", "<<wp.positionNS<<endl;
   cout<<"After Position boat: "<<positionEW<<", "<<positionNS<<endl;
   cout<<endl;
   
}

double boat::toBam(int degrees){
   return (double)(degrees/180.0)*(1<<(8  - 1)); //convert degrees to BAM

}

int boat::toDegrees(uint8_t bams){
   return (int)(bams*180.0)/(1<<(8  - 1)); //convert degrees to BAM
}

void boat::rotate(int degrees){

   switch(abs(degrees)){
      case 90:
         if(degrees<0){
            positionEW*=-1;
         }else{
            positionNS*=-1;
         }
            swapVariables<int>(positionEW,positionNS);
         break;
      case 180:
            positionNS*=-1;
            positionEW*=-1;
         break;
      case 270:
         if(degrees<0){
            positionNS*=-1;
         }else{
            positionEW*=-1;
         }
            swapVariables<int>(positionEW,positionNS);
         break;

   }

   int8_t bams = toBam(degrees);
   //cout<<"ROTATION :"<< toDegrees(rotation)<<endl;
   //cout<<"DEGREE:"<<degrees<<endl;
   rotation = rotation+bams;
   //cout<<"ROTATION :"<< toDegrees(rotation)<<endl;
   switch(toDegrees(rotation)){
      case 90:
         facing = 'E';
         break;
      case 180:
         facing = 'N';
         break;
      case 360: //fall through
      case 0:
         facing = 'S';
         break;
      case 270:
         facing = 'W';
         break;
      default:
         cout<<"ERROR INVALID ANGLE"<<endl;
   }

}

void boat::changeDirection(char turn, int degrees ){
   if(turn == 'L'){
      rotate(degrees);
   }else if(turn == 'R'){
      rotate(-degrees);
   }else{
      cout<<"INVALID TURN INSTRUCTION";
   }
}

int boat::getManhattanDistance(){
   cout<<"FACING: "<<facing<<" ";
   cout<<"EW: "<<positionEW;
   cout<<" NS: "<<positionNS<<endl;
   return abs(positionEW) + abs(positionNS);
}

void boat::moveBoat(char instruction, int value, bool isWaypoint){
   if(instruction=='F') instruction = facing;
   int tempNS = positionNS;
   int tempEW = positionEW;
   switch(instruction) {
      case 'N':
       positionNS+=value;
       if(isWaypoint && (positionNS ^ tempNS) <0){ //sign change
           if(facing == 'S'){
            positionEW*=-1;
            positionNS*=-1;
            changeDirection('R', 180);
           }
       }
       break;
      case 'S':
       positionNS-=value;
       if(isWaypoint && (positionNS ^ tempNS) <0){ //sign change
           if(facing == 'N'){
            positionEW*=-1;
            positionNS*=-1;
            changeDirection('R', 180);
           }
       }
         break;
      case 'E':
       positionEW+=value;
       if(isWaypoint &&(positionEW ^ tempEW) <0){ //sign change
           if(facing == 'W'){
            positionEW*=-1;
            positionNS*=-1;
            changeDirection('R', 180);
           }
       }
         break;
      case 'W':
       positionEW-=value;
       if(isWaypoint &&(positionEW ^ tempEW) <0){ //sign change
           if(facing == 'E'){
            positionEW*=-1;
            positionNS*=-1;
            changeDirection('R', 180);
           }
       }
         break;
      case 'L': //allow fall through
      case 'R':
         changeDirection(instruction, value);
         break;
      default:
         cout<<endl<<"ERROR INVALID INSTRUCTION"<<endl;
   }

}

int main(){
   
   ifstream file{"i.txt"};

   string row;
   boat ferry{};
   boat ferryP2{};
   boat waypoint{10, 1};
   while(getline(file,row)){
      istringstream line {row};
      char position;
      int value;
      vector<char> rowValues;
      line>>position;
      line>>value;
 //     ferry.moveBoat(position, value);
      if(position == 'F'){
         ferryP2.moveToWaypoint(waypoint, value);
      }else{
         waypoint.moveBoat(position,value,true);
      }
   }

//   cout<<"P1 Result: "<<ferry.getManhattanDistance()<<endl;
   cout<<"P2 Result: "<<ferryP2.getManhattanDistance();

}

