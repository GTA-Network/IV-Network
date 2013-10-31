
#ifndef ApplyTuple_h
#define ApplyTuple_h

#include <Common.h>

#include "CScriptVM.h"
#include <stdint.h>
#include <tuple>

template<typename T>
T getValue(CScriptVM*, int idx);

template<>
int getValue<int>(CScriptVM* pVM, int idx);

template<>
double getValue<double>(CScriptVM* pVM, int idx);

template<>
float getValue<float>(CScriptVM* pVM, int idx);

template<>
DWORD getValue<DWORD>(CScriptVM* pVM, int idx);

template<>
bool getValue<bool>(CScriptVM* pVM, int idx);

template<>
char getValue < char>(CScriptVM* pVM, int idx);

template<>
unsigned int getValue<unsigned int>(CScriptVM* pVM, int idx);

template<>
const char *getValue<const char *>(CScriptVM* pVM, int idx);

template<>
CString getValue<CString>(CScriptVM* pVM, int idx);

#if 1
template<class T>
T getValue_(CScriptVM *pVM, unsigned int idx, std::true_type)
{
	{
		return (T) pVM->GetUserData(idx);
	}
	T v = *(T *) pVM->GetUserData(idx);
	return v;

	printf("getValuePtr: failed to get a class instance for script stack value at idx: %i\n", idx);
return 0;
}

template<class T>
T getValue_(CScriptVM* pVM, unsigned int idx, std::false_type)
{
	{
		return *(T*) (T) pVM->GetUserData(idx);
	}

	return **(T **) (T) pVM->GetUserData(idx);

printf("getValue: failed to get a class instance for lua stack value at idx: %i\n", idx);
return T();
}
#endif

template<class T>
T getValue(CScriptVM* pVM, int idx)
{
	return getValue_<T>(pVM, idx, std::is_pointer<T>());
}

template<typename T>
void returnValue(CScriptVM* pVM, T);

template<>
void returnValue(CScriptVM* pVM, int v);

template<>
void returnValue(CScriptVM* pVM, double v);

template<>
void returnValue(CScriptVM* pVM, const char *v);

template<>
void returnValue(CScriptVM* pVM, CString v);

template<>
void returnValue(CScriptVM* pVM, float v);

template<>
void returnValue(CScriptVM* pVM, unsigned int v);

template<>
void returnValue(CScriptVM* pVM, char v);

template<>
void returnValue(CScriptVM* pVM, bool v);

template<>
void returnValue(CScriptVM * pVM, DWORD v);

template<>
void returnValue(CScriptVM * pVM, CVector3 v);

template<class T>
void returnValue(CScriptVM* pVM, T *v);

#ifndef _CLIENT
class CVehicleEntity;
template<>
void returnValue(CScriptVM* pVM, CVehicleEntity* v);
#endif

// this is currently a source of memory leaks :(
// need to tell the code that lua owns it somehow
template<class T>
void returnValue(CScriptVM* pVM, T v);


// original apply tuple code:
// http://stackoverflow.com/questions/687490/how-do-i-expand-a-tuple-into-variadic-template-functions-arguments
/**
* Object Function Tuple Argument Unpacking
*
* This recursive template unpacks the tuple parameters into
* variadic template arguments until we reach the count of 0 where the function
* is called with the correct parameters
*
* @tparam N Number of tuple arguments to unroll
*
* @ingroup g_util_tuple
*/
template < int N >
struct apply_obj_func
{
	template < typename T, typename R, typename... ArgsF, typename... ArgsT, typename... Args >
	static R applyTuple(CScriptVM* pVM, T* pObj,
		R (T::*f)( ArgsF... ),
		const std::tuple<ArgsT...> &t,
		Args... args )
	{
		const static int argCount = sizeof...(ArgsT);
		typedef typename std::remove_reference<decltype(std::get<N-1>(t))>::type ltype_const;
		typedef typename std::remove_const<ltype_const>::type ltype;
		return apply_obj_func<N-1>::applyTuple(pVM, pObj, f, std::forward<decltype(t)>(t), getValue<ltype>(pVM, -(argCount-N+1)), args... );
	}
};

//-----------------------------------------------------------------------------

/**
* Object Function Tuple Argument Unpacking End Point
*
* This recursive template unpacks the tuple parameters into
* variadic template arguments until we reach the count of 0 where the function
* is called with the correct parameters
*
* @ingroup g_util_tuple
*/
template <>
struct apply_obj_func<0>
{
	template < typename T, typename R, typename... ArgsF, typename... ArgsT, typename... Args >
	static R applyTuple(CScriptVM* pVM, T* pObj,
		R (T::*f)( ArgsF... ),
		const std::tuple<ArgsT...> &/* t */,
		Args... args )
	{
		return (pObj->*f)( args... );
	}
};

