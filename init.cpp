// Scheme_In_Templates.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <stdio.h>
#include "typesdef.h"
#include "outmsg.h"
#include "arith.h"
#include "pair.h"
#include "algor.h"

#pragma region �׳�
template <typename T>
struct factorial;
template <int N>
struct factorial<Int<N>>
{
    using ret = Mul(Int<N>, Ret(factorial, Sub(Int<N>, Int<1>)));
};
template <>
struct factorial<Int<0>>
{
    using ret = Int<1>;
};
#pragma endregion

#pragma region ģ��ģ�����
template <
    template <typename... Types> typename myTemp>
struct TestTemp
{
    template <typename... Types>
    using ret = myTemp<Types...>;
};

template <
    template <
    template <typename... Types> typename myTempTemp>
typename myTemp>
struct TestTemp2
{
    template <template <typename... Types> typename myTempTemp>
    using ret = myTemp<myTempTemp>;
};
#pragma endregion

//struct packStructA
//{
//    template <typename T>
//    struct Func
//    {
//        using ret = Add(T, Int<2>);
//        using MyNewRet = Add(T, Int<100>);
//    };
//};
//struct packStructB
//{
//    template <typename T>
//    struct Func
//    {
//        using ret =
//            RawRet(If(IsGreater(T, Int<0>),
//                packStructA,
//                packStructB)::Func,
//                Inc(T));
//
//        // template <typename... Ts>
//        // using __Func = typename _If<IsLess(T, Int<5>), packStructA, packStructB>::ret::Func<Ts...>;
//        // using MyNewRet =
//        //     typename __Func<Inc(T)>::MyNewRet;
//
//        //�˴��ĵݹ������﷨����
//        // TODO���������
//        // �ǲ��ǿ��Լ�һ��Caller��
//        //
//        /*RawRet(If(IsLess(T, Int<5>),
//            packStructB,
//            packStructA)::Func,
//            Inc(T));*/
//    };
//};

#pragma region ѭ������

template <typename Index>
struct doToIndex
{
    using ret = Inc(Index);
};

template <typename Index>
struct StopBy
{
    using ret = IsGreaterEqual(Index, Int<10>);
};

template <typename Context>
struct LoopFunc
{
    using ret = Mul(Context, Int<2>);
};
#pragma endregion

template <typename... Types>
constexpr int init(Types... args)
{
#pragma region �����������
    //Display(
    //    Add(Arg('e'), Arg(int, 5)));

    //Display(
    //    Inc(Arg('a')));
#pragma endregion

#pragma region ѡ��ṹ����
    //Display(
    //    If(IsEqual(Arg(1), Arg(0)),
    //        True,
    //        False));

    //Display(
    //    Ifs(Arg(1), IsEqual(Arg(1), Arg(0)),
    //        Arg(2), IsEqual(Arg(1), Arg(6))));

    //Ifs(
    //    Arg(1), IsEqual(Arg(1), Arg(0)),
    //    Arg(2), IsEqual(Arg(1), Arg(6)),
    //    Display(Arg(3)));

    //Display(
    //    Switch(Arg(1),
    //        Arg(2), Arg(2),
    //        Arg(3), Arg(3),
    //        Arg(1)));
#pragma endregion

#pragma region ��Բ���
    //using mycons = Cons<Int<1>>;
    //Display(Car(mycons));
    //Display(Cdr(mycons));
#pragma endregion

#pragma region �߼��������
    //Display(Arg(true));

    //Display(
    //    IsGreater(Arg(int, 5), Arg('e')));

    //Display(
    //    And(Arg(125), Arg(234)));

    //Display(
    //    Or(Arg(125), Arg(234)));

    //Display(
    //    Not(Arg(125)));

    //Display(
    //    Not(Arg(true)));

    //Display(
    //    Xor(Arg(125), Arg(234)));
#pragma endregion

    // Display(
    //     For(LoopFunc, Int<3>, StopBy));
    //
    //Display(
    //    If(Ret(StopBy, Int<0>),
    //        Null,
    //        Int<1>));
    //
    //Display(
    //    Ret(_If<False, packStructA, packStructB>::ret::Func, Int<1>));
    // Display(
    //     typename packStructB::Func<Int<1>>::MyNewRet);
    //Display(
    //    typename packStructB::Func<Int<1>>::ret);
    //
    //Display(
    //    RawRet(If(False,
    //        packStructA,
    //        packStructB)::Func,
    //        Int<1>));
    //
    //Display(Ret(packStructB::Func, Int<0>));

    if constexpr (Value(Ret(StopBy, Int<0>)))
    {
        Display(Null);
    }
    else
    {
        Display(Int<1>);
    }

    return 0;
}

int main()
{
    static_assert(init() != 0, "init end.");
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���:
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
