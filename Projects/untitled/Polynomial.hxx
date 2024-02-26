#ifndef POLYNOMIALHXX
#define POLYNOMIALHXX

// -------------------------------------------------------------------------
template< class S > 
Polynomial< S >::
Polynomial( )
{
}

// -------------------------------------------------------------------------
template< class S > 
Polynomial< S >::
~Polynomial( )
{
}

// -------------------------------------------------------------------------
template< class S > 
void  Polynomial< S >::
SetCoefficient( unsigned int degree, const S& coefficient )
{
  if( degree >= this->size( ) )
    this->resize( degree + 1, S( 0 ) );
  ( *this )[ degree ] = coefficient;
}

// -------------------------------------------------------------------------
  template< class S > 
  Polynomial< S >& Polynomial< S >::operator+(const Polynomial< S >& right) const
  {
      Polynomial< S >* result = new Polynomial< S >();

      unsigned int maxSize = std::max(this->size(), right.size());
     result->resize(maxSize, S(0));

      for (unsigned int i = 0; i < maxSize; ++i) {
          S term = S(0);
          if (i < this->size()) {
              term += (*this)[i];
          }
          if (i < right.size()) {
              term += right[i];
          }
        result->SetCoefficient(i, term);
      }

      return *result;
  }


// -------------------------------------------------------------------------
template< class S >
Polynomial< S > Polynomial< S >::operator*( const Polynomial< S >& right ) const
{
  Polynomial< S > result;

  // TODO #2: Calcular el producto de dos polinomios
  // Pc(x) = PA(x) * PB(x)
  // Donde
  // C = {∑ 𝑎𝑘𝑏𝑗−𝑘 𝑗 𝑘=0; 𝑎𝑘 ; 𝑏𝑗 ∈ ℝ𝛬𝑗 ∈ [0,2𝑛 − 1]}
  // n = max(grado(A), grado(B))

  // Encuentra el máximo grado entre los dos polinomios
  unsigned int maxDegree = this->size() + right.size() - 1;

  // Inicializa el polinomio resultado con coeficientes cero
  result.resize(maxDegree, S(0));

  // Multiplica los polinomios término a término y suma los resultados
  for (unsigned int i = 0; i < this->size(); ++i) {
    for (unsigned int j = 0; j < right.size(); ++j) {
      result[i + j] += (*this)[i] * right[j];
    }
  }

  return result;
}

// -------------------------------------------------------------------------
template< class S > 
S Polynomial< S >::
operator()( const S& x ) const
{
  S result = S( 0 );

  // TODO #3: Evaluar el polinomio en un valor dado de x
  // Evalúa el polinomio utilizando el método de Horner para evitar cálculos innecesarios
  // P(x) = a_n * x^n + a_(n-1) * x^(n-1) + ... + a_1 * x + a_0

  for (int i = this->size() - 1; i >= 0; --i) {
    result = result * x + (*this)[i];
  }

  return result;
} 

#endif // POLYNOMIALHXX