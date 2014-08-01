#pragma once
#include <sstream>

class Bid
{
    int _position;      // The player making the bid
    int _value;         // The value of the bid
public:

    bool passed() const 
    { 
        return _value == 0; 
    }

    int position() const
    {
        return _position;
    }

    int value() const 
    { 
        return _value; 
    }  // only use from bidRule...

    // COnvert bid to a string
    std::string str() const
    {
        std::stringstream ss;
        if ( _value == 0 )
            return "P";
        ss << rank() << trump();
        return ss.str();
    }

    // The rank of the bid, 0-C, 1-D, 2-H, 3-S, 4-NT
    int rank() const 
    { 
        return (_value - 1) / 5 + 1; 
    }

    char trump() const
    {   
        switch (( _value - 1 ) % 5 )
        {
            case 0:
                return 'C';
            case 1:
                return 'D';
            case 2:
                return 'H';
            case 3:
                return 'S';
            case 4:
                return 'N';
        }
//std::cout << "returning " << ((_value - 1 ) % 5) << std::endl;
        return 'Z';
    }

    Bid( int p, int b ) : _position(p), _value( b )
    {
    }

    Bid( int p, int r, char t ) : _position(p)
    {
        _value = (r-1) * 5 + 1;
        if ( t == 'C' )
            _value += 0;
        else if ( t == 'D' )
            _value += 1;
        else if ( t == 'H' )
            _value += 2;
        else if ( t == 'S' )
            _value += 3;
        else if ( t == 'N' )
            _value += 4;
    }

    bool operator!=( Bid const & rhs ) const
    {
        return !((*this) == rhs);
    }
    bool operator==( Bid const & rhs ) const
    {
        return _value == rhs._value;
    }
};

std::ostream & operator<<( std::ostream & stream, Bid const & rhs )
{
    stream << rhs.rank() << rhs.trump();
    return stream;
}


