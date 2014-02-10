#ifndef CScriptClass_h
#define CScriptClass_h
#include <assert.h>
#include <Squirrel/squirrel.h>

#include <Common.h>
#include <Math/CMaths.h>

#include "IScriptVM.h"
#include "ResourceSystem/CResourceManager.h"

#include <SharedUtility.h>
#include <CLogFile.h>
#include "CSquirrelVM.h"
#include "CScriptArgument.h"
#include <tuple>
#include "ApplyTuple.h"

#include <atomic>
#include <exception>
#include <memory>
#include <stdexcept>

/*
Object part, some lua stuff and some ideas taken from
https://github.com/Tomasu/LuaGlue

*/

#ifdef LUAGLUE_TYPECHECK
#	define GetLuaUdata(state, idx, name) ((LuaGlueObjectBase *)luaL_checkudata(state, idx, name))
#else
#	define GetLuaUdata(state, idx, name) ((LuaGlueObjectBase *)lua_touserdata(state, idx))
#endif

#define CastLuaGlueObject(ClassType, o) ((LuaGlueObject<ClassType> *)o)
#define CastLuaGlueObjectShared(ClassType, o) ( (LuaGlueObject<std::shared_ptr<ClassType>> *)o )

template<class _Class>
class CScriptClass;

class LuaGlueObjectImplBase
{
public:
	virtual ~LuaGlueObjectImplBase() { }
	virtual int put() = 0;

	virtual void *vget() = 0;
	virtual void *vptr() = 0;

	template<typename T>
	T *get() { return (T *)vget(); }

	template<typename T>
	T *ptr() { return (T *)vptr(); }
};

class LuaGlueObjectBase
{
public:
	LuaGlueObjectBase(bool is_shared_ptr_ = false) : is_shared_ptr(is_shared_ptr_) { }
	virtual ~LuaGlueObjectBase() { }

	virtual void put() = 0;
	virtual LuaGlueObjectImplBase *impl() const = 0;

	bool isSharedPtr() { return is_shared_ptr; }
private:
	bool is_shared_ptr;
};


template<class _Class>
class LuaGlueObjectImpl : public virtual LuaGlueObjectImplBase
{
public:
	typedef _Class Type;
	LuaGlueObjectImpl(Type *p, CScriptClass<_Class> *clss, bool owner = false) : _ref_cnt(1), _clss(clss), _ptr(p), _owner(owner)
	{
		// NOTE: std::atomic_init does not compile in GCC
		// something else will be needed for MSVC
		// std::atomic_init(&_ref_cnt, 1);

		//CLogFile::Printf("ctor");
	}

	~LuaGlueObjectImpl()
	{
		if (_clss) _clss->_impl_dtor(_ptr);
		if (_owner)
		{
			CLogFile::Printf("we're owner, delete");
			delete _ptr;
		}

		_ref_cnt = 0;
		_clss = 0;
		_ptr = 0;
		_owner = false;
	}

	void *vget()
	{
		_ref_cnt++;
		//CLogFile::Printf("inc: %i", _ref_cnt.load());
		return _ptr;
	}

	int put()
	{
		_ref_cnt--;
		//CLogFile::Printf("dec: %i", _ref_cnt.load());
		return _ref_cnt;
	}

	//Type &ref() { return *_ptr; }
	void *vptr() { return _ptr; }
private:
	std::atomic_int _ref_cnt;
	CScriptClass<Type> *_clss;
	Type *_ptr;
	bool _owner;
};

template<class _Class>
class LuaGlueObjectImpl<std::shared_ptr<_Class>> : public virtual LuaGlueObjectImplBase
{
public:
	typedef std::shared_ptr<_Class> Type;
	typedef _Class ClassType;
	LuaGlueObjectImpl(Type *p, CScriptClass<_Class> *clss, bool owner = false) : _ref_cnt(1), _clss(clss), _ptr(p), _owner(owner)
	{
		// NOTE: std::atomic_init does not compile in GCC
		// something else will be needed for MSVC
		// std::atomic_init(&_ref_cnt, 1);

		//CLogFile::Printf("ctor");
	}

