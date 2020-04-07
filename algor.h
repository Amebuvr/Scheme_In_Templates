#pragma once
#include "typesdef.h"
#include "arith.h"

#define IsEqual(...) Ret(_isEqual,__VA_ARGS__)
template<typename T, typename V> struct _isEqual { using ret = False; };
template<typename T> struct _isEqual<T, T> { using ret = True; };

#define IsGreater(...) Ret(_isGreater,__VA_ARGS__)
template<typename T, typename V> struct _isGreater { using ret = Arg(bool, (Value(T) > Value(V))); };

#define IsLess(...) Ret(_isLess,__VA_ARGS__)
template<typename T, typename V> struct _isLess { using ret = Arg(bool, (Value(T) < Value(V))); };

#define IsGreaterEqual(...) Not(IsLess(__VA_ARGS__))
#define IsLessEqual(...) Not(IsGreater(__VA_ARGS__))

//����If(cond, struct1{fun}, struct2{fun})::fun<context>
//TODO��������ʾ�Ĺ��̽��и��߽׵ĳ���

//TODO���޸�ifʹ������ӳټ���THEN��ELSE
// �ɳ���If(cond,CONS<THEN,ELSE>)
// 
//�����Ҫ��If�����������������Format
//If(cond, THEN, ELSE)
#define If(...) Ret(_If,__VA_ARGS__)
template<typename cond, typename THEN, typename ELSE = Null> struct _If;
template<typename THEN, typename ELSE> struct _If<True, THEN, ELSE>
{
    using ret = THEN;
};
template<typename THEN, typename ELSE> struct _If<False, THEN, ELSE> { using ret = ELSE; };

//��û�д���ELSE����������������������������·���Null
//Ifs(THEN1,cond1,THEN2,cond2,...,ELSE)
#define Ifs(...) Ret(_Ifs,__VA_ARGS__)
template<typename THEN = Null, typename cond = True, typename...Tcs> struct _Ifs
{
    using ret = If(cond, THEN, Ifs(Tcs...));
};

template<typename ELSE> struct _Ifs<ELSE> { using ret = ELSE; };

//��û�д���Default�����������������ƥ��ʱ����Null
//Switch(arg,THEN1,case1,THEN2,case2,...,Default)
#define Switch(arg,...) Ret(_Switch<arg>::__Switch,__VA_ARGS__)
template<typename arg> struct _Switch
{
    template<typename THEN = Null, typename __case = arg, typename...Tcs> struct __Switch
    {
        using ret = If(IsEqual(arg, __case), THEN, Ret(__Switch, Tcs...));
    };
    template<typename Default> struct __Switch<Default> { using ret = Default; };
};

//���ﶨ���For������һ��������������������ΪFunc<Func<...Func<Context>...>>
//For(LoopFunc<Context>, Context, StopBy<Index>, Index = Int<0>, doToIndex<Index> = Inc)
#define For(...) Ret(_For,__VA_ARGS__)
template<
    template<typename Context> typename LoopFunc,
    typename Context,
    template<typename Index> typename StopBy,
    template<typename Index> typename doToIndex = _Inc,
    typename Index = Int<0>> struct _For
    //ע���βε�����˳��
    //���ģ��ģ��������β�(��StopBy��doToIndex�Ĳ���Index)�������β�����������뽫ģ��ģ���������ǰ��
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