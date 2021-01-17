// ----------------------------------------------------------------------------
// vectorDefinitions.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#pragma once

#ifndef ARDUINO
#include <cstring>
#endif

template <typename T>
vector<T>::vector()
{
  values_ = NULL;
  max_size_ = 0;
  size_ = 0;
}

template <typename T>
template <size_t MAX_SIZE>
vector<T>::vector(T (&values)[MAX_SIZE],
  size_t size)
{
  setStorage(values,size);
}

template <typename T>
template <size_t MAX_SIZE>
void vector<T>::setStorage(T (&values)[MAX_SIZE],
  size_t size)
{
  values_ = values;
  max_size_ = MAX_SIZE;
  size_ = size;
}

template <typename T>
void vector<T>::setStorage(T * values,
  size_t max_size,
  size_t size)
{
  values_ = values;
  max_size_ = max_size;
  size_ = size;
}

template <typename T>
const T & vector<T>::operator[](size_t index) const
{
  return values_[index];
}

template <typename T>
T & vector<T>::operator[](size_t index)
{
  return values_[index];
}

template <typename T>
T & vector<T>::at(size_t index)
{
  return values_[index];
}

template <typename T>
const T & vector<T>::at(size_t index) const
{
  return values_[index];
}

template <typename T>
T & vector<T>::front()
{
  return values_[0];
}

template <typename T>
T & vector<T>::back()
{
  return values_[size_-1];
}

template <typename T>
void vector<T>::clear()
{
  size_ = 0;
}

template <typename T>
template <typename U>
void vector<T>::fill(const U & value)
{
  assign(max_size_,value);
}

template <typename T>
template <typename U,
  size_t N>
void vector<T>::fill(const U (&values)[N])
{
  assign(N,values);
}

template <typename T>
template <typename U>
void vector<T>::fill(const vector<U> & values)
{
  assign(values.size(),values);
}

template <typename T>
template <typename U>
void vector<T>::assign(size_t n,
  const U & value)
{
  size_t assign_size = ((n < max_size_) ? n : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = value;
  }
}

template <typename T>
template <typename U,
  size_t N>
void vector<T>::assign(size_t n,
  const U (&values)[N])
{
  size_t n_smallest = ((n < N) ? n : N);
  size_t assign_size = ((n_smallest < max_size_) ? n_smallest : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = values[i];
  }
}

template <typename T>
template <typename U>
void vector<T>::assign(size_t n,
  const vector<U> & values)
{
  size_t n_smallest = ((n < values.size()) ? n : values.size());
  size_t assign_size = ((n_smallest < max_size_) ? n_smallest : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = values[i];
  }
}

template <typename T>
void vector<T>::push_back(const T & value)
{
  if ((values_ != NULL) && (size_ < max_size_))
  {
    values_[size_++] = value;
  }
}

template <typename T>
void vector<T>::pop_back()
{
  if (size_ > 0)
  {
    --size_;
  }
}

template <typename T>
void vector<T>::remove(size_t index)
{
  if (size_ > index)
  {
    for (size_t i=index; i<(size_-1); ++i)
    {
      values_[i] = values_[i+1];
    }
    --size_;
  }
}

template <typename T>
size_t vector<T>::size() const
{
  return size_;
}

template <typename T>
size_t vector<T>::max_size() const
{
  return max_size_;
}

template <typename T>
bool vector<T>::empty() const
{
  return size_ == 0;
}

template <typename T>
bool vector<T>::full() const
{
  return size_ == max_size_;
}

template <typename T>
T * vector<T>::data()
{
  return values_;
}

template <typename T>
const T * vector<T>::data() const
{
  return values_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin()
{
  return iterator(values_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end()
{
  return iterator(values_,size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const
{
  return const_iterator(values_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const
{
  return const_iterator(values_,size_);
}