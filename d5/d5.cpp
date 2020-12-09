#include <iostream>
#include <cmath>
#include <bitset>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class plane{
  private:
  uint_fast8_t s[128]{};
  int row = -1;
  int col = -1;

  public:


  void bitPositionFind(){
      bool reachedValidSeats = false;
      int j{0};
      for(;j<(128*8/32);j++){
      //       cout << bitset<32>(*(int *)(s+4*j))<<endl;
         if(*(int *)(s+4*j) != 0xFFFFFFFF){
            if(reachedValidSeats){
            for(int m = 0; m<4; m++){
               if(s[j*4+m]!=0xFF){
                  j=j*4 + m;
                  cout<<"J"<<j;
                  goto L1;
               }
            }
         }
         }else{
            reachedValidSeats = true;
         }
         
      }
L1:

      if(s[j] && (!(s[j] & (s[j] - 1)))){
         throw runtime_error("Not a power of 2");
      }

      uint_fast8_t i{1};
      int res{};
      cout << bitset<32>(s[j])<<endl;
      s[j]=~s[j]; // flip it
      cout << bitset<32>(s[j])<<endl;
      
      while(!(i&s[j])){
         i<<=1;
         res++;
      }

      row = j;
      col = res;
  }
   
  void removeSeat(int row, int col){
     cout<<"r: "<<row<<" col: "<<col<<endl;
//     cout<<"before: "<<endl;
//      debug();
     if(row < 0 || row > 127 ||col <0|| col>7){
         throw runtime_error("SEAT OUT OF RANGE");
     }else{
         //cout<<bitset<8>(1<<col)<<endl;
         s[row]=s[row]|(1<<col); 
     }
 //    cout<<"after: "<<endl;
//      debug();
  }

  void debug(){
     for(int i = 0; i<128; i++){
      cout<<i<<": "<<bitset<(8)>(s[i])<<endl;
     }
  }

  string getSeat(){
       debug();
       bitPositionFind();
      ostringstream str{};
      str<<endl<<"row: "<<row <<"col : "<< col<<" ANS: "<<(row*8+col)<<endl;
      return str.str();
     }

};

double mid(int u, int l){
   return ((static_cast<double>(u)+static_cast<double>(l))/2);
}

void getMax(plane &p)
{
  ifstream f("i.txt");
  string s{};

  int max = -1;
     
  while(getline(f,s)){
  
     int rL{0}, rU{127}, cL{0}, cU{7}, row{-1}, col{0}, i{0};
     while(true){
      
      if(s.length()-1<=i){
 //     cout<<s.at(i);
         if(s.at(i) == 'R'){
            col = cU;
         }else{
            col = cL;
         }
         p.removeSeat(row,col);
         break;
      }
//      cout<<s.at(i);

      if((rU-rL)==1 && row == -1){
         if(s.at(i) == 'F'){
            row = rL;
         }else{
            row = rU;
         }
         continue;
      }

      switch(s.at(i++)){
         case 'F':
            rU=floor(mid(rU,rL));
            break;
         case 'B':
            rL=ceil(mid(rU,rL));
            break;
         case 'R':
            cL=ceil(mid(cU,cL));
            break;
         case 'L':
            cU=floor(mid(cU,cL));
            break;
      }

   }
      /*
      cout<<"\trow: "<<row<<" col: "<<col<<", ";
      cout<<"\tcU: "<<cU<<" cL: "<<cL<<", ";
      cout<<"ANS: "<<row*8+col;
      cout<<"\trU: "<<rU<<" rL: "<<rL<<endl;
      if(max < (row*8+col)){
            max = row*8+col;
      }
      */
      if(max < (row*8+col)){
            max = row*8+col;
      }



   //   list.removeSeat(rL,cL);
  }
  cout<<"MAX: "<<max<<endl;
   
}


int main(){
   plane p{};
   getMax(p);
   cout<< p.getSeat();
}



