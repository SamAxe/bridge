#pragma once
#include <vector>
#include "bid.h"

//  A class to record an auction
struct Auction
{
    std::vector< Bid > auction;     // List of bids
    bool bidOpened;                 // bool saying whether a non P bid has been made
private:
    Bid currentContract;            // current contract if the auction closed now
public:

    Auction()
     :  currentContract( 'U', 0 )
    {
        bidOpened = false;
    }
    // Is the auction open yet?
    bool open() const
    {
        return (!bidOpened && passes() != 4) || 
                (bidOpened && passes() != 3 && (lastBid( ) != Bid( 'U', 7, 'N' ) ) );
    }
 
    //  Record a bid in the auction
    void bid( Bid const & _bid )
    {
        auction.push_back( _bid );
        if ( !_bid.passed() )
        {
            bidOpened = true;
            currentContract = _bid;
        }
    }

    // What was the last bid made
    Bid lastBid() const
    {
        return auction[ auction.size() - 1];
    }

    //  Count of consecutive passes
    int passes() const
    {
        int c = 0;
        int i = auction.size() - 1; 
        while ( i >= 0 && auction[i].passed() )
        {
            c++;
            i--;
        }
        return c;
    }
    //  The current contract
    Bid contract() const
    {
        return currentContract;
    }

    //  The declarer who won the auction
    int declarer() const
    {
        char trump = contract().trump();
        int  position = contract().position();
        unsigned int i = 0;
        for ( ; i < auction.size(); i++ )
        {
            if ( !auction[i].passed() && auction[i].trump() == trump && ((auction[i].position() % 2) == (position % 2 )) )
                break;
        }
        return auction[i].position();
    }
};

