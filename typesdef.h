#pragma once

#include <type_traits>

//Ret(Function<Context>, Context...)
#define Ret(func,...) typename func<__VA_ARGS__>::ret

//��ʱ��������RetǶ�ף��⽫������������typename����. ��ʱʹ��RawRet
#define RawRet(func,...) func<__VA_ARGS__>::ret

//����������Ƕ�ף���IntType<IntType<1>>
template<typename T, T value> struct Arg__
{
    using __type = T;
    static constexpr T __value = value;
};

//MSVC��__VA_ARGS__����Ϊһ���������壬���Ա�����м��__Expand
#define __Expand(...)                           __VA_ARGS__
//#define __UntypedArg(value)                     Arg__<std::decay_t<decltype(value)>,value>
#define __TypedArg(type,value)                  Arg__<type,value>
#define __UntypedArg(value)                     __TypedArg(std::decay_t<decltype(value)>,value)
#define __FIND_3RD_ARG(arg1,arg2,arg3,...)      arg3
//���ڴ����±�������ʡ������˵��
//Arg(optional type, value)
#define Arg(...)                                __Expand(\
                                                    __Expand(\
                                                        __FIND_3RD_ARG(\
                                                            __VA_ARGS__,__TypedArg,__UntypedArg))\
                                                    (__VA_ARGS__))

#define Type(...) Ret(_getType::template Func,__VA_ARGS__)//Ret(_getType,__VA_ARGS__)
//template<typename T> struct _getType { using ret = typename T::__type; };
struct _getType
{
    template<typename T> struct Func;
    template<typename U, U value>
    struct Func<Arg(U, value)> { using ret = U; };
};

//����ʹ��auto������������޷���ȷ��ȡ������
#define Value(...) RawRet(_getValue::template Func,__VA_ARGS__)//_getValue<__VA_ARGS__>::ret
struct _getValue
{
    template<typename T> struct Func;
    template<typename U, U value>
    struct Func<Arg(U, value)> { static constexpr U ret = value; };
};

// #define IntType(N)          Arg(int,N)
// #define BoolType(b)         Arg(bool,b)
// #define CharType(ch)        Arg(char,ch)

template<int N>     using Int = Arg__<int, N>;
template<bool b>    using Bool = Arg__<bool, b>;
template<char ch>   using Char = Arg__<char, ch>;

// template<int N> struct IntType { enum { __value = N }; };
// template<bool b> struct BoolType { enum { __value = b }; };
// template<char ch> struct CharType { enum { __value = ch }; };

using True = Bool<true>;
using False = Bool<false>;

//struct Null;