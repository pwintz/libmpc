/*
 *   Copyright (c) 2023 Nicola Piccinelli
 *   All rights reserved.
 */
#pragma once
#include <mpc/Types.hpp>

namespace mpc
{
    class Size
    {
    public:
        constexpr Size(const int value) : value(value) {}
        constexpr Size(const Size &s) : value(s.value){};

        /**
         * @brief Sum two dimensions, in case of static or dynamic allocation
         * it automatically propagates the right object
         *
         * @tparam W static dimension of the other operand
         * @return constexpr auto instance of the result dimension
         */
        constexpr Size operator+(const Size &v) const
        {
            return Size(make_dimension(value + v.value, is_static(value, v.value)));
        }

        constexpr Size operator+(const int &v) const
        {
            return Size(make_dimension(value + v, is_static(value, v)));
        }

        /**
         * @brief Subtract two dimensions, in case of static or dynamic allocation
         * it automatically propagates the right object
         *
         * @tparam W static dimension of the other operand
         * @return constexpr auto instance of the result dimension
         */
        constexpr Size operator-(const Size &v) const
        {
            return Size(make_dimension(value - v.value, is_static(value, v.value)));
        }

        constexpr Size operator-(const int &v) const
        {
            return Size(make_dimension(value - v, is_static(value, v)));
        }

        /**
         * @brief Multiply two dimensions, in case of static or dynamic allocation
         * it automatically propagates the right object
         *
         * @tparam W static dimension of the other operand
         * @return constexpr auto instance of the result dimension
         */
        constexpr Size operator*(const Size &v) const
        {
            return Size(make_dimension(value * v.value, is_static(value, v.value)));
        }

        constexpr Size operator*(const int &v) const
        {
            return Size(make_dimension(value * v, is_static(value, v)));
        }

        /**
         * @brief Override the int typecasting to provide the template argument
         * automatically during assigments
         *
         * @return int the template class argument
         */
        constexpr operator int() const { return value; }

        const int value;

        /**
         * @brief Check whenever the operator should create a static
         * or dynamic dimension object instance
         *
         * @tparam A first dimension
         * @tparam B second dimension
         * @return true
         * @return false
         */
        constexpr static bool is_static(const int A, const int B)
        {
            return A > Eigen::Dynamic && B > Eigen::Dynamic;
        }
    };

    constexpr Size operator+(const int &v, const Size &w)
    {
        return Size(make_dimension(w.value + v, Size::is_static(w.value, v)));
    }

    constexpr Size operator-(const int &v, const Size &w)
    {
        return Size(make_dimension(w.value - v, Size::is_static(w.value, v)));
    }

    constexpr Size operator*(const int &v, const Size &w)
    {
        return Size(make_dimension(w.value * v, Size::is_static(w.value, v)));
    }

    struct MPCSize
    {
        constexpr MPCSize(const int nx,  // Dimension of state
                          const int nu,  // Dimension of input
                          const int ndu, // Dimension of disturbance
                          const int ny,  // Dimension of output
                          const int ph,  // Prediction horizon
                          const int ch,  // Control horizon
                          const int ineq,// Number of inequality constraints
                          const int eq   // Number of equality constraints
                                      ) : nx(nx), nu(nu),
                                          ndu(ndu),
                                          ny(ny),
                                          ph(ph),
                                          ch(ch),
                                          ineq(ineq),
                                          eq(eq) {}

        Size nx;  // Dimension of state
        Size nu;  // Dimension of input
        Size ndu; // Dimension of disturbance
        Size ny;  // Dimension of output
        Size ph;  // Prediction horizon
        Size ch;  // Control horizon
        Size ineq;// Number of inequality constraints
        Size eq;  // Number of equality constraints
    };

} // namespace mpc