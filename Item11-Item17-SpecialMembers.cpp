#include <iostream>
#include <string>
#include <typeinfo>
#include <utility>

class Empty
{
    private:
        std::string name_;

    public:
        void name( const std::string& name )
        {
            name_ = name;
        }

        const std::string& name()
        {
            return name_;
        }
};


class OnlyDtor
{
    private:
        std::string name_;

    public:
        ~OnlyDtor()
        {
        }

    public:
        void name( const std::string& name )
        {
            name_ = name;
        }

        const std::string& name()
        {
            return name_;
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
            : name_( other.name_ )
        {
            std::cout << "  OnlyCCtor: I am copy ctor\n";
        }

    public:
        void name( const std::string& name )
        {
            name_ = name;
        }

        const std::string& name()
        {
            return name_;
        }
};


class OnlyCopyAssignOperator
{
    private:
        std::string name_;

    public:
        OnlyCopyAssignOperator& operator=( const OnlyCopyAssignOperator& rhs )
        {
            name_ = rhs.name_;
            std::cout << "  OnlyCopyAssignOperator: I am copy assign operator\n";
            return *this;
        }

    public:
        void name( const std::string& name )
        {
            name_ = name;
        }

        const std::string& name()
        {
            return name_;
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
            : name_( std::move( other.name_ ) )
        {
        }

    public:
        void name( const std::string& name )
        {
            name_ = name;
        }

        const std::string& name()
        {
            return name_;
        }
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
            name_ = std::move( other.name_ );
            return *this;
        };

    public:
        void name( const std::string& name )
        {
            name_ = name;
        }

        const std::string& name()
        {
            return name_;
        }
};


template< typename T >
void specialMembers( const std::string& name1, const std::string& name2, const std::string& name3 )
{
    std::cout << '\n' << typeid( T ).name() << " Start\n";
    T t1;
    std::cout << "\ndefault ctor\n";
    t1.name( name1 );
    std::cout << "    t1.name()=(" << t1.name() << ")\n";

    std::cout << "\ncopy ctor\n";
    T t2( t1 ); // copy
    std::cout << "    t2.name()=(" << t2.name() << ")\n";
    std::cout << "    t1.name()=(" << t1.name() << ")\n";

    std::cout << "\nmove ctor\n";
    T t3( std::move( t1 ) ); // ?? move if move ctor exist, otherwise copy
    std::cout << "    t3.name()=(" << t3.name() << ")\n";
    std::cout << "    t1.name()=(" << t1.name() << ")\n";

    std::cout << "\ncopy assign operator\n";
    std::cout << "  Before\n";
    t2.name( name2 );
    t3.name( name3 );
    std::cout << "    t2.name()=(" << t2.name() << ")\n";
    std::cout << "    t3.name()=(" << t3.name() << ")\n";
    t3 = t2; //	copy
    std::cout << "  After\n";
    std::cout << "    t2.name()=(" << t2.name() << ")\n";
    std::cout << "    t3.name()=(" << t3.name() << ")\n";

    std::cout << "\nmove assign operator\n";
    t3.name( name3 );
    std::cout << "  Before\n";
    std::cout << "    t2.name()=(" << t2.name() << ")\n";
    std::cout << "    t3.name()=(" << t3.name() << ")\n";
    t3 = std::move( t1 );//T(); // move if move assign operator exists, otherwise copy
    std::cout << "  After\n";
    std::cout << "    t2.name()=(" << t2.name() << ")\n";
    std::cout << "    t3.name()=(" << t3.name() << ")\n";

    std::cout << typeid( T ).name() << " End\n\n";
}


int main( int argc, char* argv[] )
{
    specialMembers< Empty >( "empty1", "empty2", "empty3" );

    //	C++98 compatible
    specialMembers< OnlyDtor >( "OnlyDtor1", "OnlyDtor2", "OnlyDtor3" );
    specialMembers< OnlyCCtor >( "OnlyCCtor1", "OnlyCCtor2", "OnlyCCtor3" );
    specialMembers< OnlyCopyAssignOperator >( "OnlyCpyAssignOperator1", "OnlyCpyAssignOperator2", "OnlyCpyAssignOperato3" );
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
