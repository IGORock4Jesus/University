#include "stdafx.h"
#include "CppUnitTest.h"
#include <rect.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UniversityTests
{		
	TEST_CLASS(MathTests)
	{
	public:
		
		TEST_METHOD(ContainsRectTests)
		{
			rect r1{ {-2.0f, -2.0f}, {4.0f, 4.0f} },
				noR1{ {-5.0f, -5.0f}, {2.0f, 2.0f} },
				noR2{ {3.0f, -5.0f}, {2.0f, 2.0f} },
				noR3{ {3.0f, 3.0f}, {2.0f, 2.0f} },
				noR4{ {-5.0f, 3.0f}, {2.0f, 2.0f} },
				innerR1{ {-1.0f, -1.0f}, {2.0f, 2.0f} },
				interR1{ {-0.5f, 0.0f}, {3.0f, 3.0f} },
				interR2{ {1.0f, 1.0f}, {2.0f, 2.0f} },
				interR3{ {-2.0f, -2.0f}, {4.0f, 4.0f} },
				interR4{ {0.0f, -1.0f}, {2.0f, 2.0f} },
				interR5{ {-1.0f, 0.0f}, {2.0f, 2.0f} },
				outerR1{ {-5.0f, -5.0f}, {10.0f, 10.0f} };

			Assert::IsFalse(containsRect(&r1, &noR1), L"noR1");
			Assert::IsFalse(containsRect(&r1, &noR2), L"noR2");
			Assert::IsFalse(containsRect(&r1, &noR3), L"noR3");
			Assert::IsFalse(containsRect(&r1, &noR4), L"noR4");
			Assert::IsTrue(containsRect(&r1, &innerR1), L"innerR1");
			Assert::IsTrue(containsRect(&r1, &interR1), L"interR1");
			Assert::IsTrue(containsRect(&r1, &interR2), L"interR2");
			Assert::IsTrue(containsRect(&r1, &interR3), L"interR3");
			Assert::IsTrue(containsRect(&r1, &interR4), L"interR4");
			Assert::IsTrue(containsRect(&r1, &interR5), L"interR5");
			Assert::IsTrue(containsRect(&r1, &outerR1), L"outerR1");
		}

	};
}