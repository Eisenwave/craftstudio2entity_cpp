//
// Created by user on 4/14/19.
//

#ifndef CRAFTSTUDIO2ENTITY_CPP_IO_UTIL_HPP
#define CRAFTSTUDIO2ENTITY_CPP_IO_UTIL_HPP

#include <cstdint>
#include <iostream>
#include <istream>

class membuf : public std::basic_streambuf<char> {
public:
    membuf(const uint8_t *p, size_t l) {
        setg((char *) p, (char *) p, (char *) p + l);
    }
};

class memstream : public std::istream {
private:
    membuf _buffer;

public:
    memstream(const uint8_t *p, size_t l) : std::istream(&_buffer), _buffer(p, l) {
        rdbuf(&_buffer);
    }

};

#endif //CRAFTSTUDIO2ENTITY_CPP_IO_UTIL_HPP
