#include "image.hpp"

#include <array>
#include <cstring>
#include <vector>

namespace fractal {

// Explicit instantiation for Color
template class Image<Color>;

// -----------------------------------------------------------------------
//  PNG writer helpers
// -----------------------------------------------------------------------

namespace {

// Big-endian write helpers
void write_be32(std::ofstream& os, uint32_t val) {
    os.put(static_cast<char>((val >> 24) & 0xff));
    os.put(static_cast<char>((val >> 16) & 0xff));
    os.put(static_cast<char>((val >> 8) & 0xff));
    os.put(static_cast<char>(val & 0xff));
}

// Write a PNG chunk: length (4) + type (4) + data + CRC32 (4)
void write_chunk(std::ofstream& os, const char* type,
                 const void* data, uint32_t length) {
    write_be32(os, length);
    os.write(type, 4);

    // CRC covers type + data
    uint32_t crc = crc32(0, reinterpret_cast<const Bytef*>(type), 4);
    if (data && length > 0) {
        crc = crc32(crc, reinterpret_cast<const Bytef*>(data), length);
    }
    if (data && length > 0) {
        os.write(static_cast<const char*>(data), length);
    }
    write_be32(os, crc);
}

} // anonymous namespace

// -----------------------------------------------------------------------
//  write_png — writes a 24-bit RGB PNG using zlib deflate
// -----------------------------------------------------------------------

void write_png(const Image<Color>& img, const std::filesystem::path& path) {
    const uint32_t w = static_cast<uint32_t>(img.width());
    const uint32_t h = static_cast<uint32_t>(img.height());

    std::ofstream ofs(path, std::ios::binary);
    if (!ofs)
        throw std::runtime_error("Cannot open " + path.string());

    // PNG signature
    const std::array<uint8_t, 8> sig = {137, 80, 78, 71, 13, 10, 26, 10};
    ofs.write(reinterpret_cast<const char*>(sig.data()), sig.size());

    // --- IHDR ---
    // Write 13-byte IHDR data manually in big-endian:
    {
        std::array<uint8_t, 13> ihdr{};
        // width (big-endian)
        ihdr[0] = (w >> 24) & 0xff; ihdr[1] = (w >> 16) & 0xff;
        ihdr[2] = (w >> 8) & 0xff;  ihdr[3] = w & 0xff;
        // height (big-endian)
        ihdr[4] = (h >> 24) & 0xff; ihdr[5] = (h >> 16) & 0xff;
        ihdr[6] = (h >> 8) & 0xff;  ihdr[7] = h & 0xff;
        ihdr[8] = 8;   // bit_depth
        ihdr[9] = 2;   // color_type RGB
        ihdr[10] = 0;  // compression
        ihdr[11] = 0;  // filter
        ihdr[12] = 0;  // interlace
        write_chunk(ofs, "IHDR", ihdr.data(), ihdr.size());
    }

    // === Build raw filtered image data (filter byte 0 = None per row) ===
    // Each row: [0x00] + R G B R G B ...
    const uint32_t row_bytes = w * 3 + 1;  // filter byte + RGB pixels
    std::vector<uint8_t> raw(row_bytes * h);

    for (uint32_t y = 0; y < h; ++y) {
        uint8_t* row = raw.data() + y * row_bytes;
        row[0] = 0;  // filter: None
        const Color* src = img.row(y);
        for (uint32_t x = 0; x < w; ++x) {
            row[1 + x * 3 + 0] = src[x].r;
            row[1 + x * 3 + 1] = src[x].g;
            row[1 + x * 3 + 2] = src[x].b;
        }
    }

    // === Compress with zlib deflate ===
    z_stream zs{};
    if (deflateInit(&zs, Z_BEST_COMPRESSION) != Z_OK)
        throw std::runtime_error("deflateInit failed");

    zs.next_in = raw.data();
    zs.avail_in = static_cast<uInt>(raw.size());

    // Worst-case bound: deflateBound
    uLong bound = deflateBound(&zs, zs.avail_in);
    std::vector<uint8_t> compressed(bound);

    zs.next_out = compressed.data();
    zs.avail_out = static_cast<uInt>(compressed.size());

    int ret = deflate(&zs, Z_FINISH);
    if (ret != Z_STREAM_END) {
        deflateEnd(&zs);
        throw std::runtime_error("deflate compression failed");
    }
    uint32_t compressed_size = static_cast<uint32_t>(zs.total_out);
    deflateEnd(&zs);

    // --- IDAT ---
    write_chunk(ofs, "IDAT", compressed.data(), compressed_size);

    // --- IEND ---
    write_chunk(ofs, "IEND", nullptr, 0);
}

} // namespace fractal