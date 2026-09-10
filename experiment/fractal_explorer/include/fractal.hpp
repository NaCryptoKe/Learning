#ifndef FRACTAL_FRACTAL_HPP
#define FRACTAL_FRACTAL_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <complex>  // Only for seeding types in public API

#include "complex.hpp"

namespace fractal {

/// Specifies the region of the complex plane to render.
struct Viewport {
    double center_x = -0.5;
    double center_y = 0.0;
    double zoom = 1.0;         // 1.0 = default, >1 = zoomed in
    double aspect_ratio = 1.0; // width / height
};

/// Parameters that define a fractal render job.
struct FractalParams {
    Viewport view;
    size_t max_iterations = 256;
    size_t width = 1920;
    size_t height = 1080;
};

/// ============================================================
///  Mandelbrot set iterator
/// ============================================================
///
/// Iterates z_{n+1} = z_n^2 + c, starting from z_0 = 0.
/// Returns the number of iterations before |z| > 2, up to max_iter.

[[nodiscard]] inline float mandelbrot_iteration(ComplexD c,
                                                size_t max_iter) noexcept {
    double z_re = 0.0, z_im = 0.0;
    const double c_re = c.real(), c_im = c.imag();

    for (size_t i = 0; i < max_iter; ++i) {
        // Early bail — cardioid / period-2 bulb detection
        // (optimisation: skip iteration for points definitely inside)
        if (i == 0) {
            const double p = std::hypot(c_re - 0.25, c_im);
            if (c_re < p - 2.0 * p * p + 0.25) return static_cast<float>(max_iter);
            if ((c_re + 1.0) * (c_re + 1.0) + c_im * c_im < 0.0625) return static_cast<float>(max_iter);
        }

        double z_re2 = z_re * z_re;
        double z_im2 = z_im * z_im;
        if (z_re2 + z_im2 >= 4.0) {
            // Smooth iteration count
            return static_cast<float>(i) + 1.0f - std::log2(std::log2(std::sqrt(z_re2 + z_im2)));
        }
        z_im = 2.0 * z_re * z_im + c_im;
        z_re = z_re2 - z_im2 + c_re;
    }
    return static_cast<float>(max_iter);
}

/// ============================================================
///  Julia set iterator
/// ============================================================
///
/// Iterates z_{n+1} = z_n^2 + c for a fixed c and varying z_0.

[[nodiscard]] inline float julia_iteration(ComplexD z,
                                           ComplexD c,
                                           size_t max_iter) noexcept {
    double z_re = z.real(), z_im = z.imag();
    const double c_re = c.real(), c_im = c.imag();

    for (size_t i = 0; i < max_iter; ++i) {
        double z_re2 = z_re * z_re;
        double z_im2 = z_im * z_im;
        if (z_re2 + z_im2 >= 4.0) {
            return static_cast<float>(i) + 1.0f - std::log2(std::log2(std::sqrt(z_re2 + z_im2)));
        }
        z_im = 2.0 * z_re * z_im + c_im;
        z_re = z_re2 - z_im2 + c_re;
    }
    return static_cast<float>(max_iter);
}

// ============================================================
//  Callback-based pixel calculation
// ============================================================

/// Signature: (double cx, double cy) -> normalized_iteration in [0,1]
using PixelFunc = std::function<float(double, double)>;

/// Build a pixel function from Mandelbrot parameters.
[[nodiscard]] PixelFunc make_mandelbrot_func(const FractalParams& params);

/// Build a pixel function from Julia parameters (c is the Julia constant).
[[nodiscard]] PixelFunc make_julia_func(const FractalParams& params,
                                        ComplexD julia_c);

/// Convert pixel coordinates to complex-plane coordinates.
[[nodiscard]] inline ComplexD pixel_to_complex(size_t px, size_t py,
                                                const FractalParams& params) {
    const double w = static_cast<double>(params.width);
    const double h = static_cast<double>(params.height);
    const double scale = 4.0 / (w * params.view.zoom);

    const double cx = (static_cast<double>(px) - w / 2.0) * scale + params.view.center_x;
    const double cy = (static_cast<double>(py) - h / 2.0) * scale + params.view.center_y;
    return {cx, cy};
}

} // namespace fractal

#endif // FRACTAL_FRACTAL_HPP