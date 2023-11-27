#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GBEmulatorTests
{
	TEST_CLASS(GBEmulatorTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Bus bus;
			CPU cpu(bus);

			Assert::AreEqual(1, 1);
		}
	};
}
