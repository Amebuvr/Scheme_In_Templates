#pragma once

#include "typesdef.h"

#ifdef SCHEME
//Schemeʽ����Զ��壬���ֶ��彫ʹDisplay�������

//��Ե�Ԫ���ǲ��ɱ��
#define Car(...) Ret(__VA_ARGS__::__dispatcher,True)
#define Cdr(...) Ret(__VA_ARGS__::__dispatcher,False)
//�����Ҫ����(ģ��)��ԣ��ɽ�ģ���װ��һ��ʱ�ṹ����
template<typename T, typename V = Null> struct Cons
{
    //True��False�����Ǳ�ǣ����Բ�ʹ��If
    template<typename b> struct __dispatcher;
    template<> struct __dispatcher<True> { using ret = T; };
    template<> struct __dispatcher<False> { using ret = V; };
};
#endif

#ifndef SCHEME

//��Ե�Ԫ���ǲ��ɱ��
//#define Car(...) __VA_ARGS__::__Car
//#define Cdr(...) __VA_ARGS__::__Cdr
//�����Ҫʹ�ú���(ģ��)��ԣ��ɽ�ģ���װ��һ��ʱ�ṹ����
//template<typename T, typename U = Null> struct Cons
//{
//    using __Car = T;
//    using __Cdr = U;
//};
//
//template<typename T>
//struct MK_CONS_FUN
//{
//    using ret = Cons<typename T::_1, typename T::_2>;
//};

//#define MK_CONS(...) Ret(_MK_Cons::Func,__VA_ARGS)
//struct _MK_Cons
//{
//    template<typename __Car, typename __Cdr = Null>
//    struct __Cons
//    {
//        using __Car = __Car;
//        using __Cdr = __Cdr;
//    };
//
//    template<typename ARGS> struct Func
//    {
//        using ret = __Cons<ARGS>;
//    };
//
//    template<typename T, typename V>
//    struct Func<pack_2_args<T, V>>
//    {
//        using ret = __Cons<T, V>;
//    };
//};

#endif

//��
//#define List(...) MK_LIST::Func<__VA_ARGS__>
//struct MK_LIST
//{
//    template<typename...Ts>
//    struct __MK_LIST_FUN;
//    template<typename T, typename...Ts>
//    struct __MK_LIST_FUN<T, Ts...>
//    {
//        using ret = MK_CONS(T, __MK_LIST_FUN<Ts...>);
//    };
//    template<typename T>
//    struct __MK_LIST_FUN<T>
//    {
//        using ret = T;
//    };
//    template<> struct __MK_LIST_FUN<> { using ret = Null; };
//
//    template<typename...Ts> using Func = typename __MK_LIST_FUN<Ts...>::ret;
//};

//template<
//    template<typename T> typename F>
//struct CONS_MAP
//{
//    template<typename U>
//    struct on
//    {
//        using ret = Ret(F, U);
//    };
//
//    template<typename P, typename Q>
//    struct on<Cons<P, Q>>
//    {
//        using ret = Cons<Ret(on, P), Ret(on, Q)>;
//    };
//};

template<typename...items> struct List;
template<typename __car, typename...__cdr>
struct List<__car, __cdr...>
{
    using car = __car;
    using cdr = List<__cdr...>;
};
template<typename __car, typename __cdr>
struct List<__car, __cdr>
{
    using car = __car;
    using cdr = __cdr;
};
template<typename __car>
struct List<__car>
{
    using car = __car;
};

struct Union
{
    template<typename args> struct Func;
    template<typename...Ts, typename...Vs>
    struct Func<List<List<Ts...>, List<Vs...>>>
    {
        using ret = List<Ts..., Vs...>;
    };
};

struct Merge
{
    template<typename args> struct Func;

    template<typename...Ts, typename...Vs>
    struct Func<List<List<Ts...>, Vs...>>
    {
        using ret =
            Ret(Union::Func, List<
                List<Ts...>,
                Ret(Func, List<Vs...>)>);
    };

    template<typename T, typename...Vs>
    struct Func<List<T, Vs...>>
    {
        using ret =
            Ret(Union::Func, List<
                List<T>,
                Ret(Func, List<Vs...>)>);
    };

    template<>
    struct Func<List<>>
    {
        using ret = List<>;
    };
};

struct Flatten
{
    template<typename args> struct Func;

    template<typename...Ts, typename...Vs>
    struct Func<List<List<Ts...>, Vs...>>
    {
        using ret = typename Func<List<Ts..., Vs...>>::ret;
    };

    template<typename...Ts>
    struct Func<List<List<Ts...>>>
    {
        using ret = typename Func<List<Ts...>>::ret;
    };

    template<typename T, typename...Vs>
    struct Func<List<T, Vs...>>
    {
        using ret =
            typename Merge::Func<List<
            List<T>,
            typename Func<List<Vs...>>::ret
            >>::ret;
    };

    template<typename T>
    struct Func<List<T>>
    {
        using ret = T;
    };
};

struct Map
{
    template<typename args> struct Func;
    template<typename F, typename...items>
    struct Func<List<F, List<items...>>>
    {
        template<typename T> struct MapOn;

        template<typename T>
        struct MapOn<List<T>>
        {
            using ret = List<
                Ret(F::template Func, List<T>)>;
        };

        template<typename T, typename V>
        struct MapOn<List<T, V>>
        {
            using ret = List<
                Ret(F::template Func, List<T>),
                Ret(F::template Func, List<V>)>;
        };

        template<typename T, typename...Ts>
        struct MapOn<List<T, Ts...>>
        {
            using L = List<Ts...>;
            using ret = typename Flatten::Func<List<
                Ret(F::template Func, List<T>),
                Ret(MapOn, L)>>::ret;
        };

        using ret = Ret(MapOn, List<items...>);
    };
};

struct DeepMap
{
    template<typename args> struct Func;
    template<typename F, typename...items>
    struct Func<List<F, List<items...>>>
    {
        template<typename T> struct MapOn
        {
            using ret = Ret(F::template Func, List<T>);
        };

        template<typename T>
        struct MapOn<List<T>>
        {
            using ret = List<Ret(MapOn, T)>;
        };

        template<typename T, typename...Ts>
        struct MapOn<List<T, Ts...>>
        {
            using L = List<Ts...>;

            using ret =
                Ret(Union::Func, List<
                    List<Ret(MapOn, T)>,
                    Ret(MapOn, L)>);
        };

        using ret = Ret(MapOn, List<items...>);
    };
};