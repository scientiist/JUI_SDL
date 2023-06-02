#include <string>
#include <sstream>
#include <cmath>

#pragma once



namespace JUI
{
    // Rounds a number to a certain number of decimal places.
    float Round(float num, int digits = 0) {
        float mult = std::pow(10.0f, (float) digits);
        return std::floor(num * mult + 0.5) / mult;
    }

// Truncates a number with an appropriate metric suffix
// 999 = 999
// 1123 = 1.1K
// 123,456 = 123K
// 420,420,420 = 420M
// 420,420,420,420 = 420B

    int sig_figs[] = {
            0, 0, 0, 1, 0, 0, 1, 0, 0, 1
    };

    int divisions[] = {
            1, 1, 1,
            1000, 1000, 1000,
            100000, 100000, 100000,
            100000000, 100000000, 100000000
    };

    std::string suffixes[] = {
            "", "", "",
            "K", "K", "K",
            "M", "M", "M",
            "B", "B", "B",
            "T", "T", "T",
            "Q", "Q", "Q",
    };


    static std::string format_num(float input, int precision) {
        std::ostringstream out;
        out.precision(precision);
        out << std::fixed << input;
        return std::move(out).str();
    }

    static std::string Trunicate(float num) {
        if (num < 1000) {
            return format_num(num, 0);
            //return std::to_string(num);
        }


        int figs = std::ceil(std::log10(num));
        auto suffix = suffixes[figs];
        auto round_to = sig_figs[figs];
        auto denominator = divisions[figs];
        float fraction = num / denominator;

        std::ostringstream out;
        out.precision(round_to);
        out << std::fixed << Round(fraction, round_to);
        out << suffix;
        return std::move(out).str();
    }
}