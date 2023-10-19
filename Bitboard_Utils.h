#ifndef BITBOARD_UTILITY_H
#define BITBOARD_UTILITY_H

/// Bitboard Helpers
struct Bitboard_Utility
{
    Bitboard_Utility() {};
    // Mutators
    /**
     * @brief Sets the desired bit
     * @param bitboard The bitboard to modify
     * @param index The index of the bit (L->R) you want to modify
    */
    void Set_Bit(unsigned long long& bitboard, int index) {
        bitboard |= ((unsigned long long) 1 << index);
    }

    /**
     * @brief Clears the desired bit
     * @param bitboard The bitboard to modify
     * @param index The index of the bit (L->R) you want to zero
    */
    void Zero_Bit(unsigned long long& bitboard, int index) {
        bitboard &= ~((unsigned long long) 1 << index);
    }

    /**
     * @brief Flips the desired bit to the opposite state
     * @param bitboard The bitboard to modify
     * @param index The index of the bit (L->R) you want to flip
    */
    void Flip_Bit(unsigned long long& bitboard, int index) {
        bitboard ^= ((unsigned long long) 1 << index);
    }

    /**
     * @brief Flips two bits on the same bitboard at once. Primarily used to move pieces on a bitboard with one function call
     * @param bitboard The bitboard to modify
     * @param indexA The index of the first bit to flip
     * @param indexB The index of the second bit to flip
    */
    void Flip_Bits(unsigned long long& bitboard, int indexA, int indexB) {
        bitboard ^= ((unsigned long long) 1 << indexA) | ((unsigned long long) 1 << indexB);
    }

    /**
     * @brief Zeros and returns the index of the least significant bit LSB
     * @param bitboard The bitboard to modify
     * @return The index of the LSB
    */
    int Pop_LSB(unsigned long long &bitboard) {
        if(bitboard == 0) {
            return -1; // empty bitboard
        }

        int position = 0;
        while((bitboard & 1) == 0) {
            bitboard >>= 1;
            position++;
        }
        // Zero the bit
        bitboard &= (bitboard - 1);
        // Shift everything back so later pops will count the position correctly
        bitboard <<= position;
        return position;
    }

    // Accessors
    bool Is_Set(unsigned long long bitboard, int index) {
        return ((bitboard >> index) & 1) == 1;
    }
};

#endif