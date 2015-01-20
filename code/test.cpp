struct TestStruct
{
    float f;
    float fnan;
    float finf;
    double d;
    double dnan;
    double dinf;
    long double ld;
    long double ldnan;
    long double ldinf;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & f;
        ar & fnan;
        ar & finf;
        ar & d;
        ar & dnan;
        ar & dinf;
        ar & ld;
        ar & ldnan;
        ar & ldinf;
    }
};

ostream& operator<<(ostream& os, const TestStruct& t)
{
    os << t.f << endl
       << t.fnan << endl
       << t.finf << endl
       << t.d << endl
       << t.dnan << endl
       << t.dinf << endl
       << t.ld << endl
       << t.ldnan << endl
       << t.ldinf << endl;
    return os;
}

void load()
{
    string filename;
    cout << "Filename: ";
    cin >> filename;

    TestStruct t2;
    ifstream inFile(filename.c_str());
    IEEE754Deserializer ieee;
    portable_binary_iarchive inArchive(inFile, ieee);
    inArchive >> t2;
    cout << t2 << endl;
}

void save()
{
    string filename;
    cout << "Filename: ";
    cin >> filename;

    TestStruct t1 = { 
        123.456F, 
        numeric_limits<float>::quiet_NaN(), 
        numeric_limits<float>::infinity(),
        5678.01234, 
        numeric_limits<double>::quiet_NaN(), 
        numeric_limits<double>::infinity(),
        12345678.901234567L, 
        numeric_limits<long double>::quiet_NaN(), 
        numeric_limits<long double>::infinity()
    };
    ofstream outFile(filename.c_str());
    IEEE754Serializer ieee;
    portable_binary_oarchive outArchive(outFile, ieee);
    outArchive << t1;
    cout << t1 << endl;
}

int main()
{
    char action;
    cout << "Load or save? [l/s] ";
    cin >> action;

    if (action == 'l')
        load();
    else
        save();

  return 0;
}