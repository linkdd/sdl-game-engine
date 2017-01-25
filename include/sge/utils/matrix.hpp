#ifndef __SGE_MATRIX_HPP
#define __SGE_MATRIX_HPP

#include <initializer_list>
#include <vector>

namespace sge
{
    template <int ROWS, int COLS>
    class Matrix
    {
        private:
            float coefs[ROWS][COLS];

        public:
            Matrix()
            {
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = (i == j ? 1 : 0);
                    }
                }
            }

            Matrix(float a[ROWS][COLS])
            {
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = a[i][j];
                    }
                }
            }

            Matrix(std::vector<std::vector<float>> a)
            {
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = a[i][j];
                    }
                }
            }

            Matrix(std::initializer_list<std::vector<float>> a)
            {
                std::vector<std::vector<float>> c = a;

                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = c[i][j];
                    }
                }
            }

            Matrix(const Matrix<ROWS,COLS> &m)
            {
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = m(i, j);
                    }
                }
            }

            Matrix<ROWS,COLS> &operator=(float a[ROWS][COLS])
            {
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = a[i][j];
                    }
                }

                return *this;
            }

            Matrix<ROWS,COLS> &operator=(std::vector<std::vector<float>> a)
            {
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = a[i][j];
                    }
                }

                return *this;
            }

            Matrix<ROWS,COLS> &operator=(std::initializer_list<std::vector<float>> a)
            {
                std::vector<std::vector<float>> c = a;

                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = c[i][j];
                    }
                }

                return *this;
            }

            Matrix<ROWS,COLS> &operator=(const Matrix<ROWS,COLS> &m)
            {
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        coefs[i][j] = m(i, j);
                    }
                }

                return *this;
            }

            float &operator()(int row, int col)
            {
                return coefs[row][col];
            }

            const float &operator()(int row, int col) const
            {
                return coefs[row][col];
            }

            Matrix<COLS,ROWS> transpose() const
            {
                Matrix<COLS,ROWS> result;

                for (int i = 0; i < COLS; i++)
                {
                    for (int j = 0; j < ROWS; j++)
                    {
                        result(i, j) = coefs[j][i];
                    }
                }

                return result;
            }

            template <int BROWS, int BCOLS>
            Matrix<ROWS,COLS> operator+(const Matrix<BROWS,BCOLS> &m) const
            {
                static_assert((ROWS == BROWS) && (COLS == BCOLS), "Invalid matrix size");
                Matrix<ROWS,COLS> result;

                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        result(i, j) = coefs[i][j] + m(i, j);
                    }
                }

                return result;
            }

            template <int BROWS, int BCOLS>
            Matrix<ROWS,COLS> operator-(const Matrix<BROWS,BCOLS> &m) const
            {
                static_assert((ROWS == BROWS) && (COLS == BCOLS), "Invalid matrix size");
                Matrix<ROWS,COLS> result;

                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        result(i, j) = coefs[i][j] - m(i, j);
                    }
                }

                return result;
            }

            template <int BROWS, int BCOLS>
            Matrix<ROWS,BCOLS> operator*(const Matrix<BROWS, BCOLS> &m) const
            {
                static_assert((COLS == BROWS), "Invalid matrix size");
                Matrix<ROWS,BCOLS> result;

                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < BCOLS; j++)
                    {
                        result(i, j) = 0;

                        for (int k = 0; k < COLS; k++)
                        {
                            result(i, j) += coefs[i][k] * m(k, j);
                        }
                    }
                }

                return result;
            }

            Matrix operator*(float f) const
            {
                Matrix<ROWS,COLS> result;

                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        result(i, j) = coefs[i][j] * f;
                    }
                }

                return result;
            }

            Matrix operator/(float f) const
            {
                Matrix<ROWS,COLS> result;

                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        result(i, j) = coefs[i][j] / f;
                    }
                }

                return result;
            }

            template <int BROWS, int BCOLS>
            bool operator==(const Matrix<BROWS, BCOLS> &m) const
            {
                if (ROWS == BROWS && COLS == BCOLS)
                {
                    for (int i = 0; i < ROWS; i++)
                    {
                        for (int j = 0; j < COLS; j++)
                        {
                            if (coefs[i][j] != m(i, j))
                            {
                                return false;
                            }
                        }
                    }

                    return true;
                }

                return false;
            }

            template <int BROWS, int BCOLS>
            bool operator!=(const Matrix<BROWS, BCOLS> &m) const
            {
                return !(*this == m);
            }
    };

    template <int ROWS, int COLS>
    Matrix<ROWS, COLS> operator*(int i, const Matrix<ROWS, COLS> &m)
    {
        return m * i;
    }

    template <int ROWS, int COLS>
    Matrix<ROWS, COLS> operator*(float f, const Matrix<ROWS, COLS> &m)
    {
        return m * f;
    }

    template <int ROWS, int COLS>
    Matrix<ROWS, COLS> operator-(const Matrix<ROWS, COLS> &m)
    {
        return -1 * m;
    }
}

#endif /* __SGE_MATRIX_HPP */