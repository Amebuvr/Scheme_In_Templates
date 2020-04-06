#pragma once

#include "typesdef.h"
#include "pair.h"
#include "algor.h"

//������ת��Ϊ������ʽ(Int��Bool��Char��Null)���Ծ�����Ϣ����ʽ���
//������кţ���ΪVS������кŲ�׼ȷ�����һ�ϲ�������ͬ�ľ�����Ϣ
#define Display(...) __CastAndBind<__VA_ARGS__,__LINE__>::ret
template<int Line> struct Line__;

template<typename T, int LINE> struct __CastAndBind { using ret = Cons<Arg(Value(T)), Line__<LINE>>; };
template<int LINE> struct __CastAndBind<True, LINE> { using ret = Cons<True, Line__<LINE>>; };
template<int LINE> struct __CastAndBind<False, LINE> { using ret = Cons<False, Line__<LINE>>; };
/*template<bool b, int LINE> struct __CastAndBind<Bool<b>, LINE> { using ret = Cons<Bool<b>, Line__<LINE>>; };*/
template<int LINE> struct __CastAndBind<Null, LINE> { using ret = Cons<Null, Line__<LINE>>; };