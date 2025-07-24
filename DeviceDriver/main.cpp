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



int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}