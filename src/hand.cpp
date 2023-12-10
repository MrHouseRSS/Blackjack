#include "hand.h"
#include <iostream>

Hand::Hand() {
  total = 0;
  choice = 0;
  splitable = false;
};

void Hand::addcard(Card c) { currenthand.push_back(c); }

void Hand::printcards() {
  cout << endl;
  for (int i = 0; i < currenthand.size(); i++) {
    cout << "Card " << i + 1 << ": " << currenthand[i].getface() << " of "
         << currenthand[i].getsuit() << " (" << currenthand[i].getnumber()
         << ")\n";
  }
}

void Hand::printfrontcard() {
  cout << "\nCard 1: " << currenthand[0].getface() << " of "
       << currenthand[0].getsuit() << " (" << currenthand[0].getnumber()
       << ")\n";
}

void Hand::printchances() {
  cout << "\nThis hand has a chance to win\n----------\n";
}

bool Hand::checksplit() {
  if (currenthand.size() == 2 &&
      currenthand[0].getface() == currenthand[1].getface()) {
    splitable = true;
  } else {
    splitable = false;
  }
  return splitable;
}

void Hand::clearhand() { currenthand.clear(); }

int Hand::gettotal() {
  total = 0;
  for (int i = 0; i < currenthand.size(); i++) {
    total = total + currenthand[i].getnumber();
  }
  return total;
}

Card Hand::getback() { return currenthand[1]; }

void Hand::popback() { currenthand.pop_back(); }

void Hand::flipace() {
  for (int i = 0; i < currenthand.size(); i++) {
    if (currenthand[i].getace() == true) {
      currenthand[i].setnumber(1);
    }
  }
}

int Hand::countcard(int f) {
  int counter = 0;
  for (int i = 0; i < currenthand.size(); i++) {
    if (currenthand[i].getnumber() <= f) {
      if (currenthand[i].getnumber() != 1) {
        if (currenthand[i].getnumber() != 11) {
          counter = counter + 1;
        }
      }
    }
  }
  if (f >= 1) {
    for (int i = 0; i < currenthand.size(); i++) {
      if (currenthand[i].getnumber() == 1 || currenthand[i].getnumber() == 11) {
        counter = counter + 1;
      }
    }
  }
  return counter;
}

int Hand::countfront(int f) {
  int counter = 0;
  if (currenthand[0].getnumber() <= f) {
    if (currenthand[0].getnumber() != 1) {
      if (currenthand[0].getnumber() != 11) {
        counter = 1;
      }
    }
  }

  if (f >= 1) {
    if (currenthand[0].getnumber() == 1 || currenthand[0].getnumber() == 11) {
      counter = counter + 1;
    }
  }
  return counter;
}

int Hand::countexact(int f) {
  int counter = 0;
  if (f == 1 || f == 11) {
    for (int i = 0; i < currenthand.size(); i++) {
      if (currenthand[i].getnumber() == 1 || currenthand[i].getnumber() == 11) {
        counter = counter + 1;
      }
    }
  } else {
    for (int i = 0; i < currenthand.size(); i++) {
      if (currenthand[i].getnumber() == f) {
        if (currenthand[i].getnumber() != 1) {
          if (currenthand[i].getnumber() != 11) {
            counter = counter + 1;
          }
        }
      }
    }
  }
  return counter;
}

int Hand::countfrontexact(int f) {
  int counter = 0;
  if (currenthand[0].getnumber() == f) {
    if (currenthand[0].getnumber() != 1) {
      if (currenthand[0].getnumber() != 11) {
        counter = 1;
      }
    }
  }
  if (f == 1 || f == 11) {
    if (currenthand[0].getnumber() == 1 || currenthand[0].getnumber() == 11) {
      counter = 1;
    }
  }
  return counter;
}