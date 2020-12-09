#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

using namespace std;

int getMatch(string s, regex r);

int main(int argc, char *argv[])
{
   string str{""};

   ifstream file("index.txt");
    regex r2{"byr:1[2-9]\\d{2}|byr:200[0-2]|iyr:2020|iyr:201\\d|eyr:202\\d|eyr:2030|hcl:#[0-9|a-f]{6}|ecl:amb|ecl:blu|ecl:brn|ecl:gry|ecl:grn|ecl:hzl|ecl:oth|pid:\\d{9}\\b|hgt:1[5-8]\\dcm|hgt:19[0-3]cm|hgt:59in|hgt:6\\din|hgt:7[0-6]in"};
regex r1{"((byr:)|(iyr:)|(eyr:)|(hgt:)|(hcl:)|(ecl:)|(pid:))"};

   string c ="";
   int valid{0};
   while(true){
      getline(file,str);
      if(file.eof() || str.length() == 0){
         if(getMatch(c,r2)== 7){
            valid++; 
         }
       if(file.eof()) break;
        c = "";
      }else{
         c+=" " + str;
      }
   }
   cout<<"ANS"<<valid;
}

int getMatch(string s, regex r){

      regex words_regex(r);
      auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
      auto words_end = std::sregex_iterator();

      cout<<endl<<"count: "<<distance(words_begin, words_end)<<endl<<" string: "<<s<<endl;
      
      return distance(words_begin, words_end);
}
