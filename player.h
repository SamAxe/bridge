#pragma once

#include <string>
#include "hand.h"

class Player
{
protected:
    int pos;
    std::string position;
    Hand hand;
public:

    void acceptCard( Card const & c )
    {
        hand.addCard( c );
    }

    explicit Player( int _pos, std::string const & _position ) : pos( _pos ), position( _position )
    {
    }

    virtual Bid  pickBid( Auction const & auction ) const = 0;
    virtual Card pickCard( Trick const & trick ) const = 0;

    std::string const & getName() const { return position; }

    void show()
    {
        hand.show();
    }
    void playCard( Card const & c )
    {
        hand.playCard( c );
    }
    virtual void dealDone()
    {
    }
};

struct PlayerComputer : public Player
{
    explicit PlayerComputer( int _pos, std::string const & _position ) 
     : Player( _pos, _position ) 
    {
    }
    Bid pickBid( Auction const & auction ) const
    {
        if ( pos == 0 )
            return Bid( pos, 5 );
        else
            return Bid( pos, 0 );
    }
    Card pickCard( Trick const & trick ) const
    {
        std::vector< Card > possible;

        if ( trick.position() > 0 )
        {
            for( Card const & c : hand.cards() )
            {
                if ( c.suit() == trick.suitLead() )
                    possible.push_back( c );
            }
        }
        if ( possible.size() == 0 )
            possible = hand.cards();

        std::sort( possible.begin(), possible.end() );
        if ( trick.position() == 1 )                  // 2nd hand low
            return possible[0];
        else if ( trick.position() == 2 )             // 3rd hand high
            return possible[ possible.size() - 1];
        else                                          // random card
            return possible[ rand() % possible.size() ];
    }
};

