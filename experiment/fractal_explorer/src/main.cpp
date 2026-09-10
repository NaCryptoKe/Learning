#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string_view>

#include "color.hpp"
#include "complex.hpp"
#include "fractal.hpp"
#include "image.hpp"
#include "renderer.hpp"

using namespace fractal;
namespace fs = std::filesystem;

// ============================================================
//  Demonstration of all features
// ============================================================

static void print_banner() {
    std::cout << R"(
 ╔══════════════════════════════════════════════╗
 ║       Fractal Explorer  v1.0                 ║
 ║       C++20  ·  Multi-Threaded               ║
 ║       Mandelbrot & Julia Sets                ║
 ╚══════════════════════════════════════════════╝
)" << '\n';
}

static void print_complex_demo() {
    std::cout << "─── Complex Number Demo ───\n";
    ComplexD z1{3.0, 4.0};
    ComplexD z2{1.0, -2.0};
    std::cout << "z1 = " << z1 << "\n";
    std::cout << "z2 = " << z2 << "\n";
    std::cout << "|z1| = " << z1.magnitude() << "\n";
    std::cout << "|z2| = " << z2.magnitude() << "\n";
    std::cout << "z1 + z2 = " << (z1 + z2) << "\n";
    std::cout << "z1 * z2 = " << (z1 * z2) << "\n";
    std::cout << "z1^2    = " << z1.squared() << "\n\n";
}

static void print_palette_demo() {
    std::cout << "─── Palette Demo (sampling at 0.0, 0.25, 0.5, 0.75, 1.0) ───\n";
    auto palettes = std::initializer_list<std::pair<std::string_view, Palette>>{
        {"Fire",      Palette::fire()},
        {"Ocean",     Palette::ocean()},
        {"Neon",      Palette::neon()},
        {"Spectral",  Palette::spectral()},
        {"Monochrome",Palette::monochrome()},
    };

    for (const auto& [name, pal] : palettes) {
        std::cout << "  " << std::setw(12) << name << " : ";
        for (float t = 0.0f; t <= 1.01f; t += 0.25f) {
            auto c = pal.sample(t);
            std::cout << "\x1b[48;2;" << static_cast<int>(c.r) << ";"
                      << static_cast<int>(c.g) << ";"
                      << static_cast<int>(c.b) << "m  \x1b[0m";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

static void render_mandelbrot_samples() {
    std::cout << "─── Rendering Mandelbrot Samples ───\n";
    fs::create_directories("outputs");
    constexpr size_t W = 1920, H = 1080;
    constexpr size_t MAX_ITER = 512;
    Renderer renderer;

    FractalParams full_view{
        .view = {.center_x = -0.5, .center_y = 0.0, .zoom = 1.0},
        .max_iterations = MAX_ITER, .width = W, .height = H
    };
    auto mandelbrot = make_mandelbrot_func(full_view);
    renderer.render_to_file(mandelbrot, full_view, Palette::fire(),    "outputs/mandelbrot_fire.png");
    renderer.render_to_file(mandelbrot, full_view, Palette::ocean(),   "outputs/mandelbrot_ocean.png");
    renderer.render_to_file(mandelbrot, full_view, Palette::neon(),    "outputs/mandelbrot_neon.png");

    FractalParams zoomed{
        .view = {.center_x = -0.7453, .center_y = 0.1127, .zoom = 50.0},
        .max_iterations = 1024, .width = W, .height = H
    };
    renderer.render_to_file(make_mandelbrot_func(zoomed), zoomed, Palette::spectral(),
                            "outputs/mandelbrot_seahorse.png");

    FractalParams deep{
        .view = {.center_x = -1.7499, .center_y = 0.0000, .zoom = 200.0},
        .max_iterations = 2048, .width = W, .height = H
    };
    renderer.render_to_file(make_mandelbrot_func(deep), deep, Palette::neon(),
                            "outputs/mandelbrot_deep.png");
    std::cout << "\n";
}

static void render_julia_samples() {
    std::cout << "─── Rendering Julia Set Samples ───\n";
    constexpr size_t W = 1920, H = 1080;
    constexpr size_t MAX_ITER = 256;
    Renderer renderer;

    FractalParams params{
        .view = {.center_x = 0.0, .center_y = 0.0, .zoom = 1.0,
                 .aspect_ratio = static_cast<double>(W) / H},
        .max_iterations = MAX_ITER, .width = W, .height = H
    };

    renderer.render_to_file(make_julia_func(params, ComplexD{-0.7, 0.27015}), params, Palette::fire(),   "outputs/julia_dendrite.png");
    renderer.render_to_file(make_julia_func(params, ComplexD{-0.8, 0.156}),   params, Palette::ocean(),  "outputs/julia_spiral.png");
    renderer.render_to_file(make_julia_func(params, ComplexD{0.285, 0.01}),   params, Palette::neon(),   "outputs/julia_cloud.png");
    std::cout << "\n";
}

static void run_perf_benchmark() {
    std::cout << "─── Performance Benchmark ───\n";
    constexpr size_t W = 3840, H = 2160;
    constexpr size_t MAX_ITER = 256;

    FractalParams params{
        .view = {.center_x = -0.5, .center_y = 0.0, .zoom = 1.0},
        .max_iterations = MAX_ITER, .width = W, .height = H
    };
    auto func = make_mandelbrot_func(params);
    auto palette = Palette::fire();

    std::vector<size_t> thread_counts = {1, 2, 4, 8, 16, 0};

    for (size_t tc : thread_counts) {
        Renderer r(tc);
        size_t actual = r.thread_count();
        auto t0 = std::chrono::steady_clock::now();
        auto img = r.render(func, params, palette, FractalColorizer<float>::smooth_log);
        auto t1 = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
        std::cout << "  " << std::setw(2) << actual << " thread"
                  << (actual == 1 ? " " : "s")
                  << " \u2192 " << ms.count() << " ms  ("
                  << (ms.count() > 0 ? std::to_string(W * H / ms.count() / 1000) : "?")
                  << " Mpx/s)\n";
    }
    std::cout << "\n";
}

// ============================================================
//  main
// ============================================================

int main() {
    print_banner();
    print_complex_demo();
    print_palette_demo();

    auto t_start = std::chrono::steady_clock::now();

    render_mandelbrot_samples();
    render_julia_samples();
    run_perf_benchmark();

    std::cout << "─── Zoom Animation (5 frames preview) ───\n";
    FractalParams anim_base{
        .view = {.center_x = -0.7453, .center_y = 0.1127, .zoom = 1.0},
        .max_iterations = 512, .width = 1280, .height = 720
    };
    render_zoom_sequence("outputs/zoom_seq", anim_base,
                         Palette::spectral(), 5, 0.7, 0);

    auto t_end = std::chrono::steady_clock::now();
    auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
    std::cout << "\n\u2554\u2550\u2550\u2550 All done! Total time: " << total_ms << " ms ("
              << (total_ms / 1000.0) << " s) \u2550\u2550\u2550\u2557\n";

    std::cout << "\nOutput files:\n";
    for (const auto& entry : fs::directory_iterator("outputs")) {
        if (entry.is_regular_file()) {
            auto sz = entry.file_size();
            std::cout << "  " << entry.path().filename().string() << "  (" << (sz / 1024) << " KB)\n";
        }
    }

    return EXIT_SUCCESS;
}