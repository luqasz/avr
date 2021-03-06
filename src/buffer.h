#pragma once

#include "utils.h"

#include <stdint.h>

namespace Buffer {

    using SIZE_TYPE = unsigned int;

    class Bytes {
    private:
        uint8_t * const begin_ptr;
        uint8_t * const end_ptr;

    protected:
        Bytes(uint8_t * const b, uint8_t * const e) :
            begin_ptr(b),
            end_ptr(e)
        {
        }

    public:
        constexpr uint8_t *
        begin() const
        {
            return begin_ptr;
        };

        constexpr uint8_t *
        end() const
        {
            return end_ptr;
        };

        /*
         * Return pointer to last element in array.
         */
        constexpr uint8_t *
        lastElemPtr() const
        {
            return end() - 1;
        }

        constexpr uint8_t & operator[](const SIZE_TYPE idx) const
        {
            return begin_ptr[idx];
        };

        constexpr SIZE_TYPE
        size() const
        {
            return static_cast<SIZE_TYPE>(end() - begin());
        };
    };

    template <unsigned int SIZE>
    class SizedBytesArray : public Bytes {
        static_assert(SIZE > 0, "buffer size must be > 0");
        uint8_t array[SIZE] = { 0 };

    public:
        SizedBytesArray() :
            Bytes(array, array + SIZE) {}
    };

    template <uint8_t BUFFER_SIZE>
    class Circular {
        static_assert(BUFFER_SIZE < 256, "Size bust be < 256.");
        static_assert(BUFFER_SIZE > 0, "Size bust be > 0.");

    private:
        uint8_t head              = 0;
        uint8_t tail              = 0;
        uint8_t data[BUFFER_SIZE] = { 0 };
        uint8_t elements          = 0;

    public:
        uint8_t
        read() volatile
        {
            uint8_t next_tail = static_cast<uint8_t>(tail + 1);
            if (next_tail >= BUFFER_SIZE)
                next_tail = 0;

            uint8_t value = data[tail];
            tail          = next_tail;
            elements--;
            return value;
        }

        void
        write(uint8_t byte) volatile
        {
            uint8_t next_head = static_cast<uint8_t>(head + 1);
            if (next_head >= BUFFER_SIZE)
                next_head = 0;

            data[head] = byte;
            head       = next_head;
            elements++;
        }

        // Return how many elements are in the buffer.
        uint8_t
        size() volatile const
        {
            return elements;
        }

        // Return free space.
        uint8_t
        free() volatile const
        {
            return static_cast<uint8_t>(BUFFER_SIZE - elements);
        }
    };

    template <uint8_t BUFFER_SIZE>
    class CircularPowerOf2 {
        static_assert(isPowerOfTwo(BUFFER_SIZE), "Size must be power of 2.");

    private:
        uint8_t head              = 0;
        uint8_t tail              = 0;
        uint8_t data[BUFFER_SIZE] = { 0 };

    public:
        uint8_t
        size() volatile
        {
            return static_cast<uint8_t>(head - tail);
        }

        uint8_t
        mask(uint8_t val) volatile
        {
            return val % BUFFER_SIZE;
        }

        void
        write(uint8_t byte) volatile
        {
            data[mask(head++)] = byte;
        }

        uint8_t
        read() volatile
        {
            return data[mask(tail++)];
        }
    };

}
