#include "card.h"
#include "hand.h"
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

string playername = "Player";
int playermoney = 500;
int playerscore = 0;
int bet = 0;
int retry = 1;
string cont = "";
string suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
string faces[13] = {"Ace",   "Two",  "Three", "Four", "Five",  "Six", "Seven",
                    "Eight", "Nine", "Ten",   "Jack", "Queen", "King"};
int number[13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
void stats();
void intro();

int main() {
  intro();

  /// MAIN MENU
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  cout << "Welcome to Caesar's Underground Palace!\n";
  bool end = false;
  do {
    cout << "\n----------\nMain Menu:\n----------\n1: Play\n2: Stats\n3: "
            "Quit\nPlease enter a number: ";
    int choice = 0;
    cin >> choice;
    switch (choice) {
    case 1: {
      cout << "You chose to Play." << endl;
      cout << "\nDealer: \"Hello, " << playername
           << " my name is Dan Dealer, let's play.\"";
      do {
        if (playermoney > 0) {
          bool next = false;
          do {
            cout << "\nCurrent money: $" << playermoney
                 << "\nPlease enter your bet: $";
            cin >> bet;
            if (bet <= playermoney && bet > 0) {
              playermoney = playermoney - bet;
              next = true;
            } else {
              cout << "Please enter a valid number." << endl;
            }
          } while (next == false);
          cout << "\nDealer: \"You have bet $" << bet << ".\n\"";
          cout << "Dealer: \"Let me shuffle the deck real quick...\"\nEnter "
                  "any key "
                  "to continue\n";
          cin >> cont;
        } else {
          cout << "You have $" << playermoney << ". Please leave.\n";
        }
        /// MAKING/SHUFFLING DECK
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        vector<Card> deck;
        for (int i = 0; i < 4; i++) {
          Card insert;
          insert.setsuit(suits[i]);
          for (int i = 0; i < 13; i++) {
            insert.setface(faces[i]);
            insert.setnumber(number[i]);
            if (i == 0) {
              insert.setace(true);
            } else {
              insert.setace(false);
            }
            deck.push_back(insert);
          }
        }
        int result1 = 0;
        int result2 = 5;
        int result3 = 5;
        int earnings1 = bet;
        int earnings2 = 0;
        int earnings3 = 0;
        double multiplier1 = 2.0;
        double multiplier2 = 2.0;
        double multiplier3 = 2.0;
        random_device rd;
        default_random_engine rng(rd());
        shuffle(deck.begin(), deck.end(), rng);
        cout << "\nDealer: \"All " << deck.size()
             << " cards have been shuffled.\"\nEnter any key to continue...\n";
        cin >> cont;
        ///   DEALING CARDS
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "\nThe dealer draws two cards, one facing down.\n";
        Hand Dealer;
        Dealer.addcard(deck.back());
        deck.pop_back();
        Dealer.addcard(deck.back());
        deck.pop_back();
        Dealer.printfrontcard();

        cout << "\nThe dealer slides over two cards.\n";
        Hand Player1;
        Hand Player2;
        Hand Player3;
        Player1.addcard(deck.back());
        deck.pop_back();
        Player1.addcard(deck.back());
        deck.pop_back();
        Player1.printcards();
        cout << "Total: " << Player1.gettotal();

        /// Calculating probabability
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        double chances = 0;
        double count = 0;
        int need = 21 - Player1.gettotal();
        if (need >= 1) {
          count = count + 4;
        }
        for (int i = 1; i < 13; i++) {
          if (number[i] <= need) {
            count = count + 4;
          }
        }
        count = count - Player1.countcard(need);
        count = count - Dealer.countfront(need);
        chances = count / (deck.size() + 1);
        cout << "\n\nChances of not exceeding 21: " << chances * 100 << "%";
        double exactchances = 0;
        double exactcount = 0;
        int exactneed = 21 - Player1.gettotal();
        if (exactneed == 1 || exactneed == 11) {
          exactcount = 4;
        } else {
          for (int i = 1; i < 13; i++) {
            if (number[i] == exactneed) {
              exactcount = exactcount + 4;
            }
          }
        }
        exactcount = exactcount - Player1.countexact(exactneed);
        exactcount = exactcount - Dealer.countfrontexact(exactneed);
        exactchances = exactcount / (deck.size() + 1);
        cout << "\nChances of reaching a perfect 21: " << exactchances * 100
             << "%\n";

        if (Player1.gettotal() == 21) {
          cout << "Dealer: \"A Lucky Blackjack!\"\nYou won $" << earnings1
               << ".\n";
          playermoney = playermoney + (earnings1 * 2.5);
          playerscore = playerscore + 1;
          result1 = 5;
        }
        /// Main Game Menu
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (result1 != 5) {
          int choice = 0;
          do {
            cout << "\n\"What would you like to do for this hand?\""
                 << "\n1: Hit"
                 << "\n2: Stand"
                 << "\n3: Double Down"
                 << "\n4: Split"
                 << "\n5: Talk";
            do {
              cout << "\nEnter Choice: ";
              cin >> choice;
              if (choice < 1 || choice > 5) {
                cout << "\"Please enter a valid option.\"\n";
              }
            } while (choice < 1 || choice > 5);
            switch (choice) {
            case 1: {
              cout << "\nYou chose to hit.\n";
              Player1.addcard(deck.back());
              deck.pop_back();
              Player1.printcards();
              cout << "Total: " << Player1.gettotal();
              if (Player1.gettotal() > 21) {
                Player1.flipace();
                cout << "\nAces Flipped Total: " << Player1.gettotal();
                double chances = 0;
                double count = 0;
                int need = 21 - Player1.gettotal();
                if (need >= 1) {
                  count = count + 4;
                }
                for (int i = 1; i < 13; i++) {
                  if (number[i] <= need) {
                    count = count + 4;
                  }
                }
                count = count - Player1.countcard(need);
                count = count - Player2.countcard(need);
                count = count - Player3.countcard(need);
                count = count - Dealer.countfront(need);
                chances = count / deck.size() + 1;
                cout << "\n\nChances of not exceeding 21: " << chances * 100
                     << "%";
                double exactchances = 0;
                double exactcount = 0;
                int exactneed = 21 - Player1.gettotal();
                if (exactneed == 1 || exactneed == 11) {
                  exactcount = 4;
                } else {
                  for (int i = 1; i < 13; i++) {
                    if (number[i] == exactneed) {
                      exactcount = exactcount + 4;
                    }
                  }
                }
                exactcount = exactcount - Player1.countexact(exactneed);
                exactcount = exactcount - Player2.countexact(exactneed);
                exactcount = exactcount - Player3.countexact(exactneed);
                exactcount = exactcount - Dealer.countfrontexact(exactneed);
                exactchances = exactcount / (deck.size() + 1);
                cout << "\nChances of reaching a perfect 21: "
                     << exactchances * 100 << "%\n";
                if (Player1.gettotal() > 21) {
                  cout << "\nYou busted...\n";
                  result1 = 2;
                }
              } else if (Player1.gettotal() == 21) {
                cout << "\nYou got 21!\n";
                result1 = 4;
              }
              double chances = 0;
              double count = 0;
              int need = 21 - Player1.gettotal();
              if (need >= 1) {
                count = count + 4;
              }
              for (int i = 1; i < 13; i++) {
                if (number[i] <= need) {
                  count = count + 4;
                }
              }
              count = count - Player1.countcard(need);
              count = count - Player2.countcard(need);
              count = count - Player3.countcard(need);
              count = count - Dealer.countfront(need);
              chances = count / (deck.size() + 1);
              cout << "\n\nChances of not exceeding 21: " << chances * 100
                   << "%";
              double exactchances = 0;
              double exactcount = 0;
              int exactneed = 21 - Player1.gettotal();
              if (exactneed == 1 || exactneed == 11) {
                exactcount = 4;
              } else {
                for (int i = 1; i < 13; i++) {
                  if (number[i] == exactneed) {
                    exactcount = exactcount + 4;
                  }
                }
              }
              exactcount = exactcount - Player1.countexact(exactneed);
              exactcount = exactcount - Player2.countexact(exactneed);
              exactcount = exactcount - Player3.countexact(exactneed);
              exactcount = exactcount - Dealer.countfrontexact(exactneed);
              exactchances = exactcount / (deck.size() + 1);
              cout << "\nChances of reaching a perfect 21: "
                   << exactchances * 100 << "%\n";
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 2: {
              cout << "\nYou chose to stand.";
              result1 = 4;
              break;
            }
            case 3: {
              if (playermoney >= earnings1 && multiplier1 != 4.0) {
                playermoney = playermoney - earnings1;
                cout << "\nYou chose to double down.";
                multiplier1 = 4.0;
                Player1.addcard(deck.back());
                deck.pop_back();
                Player1.printcards();
                cout << "Total: " << Player1.gettotal();
                if (Player1.gettotal() > 21) {
                  Player1.flipace();
                  cout << "\n Aces Flipped Total: " << Player1.gettotal();
                  if (Player1.gettotal() > 21) {
                    cout << "\nYou busted...\n";
                    result1 = 2;
                  }
                } else if (Player1.gettotal() == 21) {
                  cout << "\nYou got 21!\n";
                  result1 = 4;
                } else {
                  result1 = 4;
                }
              } else if (multiplier1 == 4.0) {
                cout << "\nYou already double downed!\n";
              } else {
                cout << "\nYou don't have enough money to double down.\n";
              }
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 4: {
              if (!Player1.checksplit()) {
                cout << "\nYou need two of the same faces to split.";
              } else if (result2 != 5 || result3 != 5) {
                cout << "\nYou can't split thrice.";
              } else if (!(playermoney >= earnings1)) {
                cout << "\nYou don't have enough money to split.";
              } else if (result2 == 5) {
                result2 = 0;
                playermoney = playermoney - earnings1;
                earnings2 = earnings1;
                Player2.addcard(Player1.getback());
                Player1.popback();
                cout << "\nYou decided to split, this hand has only one card "
                        "now.\nNew Deck: \n";
                Player2.printcards();
                cout << "\nWe'll focus on the original hand for now.";
                Player1.printcards();
              } else {
                playermoney = playermoney - earnings1;
                earnings3 = earnings1;
                Player3.addcard(Player1.getback());
                Player1.popback();
                cout << "\nYou decided to split, this hand has only one card "
                        "now.\n "
                        "<< "
                        "New Deck: \n";
                Player3.printcards();
                cout << "\nWe'll focus on the original hand for now.";
                Player1.printcards();
              }
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 5: {
              cout << "\nYou chose to talk."
                   << "\nDealer: \" Here is a reminder of your current "
                      "hand.\"\n";
              Player1.printcards();
              double chances = 0;
              double count = 0;
              int need = 21 - Player1.gettotal();
              if (need >= 1) {
                count = count + 4;
              }
              for (int i = 1; i < 13; i++) {
                if (number[i] <= need) {
                  count = count + 4;
                }
              }
              count = count - Player1.countcard(need);
              count = count - Player2.countcard(need);
              count = count - Player3.countcard(need);
              count = count - Dealer.countfront(need);
              chances = count / (deck.size() + 1);
              cout << "\n\nChances of not exceeding 21: " << chances * 100
                   << "%";
              double exactchances = 0;
              double exactcount = 0;
              int exactneed = 21 - Player1.gettotal();
              if (exactneed == 1 || exactneed == 11) {
                exactcount = 4;
              } else {
                for (int i = 1; i < 13; i++) {
                  if (number[i] == exactneed) {
                    exactcount = exactcount + 4;
                  }
                }
              }
              exactcount = exactcount - Player1.countexact(exactneed);
              exactcount = exactcount - Player2.countexact(exactneed);
              exactcount = exactcount - Player3.countexact(exactneed);
              exactcount = exactcount - Dealer.countfrontexact(exactneed);
              exactchances = exactcount / (deck.size() + 1);
              cout << "\nChances of reaching a perfect 21: "
                   << exactchances * 100 << "%\n";
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            default: {
              cout << "\nERROR!";
            }
            }
          } while (result1 == 0);
          while (result2 == 0) {
            cout << "\n\"What would you like to do for your second hand?\""
                 << "\n1: Hit"
                 << "\n2: Stand"
                 << "\n3: Double Down"
                 << "\n4: Split"
                 << "\n5: Talk";
            do {
              cout << "\nEnter Choice: ";
              cin >> choice;
              if (choice < 1 || choice > 5) {
                cout << "\"Please enter a valid option.\"\n";
              }
            } while (choice < 1 || choice > 5);
            switch (choice) {
            case 1: {
              cout << "\nYou chose to hit.\n";
              Player2.addcard(deck.back());
              deck.pop_back();
              Player2.printcards();
              cout << "Total: " << Player2.gettotal();
              if (Player2.gettotal() > 21) {
                Player2.flipace();
                cout << "\n Aces Flipped Total: " << Player2.gettotal();
                double chances = 0;
                double count = 0;
                int need = 21 - Player2.gettotal();
                if (need >= 1) {
                  count = count + 4;
                }
                for (int i = 1; i < 13; i++) {
                  if (number[i] <= need) {
                    count = count + 4;
                  }
                }
                count = count - Player1.countcard(need);
                count = count - Player2.countcard(need);
                count = count - Player3.countcard(need);
                count = count - Dealer.countfront(need);
                chances = count / (deck.size() + 1);
                cout << "\n\nChances of not exceeding 21: " << chances * 100
                     << "%";
                double exactchances = 0;
                double exactcount = 0;
                int exactneed = 21 - Player2.gettotal();
                if (exactneed == 1 || exactneed == 11) {
                  exactcount = 4;
                } else {
                  for (int i = 1; i < 13; i++) {
                    if (number[i] == exactneed) {
                      exactcount = exactcount + 4;
                    }
                  }
                }
                exactcount = exactcount - Player1.countexact(exactneed);
                exactcount = exactcount - Player2.countexact(exactneed);
                exactcount = exactcount - Player3.countexact(exactneed);
                exactcount = exactcount - Dealer.countfrontexact(exactneed);
                exactchances = exactcount / (deck.size() + 1);
                cout << "\nChances of reaching a perfect 21: "
                     << exactchances * 100 << "%\n";
                if (Player2.gettotal() > 21) {
                  cout << "\nYou busted...\n";
                  result2 = 2;
                }
              } else if (Player2.gettotal() == 21) {
                cout << "\nYou got 21!\n";
                result2 = 4;
              }
              double chances = 0;
              double count = 0;
              int need = 21 - Player2.gettotal();
              if (need >= 1) {
                count = count + 4;
              }
              for (int i = 1; i < 13; i++) {
                if (number[i] <= need) {
                  count = count + 4;
                }
              }
              count = count - Player1.countcard(need);
              count = count - Player2.countcard(need);
              count = count - Player3.countcard(need);
              count = count - Dealer.countfront(need);
              chances = count / (deck.size() + 1);
              cout << "\n\nChances of not exceeding 21: " << chances * 100
                   << "%";
              double exactchances = 0;
              double exactcount = 0;
              int exactneed = 21 - Player2.gettotal();
              if (exactneed == 1 || exactneed == 11) {
                exactcount = 4;
              } else {
                for (int i = 1; i < 13; i++) {
                  if (number[i] == exactneed) {
                    exactcount = exactcount + 4;
                  }
                }
              }
              exactcount = exactcount - Player1.countexact(exactneed);
              exactcount = exactcount - Player2.countexact(exactneed);
              exactcount = exactcount - Player3.countexact(exactneed);
              exactcount = exactcount - Dealer.countfrontexact(exactneed);
              exactchances = exactcount / (deck.size() + 1);
              cout << "\nChances of reaching a perfect 21: "
                   << exactchances * 100 << "%\n";
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 2: {
              cout << "\nYou chose to stand.";
              result2 = 4;
              break;
            }
            case 3: {
              if (playermoney >= earnings2 && multiplier2 != 4.0) {
                playermoney = playermoney - earnings2;
                cout << "\nYou chose to double down.";
                multiplier2 = 4.0;
                Player2.addcard(deck.back());
                deck.pop_back();
                Player2.printcards();
                cout << "Total: " << Player2.gettotal();
                if (Player2.gettotal() > 21) {
                  Player2.flipace();
                  cout << "\n Aces Flipped Total: " << Player2.gettotal();
                  if (Player2.gettotal() > 21) {
                    cout << "\nYou busted...\n";
                    result2 = 2;
                  }
                } else if (Player2.gettotal() == 21) {
                  cout << "\nYou got 21!\n";
                  result2 = 4;
                } else {
                  result2 = 4;
                }
              } else if (multiplier2 == 4.0) {
                cout << "\nYou already double downed!\n";
              } else {
                cout << "\nYou don't have enough money to double down.\n";
              }
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 4: {
              if (!Player2.checksplit()) {
                cout << "\nYou need two of the same faces to split.";
              } else if (result3 != 5) {
                cout << "\nYou can't split thrice.";
              } else if (!(playermoney >= earnings2)) {
                cout << "\nYou don't have enough money to split.";
              } else if (result3 == 5) {
                result3 = 0;
                playermoney = playermoney - earnings2;
                earnings3 = earnings2;
                Player3.addcard(Player2.getback());
                Player2.popback();
                cout << "\nYou decided to split, this hand has only one card "
                        "now.\nNew Deck: \n";
                Player3.printcards();
                cout << "\nWe'll focus on the second hand for now.";
                Player2.printcards();
              } else {
                cout << "\nERROR";
              }
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 5: {
              cout << "\nYou chose to talk."
                   << "\nDealer: \" Here is a reminder of your current "
                      "hand.\"\n";
              Player2.printcards();
              double chances = 0;
              double count = 0;
              int need = 21 - Player2.gettotal();
              if (need >= 1) {
                count = count + 4;
              }
              for (int i = 1; i < 13; i++) {
                if (number[i] <= need) {
                  count = count + 4;
                }
              }
              count = count - Player1.countcard(need);
              count = count - Player2.countcard(need);
              count = count - Player3.countcard(need);
              count = count - Dealer.countfront(need);
              chances = count / (deck.size() + 1);
              cout << "\n\nChances of not exceeding 21: " << chances * 100
                   << "%";
              double exactchances = 0;
              double exactcount = 0;
              int exactneed = 21 - Player2.gettotal();
              if (exactneed == 1 || exactneed == 11) {
                exactcount = 4;
              } else {
                for (int i = 1; i < 13; i++) {
                  if (number[i] == exactneed) {
                    exactcount = exactcount + 4;
                  }
                }
              }
              exactcount = exactcount - Player1.countexact(exactneed);
              exactcount = exactcount - Player2.countexact(exactneed);
              exactcount = exactcount - Player3.countexact(exactneed);
              exactcount = exactcount - Dealer.countfrontexact(exactneed);
              exactchances = exactcount / (deck.size() + 1);
              cout << "\nChances of reaching a perfect 21: "
                   << exactchances * 100 << "%\n";
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            default: {
              cout << "\nERROR!";
            }
            }
          }
          while (result3 == 0) {
            cout << "\n\"What would you like to do for your third hand?\""
                 << "\n1: Hit"
                 << "\n2: Stand"
                 << "\n3: Double Down"
                 << "\n4: Split"
                 << "\n5: Talk";
            do {
              cout << "\nEnter Choice: ";
              cin >> choice;
              if (choice < 1 || choice > 5) {
                cout << "\"Please enter a valid option.\"\n";
              }
            } while (choice < 1 || choice > 5);
            switch (choice) {
            case 1: {
              cout << "\nYou chose to hit.\n";
              Player3.addcard(deck.back());
              deck.pop_back();
              Player3.printcards();
              cout << "Total: " << Player3.gettotal();
              if (Player3.gettotal() > 21) {
                Player3.flipace();
                cout << "\n Aces Flipped Total: " << Player3.gettotal();
                double chances = 0;
                double count = 0;
                int need = 21 - Player3.gettotal();
                if (need >= 1) {
                  count = count + 4;
                }
                for (int i = 1; i < 13; i++) {
                  if (number[i] <= need) {
                    count = count + 4;
                  }
                }
                count = count - Player1.countcard(need);
                count = count - Player2.countcard(need);
                count = count - Player3.countcard(need);
                count = count - Dealer.countfront(need);
                chances = count / (deck.size() + 1);
                cout << "\n\nChances of not exceeding 21: " << chances * 100
                     << "%";
                double exactchances = 0;
                double exactcount = 0;
                int exactneed = 21 - Player3.gettotal();
                if (exactneed == 1 || exactneed == 11) {
                  exactcount = 4;
                } else {
                  for (int i = 1; i < 13; i++) {
                    if (number[i] == exactneed) {
                      exactcount = exactcount + 4;
                    }
                  }
                }
                exactcount = exactcount - Player1.countexact(exactneed);
                exactcount = exactcount - Player2.countexact(exactneed);
                exactcount = exactcount - Player3.countexact(exactneed);
                exactcount = exactcount - Dealer.countfrontexact(exactneed);
                exactchances = exactcount / (deck.size() + 1);
                cout << "\nChances of reaching a perfect 21: "
                     << exactchances * 100 << "%\n";
                if (Player3.gettotal() > 21) {
                  cout << "\nYou busted...\n";
                  result3 = 2;
                }
              } else if (Player2.gettotal() == 21) {
                cout << "\nYou got 21!\n";
                result3 = 4;
              }
              double chances = 0;
              double count = 0;
              int need = 21 - Player3.gettotal();
              if (need >= 1) {
                count = count + 4;
              }
              for (int i = 1; i < 13; i++) {
                if (number[i] <= need) {
                  count = count + 4;
                }
              }
              count = count - Player1.countcard(need);
              count = count - Player2.countcard(need);
              count = count - Player3.countcard(need);
              count = count - Dealer.countfront(need);
              chances = count / (deck.size() + 1);
              cout << "\n\nChances of not exceeding 21: " << chances * 100
                   << "%";
              double exactchances = 0;
              double exactcount = 0;
              int exactneed = 21 - Player3.gettotal();
              if (exactneed == 1 || exactneed == 11) {
                exactcount = 4;
              } else {
                for (int i = 1; i < 13; i++) {
                  if (number[i] == exactneed) {
                    exactcount = exactcount + 4;
                  }
                }
              }
              exactcount = exactcount - Player1.countexact(exactneed);
              exactcount = exactcount - Player2.countexact(exactneed);
              exactcount = exactcount - Player3.countexact(exactneed);
              exactcount = exactcount - Dealer.countfrontexact(exactneed);
              exactchances = exactcount / (deck.size() + 1);
              cout << "\nChances of reaching a perfect 21: "
                   << exactchances * 100 << "%\n";
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 2: {
              cout << "\nYou chose to stand.";
              result3 = 4;
              break;
            }
            case 3: {
              if (playermoney >= earnings3 && multiplier3 != 4.0) {
                playermoney = playermoney - earnings3;
                cout << "\nYou chose to double down.";
                multiplier3 = 4.0;
                Player3.addcard(deck.back());
                deck.pop_back();
                Player3.printcards();
                cout << "Total: " << Player3.gettotal();
                if (Player3.gettotal() > 21) {
                  Player3.flipace();
                  cout << "\n Aces Flipped Total: " << Player3.gettotal();
                  if (Player3.gettotal() > 21) {
                    cout << "\nYou busted...\n";
                    result3 = 2;
                  }
                } else if (Player3.gettotal() == 21) {
                  cout << "\nYou got 21!\n";
                  result3 = 4;
                } else {
                  result3 = 4;
                }
              } else if (multiplier3 == 4.0) {
                cout << "\nYou already double downed!\n";
              } else {
                cout << "\nYou don't have enough money to double down.\n";
              }
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 4: {
              cout << "\nYou can't split thrice."
                   << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            case 5: {
              cout << "\nYou chose to talk."
                   << "\nDealer: \" Here is a reminder of your current "
                      "hand.\"\n";
              Player3.printcards();
              Player3.printchances();
              cout << "\nEnter any key to continue...\n";
              cin >> cont;
              break;
            }
            default: {
              cout << "\nERROR!";
            }
            }
          }

          /// END OF ROUND TALLY
          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          cout << "\nDealer's turn." << endl;
          Dealer.printfrontcard();
          cout << "\nEnter any key to continue...\n";
          cin >> cont;
          Dealer.printcards();
          cout << "Total :" << Dealer.gettotal();

          if (Dealer.gettotal() <= 16) {
            cout << "\nDealer: \" I won't give up!.\"";
            cout << "\nEnter any key to continue...\n";
            cin >> cont;
            Dealer.addcard(deck.back());
            deck.pop_back();
            Dealer.printcards();
            cout << "Total: " << Dealer.gettotal();
          }

          if (Dealer.gettotal() > 21) {
            Dealer.flipace();
            if (Dealer.gettotal() > 21) {
              cout << "\nDealer busted!\n"
                   << "Dealer: \"Oops.\"\n";
              Dealer.clearhand();
            } else {
              cout << "Total: " << Dealer.gettotal();
            }
          }

          if (Player1.gettotal() > Dealer.gettotal() &&
              Player1.gettotal() <= 21) {
            result1 = 1;
          } else if (Player1.gettotal() < Dealer.gettotal()) {
            result1 = 2;
          } else if (Player1.gettotal() > 21) {
            result1 = 2;
          } else if (Player1.gettotal() == Dealer.gettotal()) {
            result1 = 3;
          } else {
            cout << "\nERROR";
          }
          if (result2 != 5) {
            if (Player2.gettotal() > Dealer.gettotal() &&
                Player2.gettotal() <= 21) {
              result2 = 1;
            } else if (Player2.gettotal() < Dealer.gettotal()) {
              result2 = 2;
            } else if (Player2.gettotal() > 21) {
              result2 = 2;
            } else if (Player2.gettotal() == Dealer.gettotal()) {
              result2 = 3;
            } else {
              cout << "\nERROR";
            }
          }
          if (result3 != 5) {
            if (Player3.gettotal() > Dealer.gettotal() &&
                Player3.gettotal() <= 21) {
              result3 = 1;
            } else if (Player3.gettotal() < Dealer.gettotal()) {
              result3 = 2;
            } else if (Player3.gettotal() > 21) {
              result3 = 2;
            } else if (Player3.gettotal() == Dealer.gettotal()) {
              result3 = 3;
            } else {
              cout << "\nERROR";
            }
          }

          if (result1 == 1) {
            cout << "\nYou win! +$" << (earnings1 * multiplier1) << endl;
            playermoney = playermoney + (earnings1 * multiplier1);
            playerscore = playerscore + 1;
          } else if (result1 == 2) {
            cout << "\nYou lose!\n";
          } else if (result1 == 3) {
            cout << "\nYou tie!\n";
            playermoney = playermoney + earnings1;
            if (multiplier1 == 4) {
              playermoney = playermoney + earnings1;
            }
          } else {
            cout << "\nERROR";
          }

          if (result2 != 5) {
            cout << "\nFor your second hand...\n";
            if (result2 == 1) {
              cout << "\nYou win! +$" << (earnings2 * multiplier2) << endl;
              playermoney = playermoney + (earnings2 * multiplier2);
            } else if (result2 == 2) {
              cout << "\nYou lose!\n";
            } else if (result2 == 3) {
              cout << "\nYou tie!\n";
              playermoney = playermoney + earnings2;
              if (multiplier2 == 4) {
                playermoney = playermoney + earnings2;
              }
            } else {
              cout << "\nERROR";
            }
          }

          if (result3 != 5) {
            cout << "\nFor your third hand...\n";
            if (result3 == 1) {
              cout << "\nYou win! +$" << (earnings3 * multiplier3) << endl;
              playermoney = playermoney + (earnings3 * multiplier3);
            } else if (result3 == 2) {
              cout << "\nYou lose!\n";
            } else if (result3 == 3) {
              cout << "\nYou tie!\n";
              playermoney = playermoney + earnings3;
              if (multiplier3 == 4) {
                playermoney = playermoney + earnings3;
              }
            } else {
              cout << "\nERROR";
            }
          }
        }
        cout << "\nDealer: \"Would you like to continue playing?\" (Type 0 to "
                "quit)\n";
        cin >> retry;
      } while (retry != 0);
      break;
    }
    case 2: {
      cout << "You chose to view your Stats." << endl;
      stats();
      break;
    }
    case 3: {
      end = true;
      cout << "You chose to Quit."
           << "\nYou ended with $" << playermoney << " and " << playerscore
           << " win(s).";
      break;
    }
    default: {
      cout << "Please enter a valid option." << endl;
      break;
    }
    }
  } while (end != true);
  cout << "\nEnding Program";
  return 0;
}

void stats() {
  cout << "\nCurrent Money: $" << playermoney
       << "\nCurrent Score: " << playerscore
       << "\nEnter any key to continue...";
  cin >> cont;
}

/// LOOSE MAIN FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void intro() {
  string choice = "Blank";

  cout << "Please enter your name: ";
  getline(cin, playername);

  cout << "\n\"Hello " << playername << "!\"\n"
       << "\"I'm giving you $" << playermoney << "!\"\n"
       << "\"I have a favour to ask, care to listen?(Y/N)\"\n";

  while (choice != "y" || choice != "Y") {
    getline(cin, choice);

    if (choice == "n" || choice == "N") {
      playermoney += 500;
      cout << "\n\"Hey wait! Come back! Please, I'll pay you $" << playermoney
           << "!\" (Y/N)\n";
    }

    else if (choice == "y" || choice == "Y") {
      cout << "\n\"Great! Now listen...\"\n";
      break;
    }

    else {
      cout << "(You should enter a valid option.)\n";
    }
  }

  cout << "\"I promised some people that I would show up to a Blackjack game, "
          "but "
          "I have more important things to do...\"\nEnter any key to "
          "continue...\n";
  getline(cin, cont);
  cout << "\n\"You should play for me! I already paid you some money to play "
          "with, "
          "the place is called \"Caesar's Underground Casino\". Anyway, see "
          "you "
          "later!\"\nThe stranger left and you are forced to go to the "
          "casino...\n"
          "Enter any key to continue...\n";
  getline(cin, cont);
  cout << "\nYou arrive at the casino, and after pleasantries you can now "
          "play Blackjack.\n";
}