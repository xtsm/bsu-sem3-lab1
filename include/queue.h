#pragma once
#include <algorithm>
#include <istream>
#include <ostream>
#include <utility>
#include "visitor.h"

template<class T> class Queue;
template<class T> class QueueIterator;
template<class T> std::istream& operator>>(std::istream& is, Queue<T>& q);
template<class T> std::ostream& operator<<(std::ostream& os, const Queue<T>& q);

template<class T>
class Queue : public IAcceptsVisitor<Queue<T>> {
 public:
  Queue() : data_(nullptr), size_(0), head_(0), tail_(0) {
  }

  Queue(const std::initializer_list<T>& rhs) :
      data_(new T[rhs.size()]),
      size_(rhs.size()),
      head_(0),
      tail_(rhs.size()) {
    std::copy(rhs.begin(), rhs.end(), data_);
  }

  Queue(const Queue& rhs) :
      data_(new T[rhs.Size()]),
      size_(rhs.Size()),
      head_(0),
      tail_(rhs.Size()) {
    std::copy(rhs.data_ + rhs.head_, rhs.data_ + rhs.tail_, data_);
  }

  Queue(Queue&& rhs) :
      data_(rhs.data_),
      size_(rhs.size_),
      head_(rhs.head_),
      tail_(rhs.tail_) {
    rhs.data_ = nullptr;
    rhs.size_ = 0;
    rhs.head_ = 0;
    rhs.tail_ = 0;
  }

  Queue& operator=(const std::initializer_list<T>& rhs) {
    delete[] data_;
    data_ = new T[rhs.size()];
    size_ = rhs.size();
    head_ = 0;
    tail_ = rhs.size();
    std::copy(rhs.begin(), rhs.end(), data_);
    return *this;
  }

  Queue& operator=(const Queue& rhs) {
    delete[] data_;
    data_ = new T[rhs.Size()];
    size_ = rhs.Size();
    head_ = 0;
    tail_ = rhs.Size();
    std::copy(rhs.data_ + rhs.head_, rhs.data_ + rhs.tail_, data_);
    return *this;
  }

  Queue& operator=(Queue&& rhs) {
    data_ = rhs.data_;
    size_ = rhs.size_;
    head_ = rhs.head_;
    tail_ = rhs.tail_;
    rhs.data_ = nullptr;
    rhs.size_ = 0;
    rhs.head_ = 0;
    rhs.tail_ = 0;
    return *this;
  }

  ~Queue() {
    delete[] data_;
  }

  void Accept(const IVisitor<Queue<T>>& visitor) {
    visitor.Visit(*this);
  }

  Queue& operator+=(const Queue& rhs) {
    if (tail_ + rhs.Size() > size_) {
      Resize(Size() + rhs.Size());
    }
    std::copy(rhs.data_ + rhs.head_, rhs.data_ + rhs.tail_, data_ + tail_);
    tail_ += rhs.Size();
    return *this;
  }

  Queue operator+(const Queue& rhs) const {
    return Queue(*this) += rhs;
  }

  bool operator==(const Queue& rhs) const {
    size_t sz = Size();
    if (sz != rhs.Size()) {
      return false;
    }
    for (size_t i = 0; i < sz; i++) {
      if (data_[head_ + i] != rhs.data_[rhs.head_ + i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Queue& rhs) const {
    return !(*this == rhs);
  }

  bool IsEmpty() const {
    return head_ == tail_;
  }

  size_t Size() const {
    return tail_ - head_;
  }

  void Clear() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    head_ = 0;
    tail_ = 0;
  }

  const T& Front() const {
    if (IsEmpty()) {
      throw std::runtime_error("attempt to retrieve "
          "element from empty container");
    }
    return data_[head_];
  }

  const T& Back() const {
    if (IsEmpty()) {
      throw std::runtime_error("attempt to retrieve "
          "element from empty container");
    }
    return data_[tail_ - 1];
  }

  void Push(const T& value) {
    size_t sz = Size() << 1;
    if (sz == 0) {
      sz = 1;
    }
    if (tail_ + 1 > size_) {
      Resize(sz);
    }
    data_[tail_++] = value;
  }

  T Pop() {
    if (IsEmpty()) {
      throw std::runtime_error("attempt to pop from empty queue");
    }
    T ret = std::move(data_[head_++]);
    size_t sz = Size();
    if (sz < size_ >> 2) {
      Resize(sz << 1);
    }
    return ret;
  }

  void Swap(Queue& rhs) {
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
  }

 protected:
  T* data_;
  size_t size_;
  size_t head_;
  size_t tail_;
  friend std::istream& operator>><T>(std::istream& is, Queue& q);
  friend std::ostream& operator<<<T>(std::ostream& os, const Queue& q);
  friend class QueueIterator<T>;

  void Resize(size_t new_size) {
    T* data_new = new T[new_size];
    std::move(data_ + head_, data_ + tail_, data_new);
    delete[] data_;
    data_ = data_new;
    size_ = new_size;
    tail_ -= head_;
    head_ = 0;
  }
};

template<class T>
class QueueIterator {
 public:
  QueueIterator(const Queue<T>& q) : ptr_(q.data_ + q.head_), q_(q) {
  }
  T& Next() {
    if (ptr_ == q_.data_ + q_.tail_) {
      throw std::runtime_error("iterator out of range");
    }
    return *(ptr_++);
  }
  bool HasNext() {
    return ptr_ != q_.data_ + q_.tail_;
  }
 private:
  T* ptr_;
  const Queue<T>& q_;
};

template<class T>
std::istream& operator>>(std::istream& is, Queue<T>& q) {
  q.head_ = 0;
  is >> q.tail_;
  delete[] q.data_;
  q.data_ = new T[q.tail_ - q.head_];
  QueueIterator<T> it(q);
  do {
    is >> it.Next();
  } while (it.HasNext());
  return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q) {
  os << "[ ";
  QueueIterator<T> it(q);
  do {
    os << it.Next() << ' ';
  } while (it.HasNext());
  return os << ']';
}
