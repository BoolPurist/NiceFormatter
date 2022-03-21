# User Manual

## Include It

This library provides a function called "Format". To use it, include the header 
file called "Format.h" via
```c++
#include <Format.h>
```

## How to call function Format.

The variadic function take at least 2 arguments. The 1. one must be string. This string provides the 
format. In this format the values of the rest of arguments are inserted. A format marks a place 
for an insertion of value with curly braces, called placeholder.

If the format is not valid or not enough arguments are provided for the format 
then an exception is thrown. This exception is of type InvalidFormat.

A placeholder has the following syntax variants.

1. {<placeholder-number>,\[amount-of-padding\]}
2. {,\[amount-of-padding\]}

The 1. syntax is for a numbered placeholder. 
The 2. syntax is for not numbered placeholder.

A numbered placeholder provides a number for the n-th value to be inserted there.
Example: {0} tells to use the first given value, second argument of the call, to be inserted.

### Example with numbered brackets

```cpp
const std::pair<int, int> coords{2, 2};
std::cout << NiceGraphic::Format("({0},{1})", coords.first, coords.second)
<< std::endl;
```

Output 
```
(2,2)
```

Here {0} is replaced by the 2. argument "coords.first".

### Example with not numbered curly brackets

```cpp
  const std::vector<int> scores{4500, 2000, 1000};
  std::cout << NiceGraphic::Format(
    "1. {}\n2. {}\n3. {}",
    scores.at(0),
    scores.at(1),
    scores.at(2)
    ) << std::endl;
```

Output:
```
1. 4500
2. 2000
3. 1000
```

### Example with not numbered and numbered curly brackets

```cpp
  std::cout << NiceGraphic::Format("An {1} from the {}", "apple", "tree") << std::endl;
```

Output:
```
An tree from the apple
```

### Example with space padding to the right

```c++
    std::cout
    << NiceGraphic::Format("{,12}{,8}{,4}\n{,12}{,8}{,4}", "Name", "Price", "ID", "Computer", "400$", "45")
    << std::endl;
```

```
        Name   Price  ID
    Computer    400$  45
```

### Example with space padding to the left

```cpp
std::cout
<< NiceGraphic::Format("{,-12}{,-8}{,-4}\n{,-12}{,-8}{,-4}", "Name", "Price", "ID", "Computer", "400$", "45")
<< std::endl;
```

Output:
```
Name        Price   ID  
Computer    400$    45
```
