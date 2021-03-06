#pragma once

#include <common/types.h>

union u128 {
    struct {
        u64 lo;
        u64 hi;
    } i;

    u64 ud[2];
    u32 uw[4];

    u128 inline operator |(u128 value) {
        u128 data;
        data.i.lo = i.lo | value.i.lo;
        data.i.hi = i.hi | value.i.hi;

        return data;
    }

    u128& operator=(const int value) {
        uw[0] = value;

        return *this;
    }
};

union s128 {
    struct {
        s64 lo;
        s64 hi;
    } i;

    s64 sd[2];
};