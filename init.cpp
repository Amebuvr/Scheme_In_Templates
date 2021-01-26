// Scheme_In_Templates.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <stdio.h>
#include "typesdef.h"
#include "outmsg.h"
#include "arith.h"
#include "pair.h"
#include "algor.h"
#include "stream.h"
#include <type_traits>

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
    //Format(
    //    Add(Arg('e'), Arg(int, 5)));
    //
    //Format(
    //    Mul(Arg('e'), Arg(int, 5)));
    //
    //Format(
    //    Inc(Arg('a')));
#pragma endregion

#pragma region ѡ��ṹ����
    //Format(
    //    If(IsEqual(Arg(1), Arg(0)),
    //        True,
    //        False));

    //Format(
    //    Ifs(Arg(1), IsEqual(Arg(1), Arg(0)),
    //        Arg(2), IsEqual(Arg(1), Arg(6))));

    //Ifs(
    //    Arg(1), IsEqual(Arg(1), Arg(0)),
    //    Arg(2), IsEqual(Arg(1), Arg(6)),
    //    Format(Arg(3)));

    //Format(
    //    Switch(Arg(1),
    //        Arg(2), Arg(2),
    //        Arg(3), Arg(3),
    //        Arg(1)));
#pragma endregion

#pragma region ��Բ���
    //using mycons = Cons<Int<1>>;
    //Format(Car(mycons));
    //Format(Cdr(mycons));
#pragma endregion

#pragma region �߼��������
    //Format(Arg(true));

    //Format(
    //    IsGreater(Arg(int, 5), Arg('e')));

    //Format(
    //    And(Arg(125), Arg(234)));

    //Format(
    //    Or(Arg(125), Arg(234)));

    //Format(
    //    Not(Arg(125)));

    //Format(
    //    Not(Arg(true)));

    //Format(
    //    Xor(Arg(125), Arg(234)));
#pragma endregion

    Format(STREAM_CAR(evens));
    Format(STREAM_CAR(STREAM_CDR(evens)));

    Format(STREAM_CAR(odds));
    Format(STREAM_CAR(STREAM_CDR(odds)));

    Format(STREAM_CAR(integers));
    Format(STREAM_CAR(STREAM_CDR(integers)));
    STREAM_CDR(integers);

    using my_cons =
        Cons<
        Cons<Int<1>, Int<2>>,
        Cons<Int<3>,
        Cons<Int<5>, Int<9>>>>;

    CONS_MAP<_Inc>::on<my_cons>::ret;

    //If(IsGreater(Int<1>, Int<0>), Int<3>, Int<4>);
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
