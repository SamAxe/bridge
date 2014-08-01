#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "score.h"
#include "player.h"
#include "deck.h"


// The components for the game of contract bridge
class Bridge
{
    Deck     deck;                    // Deck of cards
    int      dealer;                  // The dealer
    Auction  auction;                 // The auction
    int      nsTricks;                // # of NS tricks
    int      ewTricks;                // # of EW tricks
    Player * players[4];              // 4 players
public:

    Bridge()
    {
        players[0] = new PlayerComputer(0, "North" );
        players[1] = new PlayerComputer(1, "East" );
        players[2] = new PlayerComputer(2, "South" );
        players[3] = new PlayerComputer(3, "West" );
        dealer     = 0;
        nsTricks = 0;
        ewTricks = 0;
    }

    void shuffleAndDeal()
    {
        std::cout << "Shuffling the cards...";
        deck.shuffle();
        std::cout << "done\nDealing the hands...";
        deck.deal( players, dealer );
        std::cout << "done" << std::endl;
        for ( int i = 0; i < 4; i++ ) //( Player * player, players )
        {
            players[i]->dealDone();
        }
    }

    void showHands() const
    {
        for ( unsigned int i = 0; i < 4; i++ )
        {
            std::cout << players[i]->getName() << std::endl;
            players[i]->show();
        }
    }

    void conductAuction()
    {
        int bidder = dealer;
        while ( auction.open() )
        {
            std::cout << players[bidder ]->getName() << ": ";
            Bid _bid = players[bidder]->pickBid( auction );
            if ( _bid.passed() )
                std::cout << " passes" << std::endl;
            else
                std::cout << " bids " << _bid.rank() << _bid.trump() << std::endl;
            auction.bid( _bid );
            bidder = (bidder + 1) % 4;
        }
        std::cout << "Final auction is: " << auction.contract().str() << " by " << players[ auction.declarer() ]->getName() << std::endl;
    }

    void play()
    {
        int leader = (auction.declarer() + 3) % 4;
        for ( int i = 0; i < 13; i++ )
        {
std::cout << i << " ";
            Trick trick;
            for ( int j = 0; j < 4; j++ )
            {
                Card c = players[ (leader+j)%4]->pickCard( trick );
std::cout << players[ (leader + j) % 4 ]->getName() << " plays " << c << ". ";
                players[ (leader+j)%4]->playCard( c );
                trick.play( c );
            }
            int winner = trick.winner( auction.contract().trump() );
            leader += winner;
            leader %= 4;
            std::cout << "  " << players[leader]->getName() << " wins the trick";
            if ( leader == 0 || leader == 2 )
                nsTricks++;
            else
                ewTricks++;
std::cout << std::endl;
        }
std::cout << "N/S took " << nsTricks << std::endl;
std::cout << "E/W took " << ewTricks << std::endl;
    }

    void score()
    {
        Score _score;
        int points(0);
        if ( auction.declarer() == 0 || auction.declarer() == 2 )
        {
            points = _score( auction.contract(), nsTricks );
        }
        else
        {
            points = _score( auction.contract(), ewTricks );
        }
        std::cout << "Scoring " << points << " points" << std::endl;
    }
};

