//source chatgpt
//error code

#include <variant>
#include <functional>
#include <iostream>
#include <string>
#include <ranges>

// template <typename... Ts, typename F>
// decltype(auto) match(std::variant<Ts...>& v, F&& f) {
//     return std::visit([&f](auto&& arg) -> decltype(auto) {
//         using callable_t = std::decay_t<decltype(f(std::forward<decltype(arg)>(arg)))>;
//         using result_t = decltype(std::declval<callable_t>()(std::forward<decltype(arg)>(arg)));
//         return f(std::forward<decltype(arg)>(arg));
//     }, v);
// }

// template <typename... Ts, typename F>
// decltype(auto) match(std::variant<Ts...> const& v, F&& f) {
//     return std::visit([&f](auto&& arg) -> decltype(auto) {
//         using callable_t = std::decay_t<decltype(f(std::forward<decltype(arg)>(arg)))>;
//         using result_t = decltype(std::declval<callable_t>()(std::forward<decltype(arg)>(arg)));
//         return f(std::forward<decltype(arg)>(arg));
//     }, v);
// }

// template <typename... Ts, typename F>
// decltype(auto) match(std::variant<Ts...>&& v, F&& f) {
//     return std::visit([&f](auto&& arg) -> decltype(auto) {
//         using callable_t = std::decay_t<decltype(f(std::forward<decltype(arg)>(arg)))>;
//         using result_t = decltype(std::declval<callable_t>()(std::forward<decltype(arg)>(arg)));
//         return f(std::forward<decltype(arg)>(arg));
//     }, std::move(v));
// }

// template <typename... Ts, typename F>
// decltype(auto) match(std::variant<Ts...> const&& v, F&& f) {
//     return std::visit([&f](auto&& arg) -> decltype(auto) {
//         using callable_t = std::decay_t<decltype(f(std::forward<decltype(arg)>(arg)))>;
//         using result_t = decltype(std::declval<callable_t>()(std::forward<decltype(arg)>(arg)));
//         return f(std::forward<decltype(arg)>(arg));
//     }, std::move(v));
// }

template<typename... Ts, typename F>
decltype(auto) match2(std::variant<Ts...>& v, F&& f) {
    return std::visit(std::forward<F>(f), v);
}

int main() {
    std::variant<int, std::string> v("hello");

    auto r = match2(v,
        [](int i) { return i + 1; },
        [](std::string const& s) { return s.size(); }
    );

    std::cout << r << '\n'; // prints "5"
}