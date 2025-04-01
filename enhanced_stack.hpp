#ifndef ENHANCED_STACK_HPP
#define ENHANCED_STACK_HPP

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <memory>

namespace enhanced {

template<typename Type>
class enhanced_stack {
public:
    enhanced_stack() {
        _size = 0;
        _capacity = 32;
        _data = std::make_unique<Type[]>(_capacity);
        if (std::is_integral_v<Type>) {
            _check = true;
        }
        else {
            _check = false;
        }
    }

    ~enhanced_stack() = default;

    enhanced_stack(const enhanced_stack &other) {
        _size = other._size;
        _capacity = other._capacity;
        _data = std::make_unique<Type[]>(_capacity);
        _check = other._check;
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }

    enhanced_stack &operator=(const enhanced_stack &other) {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _data = std::make_unique<Type[]>(_capacity);
            _check = other._check;
            for (int i = 0; i < _size; i++) {
                _data[i] = other._data[i];
            }
        }
        return *this;
    }

    enhanced_stack(enhanced_stack &&other) noexcept
        : _size(other._size),
          _capacity(other._capacity),
          _data(std::move(other._data)),  // 转移所有权
          _check(other._check) {
        other._size = 0;
        other._capacity = 32;
    }

    enhanced_stack &operator=(enhanced_stack &&other) noexcept {
        if (this != &other) {
            _size = other._size;
            _data = std::move(other._data);
            _capacity = other._capacity;
            _check = other._check;
            other._size = 0;
            other._capacity = 32;
        }
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
    int _capacity;
    std::unique_ptr<Type[]> _data;
    bool _check;

    void addCapacity() {
        auto new_capacity = _capacity * 2;
        auto new_data = std::make_unique<Type[]>(new_capacity);

        for (int i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }

        _data = std::move(new_data);
        _capacity = new_capacity;
    }
};

} // namespace enhanced

#endif // ENHANCED_STACK_HPP