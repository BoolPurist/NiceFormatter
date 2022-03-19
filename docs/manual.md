# User Manual

This library provides a function 
called "Format".

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
