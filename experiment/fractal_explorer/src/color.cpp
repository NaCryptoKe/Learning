#include "color.hpp"

namespace fractal {

Palette::Palette(std::initializer_list<std::pair<float, Color>> stops)
    : stops_(stops)
{
    // Ensure stops are sorted by position
    std::sort(stops_.begin(), stops_.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });
}

Color Palette::sample(float t) const noexcept {
    if (stops_.empty()) return Color{255, 255, 255};
    if (stops_.size() == 1) return stops_.front().second;

    // Clamp to [0, 1]
    t = std::clamp(t, 0.0f, 1.0f);

    // Find the two surrounding stops
    auto it = std::upper_bound(stops_.begin(), stops_.end(), t,
                                [](float val, const auto& stop) {
                                    return val < stop.first;
                                });

    if (it == stops_.begin()) return stops_.front().second;
    if (it == stops_.end())   return stops_.back().second;

    const auto& [pos_a, color_a] = *(it - 1);
    const auto& [pos_b, color_b] = *it;

    const float local_t = (t - pos_a) / (pos_b - pos_a);
    return Color::lerp(color_a, color_b, local_t);
}

// ---- Preset palettes ----

Palette Palette::fire() {
    return Palette{
        {0.00f, Color{  0,   0,   0}},
        {0.16f, Color{ 30,   0,   0}},
        {0.33f, Color{120,   0,   0}},
        {0.50f, Color{255,  60,   0}},
        {0.66f, Color{255, 160,   0}},
        {0.83f, Color{255, 220,  80}},
        {1.00f, Color{255, 255, 200}},
    };
}

Palette Palette::ocean() {
    return Palette{
        {0.00f, Color{  0,   0,  20}},
        {0.25f, Color{  0,  20,  80}},
        {0.50f, Color{  0,  80, 180}},
        {0.75f, Color{ 20, 160, 220}},
        {1.00f, Color{180, 230, 255}},
    };
}

Palette Palette::neon() {
    return Palette{
        {0.00f, Color{ 20,   0,  30}},
        {0.20f, Color{100,   0, 120}},
        {0.40f, Color{  0, 180, 200}},
        {0.60f, Color{  0, 255,  60}},
        {0.80f, Color{255, 230,   0}},
        {1.00f, Color{255, 255, 255}},
    };
}

Palette Palette::spectral() {
    return Palette{
        {0.00f, Color{  0,   0,   0}},
        {0.17f, Color{ 30,   7, 100}},
        {0.33f, Color{ 20,  80, 200}},
        {0.50f, Color{ 60, 180,  80}},
        {0.66f, Color{200, 200,  30}},
        {0.83f, Color{220,  80,  20}},
        {1.00f, Color{150,  20,  10}},
    };
}

Palette Palette::monochrome() {
    return Palette{
        {0.00f, Color{  0,   0,   0}},
        {0.50f, Color{100, 100, 100}},
        {1.00f, Color{255, 255, 255}},
    };
}

} // namespace fractal