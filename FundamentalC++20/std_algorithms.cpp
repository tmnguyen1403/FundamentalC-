#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <list>
#include <cassert>

int main()
{
    std::vector<int> v= {1,2,3,4,5,6,7,8,9,10};
    std::cout << "for each:\n";
    auto print = [](auto &v){std::ranges::for_each(v, [](auto&& data){std::cout << data << " ";});
    };
    print(v);
    std::cout << "\ntransform:\n";
    auto out = std::vector<int>(v.size());
    std::ranges::transform(v,out.begin(), [](auto &&i) {return 3*i;});
    print(out);
    std::cout << "\nfill:\n";
    auto f = std::vector<int>(4);
    std::ranges::fill(f, -10);
    print(f);
    std::cout << "\ngenerate:\n";
    auto g = std::vector<int>(4);
    std::ranges::generate(g, std::rand);
    print(g);
    std::cout << "\niota - generate values in increasing order:\n";
    auto k = std::vector<int>(10);
    std::iota(k.begin(), k.end(),5);
    print(k);
    std::cout << "find O(n)\n";
    auto row = std::list{2,3,4,10,5,6,8};
    auto it = std::ranges::find(row,8);
    if (it != row.end()){
        std::cout << *it << "\n";
    }
    {
        std::cout << "binary search on sorted vector\n";
        auto sorted_v = std::vector{2,3,4,4,4,5,7,10,14};
        std::cout << "compile with -DNDEBUG to disable assert\n";
        assert(std::ranges::is_sorted(sorted_v));
        bool found = std::ranges::binary_search(sorted_v,4);
        std::cout << std::boolalpha << found << "\n";
        std::cout << "lower bound - knowing the position of the first\n";
        auto sorted_it = std::ranges::lower_bound(sorted_v, 4);
        if (sorted_it != sorted_v.end()){
            auto index = std::distance(sorted_v.begin(), sorted_it);
            std::cout << "index: " << index << "\n";
        }

        std::cout << "upper bound - knowing the position of the last\n";
        sorted_it = std::ranges::upper_bound(sorted_v, 4);
        if (sorted_it != sorted_v.end()){
            auto index = std::distance(sorted_v.begin(), sorted_it);
            std::cout << "index: " << index << "\n";
        }
        std::cout << "equal range - knowing the position of both\n";
        auto subrange = std::ranges::equal_range(sorted_v, 4);
        if (subrange.begin() != subrange.end()){
            auto pos1 = std::distance(sorted_v.begin(), subrange.begin());
            auto pos2 = std::distance(sorted_v.begin(), subrange.end());
            std::cout << "position start: " << pos1 <<  "\n";
            std::cout << "position end: " << pos2 <<  "\n";
            std::cout << "all position\n";
            for (auto iter = subrange.begin();iter != subrange.end();++iter) {
                std::cout << "position: " << std::distance(sorted_v.begin(), iter) << std::endl;
            }
        }
    }
}