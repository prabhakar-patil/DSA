#ifndef _LIST_EXCEPTION_H_
#define _LIST_EXCEPTION_H_

#include <stdexcept>

using std::runtime_error;

class list_empty : public runtime_error
{
public:
	list_empty () : runtime_error ("runtime_error:List empty") {}
};

class data_not_found : public runtime_error
{
public:
	data_not_found () : runtime_error ("runtime_error:Given data does not exist") {}
};

#endif /*_LIST_EXCEPTION_H_*/
