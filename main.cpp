#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <vector>

uint64_t fmix64(uint64_t k)
{
	k += 1;
	k ^= k >> 33;
	k *= 0xff51afd7ed558ccdull;
	k ^= k >> 33;
	k *= 0xc4ceb9fe1a85ec53ull;
	k ^= k >> 33;

	return k;
}

template <typename T>
struct NaiveHash
{
    static const std::size_t seed = 89901;
    std::size_t operator()(const T& m) const noexcept
    {
        std::size_t ret = seed;
        for (const auto& t : m) {
            ret += std::hash<typename T::value_type>{}(t);
        }
        return ret;
    }
};

template <typename T>
struct BiggerHash
{
    static const std::size_t seed = 89901;
    std::size_t operator()(const T& m) const noexcept
    {
        __uint128_t ret = seed;
        for (const auto& t : m) {
            auto h = std::hash<typename T::value_type>{}(t);
            // Embed 64-bit space "randomly" into 128-bit space
            // In particular, there is no value of h for which
            // tmp + h == 0.
            __uint128_t tmp = fmix64(h);
            tmp = tmp << 64;
            ret += tmp + h;
        }
        uint64_t lo = (uint64_t)ret;
        uint64_t hi = ret >> 64;
        return lo ^ (hi + 2654435769 + lo << 6 + lo >> 2);
    }
};


int main() {

std::unordered_set<std::unordered_set<std::string>, NaiveHash<std::unordered_set<std::string>>> naiveSetOfSets;
std::unordered_set<std::unordered_set<std::string>, BiggerHash<std::unordered_set<std::string>>> bighashSetOfSets;

}
