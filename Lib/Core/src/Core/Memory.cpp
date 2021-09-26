//
// Created by jngl on 22/08/2021.
//
#include "Core/Memory.h"

#include <cstring>
#include <fstream>

namespace cc{
    ByteArray::ByteArray():
    m_size(0),
    m_data(nullptr){
    }

    ByteArray::ByteArray(Uint8 *copyFrom, Uint32 size):
    m_size(size){
        m_data = new Uint8[m_size];
        memcpy(m_data, copyFrom, m_size);
    }

    ByteArray::ByteArray(Uint32 size):
    m_size(size)
    {
        m_data = new Uint8[m_size];
        for(Uint32 i=0; i<m_size; ++i){
            m_data[i] = 0;
        }
    }

    ByteArray::ByteArray(ByteArray &&moveFrom) noexcept:
    m_size(moveFrom.m_size),
    m_data(moveFrom.m_data)
    {
        moveFrom.m_size = 0;
        moveFrom.m_data = nullptr;
    }

    ByteArray::~ByteArray() {
        clear();
    }

    ByteArray &ByteArray::operator=(ByteArray&& from) {
        m_size = from.m_size;
        m_data = from.m_data;
        from.m_size = 0;
        from.m_data = nullptr;
        return *this;
    }

    Uint32 ByteArray::size() const {
        return m_size;
    }

    const Uint8 *ByteArray::data() const {
        return m_data;
    }

    std::optional<ByteArray> ByteArray::loadFromFile(std::string_view filename) {
        std::ifstream file(std::string(filename), std::ifstream::binary);
        if(!file){
            return {};
        }

        file.seekg (0, file.end);
        Uint32 size = file.tellg();
        file.seekg (0, file.beg);

        ByteArray result(size);

        file.read (reinterpret_cast<char*>(result.data()),size);

        return result;
    }

    Uint8 *ByteArray::data() {
        return m_data;
    }

    void ByteArray::copy(Uint8 *copyFrom, Uint32 size) {
        clear();
        m_size = size;
        m_data = new Uint8[m_size];
        memcpy(m_data, copyFrom, m_size);
    }

    void ByteArray::copy(void *copyFrom, Uint32 size) {
        copy(reinterpret_cast<Uint8*>(copyFrom), size);
    }

    void ByteArray::clear() {
        if(m_data)delete[] m_data;
        m_data = nullptr;
        m_size = 0;
    }
}

