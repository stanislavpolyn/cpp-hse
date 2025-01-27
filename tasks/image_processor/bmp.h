#pragma once

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "rgb_color.h"

/// Class supports BMP file storage.
/// Methods for writing content to a specific file path
/// and reading from a specific file are implemented

class BMP {
public:
    static const uint16_t BMP_SIGNATURE = 0x4D42;  // BM
    static const uint16_t BMP_BITS_PER_PIXEL = 24;

    struct BMPHeader {
        uint16_t signature;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
    } __attribute__((packed));

    struct DIBHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t color_planes_num;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        int32_t hor_res;
        int32_t ver_res;
        uint32_t colors_num;
        uint32_t important_colors_num;
    } __attribute__((packed));

public:
    BMP() {
    }

    ~BMP() {
    }

    void ReadFromFile(const std::string& filename);

    void WriteToFile(const std::string& filename);

    BMPHeader& GetBMPHeader() {
        return bmp_header_;
    }
    const BMPHeader& GetBMPHeader() const {
        return bmp_header_;
    }
    DIBHeader& GetDIBHeader() {
        return dib_header_;
    }
    const DIBHeader& GetDIBHeader() const {
        return dib_header_;
    }

    const int32_t& GetHeight() const {
        return dib_header_.height;
    }
    int32_t& GetHeight() {
        return dib_header_.height;
    }
    const int32_t& GetWidth() const {
        return dib_header_.width;
    }
    int32_t& GetWidth() {
        return dib_header_.width;
    }

    std::vector<RGB24>& GetData() {
        return data_;
    }
    const std::vector<RGB24>& GetData() const {
        return data_;
    }

protected:
    /// File I/O
    std::fstream OpenToRead(const std::string& filename);
    std::fstream OpenToWrite(const std::string& filename);
    void ReadBmp(std::fstream& file);
    void WriteBmp(std::fstream& file);
    void ReadBmpHeader(std::fstream& file);
    void ReadDibHeader(std::fstream& file);
    void ReadData(std::fstream& file);
    void WriteBmpHeader(std::fstream& file);
    void WriteDibHeader(std::fstream& file);
    void WriteData(std::fstream& file);

protected:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    std::vector<RGB24> data_;
};