#include "renderer.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace fractal {

// -----------------------------------------------------------------------
// Renderer
// -----------------------------------------------------------------------

Renderer::Renderer(size_t num_threads) {
    if (num_threads == 0) {
        num_threads_ = std::thread::hardware_concurrency();
        if (num_threads_ == 0) num_threads_ = 4;
    } else {
        num_threads_ = num_threads;
    }
}

Image<Color> Renderer::render(
    const PixelFunc& pixel_func,
    const FractalParams& params,
    const Palette& palette,
    std::function<Color(float, float, const Palette&)> colorizer,
    std::function<void(float)> on_progress
) const
{
    Image<Color> image(params.width, params.height);

    const size_t total_pixels = image.size();
    std::atomic<size_t> pixels_done{0};

    // Determine rows per chunk
    const size_t rows_per_chunk = std::max<size_t>(
        1, params.height / num_threads_ / 4);  // 4x over-subscription
    const size_t num_chunks =
        (params.height + rows_per_chunk - 1) / rows_per_chunk;

    // Launch async tasks — each processes a horizontal strip
    std::vector<std::future<void>> futures;
    futures.reserve(num_chunks);

    for (size_t chunk = 0; chunk < num_chunks; ++chunk) {
        const size_t y_start = chunk * rows_per_chunk;
        const size_t y_end = std::min(y_start + rows_per_chunk, params.height);

        futures.push_back(std::async(std::launch::async, [&, y_start, y_end]() {
            for (size_t y = y_start; y < y_end; ++y) {
                Color* row = image.row(y);
                for (size_t x = 0; x < params.width; ++x) {
                    const auto pt = pixel_to_complex(x, y, params);
                    const float iter = pixel_func(pt.real(), pt.imag());
                    row[x] = colorizer(iter,
                                       static_cast<float>(params.max_iterations),
                                       palette);
                }
                // Atomic progress update
                size_t done = pixels_done.fetch_add(params.width,
                                                    std::memory_order_relaxed);
                if (on_progress) {
                    float pct = 100.0f * static_cast<float>(done + params.width) /
                                static_cast<float>(total_pixels);
                    if (static_cast<int>(pct * 10) !=
                        static_cast<int>((pct - 100.0f / total_pixels) * 10)) {
                        on_progress(pct);
                    }
                }
            }
        }));
    }

    // Wait for all tasks
    for (auto& f : futures) {
        f.get();
    }

    return image;
}

double Renderer::render_to_file(
    const PixelFunc& pixel_func,
    const FractalParams& params,
    const Palette& palette,
    const std::filesystem::path& output_path,
    std::function<Color(float, float, const Palette&)> colorizer
) const
{
    auto t0 = std::chrono::steady_clock::now();

    auto progress = [](float pct) {
        std::cout << "\r  Rendering... " << std::fixed << std::setprecision(1)
                  << pct << "%" << std::flush;
    };

    Image<Color> img = render(pixel_func, params, palette, colorizer, progress);
    std::cout << "\r  Rendering... 100.0%" << std::endl;

    // Write PNG
    write_png(img, output_path);
    auto t1 = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);

    std::cout << "  Saved: " << output_path.filename().string()
              << "  [" << params.width << "x" << params.height
              << ", " << ms.count() << " ms, "
              << num_threads_ << " threads]" << std::endl;

    return static_cast<double>(ms.count());
}

// -----------------------------------------------------------------------
// Zoom sequence
// -----------------------------------------------------------------------

void render_zoom_sequence(
    const char* output_dir,
    const FractalParams& base_params,
    const Palette& palette,
    size_t frames,
    double zoom_factor,
    size_t num_threads)
{
    namespace fs = std::filesystem;
    fs::create_directories(output_dir);

    Renderer renderer(num_threads);
    auto colorizer = FractalColorizer<float>::smooth_log;
    auto pixel_func = make_mandelbrot_func(base_params);

    FractalParams params = base_params;

    std::cout << "\n=== Zoom Animation ===\n"
              << "Frames: " << frames << "\n"
              << "Output: " << output_dir << "/\n"
              << "Zoom factor per frame: " << zoom_factor << "\n\n";

    for (size_t frame = 0; frame < frames; ++frame) {
        std::ostringstream oss;
        oss << output_dir << "/frame_" << std::setw(4) << std::setfill('0')
            << frame << ".png";

        std::cout << "Frame " << (frame + 1) << "/" << frames << "\n";
        renderer.render_to_file(
            pixel_func, params, palette, oss.str(), colorizer);

        // Zoom in
        params.view.zoom /= zoom_factor;
    }

    std::cout << "\nDone! " << frames << " frames rendered to " << output_dir
              << "/\n";
}

} // namespace fractal