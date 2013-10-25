#ifndef CScriptClass_h
#define CScriptClass_h
#include <assert.h>
#include <Squirrel/squirrel.h>

#include <Common.h>
#include <Math/CMaths.h>

#include "CScriptVM.h"
#include "ResourceSystem/CResourceManager.h"

#include <SharedUtility.h>
#include <CLogFile.h>
#include "CSquirrelVM.h"
#include "CScriptArgument.h"
#include <tuple>
#include "ApplyTuple.h"

class CScriptMethodBase
{
public:
	virtual bool Register(CScriptVM* pVM) = 0;
};
// This code is taken from scrbind a multi script binding library for Lua + Squirrel
// https://github.com/Tomasu/LuaGlue

template<typename _Ret, typename _Class, typename... _Args>
class CScriptMethod : public CScriptMethodBase
{
private:
	std::string name_;
public:
	typedef _Class ClassType;
	typedef _Ret ReturnType;
	typedef _Ret(_Class::*MethodType)(_Args...);

	CScriptMethod(const std::string &name, MethodType && fn) : name_(name), fn(std::forward<decltype(fn)>(fn))
	{ }

	bool Register(CScriptVM* pVM)
	{
		// TODO: add userdata this
		/* LUA
		lua_pushlightuserdata(m_pVM, this);
		lua_pushcclosure(m_pVM, &call_func, 1);
		lua_setfield(m_pVM, -2, name_.c_str());
		*/
		if(pVM->GetVMType() == LUA_VM)
		{
			lua_State* m_pVM = ((CLuaVM*)pVM)->GetVM();

			lua_pushlightuserdata(m_pVM, this);
			lua_pushcclosure(m_pVM, (lua_CFunction)call_func, 1);
			lua_setfield(m_pVM, -2, name_.c_str());
			//lua_pushstring(m_pVM, "__index");
			//lua_pushcfunction(m_pVM, (lua_CFunction)call_func);
			//lua_settable(m_pVM, -3);

			//luaL_setfuncs
			//
			//lua_pushstring(m_pVM, name_.c_str());
			//lua_pushlightuserdata(m_pVM, this);
			//lua_pushcclosure(m_pVM, (lua_CFunction)call_func, 1);
			//lua_settable(m_pVM, -3);
		} else if(pVM->GetVMType() == SQUIRREL_VM) {
			SQVM* m_pVM = ((CSquirrelVM*)pVM)->GetVM();
			//pVM->RegisterClassFunction(name_.c_str(), call_func);
			//
			sq_pushstring(m_pVM, name_.c_str(), -1);
			sq_pushuserpointer(m_pVM, this);
			sq_newclosure(m_pVM, (SQFUNCTION)call_func, 1);
			sq_newslot(m_pVM, -3, SQFalse);
		}
		return true;
	}

	int invoke(int * VM)
	{
		GET_SCRIPT_VM_SAFE;

		ClassType *obj = (ClassType *)pVM->GetClassInstance("");

		ReturnType ret = applyTuple(pVM, (_Class *) obj, fn, args);

		CLogFile::Printf("[TODO] Pop values after call [%s]", __FUNCTION__);
		//if (Arg_Count_) pop(Arg_Count_);

		returnValue(pVM, ret);

		return 1;
	}

	static int call_func(int * VM)
	{
		GET_SCRIPT_VM_SAFE;
		if(pVM->GetVMType() == LUA_VM)
		{
			auto mimp = (CScriptMethod<_Ret, _Class, _Args...> *)pVM->GetUserData(lua_upvalueindex(1));
			return mimp->invoke(VM);
		} else if(pVM->GetVMType() == SQUIRREL_VM) {
			auto mimp = (CScriptMethod<_Ret, _Class, _Args...> *)pVM->GetUserData(-1);
			return mimp->invoke(VM);
		}
		return 0;
	}
private:
	MethodType fn;
	std::tuple<_Args...> args;
	static const unsigned int Arg_Count_ = sizeof...(_Args);
};

template<typename _Class, typename... _Args>
class CScriptMethod<void, _Class, _Args...> : public CScriptMethodBase
{
private:
	std::string name_;
public:
	typedef _Class ClassType;
	typedef void (_Class::*MethodType)(_Args...);

	CScriptMethod(const std::string &name, MethodType && fn) : name_(name), fn(std::forward<decltype(fn)>(fn))
	{ }

	bool Register(CScriptVM* pVM)
	{
		// TODO: add userdata this
		/* LUA
		lua_pushlightuserdata(m_pVM, this);
		lua_pushcclosure(m_pVM, &call_func, 1);
		lua_setfield(m_pVM, -2, name_.c_str());
		*/
		if (pVM->GetVMType() == LUA_VM)
		{
			lua_State* m_pVM = ((CLuaVM*) pVM)->GetVM();

			lua_pushlightuserdata(m_pVM, this);
			lua_pushcclosure(m_pVM, (lua_CFunction) call_func, 1);
			lua_setfield(m_pVM, -2, name_.c_str());
			//lua_pushstring(m_pVM, "__index");
			//lua_pushcfunction(m_pVM, (lua_CFunction)call_func);
			//lua_settable(m_pVM, -3);

			//luaL_setfuncs
			//
			//lua_pushstring(m_pVM, name_.c_str());
			//lua_pushlightuserdata(m_pVM, this);
			//lua_pushcclosure(m_pVM, (lua_CFunction)call_func, 1);
			//lua_settable(m_pVM, -3);
		}
		else if (pVM->GetVMType() == SQUIRREL_VM) {
			SQVM* m_pVM = ((CSquirrelVM*) pVM)->GetVM();
			//pVM->RegisterClassFunction(name_.c_str(), call_func);
			//
			sq_pushstring(m_pVM, name_.c_str(), -1);
			sq_pushuserpointer(m_pVM, this);
			sq_newclosure(m_pVM, (SQFUNCTION) call_func, 1);
			sq_newslot(m_pVM, -3, SQFalse);
		}
		return true;
	}

