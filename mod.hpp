#pragma once
#include <iostream>
#include <cstdint>
template <int radix>
#if __cplusplus > 202002L
requires(radix > 1)
#endif
class mod {
    static inline auto normalize(int64_t num) {
        const auto r = static_cast<int>(num%radix);
        return r > 0 ? r : r < 0 ? radix+r : 0; }
    int value;
public:
    inline mod(int64_t num = 0): value(normalize(num)) {}
    inline mod(const mod &num) : value(num.value) {}
    inline auto operator()() const { return value; }
    inline auto operator-() const { return mod(radix-value); }
    inline auto operator==(const mod &num) const { return value == num.value; }
    inline auto operator!=(const mod &num) const { return value != num.value; }
    inline auto& operator=(const mod &num) { value = num.value; return *this; }
    inline auto& operator+=(const mod &num) { value = normalize(value+num.value); return *this; }
    inline auto& operator-=(const mod &num) { value = normalize(value-num.value); return *this; }
    inline auto& operator*=(const mod &num) { value = normalize(1ll*value*num.value); return *this; }
    inline auto pow(uint64_t x) const {
        mod z = 1;
        for (auto y = *this; x > 0; x >>= 1, y *= y)
            if (x&1) z *= y;
        return z; }
    inline mod& operator++() { value = normalize(value+1); return *this; }
    inline mod& operator--() { value = normalize(value-1); return *this; }
    inline mod operator++(int unused) { const auto previous = *this; ++*this; return previous; }
    inline mod operator--(int unused) { const auto previous = *this; --*this; return previous; }
    inline friend auto operator+(mod a, const mod &b) { return a += b; }
    inline friend auto operator-(mod a, const mod &b) { return a -= b; }
    inline friend auto operator*(mod a, const mod &b) { return a *= b; }
    inline friend auto inv(const mod &num) { return num.pow(radix-2); }
    inline auto& operator/=(const mod &num) { value = normalize(1ll*value*inv(num).value); return *this; }
    inline friend auto operator/(mod a, const mod &b) { return a /= b; }
    inline friend auto& operator>>(std::istream &stream, mod &num) {
        int64_t v; stream >> v, num.value = normalize(v); return stream; }
    inline friend auto& operator<<(std::ostream &stream, const mod &num) { return stream << num.value; } };
