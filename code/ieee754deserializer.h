class IEEE754Deserializer : public FP_Deserializer
{
public:    
    virtual void convert(const uint32_t in, float& out) const
    {
        if (isNormal(in) || isDenormal(in) || isInf(in))
            out = *reinterpret_cast<const float*>(&in);
        else if (isNaN(in))
            out = loadedNan(in);
        else
            throw FP_UnknownType();
    }
    
    virtual float loadedNorm(const uint32_t v) const {}
    virtual float loadedDenorm(const uint32_t v) const {}
    
    virtual float loadedNan(const uint32_t v) const 
    {
        return std::numeric_limits<float>::quiet_NaN();
    }
    
    virtual float loadedInf(const uint32_t v) const {}
    
    virtual void convert(const uint64_t in, double& out) const
    {
        if (isNormal(in) || isDenormal(in) || isInf(in))
            out = *reinterpret_cast<const double*>(&in);
        else if (isNaN(in))
            out = loadedNan(in);
        else
            throw FP_UnknownType();
    }
    virtual double loadedNorm(const uint64_t v) const {}
    virtual double loadedDenorm(const uint64_t v) const {}
    
    virtual double loadedNan(const uint64_t v) const 
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    
    virtual double loadedInf(const uint64_t v) const {}

    virtual void convert(const LongDouble in, long double& out) const
    {
        if (isNormal(in))
            out = loadedNorm(in);
        else if (isDenormal(in))
            out = loadedDenorm(in);
        else if (isNaN(in))
            out = loadedNaN(in);
        else if (isInf(in))
            out = loadedInf(in);
        else
            throw FP_UnknownType();
    }
    
    virtual long double loadedNorm(const LongDouble v) const
    {
        uint64_t& hi = v.u64[0];
        uint64_t& lo = out.u64[1];
        
        if (sizeof(long double) == 8)
        {
            // drop 60 bits from the fraction
            lo >>= 60;
            // move 48 bits from the hi to the low portion
            lo |= (hi & fractionMask128hi) << 4;
            // fix the exponent
            uint64_t exponent = (hi & exponentMask128hi) >> 48;
            exponent -= (bias128 - bias64);
            // set the exponent in place
            lo |= (exponent << 52);
            // set the sign
            lo |= (hi & signMask128hi);
        }
        else if (sizeof(long double) == 10 || LDis10in16())
        {
            // drop the least significant 48 bits of lo
            lo >>= 48;
            // the least significant 48 bits of hi become the most significant 48
            // bits of lo
            lo |= (hi << 16);
            // shift the sign and exponent into position
            hi >>= 48;
        }
        else if (sizeof(long double) != 16)
            throw FP_LongDoubleSizeException();
        // else no modification necessary
        
        // swap to little endian, if needed
        if (isLittleEndian())
            std::swap(v.u64[0], v.u64[1]);
        return v.ld;
    }
    
    virtual long double loadedDenorm(const LongDouble v) const
    {
        uint64_t& hi = v.u64[0];
        uint64_t& lo = out.u64[1];
        
        if (sizeof(long double) == 8)
        {
            // drop 60 bits from the fraction
            lo >>= 60;
            // move the rest of the fraction into place
            lo |= (hi & fractionMask128hi) << 4;
            // trim the exponent and move it into place
            lo |= (hi & exponentMask128hi) << 4;
            // set the sign bit
            lo |= (hi & signMask128hi);
        }
        else if (sizeof(long double) == 10 || LDis10in16())
        {
            // drop the least significant 48 bits of lo
            lo >>= 48;
            // the least significant 48 bits of hi become the most significant 48
            // bits of lo
            lo |= (hi << 16);
            // shift the sign and exponent into position
            hi >>= 48;
        }
        else if (sizeof(long double) != 16)
            throw FP_LongDoubleSizeException();
        // else no modification necessary
        
        // swap to little endian, if needed
        if (isLittleEndian())
            std::swap(v.u64[0], v.u64[1]);
        return v.ld;
    }
    
    virtual long double loadedNan(const LongDouble v) const
    {
        return std::numeric_limits<long double>::quiet_NaN();
    }
    
    virtual long double loadedInf(const LongDouble v) const
    {
        // works the same as denormal numbers
        return loadedDenorm(v);
    }
};