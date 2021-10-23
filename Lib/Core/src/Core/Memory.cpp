//
// Created by jngl on 22/08/2021.
//
#include "Core/Memory.h"

#include <cstring>
#include <fstream>

namespace cc{
    ByteArray::ByteArray():
    m_data(nullptr),
    m_size(0){
    }

    ByteArray::ByteArray(const void *copyFrom, Uint32 size):
    m_size(size){
        m_data = new Uint8[m_size];
        memcpy(m_data, copyFrom, m_size);
    }

    ByteArray::ByteArray(Uint32 size):
    m_size(size)
    {
        m_data = new Uint8[m_size];
        memset(m_data, static_cast<int>(m_size), 1);
    }

    ByteArray::ByteArray(const ByteArray &other):
    m_size(other.size()){
        m_data = new Uint8[m_size];
        memcpy(m_data, other.m_data, m_size);
    }

    ByteArray::ByteArray(ByteArray &&moveFrom) noexcept:
    m_data(moveFrom.m_data),
    m_size(moveFrom.m_size)
    {
        moveFrom.m_size = 0;
        moveFrom.m_data = nullptr;
    }

    ByteArray::~ByteArray() {
        clear();
    }

    ByteArray &ByteArray::operator=(const ByteArray & other) {
        if(&other == this){
            return *this;
        }

        m_size = other.size();

        m_data = new Uint8[m_size];
        memcpy(m_data, other.m_data, m_size);

        return *this;
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

    const void *ByteArray::data() const {
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

        file.read (reinterpret_cast<char*>(result.m_data),size);

        return result;
    }

    void ByteArray::copy(void *copyFrom, Uint32 size) {
        clear();
        m_size = size;
        m_data = new Uint8[m_size];
        memcpy(m_data, copyFrom, m_size);
    }

    void ByteArray::clear() {
        if(m_data)delete[] m_data;
        m_data = nullptr;
        m_size = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ByteArrayView::ByteArrayView(const void *refFrom, Uint32 size):
    m_data(refFrom),
    m_size(size)
    {
    }

    ByteArrayView::ByteArrayView(const ByteArray & from):
    m_data(from.data()),
    m_size(from.size())
    {
    }

    ByteArrayView::ByteArrayView(const ByteArrayView & from):
    m_data(from.m_data),
    m_size(from.m_size)
    {
    }

    ByteArrayView::ByteArrayView(ByteArrayView &&moveFrom) noexcept:
    m_data(moveFrom.m_data),
    m_size(moveFrom.m_size)
    {
    }

    void ByteArrayView::clear() {
        m_data = nullptr;
        m_size = 0;
    }

    void ByteArrayView::ref(void *refFrom, Uint32 size) {
        m_data = refFrom;
        m_size = size;
    }

    ByteArrayView &ByteArrayView::operator=(const ByteArray& from) {
        m_data = from.data();
        m_size = from.size();
        return *this;
    }

    ByteArrayView &ByteArrayView::operator=(const ByteArrayView& from) {
        m_data = from.m_data;
        m_size = from.m_size;
        return *this;
    }

    ByteArrayView &ByteArrayView::operator=(ByteArrayView &&from) {
        m_data = from.m_data;
        m_size = from.m_size;
        return *this;
    }

    Uint32 ByteArrayView::size() const {
        return m_size;
    }

    const void *ByteArrayView::data() const {
        return m_data;
    }
}

