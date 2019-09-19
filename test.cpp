#include <cassert>
#include <random>
#include <queue>
#include <utility>
#include "include/queue.h"

void ManualTesting() {
  Queue<int> a;
  assert(a.IsEmpty());
  assert(a.Size() == 0);

  Queue<int> b = {1, 2, 3, 4, 5};
  assert(!b.IsEmpty());
  assert(b.Size() == 5);

  Queue<int> c = b;
  assert(c.Size() == 5);

  Queue<int> d = std::move(b);
  assert(d.Size() == 5);
  assert(b.IsEmpty());

  a = c + d;
  c += d;
  assert(a.Size() == 10);
  assert(a == c);
  assert(a != b);

  c.Clear();
  assert(c.IsEmpty());

  b = {6, 7, 8};
  assert(b.Size() == 3);
  c = b;
  assert(c.Size() == 3);

  assert(a.Front() == 1);
  assert(b.Front() == 6);
  assert(a.Back() == 5);
  assert(b.Back() == 8);

  b.Push(9);
  assert(b.Pop() == 6);
  assert(b.Front() == 7);
  assert(b.Back() == 9);

  a = b;
  assert(a != c);
  assert(a == b);
  b.Swap(c);
  assert(a == c);

  const Queue<std::pair<int, int>> q = {{1, 2}, {3, 4}, {5, 6}};
  auto it = q.begin();
  assert(*it == std::make_pair(1, 2));
  assert(it->first == 1);
  auto it2 = it;
  it2++;
  ++it2;
  it2--;
  --it2;
  assert(it == it2);
}

void AutomatedTesting(size_t step_count) {
  std::queue<int> a;
  Queue<int> b;
  std::mt19937 rng;
  std::bernoulli_distribution distBool;
  std::uniform_int_distribution<int> distInt(1, 100);
  for (size_t step = 0; step < step_count; step++) {
    assert(a.empty() == b.IsEmpty());
    assert(a.size() == b.Size());
    std::queue<int> tmp;
    for (int i : b) {
      tmp.push(i);
    }
    assert(a == tmp);
    distBool = std::bernoulli_distribution(exp(-pow(a.size() / 64, 2)));
    if (distBool(rng)) {
      int value = distInt(rng);
      a.push(value);
      b.Push(value);
    } else {
      assert(a.front() == b.Pop());
      a.pop();
    }
  }
}

int main() {
  ManualTesting();
  AutomatedTesting(2'000'000);
  return 0;
}
