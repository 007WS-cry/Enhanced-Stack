# Enhanced Stack

## 简介

Enhanced Stack 是一个扩展和修改了 C++ 标准库中 `std::stack` 功能的容器类，提供了增强的栈操作和特定的数值计算功能。此类库专为学习和实验目的设计，提供了标准 `stack` 的基本功能，同时添加了一些额外特性。

## 功能特点

### 基本容器操作

- **构造与析构**
    - 默认构造函数：`enhanced_stack()`
    - 拷贝构造函数：`enhanced_stack(const enhanced_stack &other)`
    - 移动构造函数：`enhanced_stack(enhanced_stack &&other)`
    - 赋值运算符：`operator=`（拷贝和移动版本）
    - 析构函数：`~enhanced_stack()`

- **元素访问**
    - 栈顶元素访问：`top()`

- **容量操作**
    - 大小查询：`size()`
    - 判断是否为空：`empty()`

- **修改操作**
    - 压入单个元素：`push(const Type &value)`
    - 压入一个范围的元素（仅适用于整数类型）：`push(const Type &left_val, const Type &right_val)`
    - 弹出单个元素：`pop()`
    - 弹出指定数量的元素：`pop(const int &num)`
    - 交换栈顶的两个元素：`swap_top()`
    - 清空栈：`clear()`

## 与 std::stack 对比

### 相同点
- 提供了栈的基本功能，遵循后进先出（LIFO）原则。
- 支持栈顶元素的访问和压入、弹出操作。

### 增强功能
1. **范围压入**：提供了 `push(const Type &left_val, const Type &right_val)` 方法，可将一个范围内的整数元素压入栈中（仅适用于整数类型）。
2. **交换栈顶元素**：提供了 `swap_top()` 方法，可交换栈顶的两个元素。
3. **批量弹出**：提供了 `pop(const int &num)` 方法，可一次性弹出指定数量的元素。

## 优势

1. **功能扩展**：在标准栈的基础上增加了一些实用的操作，提高了栈的灵活性。
2. **类型感知**：自动识别整数类型并提供相应的范围压入操作。
3. **异常处理**：在访问空栈或弹出元素数量超过栈大小时抛出异常，增强了程序的健壮性。

## 不足

1. **性能开销**：
    - 范围压入操作可能需要多次内存分配，时间复杂度较高。
    - 交换栈顶元素操作需要额外的内存交换。

2. **内存管理**：
    - 使用固定的初始容量，可能造成内存浪费。
    - 扩容操作可能导致不必要的内存重分配。

3. **设计限制**：
    - 范围压入操作仅支持整数类型。
    - 缺少一些现代 C++ 容器的高级功能（如 `emplace` 系列操作）。

4. **安全性**：
    - 部分操作缺少边界检查（虽然有异常处理，但仍可能存在潜在风险）。

## 使用示例

### 方式一：直接包含头文件（仅头文件库）

```cpp
#include "enhanced_stack.hpp"
#include <iostream>

int main() {
    // 创建整数栈
    enhanced::enhanced_stack<int> stack;

    // 压入单个元素
    stack.push(10);
    stack.push(20);

    // 压入一个范围的元素
    stack.push(30, 35);

    // 打印栈顶元素
    std::cout << "Top element: " << stack.top() << std::endl;

    // 交换栈顶元素
    stack.swap_top();
    std::cout << "Top element after swap: " << stack.top() << std::endl;

    // 弹出元素
    stack.pop();
    std::cout << "Top element after pop: " << stack.top() << std::endl;

    // 批量弹出元素
    stack.pop(2);
    std::cout << "Stack size after pop 2 elements: " << stack.size() << std::endl;

    return 0;
}
```

### 方式二：链接静态库

#### 项目结构
```
project/
├── include/
│   └── enhanced_stack.hpp
├── lib/
│   └── libenhanced.a
└── src/
    └── main.cpp
```

#### 编译命令
```bash
# 在项目根目录下执行以下命令编译程序
g++ -o myprogram src/main.cpp -I./include -L./lib -lenhanced -std=c++17
```

#### main.cpp 示例
```cpp
#include <enhanced_stack.hpp>
#include <iostream>

// 示例：使用 enhanced_stack 进行简单计算
void simple_calculation() {
    enhanced::enhanced_stack<int> stack;

    // 压入一些元素
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // 弹出元素进行计算
    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();

    int result = a + b;
    std::cout << "Result of addition: " << result << std::endl;

    // 压入结果
    stack.push(result);

    // 再次弹出元素进行计算
    int c = stack.top();
    stack.pop();
    int d = stack.top();
    stack.pop();

    result = c * d;
    std::cout << "Result of multiplication: " << result << std::endl;
}

int main() {
    simple_calculation();
    return 0;
}
```

#### CMakeLists.txt 示例
如果使用 CMake 构建系统，可以使用以下 CMakeLists.txt：

```cmake
cmake_minimum_required(VERSION 3.10)
project(EnhancedStackDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定头文件目录
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 指定库文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 链接静态库
target_link_libraries(${PROJECT_NAME} enhanced_stack.a)
```

## 未来改进方向

1. 修复内存管理问题，特别是扩容操作中的内存浪费。
2. 优化范围压入操作，减少内存分配次数。
3. 添加更多现代 C++ 容器特性，如 `emplace` 系列操作。
4. 提高类型安全性和边界检查。
5. 考虑使用更灵活的内存扩容策略。
6. 实现更完善的异常处理机制。