#pragma once
template<class T, class Q>
class IVisitor {
 public:
  virtual Q Visit(T&) const = 0;
  virtual ~IVisitor() = default;
};

template<class T, class Q>
class IAcceptsVisitor {
 public:
  virtual Q Accept(const IVisitor<T, Q>&) = 0;
  virtual ~IAcceptsVisitor() = default;
};
