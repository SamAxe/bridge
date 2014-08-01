#pragma once

#include "bid.h"

class Score
{
public:
    int operator()( Bid const & bid, int totalTricks, bool vulnerable = false, bool _double = false, bool redouble = false )
    {
        int penalityTricks = totalTricks - 6 - bid.rank();

        int minorTrickPoints = 20;
        int majorTrickPoints = 30;
        int noTrumpFirstTrickBonus = 10;

        int contractPoints   = 0;
        int overTrickPoints  = 0;

        if ( _double )
        {
            minorTrickPoints *= 2;
            majorTrickPoints *= 2;
            noTrumpFirstTrickBonus *= 2;
        }

        if ( redouble )
        {
            minorTrickPoints *= 2;
            majorTrickPoints *= 2;
            noTrumpFirstTrickBonus *= 2;
        }

        if ( penalityTricks < 0 )
        {
            int penalty = 0;
            if ( !_double && !redouble )
                penalty = penalityTricks * (vulnerable?100:50);
            if ( _double && !vulnerable )
            {
                penalty -= ( redouble ? 200 : 100);
                if ( penalityTricks < -1 )
                    penalty -= ( redouble ? 400 : 200);
                if ( penalityTricks < -2 )
                    penalty -= ( redouble ? 400: 200);
                if ( penalityTricks < -3 )
                    penalty -= ( redouble ? 600:300) * ( penalityTricks + 3 );
            }
            if ( _double && vulnerable )
            {
                penalty -= ( redouble ? 400 : 200);
                if ( penalityTricks < -1 )
                    penalty -= ( redouble ? 600 : 300);
                if ( penalityTricks < -2 )
                    penalty -= ( redouble ? 600: 300);
                if ( penalityTricks < -3 )
                    penalty -= ( redouble ? 600:300) * ( penalityTricks + 3 );
            }
            return penalty;         
        }
        else 
        {
            if ( bid.trump() == 'C' || bid.trump() == 'D' )
            {
                contractPoints = bid.rank() * minorTrickPoints;
                overTrickPoints = (totalTricks - 6 - bid.rank()) * minorTrickPoints;
            }
            else if ( bid.trump() == 'H' || bid.trump() == 'S' )
            {
                contractPoints = bid.rank() * majorTrickPoints;
                overTrickPoints = (totalTricks - 6 - bid.rank()) * majorTrickPoints;
            }
            else if ( bid.trump() == 'N' )
            {
                contractPoints = bid.rank() * majorTrickPoints + noTrumpFirstTrickBonus;
                overTrickPoints = (totalTricks - 6 - bid.rank()) * majorTrickPoints;
            }
            int insult( 0 );
            if ( _double && vulnerable && !redouble )
            {
                overTrickPoints = ( totalTricks - 6 - bid.rank() ) * 200;
                insult = 50;
            }
            if ( _double && vulnerable==false && !redouble )
            {
                overTrickPoints = ( totalTricks - 6 - bid.rank() ) * 100;
                insult = 50;
            }
            if ( _double && vulnerable && redouble )
            {
                overTrickPoints = ( totalTricks - 6 - bid.rank() ) * 400;
                insult = 100;
            }
            if ( _double && vulnerable==false && redouble )
            {
                overTrickPoints = ( totalTricks - 6 - bid.rank() ) * 200;
                insult = 100;
            }

            int bonus(0);
            if ( contractPoints < 100 )
                bonus += 50;
            if ( contractPoints >= 100 )
                bonus += (vulnerable?500:300);
            if ( bid.rank() == 6 )
                bonus += (vulnerable?750:500);
            if ( bid.rank() == 7 )
                bonus += (vulnerable?1500:1000);

            return contractPoints + overTrickPoints + bonus + insult;
        }
        return 0;
    }
};

