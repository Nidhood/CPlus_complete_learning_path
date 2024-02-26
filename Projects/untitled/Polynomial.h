#ifndef __POLYNOMIAL__H__
#define __POLYNOMIAL__H__

#include <istream>
#include <ostream>
#include <vector>

template <class S> class Polynomial : private std::vector<S> {
  friend std::ostream &operator<<(std::ostream &os, const Polynomial<S> &p) {
    if (p.size() > 0) {
      for (int i = p.size() - 1; i >= 0; --i) {
        if (p[i] != S(0)) {
          os << "(";
          if (p[i] > S(0))
            os << "+";
          os << p[i];
          if (i != 0)
            os << "x^" << i;
          os << ")";

        } // fi

      } // rof

    } // fi
    return (os);
  }

public:
  Polynomial();
  virtual ~Polynomial();

  void SetCoefficient(unsigned int degree, const S &coefficient);

  Polynomial<S> &operator+(const Polynomial<S> &right) const;
  Polynomial<S> operator*(const Polynomial<S>& right) const;
  S operator()(const S &x) const;
};

#include "Polynomial.hxx"

#endif // __POLYNOMIAL__H__

// eof - Polynomial.h
