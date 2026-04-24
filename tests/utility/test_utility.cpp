// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2025-2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

#include "test_utility.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace tests
{
namespace utility
{

std::vector<uint8_t> read_bin(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);
    EXPECT_TRUE(file.is_open()) << "Failed to open file: " << path;
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void print_hex(const std::string& prefix, const std::vector<uint8_t>& vec, size_t len, Color color)
{
    int color_index = static_cast<int>(color);
    if (color_index >= 0 && color_index < 16)
        std::cout << COLOR_CODES[color_index];
    std::cout << prefix;
    for (size_t i = 0; i < len; ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(vec[i]);
    std::cout << std::dec;
    if (color_index >= 0 && color_index < 16)
        std::cout << COLOR_RESET;
    std::cout << std::endl;
}

// =========================================================================
// Colored Print Implementations
// =========================================================================

void print_colored(const std::string& message, Color color)
{
    size_t idx = static_cast<size_t>(color) % COLOR_CODES.size();
    std::cout << COLOR_CODES[idx] << message << COLOR_RESET << std::endl;
}

void print_success(const std::string& message)
{
    std::cout << COLOR_CODES[7] << "✓ " << message << COLOR_RESET << std::endl;  // Bright Green
}

void print_error(const std::string& message)
{
    std::cout << COLOR_CODES[6] << "✗ " << message << COLOR_RESET << std::endl;  // Bright Red
}

void print_section(const std::string& message)
{
    std::cout << COLOR_CODES[12];  // Bright White
    std::cout << "\n=================================================================\n";
    std::cout << " " << message << "\n";
    std::cout << "=================================================================\n\n";
    std::cout << COLOR_RESET;
}

}  // namespace utility
}  // namespace tests