//-----------------------------------------------------------------------------

/**
* Object Function Call Forwarding Using Tuple Pack Parameters
*/
// Actual apply function
template < typename T, typename R, typename... ArgsF, typename... ArgsT >
R applyTuple(CScriptVM* pVM, T* pObj,
			 R (T::*f)( ArgsF... ),
			 const std::tuple<ArgsT...> &t )
{
	return apply_obj_func<sizeof...(ArgsT)>::applyTuple(pVM, pObj, f, std::forward<decltype(t)>(t) );
}

//-----------------------------------------------------------------------------

/**
* Static Function Tuple Argument Unpacking
*
* This recursive template unpacks the tuple parameters into
* variadic template arguments until we reach the count of 0 where the function
* is called with the correct parameters
*
* @tparam N Number of tuple arguments to unroll
*
* @ingroup g_util_tuple
*/
typedef unsigned int uint;
template < uint N >
struct apply_func
{
	template < typename R, typename... ArgsF, typename... ArgsT, typename... Args >
	static R applyTuple(CScriptVM *pVM, R (*f)( ArgsF... ),
		const std::tuple<ArgsT...>& t,
		Args... args )
	{
		const static int argCount = sizeof...(ArgsT);
		typedef typename std::remove_reference<decltype(std::get<N-1>(t))>::type ltype_const;
		typedef typename std::remove_const<ltype_const>::type ltype;
		return apply_func<N-1>::applyTuple(pVM, f, std::forward<decltype(t)>(t), getValue<ltype>(pVM, -(argCount-N+1)), args... );
	}
};

//-----------------------------------------------------------------------------

/**
* Static Function Tuple Argument Unpacking End Point
*
* This recursive template unpacks the tuple parameters into
* variadic template arguments until we reach the count of 0 where the function
* is called with the correct parameters
*
* @ingroup g_util_tuple
*/
template <>
struct apply_func<0>
{
	template < typename R, typename... ArgsF, typename... ArgsT, typename... Args >
	static R applyTuple(CScriptVM *, R (*f)( ArgsF... ),
		const std::tuple<ArgsT...>& /* t */,
		Args... args )
	{
		return f( args... );
	}
};

//-----------------------------------------------------------------------------

/**
* Static Function Call Forwarding Using Tuple Pack Parameters
*/
// Actual apply function
template < typename R, typename... ArgsF, typename... ArgsT >
R applyTuple(CScriptVM *pVM, R (*f)(ArgsF...),
			 const std::tuple<ArgsT...> & t )
{
	return apply_func<sizeof...(ArgsT)>::applyTuple(pVM, f, std::forward<decltype(t)>(t) );
}

//-----------------------------------------------------------------------------

// object constructor tuple unpack

/**
* Ctor Function Tuple Argument Unpacking
*
* This recursive template unpacks the tuple parameters into
* variadic template arguments until we reach the count of 0 where the function
* is called with the correct parameters
*
* @tparam N Number of tuple arguments to unroll
*
* @ingroup g_util_tuple
*/
template <class C, uint N >
struct apply_ctor_func
{
	template < typename... ArgsT, typename... Args >
	static C *applyTuple(CScriptVM *pVM, const std::tuple<ArgsT...>& t,
		Args... args )
	{
		const static int argCount = sizeof...(ArgsT);
		typedef typename std::remove_reference<decltype(std::get<N-1>(t))>::type ltype_const;
		typedef typename std::remove_const<ltype_const>::type ltype;
		return apply_ctor_func<C, N-1>::applyTuple(pVM, std::forward<decltype(t)>(t), getValue<ltype>(pVM, -(argCount-N+1)), args... );
	}
};

//-----------------------------------------------------------------------------

/**
* ctor Function Tuple Argument Unpacking End Point
*
* This recursive template unpacks the tuple parameters into
* variadic template arguments until we reach the count of 0 where the function
* is called with the correct parameters
*
* @ingroup g_util_tuple
*/
template <class C>
struct apply_ctor_func<C, 0>
{
	template < typename... ArgsT, typename... Args >
	static C *applyTuple(CScriptVM *pVM,  const std::tuple<ArgsT...>& /* t */,
		Args... args )
	{
		return new C( args... );
	}
};

//-----------------------------------------------------------------------------

/**
* ctor Function Call Forwarding Using Tuple Pack Parameters
*/
// Actual apply function
template < typename C, typename... ArgsT >
C *applyTuple(CScriptVM *pVM, const std::tuple<ArgsT...> & t )
{
	return apply_ctor_func<C, sizeof...(ArgsT)>::applyTuple(pVM, std::forward<decltype(t)>(t) );
}

#endif