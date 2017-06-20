#include "stdafx.h"
#include "CppUnitTest.h"
#include <Property.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{

	TEST_CLASS(UtilsTest)
	{
	public:
		TEST_METHOD(PropertyTest)
		{
			using namespace SDL;
			Auto<int> i = 0;
			Assert::AreEqual(0, i.GetValue());

			i = 150;
			Assert::AreEqual(150, static_cast<int>(i));

			int p = i + 5;
			Assert::AreEqual(150 + 5, p);
		}

		TEST_METHOD(PropertyGetOnlyTest)
		{
			using namespace SDL;
			int org = 150;
			Get<int> i = org;
			Assert::AreEqual(i.GetValue(), 150);

			i.GetValue() = 200;
			Assert::AreEqual(org, 200);

			int org_const = 250;
			Get<const int> ci = org_const;

			Assert::AreEqual(250, ci.GetValue());

			org_const = 300;
			Assert::AreEqual(300, static_cast<const int>(ci));

			Get<const int> b = 150;
			Assert::AreEqual(150, b.GetValue());
		}

		TEST_METHOD(PropertySetOnlyTest)
		{
			using namespace SDL;
			int v = 0;
			Set<int> vp = v;
			vp = 150;

			Assert::AreEqual(150, v);
		}

		TEST_METHOD(PropertyGetSetTest)
		{
			using namespace SDL;
			int p = 150;
			GetSet<int> vp = p;

			p += 20;
			Assert::AreEqual(150 + 20, static_cast<int>(vp));

			vp = 50;
			Assert::AreEqual(50, static_cast<int>(vp));
			Assert::AreEqual(p, 50);


			GetSet<int> codeTest(
				[&]() ->int& {return p; },
				[&p](int value) ->void {p = value; },
				[&p](int value) ->void {p = value; }
			);

			codeTest = std::move(950);
			Assert::AreEqual(950, static_cast<int>(vp));
			Assert::AreEqual(950, p);
		}
	};
}