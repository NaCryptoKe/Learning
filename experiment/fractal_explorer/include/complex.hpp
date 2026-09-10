#ifndef FRACTAL_COMPLEX_HPP
#define FRACTAL_COMPLEX_HPP

#include <cmath>
#include <concepts>
#include <ostream>

namespace fractal {

/// A compile-time complex number abstraction over any floating-point type.
/// Showcases: templates, concepts, operator overloading, constexpr.
template <std::floating_point T>
class Complex {
public:
    constexpr Complex() noexcept : re_(0), im_(0) {}
    constexpr Complex(T re, T im) noexcept : re_(re), im_(im) {}

    // Accessors
    [[nodiscard]] constexpr T real() const noexcept { return re_; }
    [[nodiscard]] constexpr T imag() const noexcept { return im_; }
    constexpr void real(T v) noexcept { re_ = v; }
    constexpr void imag(T v) noexcept { im_ = v; }

    // Magnitude squared — avoids sqrt for escape checks
    [[nodiscard]] constexpr T norm_sq() const noexcept {
        return re_ * re_ + im_ * im_;
    }

    [[nodiscard]] T magnitude() const noexcept {
        return std::sqrt(norm_sq());
    }

    // Arithmetic operators (member)
    constexpr Complex& operator+=(const Complex& rhs) noexcept {
        re_ += rhs.re_;
        im_ += rhs.im_;
        return *this;
    }

    constexpr Complex& operator*=(const Complex& rhs) noexcept {
        T new_re = re_ * rhs.re_ - im_ * rhs.im_;
        T new_im = re_ * rhs.im_ + im_ * rhs.re_;
        re_ = new_re;
        im_ = new_im;
        return *this;
    }

    // Square: z = z*z + c optimization
    constexpr Complex& square() noexcept {
        T new_re = re_ * re_ - im_ * im_;
        im_ = T{2} * re_ * im_;
        re_ = new_re;
        return *this;
    }

    constexpr Complex squared() const noexcept {
        return Complex(re_ * re_ - im_ * im_, T{2} * re_ * im_);
    }

    constexpr Complex operator+(const Complex& rhs) const noexcept {
        return Complex(re_ + rhs.re_, im_ + rhs.im_);
    }

    constexpr Complex operator*(const Complex& rhs) const noexcept {
        return Complex(re_ * rhs.re_ - im_ * rhs.im_,
                       re_ * rhs.im_ + im_ * rhs.re_);
    }

    // Comparison
    [[nodiscard]] constexpr bool operator==(const Complex&) const noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Complex& z) {
        os << "(" << z.re_ << ", " << z.im_ << ")";
        return os;
    }

private:
    T re_, im_;
};

// Type aliases for convenience
using ComplexF = Complex<float>;
using ComplexD = Complex<double>;

} // namespace fractal

#endif // FRACTAL_COMPLEX_HPP