//  allen@matrix:~/Study/c++11$ g++ --version
//  g++ (Debian 5.3.1-8) 5.3.1 20160205
//  Copyright (C) 2015 Free Software Foundation, Inc.
//  This is free software; see the source for copying conditions.  There is NO
//  warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

#include <utility>
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <sstream>

namespace
{
void nameIt( std::string& name, int id )
{
    std::ostringstream ostrm;

    ostrm << name << " " << std::setw( 4 ) << std::setfill( '0' ) << id ;

    name = ostrm.str();	//	move assignment ;)
}

}

class Base
{
    private:
        static int counter_;

    private:
        int id_;
        std::string name_;

    public:
        Base()
            : name_( "I am groot!" )
        {
            id_ = ++counter_;
            nameIt( name_, id_ );
        }

    public:
        virtual void whoami()
        {
            std::cout << "  Base::id_=(" << id_ << ")\n";
            std::cout << "  Base::name_=(" << name_ << ")\n";
        }
};


int Base::counter_ = 0;


class Derived : public Base
{
    private:
        static int counter_;

    private:
        int id_;
        std::string name_;

        //	ctor
        //	we don't define move ctor
    public:
        Derived()
            : name_( "gentle compiler" )
        {
            id_ = ++counter_;
            nameIt( name_, id_ );
        };

    public:
        virtual void whoami()
        {
            std::cout << "  Derived::id_=(" << id_ << ")\n";
            std::cout << "  Derived::name_=(" << name_ << ")\n";
            Base::whoami();
        }
};


class DerivedNotCallingBaseMove : public Base
{
    private:
        static int counter_;

    private:
        int id_;
        std::string name_;

    public:
        DerivedNotCallingBaseMove()
            : name_( "revenge of compiler" )
        {
            id_ = ++counter_;
            nameIt( name_, id_ );
        };

        //	we define move ctor
        //	but, don't call move ctor for base class
        //	and omit a member variable
        DerivedNotCallingBaseMove( DerivedNotCallingBaseMove&& other )
            : id_( std::move( other.id_ ) ), name_( std::move( other.name_ ) )
        {
        }

        //
    public:
        virtual void whoami()
        {
            std::cout << "  DerivedNotCallingBaseMove::id_=(" << id_ << ")\n";
            std::cout << "  DerivedNotCallingBaseMove::name_=(" << name_ << ")\n";
            Base::whoami();
        }
};

int Derived::counter_ = 0;
int DerivedNotCallingBaseMove::counter_ = 0;

template< typename T >
void testMoveCtor()
{
    std::cout << "\ntestMoveCtor Start: " << typeid( T ).name() << '\n';

    std::cout << "--------------------\n";
    T t1;
    std::cout << typeid( T ).name() << " t\n";
    t1.whoami();

    std::cout << "--------------------\n";
    T t2( std::move( t1 ) );
    std::cout << typeid( T ).name() << " t2( std::move( t1 ) )\n";
    t2.whoami();
    std::cout << "What happened to t1?\n";
    t1.whoami();

    //
    //	Revenge of compiler, but still gentle ;)
    //

    //	compiler didn't complain about absence of move assign operator unless it is called
    //T t3;
    //t3 = std::move( t2 );

    //	compiler didn't complain about absence of copy ctor unless it is called
	//T t4( t2 );
	//t4.whoami();

    std::cout << "testMoveCtor End: " << typeid( T ).name() << '\n';
}

int main( int argc, char* argv[] )
{
    Base b;
    std::cout << "Base b\n";
    b.whoami();

    testMoveCtor< Derived >();

    testMoveCtor< DerivedNotCallingBaseMove >();

    return 0;
}
