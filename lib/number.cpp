#include "number.h"
#include <cmath>
#include <string>
#include <algorithm>

uint2022_t from_uint(uint32_t i) {
    uint2022_t convert_to;
    convert_to.digits_of_uint[convert_to.max_size - 1] = i % int(pow(10, 9));
    convert_to.digits_of_uint[convert_to.max_size - 2] = i / int(pow(10, 9));
    if (convert_to.digits_of_uint[convert_to.max_size - 2] == 0) {
        convert_to.chunks = 1;
    } else {
        convert_to.chunks = 2;
    }
    return convert_to;
}

uint2022_t from_string(const char* buff) {
    uint2022_t convert_from_string;
    int counter_of_digits = 0;
    std::string digits;
    int cnt = 1;
    while (std::isdigit(buff[counter_of_digits])) {
        counter_of_digits++;
    }
    convert_from_string.chunks = counter_of_digits / 9 + ((counter_of_digits % 9 == 0) ? 0 : 1);
    for (int i = counter_of_digits - 1; i >= 0; i--) {
        digits += buff[i];
        if (digits.size() == 9) {
            std::reverse(digits.begin(), digits.end());
            convert_from_string.digits_of_uint[68 - cnt] = std::stoi(digits);
            digits = "";
            cnt++;
        }
    }
    if (!digits.empty()) {
        std::reverse(digits.begin(), digits.end());
        convert_from_string.digits_of_uint[68 - cnt] = std::stoi(digits);
    }
    return convert_from_string;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t ans;
    int buffer = 0;
    for (int i = ans.max_size - 1; i >= 0; i--) {
        buffer += lhs.digits_of_uint[i] + rhs.digits_of_uint[i];
        ans.digits_of_uint[i] = buffer % int(1e9);
        buffer /= int(1e9);
    }
    return ans;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t ans;
    int buffer = 0;
    for (int i = ans.max_size - 1; i >= 0; i--) {
        buffer += lhs.digits_of_uint[i] - rhs.digits_of_uint[i] + int(1e9);
        ans.digits_of_uint[i] = buffer % int(1e9);
        if (buffer < int(1e9)) {
            buffer -= 1;
        } else {
            buffer = 0;
        }
    }
    if (lhs == rhs) {
        uint2022_t a;
        return a;
    }
    return ans;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t ans;
    int64_t buffer = 0;
    for (int i = 0; i < lhs.chunks; i++) {
        for (int j = 0; j < rhs.chunks || buffer != 0; j++) {
            int64_t chunk1 = lhs.digits_of_uint[lhs.max_size - 1 - i];
            int64_t chunk2 = rhs.digits_of_uint[rhs.max_size - 1 - j];
            buffer += chunk1 * chunk2 + ans.digits_of_uint[ans.max_size - 1 - (i + j)];
            ans.digits_of_uint[ans.max_size - 1 - (i + j)] = buffer % int(1e9);
            buffer = buffer / int(1e9);
        }
    }
    return ans;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 67; i >= 0; i--) {
        if (lhs.digits_of_uint[i] != rhs.digits_of_uint[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 67; i >= 0; i--) {
        if (lhs.digits_of_uint[i] != rhs.digits_of_uint[i]) {
            return true;
        }
    }
    return false;
}
int counter_of_dig(int num) {
    int cnt = 0;
    if (num == 0) {
        return 1;
    }
    while (num != 0) {
        num /= 10;
        cnt++;
    }
    return cnt;
}
std::ostream &operator<<(std::ostream& stream, const uint2022_t& value) {
    bool ValueNumber = false;
    bool firstdigit = true;

    for (int i : value.digits_of_uint) {
        if (i != 0) {
            ValueNumber = true;
        }
        if (ValueNumber) {
            if (firstdigit) {
                stream << i;
                firstdigit = false;
            } else {
                for (int j = 0; j < (9 - counter_of_dig(i)); j++) {
                    stream << 0;
                }
                stream << i;
            }
        }
    }
    if (!ValueNumber) {
        stream << 0;
    }
    return stream;
}
