#include <iostream>
#include <string>

class Empty
{
    private:
        std::string name_;

};


class OnlyDtor
{
    private:
        std::string name_;

    public:
        ~OnlyDtor()
        {
        }
};


class OnlyCCtor
{
    private:
        std::string name_;

    public:
        //	When we define either of copy ctor, move ctor or move operator,
        //	compiler doesn't creat default ctor
        OnlyCCtor()
        {
        }

        //	copy ctor
        OnlyCCtor( const OnlyCCtor& other )
        {
            std::cout << "  OnlyCCtor: I am copy ctor\n";
        }
};


class OnlyCopyAssignOperator
{
    private:
        std::string name_;

    public:
        OnlyCopyAssignOperator& operator=( const OnlyCopyAssignOperator& rhs )
        {
            std::cout << "  OnlyCopyAssignOperator: I am copy assign operator\n";
            return *this;
        }
};


class OnlyMCtor
{
    private:
        std::string name_;

    public:
        //	When we define either of copy ctor, move ctor or move operator,
        //	compiler doesn't creat default ctor
        OnlyMCtor()
        {
        }

        //	Compiler doesn't create
        //		copy ctor
        //		copy assign operator
        //		move opertor
        OnlyMCtor( OnlyMCtor&& other )
        {
        };
};


class OnlyMoveAssignOperator
{
    private:
        std::string name_;

    public:
        //	When we define either of copy ctor, move ctor or move operator,
        //	compiler doesn't creat default ctor
        OnlyMoveAssignOperator()
        {
        }

    public:
        //	Compiler doesn't create move ctor
        OnlyMoveAssignOperator& operator=( OnlyMoveAssignOperator&& other )
        {
            return *this;
        };
};


template< typename T >
void specialMembers( const std::string& ClassName )
{
    std::cout << ClassName << " Start\n";
    T t1;

    std::cout << "copy ctor\n";
    T t2( t1 ); // copy
    std::cout << "move ctor\n";
    T&& t3( std::move( t1 ) ); // ?? move if move ctor exist, otherwise copy

    std::cout << "copy assign operator\n";
    t2 = t1; //	copy
    std::cout << "move assign operator\n";
    t3 = T(); // move if move assign operator exists, otherwise copy
    std::cout << ClassName << " End\n\n";
}


int main( int argc, char* argv[] )
{
    specialMembers< Empty >( "Empty" );

    //	C++98 compatible
    specialMembers< OnlyDtor >( "OnlyDtor" );
    specialMembers< OnlyCCtor >( "OnlyCCtor" );
    specialMembers< OnlyCopyAssignOperator >( "OnlyCpyAssignOperator" );
    //	C++11
#if 1
    //specialMembers< OnlyMCtor >( "OnlyMCtor" );
#else
    OnlyMCtor t1;
    OnlyMCtor t2( t1 );
    OnlyMCtor&& t3 = OnlyMCtor();
    t2 = t3;
    t3 = OnlyMCtor();
#endif

#if 1
    //specialMembers< OnlyMoveAssignOperator >( "OnlyMoveAssignOperator" );
#else
    OnlyMoveAssignOperator t1;
    OnlyMoveAssignOperator t2( t1 );
    OnlyMoveAssignOperator&& t3 = OnlyMoveAssignOperator();
    t2 = t3;
    t3 = OnlyMoveAssignOperator();
#endif

    return 0;
}
