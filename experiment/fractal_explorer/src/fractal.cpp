#include "fractal.hpp"

namespace fractal {

PixelFunc make_mandelbrot_func(const FractalParams& params) {
    const size_t max_iters = params.max_iterations;
    return [max_iters](double cx, double cy) -> float {
        return mandelbrot_iteration({cx, cy}, max_iters);
    };
}

PixelFunc make_julia_func(const FractalParams& params, ComplexD julia_c) {
    const size_t max_iters = params.max_iterations;
    const double jc_re = julia_c.real();
    const double jc_im = julia_c.imag();
    return [max_iters, jc_re, jc_im](double zx, double zy) -> float {
        return julia_iteration({zx, zy}, {jc_re, jc_im}, max_iters);
    };
}

} // namespace fractal