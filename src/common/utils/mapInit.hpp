#ifndef BLE_SRC_COMMON_UTILS_MAPINIT_H_
#define BLE_SRC_COMMON_UTILS_MAPINIT_H_

#include <type_traits>

namespace ble_src::common::utils {

template <typename T>
struct map_init_helper {
    T& data;
    map_init_helper(T& d)
        : data(d)
    {
    }
    map_init_helper& operator()(typename T::key_type const& key, typename T::mapped_type const& value)
    {
        data[key] = value;
        return *this;
    }
};

template <typename T>
map_init_helper<T> map_init(T& item)
{
    return map_init_helper<T>(item);
}

template <typename C, C beginVal, C endVal>
class Iterator {
    typedef typename std::underlying_type<C>::type val_t;
    int val;

public:
    Iterator(const C& f)
        : val(static_cast<val_t>(f))
    {
    }
    Iterator()
        : val(static_cast<val_t>(beginVal))
    {
    }
    Iterator operator++()
    {
        ++val;
        return *this;
    }
    C operator*() { return static_cast<C>(val); }
    Iterator begin() { return *this; } //default ctor is good
    Iterator end()
    {
        static const Iterator endIter = ++Iterator(endVal); // cache it
        return endIter;
    }
    bool operator!=(const Iterator& i) { return val != i.val; }
};

} // namespace ble_src

#endif
