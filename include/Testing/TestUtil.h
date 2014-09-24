#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <vector>
#include <Util/Util.h>
#include <Testing/Config.h>

TESTING_BEGIN

template<typename T>
vector<T> RandomUniqueDatas(size_t size
                             , T minnum = 0
                             , T maxnum = 0)
{
    vector<T>  ret;

    maxnum = (maxnum && maxnum - minnum > (T)size) ? maxnum : size + minnum;

    maxnum = maxnum > (T)ret.max_size() ? Util::NumericLimits::Max<unsigned short>() : maxnum;

    ret.reserve(maxnum - minnum + 1);

    for (T i = minnum; i <= maxnum; i++)
    {
        ret.push_back(i);
    }

    for (size_t i = 0; i < size; i++) 
    {
        unsigned pos = Random(i, ret.size() - 1);
        std::swap(ret[i], ret[pos]);
    }

    ret.resize(size);

    return ret;
}

TESTING_END

#endif