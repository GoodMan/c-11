#include "Warpper.h"

Wrapper::Wrapper()
{
}

Wrapper::~Wrapper()
{
    std::cout << "data_.size()=(" <<  data_.size() << ")\n";
}


Wrapper::DataType& Widget::data()& 	//	for lvalue wrapper
{
    return data_;
}


Wrapper::DataType Widget::data()&& 	//	for rvalue wrapper
{
    return data_;
}

void Wrapper::push_back( const Widget& w )
{
    data_.push_back( w );
}
