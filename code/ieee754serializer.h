class IEEE754Serializer : public FP_Serializer
{
public:
    virtual void convert(const float in, uint32_t& out) const
    {
        out = *reinterpret_cast<const uint32_t*>(&in);
    }

    virtual void convert(const double in, uint64_t& out) const
    {
        out = *reinterpret_cast<const uint64_t*>(&in);
    }

    virtual void convert(const long double in, LongDouble& out) const
    {
        const int hiIdx = isLittleEndian() ? 1 : 0;
        const int loIdx = !hiIdx;

        uint64_t& outHi = out.u64[hiIdx];
        outHi = in.u64[hiIdx];
        uint64_t& outLo = out.u64[loIdx];
        outLo = in.u64[loIdx];

        if (sizeof(long double) == 8)
        {
            // have to tweak the exponent of normal values
            if (isNormal(outLo))
            {
                // fix the exponent
                uint64_t exponent = (outLo & exponentMask64) >> 52;
                exponent += (bias128 - bias64);

                outHi = 0;
                // grab the sign
                outHi = (outLo & signMask64);
                // set the new exponent
                outHi |= (exponent << 48);
                // the most significant 48 bits of the fraction are 
                // moved to the least significant part of outHi
                outHi |= ((outLo & fractionMask64) >> 4);
                // pad 60 bits into the fraction
                outLo <<= 60;
            }
            // denormal are fine just padding the fields into place
            else if (isDenormal(outLo))
            {
                // long double is an alias for double.  outLo contains 
                // the entire double
                // set the sign bit
                outHi = outLo & signMask64;
                // get the exponent and left pad by 4 bits
                outHi |= ((outLo & exponentMask64) >> 4);
                // the most significant 48 bits of the fraction are moved 
                // to the least significant part of outHi
                outHi |= ((outLo & fractionMask64) >> 4);
                // pad 60 bits into the fraction
                outLo <<= 60;
            }
            else if (isNaN(outLo) || isInf(outLo))
            {
                outHi = 0;
                // grab the sign bit
                outHi |= (outLo & signMask64);
                // set all the exponent bits
                outHi |= exponentMask128hi;
                // the most significant 48 bits of the fraction are 
                // moved to the least significant part of outHi
                outHi |= ((outLo & fractionMask64) >> 4);
                // pad 60 bits into the fraction
                outLo <<= 60;
            }
            else
                throw FP_UnknownType();
        } 
        else if (sizeof(long double) == 10 || LDis10in16())
        {
            // shift the sign and exponent into place
            outHi <<= 48;
            // move the most significant 48 bits of lo to the 
            // least significant part of hi
            outHi |= (outLo >> 16);
            // pad in 48 bits to the least significant part of lo
            outLo <<= 48;
        }
        else if (sizeof(long double) != 16)
            throw FP_LongDoubleSizeException();
        // else 16 byte type, already formatted correctly

        // swap to big endian if needed
        if (isLittleEndian())
            std::swap(outHi, outLo);
    }
};