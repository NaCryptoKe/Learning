#ifndef FRACTAL_IMAGE_HPP
#define FRACTAL_IMAGE_HPP

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

#include <zlib.h>

#include "color.hpp"

namespace fractal {

/// A 2D raster image of pixels of type T.
/// Showcases: templates, RAII, move semantics, contiguous memory.
template <typename T>
class Image {
public:
    using value_type = T;

    Image() noexcept : width_(0), height_(0) {}

    Image(size_t width, size_t height)
        : width_(width), height_(height)
        , pixels_(width * height)
    {}

    // Move semantics
    Image(Image&&) noexcept = default;
    Image& operator=(Image&&) noexcept = default;

    // No copy — images are large; use move or clone
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    // Dimensions
    [[nodiscard]] size_t width() const noexcept { return width_; }
    [[nodiscard]] size_t height() const noexcept { return height_; }
    [[nodiscard]] size_t size() const noexcept { return pixels_.size(); }

    // Pixel access (bounds-checked in debug; at() free in release)
    T& at(size_t x, size_t y) {
        if (x >= width_ || y >= height_)
            throw std::out_of_range("Image::at: (" + std::to_string(x) + "," +
                                    std::to_string(y) + ") out of bounds");
        return pixels_[y * width_ + x];
    }

    const T& at(size_t x, size_t y) const {
        if (x >= width_ || y >= height_)
            throw std::out_of_range("Image::at: (" + std::to_string(x) + "," +
                                    std::to_string(y) + ") out of bounds");
        return pixels_[y * width_ + x];
    }

    // Unsafe direct row pointer for performance
    [[nodiscard]] T* row(size_t y) noexcept {
        return pixels_.data() + y * width_;
    }
    [[nodiscard]] const T* row(size_t y) const noexcept {
        return pixels_.data() + y * width_;
    }

    // Raw data span
    [[nodiscard]] std::span<T> data_span() noexcept { return pixels_; }
    [[nodiscard]] std::span<const T> data_span() const noexcept { return pixels_; }

    // Fill entire image with a value
    void fill(const T& value) noexcept {
        std::fill(pixels_.begin(), pixels_.end(), value);
    }

private:
    size_t width_, height_;
    std::vector<T> pixels_;
};

/// ============================================================
///  PPM writer (specialized for Color / 24-bit RGB)
/// ============================================================

namespace detail {

template <typename T>
struct PPMTraits {};

template <>
struct PPMTraits<Color> {
    static constexpr const char* magic = "P6";
    static constexpr size_t bytes_per_pixel = 3;
};

} // namespace detail

/// Write an Image<Color> to a PPM P6 binary file.
/// Demonstrates: template specialization, RAII file handling.
inline void write_ppm(const Image<Color>& img,
                      const std::filesystem::path& path) {
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs)
        throw std::runtime_error("Cannot open " + path.string());

    // Header
    ofs << "P6\n"
        << img.width() << ' ' << img.height() << '\n'
        << 255 << '\n';

    // Pixel data — contiguous RGB triplets
    for (size_t y = 0; y < img.height(); ++y) {
        std::span<const Color> row(img.row(y), img.width());
        for (const auto& c : row) {
            ofs.put(static_cast<char>(c.r));
            ofs.put(static_cast<char>(c.g));
            ofs.put(static_cast<char>(c.b));
        }
    }
}

/// Write an Image<Color> to a PNG file using zlib compression.
void write_png(const Image<Color>& img, const std::filesystem::path& path);

} // namespace fractal

#endif // FRACTAL_IMAGE_HPP