#pragma once
template<class T>
class IVisitor {
 public:
  virtual void Visit(T&) const = 0;
  virtual ~IVisitor() = default;
};

template<class T>
class IAcceptsVisitor {
 public:
  virtual void Accept(const IVisitor<T>&) = 0;
  virtual ~IAcceptsVisitor() = default;
};
