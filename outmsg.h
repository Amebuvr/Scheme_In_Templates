#pragma once

#include "typesdef.h"
#include "pair.h"
#include "algor.h"
#include <type_traits>

struct Format
{
    template<typename arg_list> struct Func;

    template<typename T>
    struct Func<List<T>>
    {
        using ret = typename T::formatted;
    };
};

template <int Line> struct LINE;
template<typename LINE, typename T> struct Output;

//������ת��Ϊ������ʽ(Int��Bool��Char)���Ծ�����Ϣ����ʽ���
//������кţ���ΪVS������кŲ�׼ȷ�����һ�ϲ�������ͬ�ľ�����Ϣ
//�����ʽ������б�
#define Formatted(...)              \
        Ret(DeepMap::template Func, \
            List<                   \
                Format,             \
                List<__VA_ARGS__>>)

#define Display(...) Output<LINE<__LINE__>,__VA_ARGS__>
