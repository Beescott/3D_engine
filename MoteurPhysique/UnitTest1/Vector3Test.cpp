#include "stdafx.h"
#include "CppUnitTest.h"
#include "../MoteurPhysique/Vector3.h"
#include "../MoteurPhysique/Vector3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vector3Testing
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestClassNoArguments)
		{
			Vector3 v = Vector3();
			Assert::AreEqual(0.0f, v.x);
			Assert::AreEqual(0.0f, v.y);
			Assert::AreEqual(0.0f, v.z);
		}

		TEST_METHOD(TestClassFloatArguments)
		{
			float x = 3;
			float y = 5;
			float z = 5;

			Vector3 v(x, y, z);
			Assert::AreEqual(x, v.x);
			Assert::AreEqual(y, v.y);
			Assert::AreEqual(z, v.z);
		}

		TEST_METHOD(TestClassDisplay)
		{
			std::string s = "3.000000 5.000000 5.000000";
			Vector3 v(3., 5, 5);

			Assert::AreEqual(s, v.toString());
		}

		TEST_METHOD(TestClassAffectation)
		{
			Vector3 v = Vector3();
			Vector3 v2(3, 5, 5);
			v = v2;

			Assert::AreEqual(3.0f, v.x);
			Assert::AreEqual(5.0f, v.y);
			Assert::AreEqual(5.0f, v.z);
		}

		TEST_METHOD(TestClassIsEqual)
		{
			Vector3 v(3, 5, 5);
			Vector3 v2(3, 5, 5);
			
			Assert::IsTrue(v == v2);
		}

		TEST_METHOD(TestClassNotEqual)
		{
			Vector3 v = Vector3();
			Vector3 v2(3, 5, 5);
			Vector3 v3 = Vector3();

			Assert::IsTrue(v != v2);
			Assert::IsFalse(v != v3);
		}

		TEST_METHOD(TestClassNegation)
		{
			Vector3 v = Vector3();
			Vector3 v2(3, 5, 5);
			Vector3 v3(-3, -5, -5);

			Assert::IsTrue(v == v.neg());
			Assert::IsTrue(v2.neg() == v3);
		}

		TEST_METHOD(TestClassMagnitude)
		{
			Vector3 v = Vector3();
			Vector3 v2(2, 4, 4);

			Assert::AreEqual(v.mag(), 0.0f);
			Assert::AreEqual(v2.mag(), 6.0f);
		}


		TEST_METHOD(TestClassMultiplication)
		{
			Vector3 v = Vector3(1, 1, 1);
			Vector3 v2 = Vector3(3, 3, 3);
			v = v * 3;

			Assert::IsTrue(v2 == v);
		}

		TEST_METHOD(TestClassDivision)
		{
			Vector3 v = Vector3(3, 3, 3);
			Vector3 v2 = Vector3(1, 1, 1);
			v = v / 3;

			Assert::IsTrue(v == v2);
		}
		/*
		TEST_METHOD(TestClassDivisionByZero)
		{
			Vector3 v = Vector3(3, 3, 3);
			try {
				v = v / 0;
			}
			catch (std::invalid_argument const & err)
			{
				EXPECT_EQ(err.what(), std::string("Division by 0"));
			}
		}
		*/

		TEST_METHOD(TestClassDot)
		{
			Vector3 v = Vector3();
			Vector3 v2 = Vector3(1, 1, 1);

			Assert::AreEqual(3.0f, v.dot(v2));
		}
	};
}