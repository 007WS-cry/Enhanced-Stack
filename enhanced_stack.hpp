/**
* 文件名: enhanced_stack.hpp
 * 项目名称: enhanced_stack
 * 文件创建日期: 2025-03-25
 * 作者: 007WS
 * 联系方式: a2901805528@163.com
 *
 * 最后编辑日期: 2025-03-27
 * 最后编辑者: 007WS
 * 最后编辑者联系方式: a2901805528@163.com
 *
 * 文件描述:
 * C++ STL stack 扩展版本（大学生练手项目）
 *
 * 许可证:
 * 无
 */

#ifndef ENHANCED_STACK_HPP
#define ENHANCED_STACK_HPP

#include <iostream>
#include <stdexcept>
#include <cmath>

namespace enhanced {

template<typename Type>
class enhanced_stack {
public:
    enhanced_stack() {
        _size = 0;
        _capacity = 32;
        _data = new Type[_capacity];
        if (std::is_integral_v<Type>) {
            _check = true;
        }
        else {
            _check = false;
        }
    }
    ~enhanced_stack() {
        _size = 0;
        _capacity = 32;
        delete[] _data;
    }
    enhanced_stack(const enhanced_stack &other) {
        _size = other._size;
        _capacity = other._capacity;
        _data = new Type[_capacity];
        _check = other._check;
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
    enhanced_stack &operator=(const enhanced_stack &other) {
        _size = other._size;
        _capacity = other._capacity;
        delete[] _data;
        _data = new Type[_capacity];
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
        return *this;
    }
    enhanced_stack(enhanced_stack &&other) noexcept {
        _size = other._size();
        _capacity = other._capacity;
        _data = new Type[_capacity];
        _check = other._check;
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
        other._size = 0;
        other._capacity = 32;
        delete[] other._data;
    }
    enhanced_stack &operator=(enhanced_stack &&other) noexcept {
        _size = other._size;
        _capacity = other._capacity;
        delete[] _data;
        _data = new Type[_capacity];
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
        other._size = 0;
        other._capacity = 32;
        delete[] other._data;
        return *this;
    }

    [[nodiscard]] int size() const {
        return _size;
    }
    [[nodiscard]] bool empty() const {
        return _size == 0;
    }
    Type top() const {
        if (_size == 0) {
            throw std::runtime_error("Error: Stack is empty");
        }
        return _data[_size - 1];
    }

    void push(const Type &value) {
        if (_size == _capacity) {
            addCapacity();
        }
        _data[_size++] = value;
    }
    void push(const Type &left_val, const Type &right_val) {
        if (!_check) {
            throw std::runtime_error("Error: Invalid Type");
        }
        while (_size + abs(left_val - right_val) >= _capacity) {
            addCapacity();
        }
        if (left_val < right_val) {
            for (int i = left_val; i < right_val; ++i) {
                _data[_size++] = i;
            }
        }
        else {
            for (int i = left_val; i > right_val; --i) {
                _data[_size++] = i;
            }
        }
    }
    void pop() {
        if (_size == 0) {
            throw std::runtime_error("Error: Stack is empty");
        }
        _size--;
    }
    void pop(const int &num) {
        if (_size < num) {
            throw std::runtime_error("Error: Stack size is smaller than your input");
        }
        _size -= num;
    }

    void swap_top() {
        if (_size <= 1) {
            throw std::runtime_error("Error: Stack size is smaller than 2");
        }
        std::swap(_data[_size - 1], _data[_size - 2]);
    }

    void clear() {
        _size = 0;
    }

private:
    int _size;
    Type *_data;
    int _capacity;
    bool _check;
    void addCapacity() {
        Type *tmp_data = new Type[_capacity];
        for (int i = 0; i < _size; i++) {
            tmp_data[i] = _data[i];
        }
        delete[] _data;
        _data = new Type[_capacity * 2];
        for (int i = 0; i < _size; i++) {
            _data[i] = tmp_data[i];
        }
    }
};

} // enhanced

#endif //ENHANCED_STACK_HPP
