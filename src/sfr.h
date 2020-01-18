#ifndef sfr_h
#define sfr_h

#include "utils.h"

#include <stdint.h>

namespace SFR {

    template <typename WIDTH>
    WIDTH volatile &
    iomem(uint16_t address)
    {
        return *reinterpret_cast<WIDTH volatile *>(address);
    }

    void
    setBit(const uint16_t address, const uint8_t bit)
    {
        iomem<uint8_t>(address) |= bit;
    }

    void
    setBit(const uint16_t address, const uint8_t bit, const uint8_t set_mask)
    {
        uint8_t current = iomem<uint8_t>(address);
        current         = current | inverted<uint8_t>(set_mask);
        iomem<uint8_t>(address) |= bit;
    }

    void
    clearBit(const uint16_t address, const uint8_t bit)
    {
        iomem<uint8_t>(address) &= static_cast<uint8_t>(~bit);
    }

    template <typename REG_TYPE, typename WIDTH>
    class BitRegisterRO : public REG_TYPE {
    public:
        WIDTH
        read() const
        {
            return iomem<WIDTH>(REG_TYPE::address);
        }

        bool
        isSet(const uint8_t bit) const
        {
            return read() & bit;
        }
    };

    template <typename REG_TYPE, typename WIDTH>
    class DataRegisterRO : public REG_TYPE {
    public:
        WIDTH
        read() const
        {
            return iomem<WIDTH>(REG_TYPE::address);
        }
    };

    template <typename REG_TYPE, typename WIDTH>
    class DataRegisterRW : public DataRegisterRO<REG_TYPE, WIDTH> {
    public:
        void
        write(const WIDTH value) const
        {
            SFR::iomem<WIDTH>(REG_TYPE::address) = value;
        }

        void
        operator=(const WIDTH value) const
        {
            write(value);
        }
    };

    template <typename REG_TYPE, typename WIDTH>
    class BitRegisterRW : public SFR::BitRegisterRO<REG_TYPE, WIDTH> {
    public:
        void
        write(const WIDTH value) const
        {
            SFR::iomem<WIDTH>(REG_TYPE::address) = value;
        }

        void
        operator=(const WIDTH value) const
        {
            write(value);
        }

        void
        setBit(const uint8_t bit) const
        {
            SFR::setBit(REG_TYPE::address, bit);
        }

        void
        setBit(const uint8_t bit, const uint8_t set_mask) const
        {
            SFR::setBit(REG_TYPE::address, bit, set_mask);
        }

        void
        clearBit(const WIDTH bit) const
        {
            SFR::clearBit(REG_TYPE::address, bit);
        }
    };
}

#include <mcu_sfr.h>

#endif