	int invoke(int * VM)
	{
		GET_SCRIPT_VM_SAFE;

		ClassType *obj = (ClassType *) pVM->GetClassInstance("");

		applyTuple(pVM, (_Class *) obj, fn, args);

		CLogFile::Printf("[TODO] Pop values after call [%s]", __FUNCTION__);
		//if (Arg_Count_) pop(Arg_Count_);

		return 0;
	}

	static int call_func(int * VM)
	{
		GET_SCRIPT_VM_SAFE;
		if (pVM->GetVMType() == LUA_VM)
		{
			auto mimp = (CScriptMethod<void, _Class, _Args...> *)pVM->GetUserData(lua_upvalueindex(1));
			return mimp->invoke(VM);
		}
		else if (pVM->GetVMType() == SQUIRREL_VM) {
			auto mimp = (CScriptMethod<void, _Class, _Args...> *)pVM->GetUserData(-1);
			return mimp->invoke(VM);
		}
		return 0;
	}
private:
	MethodType fn;
	std::tuple<_Args...> args;
	static const unsigned int Arg_Count_ = sizeof...(_Args);
};

template<typename _Class>
class CScriptClass
{
private:
	
	std::list<CScriptMethodBase *> methods;
	CScriptMethodBase* m_pCtorMethod;
	
public:
	std::string name_;
	typedef _Class ClassType;

	CScriptClass(const std::string &name) : name_(name)
	{ }

	~CScriptClass() { }

	template<typename _Ret, typename... _Args>
	CScriptClass<_Class> &SetCtor(const std::string &name, _Ret(_Class::*fn)(_Args...))
	{
		m_pCtorMethod = new CScriptMethod<_Ret, _Class, _Args...>(name, std::forward<decltype(fn)>(fn));

		return *this;
	}

	template<typename... _Args>
	CScriptClass<_Class> &SetCtor(const std::string &name, void (_Class::*fn)(_Args...))
	{
		m_pCtorMethod = new CScriptMethod<void, _Class, _Args...>(name, std::forward<decltype(fn)>(fn));
		return *this;
	}

	template<typename _Ret, typename... _Args>
	CScriptClass<_Class> &AddMethod(const std::string &name, _Ret(_Class::*fn)(_Args...))
	{
		auto impl = new CScriptMethod<_Ret, _Class, _Args...>(name, std::forward<decltype(fn)>(fn));
		methods.push_back(impl);

		return *this;
	}

	template<typename... _Args>
	CScriptClass<_Class> &AddMethod(const std::string &name, void (_Class::*fn)(_Args...))
	{
		auto impl = new CScriptMethod<void, _Class, _Args...>(name, std::forward<decltype(fn)>(fn));
		methods.push_back(impl);

		return *this;
	}

	bool Register(CScriptVM* pVM)
	{
		// Do additional stuff before add something to the vm
		if(pVM->GetVMType() == LUA_VM)
		{
			lua_State* m_pVM = ((CLuaVM*)pVM)->GetVM();
			lua_pushstring(m_pVM, name_.c_str());
			lua_pushlightuserdata(m_pVM, this);
		}
		// Register Script class have to prepare the stack and register to start registering the methods
		pVM->RegisterScriptClass(name_.c_str(), ctor, this);

		// Register member methods
		for (auto &method : methods)
		{
			if (!method->Register(pVM))
				return false;
		}

		pVM->FinishRegisterScriptClass();

		return true;
	}

	bool RegisterMethods(CScriptVM* pVM)
	{
		// Register member methods
		for (auto &method : methods)
		{
			if (!method->Register(pVM))
				return false;
		}
		return true;
	}

	static int ctor(int *VM)
	{	
		GET_SCRIPT_VM_SAFE;

		switch (pVM->GetVMType())
		{
		case LUA_VM:
			{
				auto mimp = ((CScriptClass<_Class> *)pVM->GetUserData(lua_upvalueindex(1)));
				pVM->SetClassInstance(mimp->name_.c_str(), new ClassType);
			}
			break;
		case SQUIRREL_VM:
			{
				auto mimp = ((CScriptClass<_Class> *)pVM->GetUserData(-1));
				pVM->SetClassInstance(mimp->name_.c_str(), new ClassType);
			}
			break;
		default:
			{
				CLogFile::Printf("Warning: Unknown VM Type");
			}
			break;
		}
		// Note class need default constructor
		return 1;
	}
};

#endif