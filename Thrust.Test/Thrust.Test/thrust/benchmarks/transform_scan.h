#pragma once 
#ifdef MSVER
#include "stdafx.h" 
#endif

#include <thrust/transform_scan.h>

template <typename Container1,
          typename Container2 = Container1,
          typename UnaryFunction = thrust::negate<typename Container1::value_type>,
          typename BinaryFunction = thrust::plus<typename Container1::value_type> >
struct TransformInclusiveScan
{
  Container1 A;
  Container2 B;
  UnaryFunction unary_op;
  BinaryFunction binary_op;

  template <typename Range1, typename Range2>
  TransformInclusiveScan(const Range1& X, const Range2& Y,
                         UnaryFunction unary_op = UnaryFunction(),
                         BinaryFunction binary_op = BinaryFunction())
    : A(X.begin(), X.end()),
      B(Y.begin(), Y.end()),
      unary_op(unary_op),
      binary_op(binary_op)
  {}

  void operator()(void)
  {
    thrust::transform_inclusive_scan(A.begin(), A.end(), B.begin(), unary_op, binary_op);
  }
  
  void reset(void)
  {
    // nothing to do
  }
};

template <typename Container1,
          typename Container2 = Container1,
          typename UnaryFunction = thrust::negate<typename Container1::value_type>,
          typename T = typename Container1::value_type,
          typename BinaryFunction = thrust::plus<T> >
struct TransformExclusiveScan
{
  Container1 A;
  Container2 B;
  T init;
  UnaryFunction unary_op;
  BinaryFunction binary_op;

  template <typename Range1, typename Range2>
  TransformExclusiveScan(const Range1& X, const Range2& Y,
                         UnaryFunction unary_op = UnaryFunction(),
                         T init = T(0),
                         BinaryFunction binary_op = BinaryFunction())
    : A(X.begin(), X.end()),
      B(Y.begin(), Y.end()),
      init(init),
      unary_op(unary_op),
      binary_op(binary_op)
  {}

  void operator()(void)
  {
    thrust::transform_exclusive_scan(A.begin(), A.end(), B.begin(), unary_op, init, binary_op);
  }
  
  void reset(void)
  {
    // nothing to do
  }
};

