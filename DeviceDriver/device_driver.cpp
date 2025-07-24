#include "device_driver.h"
#include <set>

using std::set;
DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int ret;
    set<int> readDataSet;
    for (int i = 0; i < READ_COUNT;i++) {
        ret = (int)(m_hardware->read(address));
        readDataSet.insert(ret);
    }
    if (readDataSet.size()==1)return ret;
    else throw ReadFailException();
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}