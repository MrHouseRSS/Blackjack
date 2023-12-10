# Blackjack

## Overview

This is a C++ blackjack program that calculates the probability of the player's hand of busting or getting a 21.  
The program is menu-driven and allows the player to select decisions by inputting numbers for choices.

The program uses objects and vectors to create a deck of cards and pops them in and out the player's hand and dealer's hand.

## Project Team

Robert Singharath - This was just a solo project by me.

## Date Published

### 12/10/2023 - December 10th, 2023

## How to use this program

The src folder contains the the .cpp and .h files that I used to create the project.  
Download and load the files in an IDE like **[replit.com](https://replit.com/~)** .  
Running the program will take a few seconds to start up. Once it runs, you'll be prompted to enter a name. Then dialogue will start being output, enter (Y/N) to answer the man's question. You can advance the dialogue and messages by inputting any key and pressing enter. After a few message you will reach the main menu screen.  

### The main menu has a few options:

**Play** - Plays the main blackjack game  
**Stats** - Shows how much money and score you have  
**Quit** - Ends the game and shows your final balance and score.

---

## Playing Blackjack

Choosing play will bring up a dealer that will ask you how much to bet, input a wager.  
After betting, the dealer will hand you two cards that the program tallies up for you. The dealer draws two cards and keeps one hidden. The program will also show you the probabability of a few outcomes, the probability of the next card putting your total over 21 and the probability of the next card being exactly what you need to reach 21.

If you got blackjack already, the game will automatically end the round. If not, then you'll continue to the next menu.

### Blackjack Menu
There are several options to choose from while playing Blackjack.  
**Hit** - The dealer will give you another card and the probababilities will be recalculated.  
**Stand** - Stands the current hand, you will not be able to make any more choices for it.  
**Double Down** - Takes you bet if you have enough and doubles your return if you win. Hits and stands your hand.  
**Split** - If you have 2 of the same face card, you can split your hand into multiple hands. Takes another bet for the second hand and is played after your first hand is done. You can only have 3 hands maximum.  
**Talk** - The dealer reminds you of the cards of your current hand and their probablilities.

---

After finishing all hands, the dealer reveals their second card. The dealer may draw another card to increase their total.

Scores are compared and if you are closer to 21 without passing it, you win back 2x your bet for that hand, 4x if you double downed. If you tie, you original bet is returned to you. If the dealer is closer to 21 without passing it, you lose your bet. If both you and the dealer busts, you lose.

After the round ends, the dealer asks if you want to continue. You can stop playing by inputting 0.  
Afterwards, you return back to the main menu and can quit the game.