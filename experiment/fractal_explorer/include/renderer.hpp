#ifndef FRACTAL_RENDERER_HPP
#define FRACTAL_RENDERER_HPP

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <thread>
#include <vector>

#include "image.hpp"
#include "color.hpp"
#include "fractal.hpp"

namespace fractal {

/// Multi-threaded fractal renderer.
/// Showcases: thread pools (via std::async), atomic progress,
///            move semantics, RAII, timing utilities.
class Renderer {
public:
    explicit Renderer(size_t num_threads = 0);

    // No copy, move allowed
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) noexcept = default;
    Renderer& operator=(Renderer&&) noexcept = default;

    /// Render a fractal into a Color image.
    /// @param pixel_func  Callback that maps (cx,cy) -> iteration float
    /// @param params      Image dimensions and viewport
    /// @param palette     Color gradient
    /// @param colorizer   Function: (iter, max_iter, palette) -> Color
    /// @param on_progress Optional progress callback (called from multiple threads)
    /// @return            The rendered image
    Image<Color> render(
        const PixelFunc& pixel_func,
        const FractalParams& params,
        const Palette& palette,
        std::function<Color(float, float, const Palette&)> colorizer =
            FractalColorizer<float>::smooth_log,
        std::function<void(float)> on_progress = nullptr
    ) const;

    /// Render and save to PPM in one call.  Returns render time in ms.
    double render_to_file(
        const PixelFunc& pixel_func,
        const FractalParams& params,
        const Palette& palette,
        const std::filesystem::path& output_path,
        std::function<Color(float, float, const Palette&)> colorizer =
            FractalColorizer<float>::smooth_log
    ) const;

    /// Returns number of threads used.
    [[nodiscard]] size_t thread_count() const noexcept { return num_threads_; }

private:
    size_t num_threads_;
};

/// Utility: render a zoom animation sequence
void render_zoom_sequence(
    const char* output_dir,
    const FractalParams& base_params,
    const Palette& palette,
    size_t frames = 30,
    double zoom_factor = 0.85,  // multiply zoom by this each frame
    size_t num_threads = 0
);

} // namespace fractal

#endif // FRACTAL_RENDERER_HPP