	~LuaGlueObjectImpl()
	{
		if (_clss) _clss->_impl_dtor(_ptr);
		if (_owner)
		{
			CLogFile::Printf("we're owner, delete");
			delete _ptr;
		}

		_ref_cnt = 0;
		_clss = 0;
		_ptr = 0;
		_owner = false;
	}

	void *vget()
	{
		_ref_cnt++;
		return _ptr;
	}

	int put()
	{
		_ref_cnt--;
		return _ref_cnt;
	}

	//Type &ref() { return *_ptr; }
	void *vptr() { return _ptr; }
private:
	std::atomic_int _ref_cnt;
	CScriptClass<ClassType> *_clss;
	Type *_ptr;
	bool _owner;
};

template<class _Class>
class LuaGlueObject : public LuaGlueObjectBase
{
public:
	typedef _Class Type;

	LuaGlueObject() : LuaGlueObjectBase(false), p(0)
	{
		//CLogFile::Printf("ctor()");
	}

	LuaGlueObject(Type *optr, CScriptClass<Type> *clss = nullptr, bool owner = false) : LuaGlueObjectBase(false), p(new LuaGlueObjectImpl<Type>(optr, clss, owner))
	{
		//CLogFile::Printf("ctor(%p, %s, %i)", ptr, clss->name().c_str(), owner);
	}

	LuaGlueObject(const LuaGlueObjectBase *rhs) : LuaGlueObjectBase(false), p(rhs->impl())
	{
		//CLogFile::Printf("ctor(LuaGlueObjectBase(%p))", p->vptr());
		(void)p->vget();
	}

	LuaGlueObject(const LuaGlueObject &rhs) : LuaGlueObjectBase(false), p(rhs.p)
	{
		//CLogFile::Printf("copy ctor(%p)", p->vptr());
		(void)p->vget();
	}

	LuaGlueObject &operator=(const LuaGlueObject &rhs)
	{
		//CLogFile::Printf("assign(%p)", rhs.p->vptr());
		p = rhs.p;
		(void)p->vget();
	}

	~LuaGlueObject()
	{
		//if(!p)
		//	CLogFile::Printf("p == 0");

		if (p && !p->put())
		{
			//CLogFile::Printf("dtor ref count hit 0, delete impl");
			delete p;
		}
	}

	void put()
	{
		if (!p)
			throw new std::runtime_error("blah");

		if (!p->put())
		{
			//CLogFile::Printf("put ref count hit 0, delete impl");
			delete p;
		}
	}

	Type &operator*() { return *p->ptr<Type>(); }
	Type *operator->() { return p->ptr<Type>(); }

	Type *ptr() { return p->ptr<Type>(); }

	LuaGlueObjectImplBase *impl() const { return p; }
private:
	LuaGlueObjectImplBase *p;
};

template<class _Class>
class LuaGlueObject<std::shared_ptr<_Class>> : public LuaGlueObjectBase
{
public:
	typedef _Class ClassType;
	typedef std::shared_ptr<_Class> Type;

	LuaGlueObject() : LuaGlueObjectBase(true), p(0)
	{
		//CLogFile::Printf("ctor()");
	}

	LuaGlueObject(Type *optr, CScriptClass<ClassType> *clss = nullptr, bool owner = false) : LuaGlueObjectBase(true), p(new LuaGlueObjectImpl<Type>(optr, clss, owner))
	{
		//CLogFile::Printf("ctor(%p, %s, %i)", ptr, clss->name().c_str(), owner);
	}

	LuaGlueObject(const LuaGlueObjectBase *rhs) : LuaGlueObjectBase(true), p(rhs->impl())
	{
		//CLogFile::Printf("ctor(LuaGlueObjectBase(%p))", p->vptr());
		(void)p->vget();
	}

