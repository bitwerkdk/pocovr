// ----------------------------------------------------------------------------
// vectorIterator.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#pragma once

template<typename T>
class vectorIterator
{
public:
  vectorIterator(T * values_ptr) : values_ptr_{values_ptr}, position_{0} {}

  vectorIterator(T * values_ptr, size_t size) : values_ptr_{values_ptr}, position_{size} {}

  bool operator!=(const vectorIterator<T> & other) const
  {
    return !(*this == other);
  }

  bool operator==(const vectorIterator<T> & other) const
  {
    return position_ == other.position_;
  }

  vectorIterator & operator++()
  {
    ++position_;
    return *this;
  }

  T & operator*() const
  {
    return *(values_ptr_ + position_);
  }

private:
  T * values_ptr_;
  size_t position_;
};