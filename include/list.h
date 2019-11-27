#pragma once
#include <algorithm>
#include <istream>
#include <ostream>
#include <utility>
#include "visitor.h"
#include "tostring_visitor.h"
#include "min_visitor.h"

template<class T> class List;
template<class T> class ListIterator;

template<class T>
class List: public IAcceptsVisitor<List<T>, T> {
 public:
  List() : data_(nullptr), size_(0), tail_(0) {
  }

  List(const std::initializer_list<T>& rhs) :
      data_(new T[rhs.size()]),
      size_(rhs.size()),
      tail_(rhs.size()) {
    std::copy(rhs.begin(), rhs.end(), data_);
  }

  List(const List& rhs) :
      data_(new T[rhs.Size()]),
      size_(rhs.Size()),
      tail_(rhs.Size()) {
    std::copy(rhs.data_, rhs.data_ + rhs.tail_, data_);
  }

  List(List&& rhs) :
      data_(rhs.data_),
      size_(rhs.size_),
      tail_(rhs.tail_) {
    rhs.data_ = nullptr;
    rhs.size_ = 0;
    rhs.tail_ = 0;
  }

  List& operator=(const std::initializer_list<T>& rhs) {
    delete[] data_;
    data_ = new T[rhs.size()];
    size_ = rhs.size();
    tail_ = rhs.size();
    std::copy(rhs.begin(), rhs.end(), data_);
    return *this;
  }

  List& operator=(const List& rhs) {
    delete[] data_;
    data_ = new T[rhs.Size()];
    size_ = rhs.Size();
    tail_ = rhs.Size();
    std::copy(rhs.data_, rhs.data_ + rhs.tail_, data_);
    return *this;
  }

  List& operator=(List&& rhs) {
    data_ = rhs.data_;
    size_ = rhs.size_;
    tail_ = rhs.tail_;
    rhs.data_ = nullptr;
    rhs.size_ = 0;
    rhs.tail_ = 0;
    return *this;
  }

  ~List() {
    delete[] data_;
  }

  T Accept(const IVisitor<List<T>, T>& visitor) {
    return visitor.Visit(*this);
  }

  void push_front(const T& value) {
    size_t sz = tail_ << 1;
    if (sz == 0) {
      sz = 1;
    }
    if (tail_ + 1 > size_) {
      Resize(sz);
    }
    for (T* ptr = data_ + (tail_++); ptr != data_; ptr--) {
      *ptr = std::move(*(ptr - 1));
    }
    *data_ = value;
  }

  T toString() {
    return Accept(ToStringVisitor());
  }

  T min() {
    return Accept(MinVisitor());
  }
 
 protected:
  T* data_;
  size_t size_;
  size_t tail_;
  friend class ListIterator<T>;

  void Resize(size_t new_size) {
    T* data_new = new T[new_size];
    std::move(data_, data_ + tail_, data_new);
    delete[] data_;
    data_ = data_new;
    size_ = new_size;
  }
};

template<class T>
class ListIterator {
 public:
  ListIterator(const List<T>& q) : ptr_(q.data_), end_ptr_(q.data_ + q.tail_) {
  }
  T& Next() {
    if (ptr_ == end_ptr_) {
      throw std::runtime_error("iterator out of range");
    }
    return *(ptr_++);
  }
  bool HasNext() {
    return ptr_ != end_ptr_;
  }
 private:
  T* ptr_;
  T* end_ptr_;
};
