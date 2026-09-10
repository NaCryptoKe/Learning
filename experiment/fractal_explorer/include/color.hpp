#ifndef FRACTAL_COLOR_HPP
#define FRACTAL_COLOR_HPP

#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numbers>
#include <span>

namespace fractal {

/// A 24-bit RGB color.
/// Showcases: constexpr, trivial type, structured bindings-friendly.
struct alignas(4) Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    constexpr Color() noexcept = default;
    constexpr Color(uint8_t r_, uint8_t g_, uint8_t b_) noexcept
        : r(r_), g(g_), b(b_) {}

    // Linear interpolation between two colors
    [[nodiscard]] static constexpr Color lerp(const Color& a, const Color& b,
                                              float t) noexcept {
        auto lerp_u8 = [](uint8_t x, uint8_t y, float t) -> uint8_t {
            return static_cast<uint8_t>(std::lerp(static_cast<float>(x),
                                                  static_cast<float>(y), t));
        };
        return {lerp_u8(a.r, b.r, t),
                lerp_u8(a.g, b.g, t),
                lerp_u8(a.b, b.b, t)};
    }

    [[nodiscard]] constexpr uint32_t pack() const noexcept {
        return (static_cast<uint32_t>(r) << 16) |
               (static_cast<uint32_t>(g) << 8) |
               (static_cast<uint32_t>(b));
    }
};

/// A multi-stop color gradient palette.
/// Showcases: RAII, move semantics, std::span.
class Palette {
public:
    Palette() = default;

    // Construct from a list of (position, color) stops
    Palette(std::initializer_list<std::pair<float, Color>> stops);

    // Move support
    Palette(Palette&&) noexcept = default;
    Palette& operator=(Palette&&) noexcept = default;

    // Sample the palette at t in [0, 1], returns a color
    [[nodiscard]] Color sample(float t) const noexcept;

    // Access to raw stops
    [[nodiscard]] std::span<const std::pair<float, Color>> stops() const noexcept {
        return stops_;
    }

    // Some preset palettes
    [[nodiscard]] static Palette fire();
    [[nodiscard]] static Palette ocean();
    [[nodiscard]] static Palette neon();
    [[nodiscard]] static Palette spectral();
    [[nodiscard]] static Palette monochrome();

private:
    std::vector<std::pair<float, Color>> stops_;
};

/// Smooth-iteration → color mapping for fractals.
/// Showcases: strategy pattern via callbacks.
template <typename T>
class FractalColorizer {
public:
    using ColorFunc = Color (*)(T iteration, T max_iter, const Palette&);

    static Color smooth_linear(T iter, T max_iter, const Palette& pal) {
        if (iter >= max_iter) return Color{0, 0, 0};
        const float t = std::clamp(iter / max_iter, T{0}, T{1});
        return pal.sample(t);
    }

    static Color smooth_log(T iter, T max_iter, const Palette& pal) {
        if (iter >= max_iter) return Color{0, 0, 0};
        // Continuous (smooth) coloring
        float t = std::log2(1.0f + static_cast<float>(iter)) /
                  std::log2(1.0f + static_cast<float>(max_iter));
        t = std::clamp(t, 0.0f, 1.0f);
        return pal.sample(t);
    }

    static Color smooth_sine(T iter, T max_iter, const Palette& pal) {
        if (iter >= max_iter) return Color{0, 0, 0};
        float t = std::sin(static_cast<float>(iter) * 0.1f) * 0.5f + 0.5f;
        t = std::clamp(t, 0.0f, 1.0f);
        return pal.sample(t);
    }
};

} // namespace fractal

#endif // FRACTAL_COLOR_HPP