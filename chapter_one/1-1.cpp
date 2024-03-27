#include <iostream> 
#include <type_traits>
/*
 * Function templates - prevoide functional behavior applicable to multiple types aka family of functions
 *                    - type parameters are used to determine which types are used in instance of function
*/

/*
 * This family of functions returns the maximum value between two elements of the same type
 * Function takes in a type parameter of T, T represent an arbitrary Type determined by the caller
 * T must support < otherwise there will be a type error
 */
template<typename T>
T max (T a, T b)
{
    return b < a ? a : b;
}
/*
 * Function entities are generated for each type for which the template is used
 * In this case, the max is generated 3 different times before being compiled
 *
 * Instantiation - process of replacing template parameters by concrete types
 * Instance of template - result of instantiation
 */

/*
 * Tweo Phase Translation 
 * 1. Without instantiation - Template code is checked for syntactical correctness, ignores anything dependent on unknown types  
 * 2. Instantiation Time - Template code is checked including anything effected by template parameters
 */
/*
 * template<typename T>
 * void foo(T t) 
 * {
 * undeclared(); //Will fail in phase one if undeclared is unknown 
 * undeclared(t); //Will fail in second round if undeclared(T) is unknown
 * static_assert(sizeof(int) > 10, "int too small") //Will always fail if sizeof(int) <= 10 
 * static_assert(sizeof(T) > 10, "T too small")" //Will fail if instantiated T has size <= 10
 * }
*/

/*
 * Default arguments must be declared in Template Parameter as well as function definition
 * template<typename T = std::string>
 * void f(T = " ") {} 
 */
/*
 * Template Parameters - declared in angle brackets before function template<typename T, typename T1>  
 * Call Parameters - declared in fucntion definition T max(T a, T1 b) which type will be the return type, depends on order you pass in values 
 * To fix problem, add third template argument, typename RT. If RT cannot be deduced by template or call parameters then you must explicitly list it out
 * Ex: RT max(T a, T1 b)
 *     max<int, int, string>(4, 8) 
 *
 * You can also, mix implicit and explicit specification of arguments, specify arguments all arguments that must be stated and let the compiler figure the rest out
 * 
 * Using auto as return type 
 *     - allowable if it can be deduced based on template parameters 
 *     - use -> typename to declare return type
 *          - -> decltype(b < a ? a : b) allows us to use call parameters to determine return type 
 *
 *  Inline means a function can appear multiple times in a program and only suggests to embed it in the program
 */
 
int main () 
{
    std::cout << max(4, 7) << '\n';
    std::cout << max(3.543, 2.1) << '\n';
    std::cout << max("why wof", "nah") << '\n'; 
    int a = 5;
    int& b = a;
    std::cout << ((std::is_same_v<std::decay<decltype(b)>, decltype(a)>)?"Yes":"Nop") << '\n'; 
}
