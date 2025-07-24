#include "gmock/gmock.h"
#include "device_driver.h"
#include <vector>


using namespace std;
using namespace testing;
class MockFlashMemory : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));

};

TEST(DeviceDriver, ReadFromHW) {
	MockFlashMemory mock;

	EXPECT_CALL(mock, read(_))
		.Times(5);

	DeviceDriver driver{ &mock };
	int data = driver.read(0xFF);
}

TEST(DeviceDriver, ReadDifferentValueException) {
	MockFlashMemory mock;

	EXPECT_CALL(mock, read(_))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xB));

	DeviceDriver driver{ &mock };
	//act
	try {
		int data = driver.read(0xFF);
		FAIL(); 
	}
	catch (ReadFailException& e) {
		//assert
		EXPECT_EQ(string{ e.what() }, string{ "ReadFailException" });
	}
}

TEST(DeviceDriver, ReadBeforeWrite) {
	MockFlashMemory mock;
	// precondition : Read value == 0xFF
	int address = (long)0xFF;

	EXPECT_CALL(mock, read((long)0xB))
		.Times(1);

	DeviceDriver driver{ &mock };
	driver.write((long)0xB,7);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}