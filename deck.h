#pragma once

class Deck
{
    Card cards[52];
public:
    Deck()
    {
        for ( int i = 0; i < 4; i++ )
        {
            for ( int j = 0; j < 13; j++ )
            {
                cards[i*13+j] = Card( j, i );
            }
        }
    }
    void shuffle()
    {
        for ( int i = 0; i < 100; i++ )
        {
            int k = rand() % 52;
            int l = rand() % 52;
            std::swap( cards[k], cards[l] );
        }
    }
    void deal( Player *(&player)[4], int dealer )
    {
        for ( int i = 0; i < 13; i++ )
        {
            for ( int j = 0; j < 4; j++ )
            {
                player[ (j + dealer) % 4 ]->acceptCard( cards[i*4+j] );
            }
        }
    }
};

