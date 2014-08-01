#pragma once
#include <vector>

#include "bid.h"
#include "card.h"
#include "auction.h"
#include "trick.h"

class Hand
{
    std::vector<Card> _cards;
public:

    Hand() 
    { 
    }

    void addCard( Card const & c )
    {
        _cards.push_back( c );
    }

    std::vector<Card> const & cards() const
    {
        return _cards;
    }

    void playCard( Card const & card )
    {
        std::vector<Card>::iterator i = std::find( _cards.begin(), _cards.end(), card );        
        _cards.erase( i );
    }

    void show() const
    {
        std::vector< Card > clubs;
        std::vector< Card > diamonds;
        std::vector< Card > hearts;
        std::vector< Card > spades;

        for( Card const & card : _cards )
        {
            if ( card.suit( ) == 'C' )
                clubs.push_back( card );
            else if ( card.suit( ) == 'D' )
                diamonds.push_back( card );
            else if ( card.suit( ) == 'H' )
                hearts.push_back( card );
            else if ( card.suit( ) == 'S' )
                spades.push_back( card );
        }
        std::sort( clubs.rbegin(), clubs.rend() );
        std::sort( diamonds.rbegin(), diamonds.rend() );
        std::sort( hearts.rbegin(), hearts.rend() );
        std::sort( spades.rbegin(), spades.rend() );

        std::cout << "S: ";
        for( Card const & spade : spades )
            std::cout << spade.rank( );
        std::cout << std::endl;
        std::cout << "H: ";
        for ( Card const & heart : hearts )
            std::cout << heart.rank( );
        std::cout << std::endl;
        std::cout << "D: ";
        for( Card const & diamond : diamonds )
            std::cout << diamond.rank( );
        std::cout << std::endl;
        std::cout << "C: ";
        for( Card const & club: clubs )
            std::cout << club.rank( );
        std::cout << std::endl;
    }
         
};

