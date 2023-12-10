#include "card.h"

Card::Card() {
  suit = "Blank";
  face = "Blank";
  number = 0;
  ace = false;
}

void Card::setsuit(string s) { suit = s; }

void Card::setface(string s) { face = s; }

void Card::setnumber(int i) { number = i; }

void Card::setace(bool b) { ace = b; }

string Card::getsuit() { return suit; }

string Card::getface() { return face; }

int Card::getnumber() { return number; }

bool Card::getace() { return ace; }