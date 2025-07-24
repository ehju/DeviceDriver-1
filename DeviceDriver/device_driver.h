#pragma once
#include <stdexcept>
#include "flash_memory_device.h"



class ReadFailException : public std::exception {
public:
	char const* what() const override
	{
		return "ReadFailException";
	}
};
class WriteFailException : public std::exception {
public:
	char const* what() const override
	{
		return "WriteFailException";
	}
};
class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    virtual int read(long address);
    void write(long address, int data);

protected:
	FlashMemoryDevice* m_hardware;
	const int READ_COUNT=5;

};