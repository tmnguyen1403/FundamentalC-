# Definition
 An alias template is a name that refers not to a type but a family of types. Remember, a template is not a class, function, or variable but a blueprint that allows the creation of a family of types, functions, or variables
 ## Example

 ```
template <typename T>
using customer_addresses_t = 
std::map<int, std::vector<T>>;            // [1]

struct delivery_address_t {};
struct invoice_address_t {};

using customer_delivery_addresses_t =
customer_addresses_t<delivery_address_t>; // [2]

using customer_invoice_addresses_t =
customer_addresses_t<invoice_address_t>;  // [3]
 ```
The declaration on line [1] introduces the alias template customer_addresses_t. It's an alias for a map type where the key type is int and the value type is std::vector<T>. Since std::vector<T> is not a type, but a family of types, customer_addresses_t<T> defines a family of types. The using declarations at [2] and [3] introduce two type aliases, customer_delivery_addresses_t and customer_invoice_addresses_t, from the aforementioned family of types.