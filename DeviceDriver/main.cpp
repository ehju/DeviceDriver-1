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
		.WillOnce(Return(1))
		.WillRepeatedly(Return(3));

	DeviceDriver driver{ &mock };
	//act
	try {
		int data = driver.read(0xFF);
		FAIL(); 
	}
	catch (ReadFailException& e) {
		//assert
		EXPECT_EQ(string{ e.what() }, string{  "ReadFailException" });
	}


}



int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}