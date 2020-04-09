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
#define Car(...) __VA_ARGS__::__Car
#define Cdr(...) __VA_ARGS__::__Cdr
//�����Ҫʹ�ú���(ģ��)��ԣ��ɽ�ģ���װ��һ��ʱ�ṹ����
template<typename T, typename V = Null> struct Cons
{
    using __Car = T;
    using __Cdr = V;
};
#endif

//TODO������
template<typename T, typename...Ts> struct _List
{

};