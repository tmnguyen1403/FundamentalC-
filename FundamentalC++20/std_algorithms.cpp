#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <list>
#include <cassert>
#include <set>
#include <iterator>
#include <tuple>

int main()
{
    std::vector<int> v= {1,2,3,4,5,6,7,8,9,10};
    std::cout << "for each:\n";
    auto print = [](auto &v){std::ranges::for_each(v, [](auto&& data){std::cout << data << " ";});
    std::cout << std::endl;
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
    {
        std::cout << "std::remove:\n";
        // Example with std::remove()
        auto v = std::vector{1,1,2,2,4,3,3};
        print(v);
        std::cout << "removing 2;\n";
        auto new_end = std::remove(
        v.begin(), v.end(), 2);
        std::cout << "before erease;\n";
        print(v);
        std::cout << "after erease;\n";
        v.erase(new_end, v.end());
        print(v);
    }
    {
        std::cout << "std::unique:\n";
        auto v = std::vector{1,1,2,2,3,3};
        print(v);
        std::cout << "applying unique;\n";
        auto new_end = std::unique(
        v.begin(), v.end());
        std::cout << "before erease;\n";
        print(v);
        std::cout << "after erease;\n";
        v.erase(new_end, v.end());
        print(v);
    }
    {
        std::cout << "back inserter and inserter\n";
        const auto square_func = [](int x) { return x * x; };
        const auto v = std::vector{1, 2, 3, 4};
        print(v);
        // Insert into back of vector using std::back_inserter
        auto squared_vec = std::vector<int>{};
        
        //use back_inserter to simplify the process of inserting elements at the end of a container
        auto dst_vec = std::back_inserter(squared_vec);
       
        std::ranges::transform(v, dst_vec, square_func);
        std::cout << "squared_vec after transform back_inserter\n";
        print(squared_vec);
        // Insert into a std::set using std::inserter
        auto squared_set = std::set<int>{};
        std::cout << "using inserter to insert front\n";
        auto dst_set = std::inserter(squared_set, squared_set.end());
        std::ranges::transform(v, dst_set, square_func);
        std::cout << "squared_set after back_inserter\n";
        print(squared_set);
    }
    {
        std::cout << "Three ways operator <=>\n";
        struct Flower {
            auto operator<=>(const Flower& f) const = default; 
            bool operator==(const Flower&) const = default;
            int height_{};
        };
        auto garden = std::vector<Flower>{{67}, {28}, {14}};
        // std::max_element() uses operator<()
        auto tallest = std::max_element(garden.begin(), garden.end());
        // std::find() uses operator==()
        auto perfect = *std::find(garden.begin(), garden.end(), Flower{28});
    }
    {
        std::cout << "projection feature\n";
        std::cout << "projection arg can be function pointer, a functor, or a lambda function\n";
        auto names = std::vector<std::string>{
        "Ralph", "Lisa", "Homer", "Maggie", "Apu", "Bart"
        };
        std::cout << "sort by length: &std::string::size address to the size function\n";
        std::ranges::sort(names, std::less<>{}, &std::string::size);
        // names is now "Apu", "Lisa", "Bart", "Ralph", "Homer", "Maggie"
        
        // Find names with length 3
        auto x = std::ranges::find(names, 3, &std::string::size);
        // x points to "Apu"
    }
    {
        std::cout << "pass lambda as projection parameter\n";
        struct Player {
            std::string name_{};
            int level_{};
            float health_{};
        };
        auto players = std::vector<Player>{
            {"Aki", 1, 9.f}, 
            {"Nao", 2, 7.f}, 
            {"Rei", 2, 3.f}
        };
        auto level_and_health = [](const Player& p) {
            //create a tuple of references
            return std::tie(p.level_, p.health_);
        }; 
        // Order players by level, then health
        std::ranges::sort(players, std::greater<>{}, level_and_health);
    }
    {
        std::cout << "adjacent find\n";
         std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

        auto it = std::adjacent_find(numbers.begin(), numbers.end());

        if (it != numbers.end()) {
            std::cout << "Adjacent elements found: " << *it << " and " << *(it + 1) << std::endl;
        } else {
            std::cout << "No adjacent elements found." << std::endl;
        }
        auto isEvenAndOdd = [](const auto& a, const auto& b) {
            return (a % 2 == 0) && (b % 2 != 0);
        };
        it = std::adjacent_find(numbers.begin(), numbers.end(), isEvenAndOdd);

        if (it != numbers.end()) {
            std::cout << "Adjacent elements satisfying custom predicate found: " << *it << " and " << *(it + 1) << std::endl;
        } else {
            std::cout << "No adjacent elements satisfying custom predicate found." << std::endl;
        }

    }
    {
        std::cout <<"sort, nth_element, partial_sort\n";
        auto v = std::vector{6, 3, 2, 7,
                     4, 1, 5};
        auto it = v.begin() + v.size()/2;
        auto left = it - 1;
        auto right = it + 2;
        std::nth_element(v.begin(),
                        left, v.end());
        std::partial_sort(left, right,
                        v.end());
                    
        std::nth_element(v.begin(), it,
                 v.end());
        std::sort(it, v.end());

    }
}