#pragma once
#include "typesdef.h"
#include "arith.h"
#include "pair.h"

// ���Ϻ���
struct compose
{
    template<typename arg_list> struct Func;

    template<typename T, typename V>
    struct Func<List<T, V>>
    {
        struct ret
        {
            template<typename arg_list> struct Func
            {
                using ret = Ret(T::template Func, List<Ret(V::template Func, arg_list)>);
            };
        };
    };
};

#define IsEqual(...) Ret(_isEqual::Func, List<__VA_ARGS__>)
struct _isEqual
{
    template<typename ARGS> struct Func;

    template<typename T, typename V>
    struct Func<List<T, V>> { using ret = False; };

    template<typename T>
    struct Func<List<T, T>> { using ret = True; };
};

DEFN_BINARY_FUN(isValueEqual, x, y, bool, (Value(x) == Value(y)));
DEFN_BINARY_FUN(isGreater, x, y, bool, (Value(x) > Value(y)));
DEFN_BINARY_FUN(isLess, x, y, bool, (Value(x) < Value(y)));
#define IsValueEqual(...)   Ret(_isValueEqual::Func, List<__VA_ARGS__>)
#define IsGreater(...)      Ret(_isGreater::Func, List<__VA_ARGS__>)
#define IsLess(...)         Ret(_isLess::Func, List<__VA_ARGS__>)

//#define IsGreater(...) Ret(_isGreater,__VA_ARGS__)
//template<typename T, typename V> struct _isGreater { using ret = ARG(bool, (Value(T) > Value(V))); };
//
//#define IsLess(...) Ret(_isLess,__VA_ARGS__)
//template<typename T, typename V> struct _isLess { using ret = ARG(bool, (Value(T) < Value(V))); };

#define IsGreaterEqual(...) Not(IsLess(__VA_ARGS__))
#define IsLessEqual(...) Not(IsGreater(__VA_ARGS__))

//template<typename T> constexpr add_rvalue_reference_t<T> typedval();

//����If(cond, struct1{fun}, struct2{fun})::fun<context>
//TODO��������ʾ�Ĺ��̽��и��߽׵ĳ���

//TODO��ʹif�ӳټ���THEN��ELSE
// ����ɿ���If(cond,CONS<THEN,ELSE>)
// �����У���Ϊ�ƺ�THEN��ELSEֻҪ��Ϊ�����ͻᱻ����
// 
//�����Ҫ��If�����������������Format
//If(cond, THEN, ELSE)
//#define If(...) Ret(_If,__VA_ARGS__)


//#define If(cond, THEN, ELSE) typename _Do<THEN>::template _If<cond>::template _Else<ELSE>;
//template<typename THEN> struct _Do
//{
//    template<typename cond> struct _If;
//    template<> struct _If<True> { template<typename T> using _Else = THEN; };
//    template<> struct _If<False> { template<typename T> using _Else = T; };
//};

//#define If(cond, THEN, ELSE) typename _If<cond,THEN>::template ret<ELSE>
//template <typename cond, typename THEN> struct _If;
//template<typename THEN> struct _If<True, THEN>
//{
//    template<typename T> using ret = THEN;
//};
//template<typename THEN> struct _If<False, THEN>
//{
//    template<typename T> using ret = T;
//};

#define If(...) Ret(_if::template Func, List<__VA_ARGS__>)
struct _if
{
    template<typename ARGS> struct Func;

    template<typename THEN, typename ELSE>
    struct Func<List<True, THEN, ELSE>>
    {
        using ret = THEN;
    };

    template<typename THEN, typename ELSE>
    struct Func<List<False, THEN, ELSE>>
    {
        using ret = ELSE;
    };
};

//Ifs��Switch��������g++����Ҳ��֪��Ϊʲô
//��Ϊ�����If���ret֮ǰ�����template������SB��MSVC

//��û�д���ELSE����������������������������·���Null
//Ifs(THEN1,cond1,THEN2,cond2,...,ELSE)
#define Ifs(...) Ret(_Ifs,__VA_ARGS__)
template<typename THEN, typename cond = True, typename...Tcs> struct _Ifs
{
    using ret = If(cond, THEN, Ifs(Tcs...));
};

template<typename ELSE> struct _Ifs<ELSE> { using ret = ELSE; };

//��û�д���Default�����������������ƥ��ʱ����Null
//Switch(arg, THEN1, case1, THEN2, case2, ..., Default)
#define Switch(arg,...) Ret(_Switch<arg>::__Switch,__VA_ARGS__)
template<typename arg> struct _Switch
{
    template<typename THEN = Null, typename __case = arg, typename...Tcs>
    struct __Switch
    {
        using ret = If(IsEqual(arg, __case), THEN, Ret(__Switch, Tcs...));
    };
    template<typename Default> struct __Switch<Default> { using ret = Default; };
};

//���ﶨ���For������һ��������������������ΪFunc<Func<...Func<Context>...>>
//For(LoopFunc<Context>, Context, StopBy<Index>, doToIndex<Index> = Inc, Index = Int<0>)
#define For(...) Ret(_For,__VA_ARGS__)
template<
    template<typename Context> typename LoopFunc,
    typename Context,
    template<typename Index> typename StopBy,
    template<typename Index> typename doToIndex = _Inc::Func,//_Inc
    typename Index = Int<0>> struct _For
    // ע�������βε�˳�����ģ��ģ������Ĳ����������������������
    // ��������ģ��ģ�����. �籾�����е�StopBy��doToIndex������
    // Index֮ǰ�������п��ܳ��ִ���.
{
    //�����д��
    // 
    //template<typename Index, typename Context> struct __MainLoop
    //{
    //    using __FuncRet = Ret(LoopFunc, Context);
    //    using ret =
    //        If(Ret(StopBy, Index),
    //            __FuncRet,
    //            Ret(__MainLoop, Ret(doToIndex, Index), __FuncRet));
    //};

    template<typename shallStop, typename __Index, typename __Context> struct __MainLoop;
    template<typename __Index, typename __Context> struct __MainLoop<True, __Index, __Context>
    {
        using ret = __Context;
    };
    template<typename __Index, typename __Context> struct __MainLoop<False, __Index, __Context>
    {
        using __NextIndex = Ret(doToIndex, __Index);
        using __FuncRet = Ret(LoopFunc, __Context);

        using ret =
            Ret(__MainLoop,
                Ret(StopBy, __NextIndex),
                __NextIndex,
                __FuncRet);
    };

    using ret =
        Ret(__MainLoop,
            Ret(StopBy, Index),
            Index,
            Context);

    //����д��Ҳ����ȷ��(�����ȷ)����������������
    // ��init.cpp
    // 
    //struct __LoopEnd
    //{
    //    template<typename Index, typename Context> struct Func
    //    {
    //        using ret = Context;
    //    };
    //};

    //struct __MainLoop
    //{
    //    template<typename Index, typename Context> struct Func
    //    {
    //        using __NextIndex = Ret(doToIndex, Index);
    //        using __FuncRet = Ret(LoopFunc, Context);

    //        using ret =
    //            RawRet(
    //                If(Ret(StopBy, __NextIndex),
    //                    __LoopEnd,
    //                    __MainLoop)::Func,
    //                __NextIndex, __FuncRet);
    //    };
    //};

    //using ret =
    //    RawRet(
    //        If(Ret(StopBy, Index),
    //            __LoopEnd,
    //            __MainLoop)::Func,
    //        Index, Context);
};