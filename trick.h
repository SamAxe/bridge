#pragma once
#include "card.h"

class Trick
{
    std::vector< Card > round;
public:
    void play( Card const & c ) 
    { 
        round.push_back( c ); 
    }

    int winner( char trump ) const
    {
        // should be 4 cards in round
        int w = 0;
        for ( unsigned int i = 1; i < round.size(); i++ )
        {
            if ( ( round[w].suit() != trump && round[i].suit()  == trump) ||
                 (round[w].suit() == round[i].suit() && round[i].rank() > round[w].rank() ) )
                w = i;
        }
        return w;
    }

    int position() const
    {
        return round.size();
    }

    char suitLead() const
    {
        return round[0].suit();
    }
};


