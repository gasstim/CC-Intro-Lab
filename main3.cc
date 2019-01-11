/*
Tim Gass
Project 2
Due: Wed. Novemeber 2nd 11:59pm
*/
#include <iostream>
#include <string>
#include <queue>
#include <cassert>
#include <sstream>
#include <malloc.h>
#include <string.h>

using namespace std;

string convert(const string date) {
   // regex exp("(..)/(..)/(....)");
   const char *d = date.c_str();
   int len = strlen(d)+1;
   char *month = (char *)malloc(sizeof(char)*len);
   strncpy(month, d, len);
   month[len] = '\0';
   // cout << month << endl;

   char *day = strstr(month, "/");
   if (!day) {
      free(month);
      return date;
   }
   *day = '\0';
   day++;
   char *year = strstr(day, "/");
   if (!year) {
      free(month);
      return date;
   }
   *year = '\0';
   year++;
   stringstream ss;
   ss << year << "/" << month << "/" << day;
   string s = ss.str();
   free(month);
   return s;

}

class Seafood {
   friend ostream& operator<<(ostream& o, const Seafood& b)
      { return o << "Seafood[" << b.cap << "(" << b.contains << ")" << b.date << "]" << b.openChar; }
   friend bool operator<(const string i, const Seafood& b)
      //{ return convert(i) < convert(b.date); }
      { if (b.isOpen){
           return  b.date < i;
        }else{
             if (convert(i) < convert(b.date)) {
                return i > b.date;
                //cout << i << " is less than " << b.date << endl;
             } else if (convert(i) > convert(b.date)){
                return i < b.date;
                //cout << b.date << " is less than " << i << endl;
             }else{
                return i < b.date;
                //cout << i << " is the same as " << b.date << endl;
             }
        }
      }

   friend bool operator==(const int i, const Seafood& b)
      { return i == b.cap; }
   friend int operator+(const int i, const Seafood& b)
      { return i + b.cap; }
   public:
      bool operator<(const Seafood& b) const { if(b.isOpen){return date < b.date;}else return date > b.date; }
      Seafood(string date) : date(date) {}
      Seafood(string date, int c) {}
      void setCap(int c) { cap = c; }
      void setIsOpen(bool i) { isOpen = i; }
      void setContains(int c) { contains = c; }
      void setDate(string d) { date = d; }
      void setOpenChar(string s){openChar = s;}
      int getContains() { return contains; }
      string getDate() { return date; }
   private:
      int cap;
      string openChar;
      bool isOpen;
      int contains;
      string date;
      
};

class Shrimp : public Seafood{
public:
Shrimp(string date) : Seafood(date){
setIsOpen(false);
setOpenChar("c");
setCap(50);
setContains(50);
}

Shrimp(string date, int c) : Seafood(date, c){
setDate(date);
setContains(c);
setCap(50);
setIsOpen(true);
setOpenChar("o");
}
};

class Lobster : public Seafood{
public: 
Lobster(string date) : Seafood(date){
setIsOpen(false);
setOpenChar("c");
setCap(4);
setContains(4);
}
Lobster(string date, int c) : Seafood(date, c){
setDate(date);
setContains(c);
setCap(4);
setIsOpen(true);
setOpenChar("o");
}
};


class Crab : public Seafood{
public: 
Crab(string date) : Seafood(date){
setIsOpen(false);
setOpenChar("c");
setCap(6);
setContains(6);
}
Crab(string date, int c) : Seafood(date, c){
setDate(date);
setContains(c);
setCap(6);
setIsOpen(true);
setOpenChar("o");
}
};

class Swordfish : public Seafood{
public: 
Swordfish(string date) : Seafood(date){
setIsOpen(false);
setOpenChar("c");
setCap(8);
setContains(8);
}
Swordfish(string date, int c) : Seafood(date, c){
setDate(date);
setContains(c);
setCap(8);
setIsOpen(true);
setOpenChar("o");
}
};


priority_queue <Seafood> seafoods;
priority_queue <Seafood> shrimp;
priority_queue <Seafood> lobster;
priority_queue <Seafood> crab;
priority_queue <Seafood> swordfish;

void print (priority_queue<Seafood> pq) {
   while (!pq.empty()) {
      Seafood largest = pq.top();
      pq.pop();
      cout << largest << (!pq.empty() ? ", " : "");
   }
   cout << endl;
}

