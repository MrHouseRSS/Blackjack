#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>

class Hand {
private:
  vector<Card> currenthand;
  int total;
  int choice;
  bool splitable;

public:
  Hand();
  void addcard(Card c);
  void printcards();
  void printfrontcard();
  void printchances();
  bool checksplit();
  void clearhand();
  int gettotal();
  Card getback();
  void popback();
  void flipace();
  int countcard(int f);
  int countfront(int f);
  int countexact(int f);
  int countfrontexact(int f);
};

#endif