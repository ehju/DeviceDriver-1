#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int temp, ret;
    ret =(int)(m_hardware->read(address));
    for (int i = 0;i < 4;i++)
    {
        temp = (int)(m_hardware->read(address));
        if (temp != ret)
        {
            throw ReadFailException();
        }
    }
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}