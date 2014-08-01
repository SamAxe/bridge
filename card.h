#pragma once

struct Card
{
private:
    int _rank;
    int _suit;
public:
    Card( int r=0, int s=0 ) 
     : _rank( r ), _suit( s ) 
    {
    }

    bool operator==( Card const & rhs ) const
    {
        return _rank == rhs._rank && _suit == rhs._suit;
    }
    bool operator<( Card const & rhs ) const
    {
        if ( _suit == rhs._suit )
            return _rank < rhs._rank;
        return _suit < rhs._suit;
    }
    char const suit( ) const
    {
        switch( _suit )
        {
            case 0:
                return 'C';
            case 1:
                return 'D';
            case 2:
                return 'H';
            case 3:
                return 'S';
            default:
                return 'U';
        }
    }

    char const rank( ) const
    {
        switch( _rank )
        {
            case 0:
                return '2';
            case 1:
                return '3';
            case 2:
                return '4';
            case 3:
                return '5';
            case 4:
                return '6';
            case 5:
                return '7';
            case 6:
                return '8';
            case 7:
                return '9';
            case 8:
                return 'T';
            case 9:
                return 'J';
            case 10:
                return 'Q';
            case 11:
                return 'K';
            case 12:
                return 'A';
            default:
                return 'X';
        }
    }
};

std::ostream & operator<<( std::ostream & stream, Card const & rhs )
{
    stream << rhs.rank( ) << rhs.suit( );
    return stream;
}



