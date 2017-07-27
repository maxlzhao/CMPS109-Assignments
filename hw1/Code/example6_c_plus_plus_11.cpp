// Max Zhao 1466223 mlzhao@ucsc.edu

// C++98 example
enum Apple {FRUIT, RED, SWEET};
enum Lemon {FRUIT, YELLOW, SOUR}; // would not compile because two enumerations share the name "fruit"

// C++11 example
enum class Apple : char {FRUIT, RED, SWEET}; // can specify underlying integral type of C++11 enums
enum class Lemon : char {FRUIT, YELLOW, SOUR}; // would compile if compiler supports C++ strongly-typed enums

