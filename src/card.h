#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;

class Card {
private:
  string suit;
  string face;
  int number;
  bool ace;

public:
  Card();
  void setsuit(string s);
  void setface(string s);
  void setnumber(int i);
  void setace(bool b);
  string getsuit();
  string getface();
  int getnumber();
  bool getace();
};

#endif