	LuaGlueObject(const LuaGlueObject &rhs) : LuaGlueObjectBase(true), p(rhs.p)
	{
		//CLogFile::Printf("copy ctor(%p)", p->vptr());
		(void)p->vget();
	}

	LuaGlueObject &operator=(const LuaGlueObject &rhs)
	{
		//CLogFile::Printf("assign(%p)", rhs.p->vptr());
		p = rhs.p;
		(void)p->vget();
	}

	~LuaGlueObject()
	{
		//if(!p)
		//	CLogFile::Printf("p == 0");

		if (p && !p->put())
		{
			//CLogFile::Printf("dtor ref count hit 0, delete impl");
			delete p;
			p = nullptr;
		}

		p = nullptr;
	}

	void put()
	{
		if (!p)
			throw new std::runtime_error("blah");

		if (!p->put())
		{
			//CLogFile::Printf("put ref count hit 0, delete impl");
			delete p;
			p = nullptr;
		}
	}

	Type operator*() { CLogFile::Printf("operator*"); return *p->ptr<Type>(); }
	Type *operator->() { return p->ptr<Type>(); }

	ClassType *ptr() { return (*(p->ptr<Type>())).get(); }

	LuaGlueObjectImplBase *impl() const { return p; }
private:
	LuaGlueObjectImplBase *p;
};


class CScriptMethodBase
{
public:
	virtual bool Register(IScriptVM* pVM) = 0;
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

