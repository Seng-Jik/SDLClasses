#include "stdafx.h"
#include "CppUnitTest.h"
#include <Property.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{

	TEST_CLASS(UtilsTest)
	{
	private:
		class ClassForTest
		{
		public:
			ClassForTest(int i)
			{
				Log("default ctor:%d",i);
			}

			ClassForTest(ClassForTest&&)
			{
				Log("move ctor");
			}

			ClassForTest(const ClassForTest&)
			{
				Log("copy ctor");
			}

			const ClassForTest& operator = (const ClassForTest&)
			{
				Log("copy =");
				return *this;
			}

			const ClassForTest& operator =(ClassForTest&&)
			{
				Log("move =");
				return *this;
			}
		};
	public:
		TEST_METHOD(AutoPropertyTest)
		{
			using namespace SDL;
			Auto<int> i = 0;
			Assert::AreEqual(0, i.GetVal());

			i = 150;
			Assert::AreEqual(150, static_cast<int>(i));

			int p = i + 5;
			Assert::AreEqual(150 + 5, p);

			i = 99;
			Assert::AreEqual(99, i.GetConst());
			Assert::AreEqual(99, static_cast<const int>(i));

			Auto<ClassForTest> obj(150); //default ctor
			obj = ClassForTest(150);	//move =
			Auto<ClassForTest> obj2 = ClassForTest(250);
			obj = obj2.GetConst();
		}

		TEST_METHOD(PropertyGetOnlyTest)
		{
			using namespace SDL;
			int org = 150;
			Get<int> i(org);
			Assert::AreEqual(i.GetVal(), 150);

			i.GetVal() = 200;
			Assert::AreEqual(org, 200);
			Assert::AreEqual(org, i.GetConst());
			Assert::AreEqual(org, static_cast<const int>(i));

			int org_const = 250;
			Get<const int> ci(org_const);

			Assert::AreEqual(250, ci.GetVal());

			org_const = 300;
			Assert::AreEqual(300, static_cast<const int>(ci));

			Get<const int> b(150);
			Assert::AreEqual(150, b.GetVal());
		}

		TEST_METHOD(PropertySetOnlyTest)
		{
			/*using namespace SDL;
			int v = 0;
			Set<int> vp(v);
			vp = 150;

			Assert::AreEqual(150, v);

			ClassForTest o(1);
			Set<ClassForTest> obj(o); //default ctor
			obj = ClassForTest(150);	//move =
			obj = o;*/
		}

		TEST_METHOD(PropertyGetSetTest)
		{
			/*using namespace SDL;
			int p = 150;
			GetSet<int> vp(p);

			p += 20;
			Assert::AreEqual(150 + 20, static_cast<int>(vp));

			vp = 50;
			Assert::AreEqual(50, static_cast<int>(vp));
			Assert::AreEqual(p, 50);


			GetSet<int> codeTest(
				[&]() ->int& {return p; },
				[&p](int&& value) ->void {p = value; }
			);

			codeTest = 950;
			Assert::AreEqual(950, static_cast<int>(vp));
			Assert::AreEqual(950, p);

			ClassForTest o(1);
			GetSet<ClassForTest> obj(o); //default ctor
			obj = ClassForTest(150);	//move =*/
		}
	};
}