int main (int argc, char *argv[]) {
   string event,date,type;
   int amount;
   while (cin >> event >> date >> type >> amount) {
      if (type == "shrimp"){
           cout << type << ": "; print(shrimp);
      }else if (type == "lobster"){
           cout << type << ": "; print(lobster);
      }else if (type == "crab"){
           cout << type << ": "; print(crab);
      }else if (type == "swordfish"){
           cout << type << ": "; print(swordfish);
      }
      //cout << type << ": "; print(type);
      cout << "Event: " << event << " Date: " << date << " Item: " << type << " Amount: " << amount << endl;
      if (event == "stock") {
	 if (type == "shrimp"){
              cout << "Adding seafood to stockpile" << endl;
              for(int i = 0; i<amount; i++){
                  shrimp.push(Shrimp(date));
              }
	 }else if (type == "lobster"){
	      cout << "Adding seafood to stockpile" << endl;
              for(int i = 0; i<amount; i++){
                  lobster.push(Lobster(date));
              }
	 }else if (type == "crab"){
      	      cout << "Adding seafood to stockpile" << endl;
              for(int i = 0; i<amount; i++){
                  crab.push(Crab(date));
              }
	 }else if (type == "swordfish"){
              cout << "Adding seafood to stockpile" << endl;
              for(int i = 0; i<amount; i++){
                  swordfish.push(Swordfish(date));
              }
	 }
      } else if (event == "buy") {
	 cout << "Selling some product from stockpile" << endl;
         cout << "Using some resources from stockpile" << endl;
         if (type == "shrimp"){
              int vol = 0;
              while ( vol < amount ) {
                 if (!shrimp.empty()) {
                    Seafood top = shrimp.top();
                    int cont = top.getContains();
                    string date = top.getDate();
                    shrimp.pop();
                    if (vol + cont < amount) {
                       vol = vol + cont;
                    } else if (vol + cont == amount) {
                       vol = vol + cont;
                       break;
                    } else {
                       int remains = (vol + cont) - amount;
                       vol = amount;
                       shrimp.push(Shrimp(date, remains));
                       break;
                    }
                 } else {
                    assert(shrimp.empty());
                    cout << "Sorry I've sold out of shrimp, I can only sell you " << vol << " shrimps." << endl;
                    break;
                 }
              }

	 }else if (type == "lobster"){
	      int vol = 0;
              while ( vol < amount ) {
                 if (!lobster.empty()) {
                    Seafood top = lobster.top();
                    int cont = top.getContains();
                    string date = top.getDate();
                    lobster.pop();
                    if (vol + cont < amount) {
                       vol = vol + cont;
                    } else if (vol + cont == amount) {
                       vol = vol + cont;
                       break;
                    } else {
                       int remains = (vol + cont) - amount;
                       vol = amount;
                       lobster.push(Lobster(date, remains));
                       break;
                    }
                 } else {
                    assert(lobster.empty());
                    cout << "Sorry I've sold out of lobster, I can only sell you " << vol << " lobsters." << endl;
                    break;
                 }
              }     
                   
	 }else if (type == "crab"){
      	      int vol = 0;
              while ( vol < amount ) {
                 if (!crab.empty()) {
                    Seafood top = crab.top();
                    int cont = top.getContains();
                    string date = top.getDate();
                    crab.pop();
                    if (vol + cont < amount) {
                       vol = vol + cont;
                    } else if (vol + cont == amount) {
                       vol = vol + cont;
                       break;
                    } else {
                       int remains = (vol + cont) - amount;
                       vol = amount;
                       crab.push(Crab(date, remains));
                       break;
                    }
                 } else {
                    assert(crab.empty());
                    cout << "Sorry I've sold out of crab, I can only sell you " << vol << " crabs." << endl;
                    break;
                 }
              }     
	 }else if (type == "swordfish"){
              int vol = 0;
              while ( vol < amount ) {
                 if (!swordfish.empty()) {
                    Seafood top = swordfish.top();
                    int cont = top.getContains();
                    string date = top.getDate();
                    swordfish.pop();
                    if (vol + cont < amount) {
                       vol = vol + cont;
                    } else if (vol + cont == amount) {
                       vol = vol + cont;
                       break;
                    } else {
                       int remains = (vol + cont) - amount;
                       vol = amount;
                       swordfish.push(Swordfish(date, remains));
                       break;
                    }
                 } else {
                    assert(swordfish.empty());
                    cout << "Sorry I've sold out of swordfish, I can only sell you " << vol << " swordfishes." << endl;
                    break;
                 }
              }     
	 } else {
         cout << "Ignoring event " << event <<  endl;
      }
   }

   while (!seafoods.empty()) {
     Seafood largest = seafoods.top();
     seafoods.pop();
     cout << largest << endl;
   }
}
}