	bool Register(IScriptVM* pVM)
	{
		if(pVM->GetVMType() == LUA_VM)
		{
			lua_State* m_pVM = ((CLuaVM*)pVM)->GetVM();

			lua_pushlightuserdata(m_pVM, this);
			lua_pushcclosure(m_pVM, (lua_CFunction)call_func, 1);
			lua_setfield(m_pVM, -2, name_.c_str());

		} 
		else if(pVM->GetVMType() == SQUIRREL_VM) 
		{
			SQVM* m_pVM = ((CSquirrelVM*)pVM)->GetVM();

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

	bool Register(IScriptVM* pVM)
	{
		if (pVM->GetVMType() == LUA_VM)
		{
			lua_State* m_pVM = ((CLuaVM*) pVM)->GetVM();

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

		ClassType *obj = nullptr;

		if (pVM->GetVMType() == LUA_VM)
		{
			obj = *(ClassType **)lua_touserdata(((CLuaVM*)pVM)->GetVM(), 1);
		}
		else
			obj = (ClassType *) pVM->GetClassInstance("");

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
	
	static const char METATABLE_CLASSNAME_FIELD[];
	static const char METATABLE_INTCLASSNAME_FIELD[];
	static const char METATABLE_CLASSIDX_FIELD[];

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

	bool Register(IScriptVM* pVM)
	{
		// Do additional stuff before add something to the vm
		if(pVM->GetVMType() == LUA_VM)
		{
			lua_State* m_pVM = ((CLuaVM*)pVM)->GetVM();


			lua_pushcclosure(m_pVM, (lua_CFunction)ctor, 1);
			lua_setglobal(m_pVM, name_.c_str());

			lua_createtable(m_pVM, 0, 0);

			//printf("Glue Class: %s\n", name_.c_str());
			luaL_newmetatable(m_pVM, name_.c_str());
			int meta_id = lua_gettop(m_pVM);

		
			static int classIdx = 0;
			int idx = classIdx;
			classIdx++;
			//printf("LuaGlueClass::glue: classidx: %i\n", idx);
			lua_pushinteger(m_pVM, idx);
			lua_setfield(m_pVM, meta_id, METATABLE_CLASSIDX_FIELD);

			//printf("LuaGlueClass::glue: intclassname: %s\n", typeid(_Class).name());
			lua_pushstring(m_pVM, typeid(_Class).name());
			lua_setfield(m_pVM, meta_id, METATABLE_INTCLASSNAME_FIELD);

			//printf("LuaGlueClass::glue: classname: %s\n", name_.c_str());
			lua_pushstring(m_pVM, name_.c_str());
			lua_setfield(m_pVM, meta_id, METATABLE_CLASSNAME_FIELD);

			lua_pushlightuserdata(m_pVM, this);
			lua_pushcclosure(m_pVM, &lua_index, 1);
			lua_setfield(m_pVM, meta_id, "__index");

			lua_pushlightuserdata(m_pVM, this);
			lua_pushcclosure(m_pVM, &lua_newindex, 1);
			lua_setfield(m_pVM, meta_id, "__newindex");

			lua_pushvalue(m_pVM, -2);
			lua_setfield(m_pVM, meta_id, "__metatable");

			lua_pushlightuserdata(m_pVM, this);
			lua_pushcclosure(m_pVM, &lua_gc, 1);
			lua_setfield(m_pVM, meta_id, "__gc");

			lua_pushlightuserdata(m_pVM, this);
			lua_pushcclosure(m_pVM, &lua_meta_concat, 1);
			lua_setfield(m_pVM, meta_id, "__concat");
		}
		else
		// Register Script class have to prepare the stack and register to start registering the methods
		pVM->BeginRegisterScriptClass(name_.c_str(), ctor, this);

		// Register member methods
		for (auto &method : methods)
		{
			if (!method->Register(pVM))
				return false;
		}

		pVM->FinishRegisterScriptClass();

		if (pVM->GetVMType() == LUA_VM)
		{
			lua_State* m_pVM = ((CLuaVM*)pVM)->GetVM();
			lua_setmetatable(m_pVM, -2);

			lua_pushvalue(m_pVM, -1);
			lua_setglobal(m_pVM, name_.c_str());
		}

		return true;
	}

	bool RegisterMethods(IScriptVM* pVM)
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



	// symbol lookup metamethod
	// TODO: make sure inheritance works

	// if we skip the metatable check, we can speed things up a bit,
	// but that would mean any lua sub classes won't get their props checked.
	int index(lua_State *state)
	{
		//printf("index!\n");

		int type = lua_type(state, 2);
		if (type == LUA_TSTRING)
		{
			const char *key = lua_tostring(state, 2);

			lua_getmetatable(state, 1);
			lua_pushvalue(state, 2); // push key

			lua_rawget(state, -2); // get function
			lua_remove(state, -2); // remove metatable

			//if (properties_.exists(key))
			//{
			//	//printf("prop!\n");
			//	lua_pushvalue(state, 1); // push args
			//	lua_pushvalue(state, 2);
			//	lua_pcall(state, 2, 1, 0); // call function
			//}

		}
		else if (type == LUA_TNUMBER)
		{
			lua_getmetatable(state, 1);
			lua_pushstring(state, "m__index");

			lua_rawget(state, -2); // get m__index method from metatable
			lua_remove(state, -2); // remove metatable

			if (lua_isfunction(state, -1)) { // if m__index is a function, call it
				lua_pushvalue(state, 1); // copy 1st and 2nd stack elements
				lua_pushvalue(state, 2);

				lua_pcall(state, 2, 1, 0); // removes the argument copies
				// should always be a function.. might want to put some debug/trace messages to make sure

				//lua_dump_stack(state);
			}
		}
		else
		{
			printf("index: unsupported type: %i\n", type);
		}

		return 1;
	}

	int newindex(lua_State *state)
	{
		int type = lua_type(state, 2);
		if (type == LUA_TSTRING)
		{
			const char *key = lua_tostring(state, 2);

			lua_getmetatable(state, 1); // get metatable

			//if (properties_.exists(key))
			//{
			//	lua_pushvalue(state, 2); // push key
			//	lua_rawget(state, -2); // get field
			//	lua_remove(state, -2); // remove metatable

			//	lua_pushvalue(state, 1); // push self
			//	lua_pushvalue(state, 2); // push key
			//	lua_pushvalue(state, 3); // push value

			//	lua_pcall(state, 3, 0, 0); // call function from field above

			//	//lua_dump_stack(state);
			//}
			//else
			{
				lua_pushvalue(state, 2); // push key
				lua_pushvalue(state, 3); // push value

				//lua_dump_stack(state);
				lua_rawset(state, -3);
				//lua_dump_stack(state);
			}

			lua_pop(state, 1);
		}
		else if (type == LUA_TNUMBER)
		{
			lua_getmetatable(state, 1);

			lua_pushstring(state, "m__newindex");
			lua_rawget(state, -2); // get method
			lua_remove(state, -2); // remove metatable

			if (lua_isfunction(state, -1)) {
				lua_pushvalue(state, 1); // push self
				lua_pushvalue(state, 2); // push idx
				lua_pushvalue(state, 3); // push value
				lua_pcall(state, 3, 0, 0);
				//lua_dump_stack(state);
			}
		}
		else
		{
			printf("newindex: unsupported type: %i\n", type);
		}

		//printf("newindex end!\n");

		return 0;
	}

	int gc(lua_State *state)
	{
		if (lua_isuserdata(state, -1))
		{
			CLogFile::Printf("about to gc!");
			LuaGlueObjectBase *obj = (LuaGlueObjectBase *)lua_touserdata(state, -1);
			obj->put();
		}
		return 0;
	}

	int concat(lua_State *state)
	{
		int arg1_type = lua_type(state, 1);
		int arg2_type = lua_type(state, 2);

		push_obj_str(state, arg1_type, 1);
		push_obj_str(state, arg2_type, 2);

		lua_concat(state, 2);

		return 1;
	}

	void push_obj_str(lua_State *state, int type, int idx)
	{
		if (type == LUA_TUSERDATA)
		{
			LuaGlueObjectBase *lg_obj = (LuaGlueObjectBase *)lua_touserdata(state, idx);
			_Class *obj = nullptr;

			if (lg_obj->isSharedPtr())
			{
				auto o = CastLuaGlueObjectShared(_Class, lg_obj);
				obj = o->ptr();
			}
			else
			{
				auto o = CastLuaGlueObject(_Class, lg_obj);
				obj = o->ptr();
			}

			char buff[2048];
			sprintf(buff, "%s(%p)", name_.c_str(), obj);
			lua_pushstring(state, buff);
		}
		else if (type == LUA_TNIL)
		{
			CLogFile::Printf("nil!");
			lua_pushstring(state, "nil");
		}
		else
		{
			CLogFile::Printf("type: %s", lua_typename(state, type));
			lua_pushstring(state, lua_tostring(state, idx));
		}
	}

	static int lua_index(lua_State *state)
	{
		auto cimp = (CScriptClass<_Class> *)lua_touserdata(state, lua_upvalueindex(1));
		return cimp->index(state);
	}

	static int lua_newindex(lua_State *state)
	{
		auto cimp = (CScriptClass<_Class> *)lua_touserdata(state, lua_upvalueindex(1));
		return cimp->newindex(state);
	}

	static int lua_gc(lua_State *state)
	{
		auto cimp = (CScriptClass<_Class> *)lua_touserdata(state, lua_upvalueindex(1));
		return cimp->gc(state);
	}

	static int lua_meta_concat(lua_State *state)
	{
		auto cimp = (CScriptClass<_Class> *)lua_touserdata(state, lua_upvalueindex(1));
		return cimp->concat(state);
	}
};

template<class _Class>
const char CScriptClass<_Class>::METATABLE_CLASSNAME_FIELD[] = "LuaGlueClassName";

template<class _Class>
const char CScriptClass<_Class>::METATABLE_INTCLASSNAME_FIELD[] = "LuaGlueIntClassName";

template<class _Class>
const char CScriptClass<_Class>::METATABLE_CLASSIDX_FIELD[] = "LuaGlueClassIdx";

#endif