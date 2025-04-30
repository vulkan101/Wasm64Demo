#include "TestAllocation.h"
#include <iostream>

constexpr size_t LONG_SIZE = sizeof(long);

#if LONG_SIZE == 8
typedef uint64_t largeInt;
#else 
typedef uint32_t largeInt;
#endif 

namespace DataStore
{
    constexpr largeInt MB = 1000 * 1000;
    constexpr largeInt GB = 1000 * 1000 * 1000;
    largeInt totalMB = 0;

    struct DataArray
    {
        DataArray(largeInt numBytes)
        {
            numElements = numBytes / sizeof(char);
            data = new char[numElements];
            dataSizeBytes = data ? numBytes : 0;
            numElements = data ? numElements : 0;
        }
        largeInt dataSizeBytes{};
        largeInt numElements{};
        char* data{ nullptr };
    };
};

DataStore::DataArray* createData(largeInt numBytes)
{
    using namespace DataStore;
    try
    {
        largeInt numMB = numBytes / MB;
        DataArray* dataArrayPtr = new DataArray(numBytes);

        if (dataArrayPtr->numElements)
        {
            std::cout << "Created data with " << dataArrayPtr->numElements << " elements, using " << numMB << " MB" << std::endl;
        }
        return dataArrayPtr;
    }
    catch (std::exception ex)
    {
        std::cout << "Failed to create " << numBytes / MB << " MB" << std::endl;
        return nullptr;
    }
}
void accessData(DataStore::DataArray* data)
{
    using namespace DataStore;
    try
    {
        largeInt numElements = data->numElements;
        for (size_t i = 0; i < numElements; ++i) {
            data->data[i] = 1;
        }
        // set a value in the last part of the array
        data->data[numElements - 1] = 123;
        {

            if ((int)data->data[numElements - 1] == 123)
                std::cout << "Verified data modified correctly (" << (int)data->data[numElements - 1] << ")" << std::endl;
        }
    }
    catch (std::exception ex)
    {
        std::cout << "Error accessing data: " << ex.what() << std::endl;
    }
}
void destroyData(DataStore::DataArray* data)
{
    using namespace DataStore;
    try
    {
        {
            std::cout << "Deleting data" << std::endl;
        }
        delete (data->data);
        delete data;
    }
    catch (std::exception ex)
    {

        std::cout << "Error deleting data: " << ex.what() << std::endl;
    }
}

void TestAllocation(int numGB)
{
    constexpr uint64_t GB = 1000 * 1000 * 1000;
    uint64_t numBytes = numGB * GB;
    DataStore::DataArray* data = createData(numBytes);
    if (data)
    {
        std::cout << "Allocated!";
        accessData(data);
    }
}