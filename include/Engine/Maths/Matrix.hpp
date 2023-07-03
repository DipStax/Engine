#ifndef ENG_MATH_MATRIX_HPP
#define ENG_MATH_MATRIX_HPP

#include <array>

namespace eng
{
    template<size_t Y, size_t X>
    class Matrix : public std::array<std::array<float, X>, Y>
    {
        public:
            Matrix();
            ~Matrix() = default;

            void identity();

            void clear();

            template<size_t Z>
            Matrix<Y, Z> operator*(const Matrix<X, Z> &_matrix);
    };
}

#include "Engine/Maths/Matrix.inl"

#endif