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
			Property<int> i = 0;
			Assert::AreEqual(0, i.Get());

			i = 150;
			Assert::AreEqual(150, static_cast<int>(i));

			int p = i + 5;
			Assert::AreEqual(150 + 5, p);
		}

		TEST_METHOD(PropertyGetOnlyTest)
		{
			using namespace SDL;
			int org = 150;
			PropertyGetOnly<int> i = org;
			Assert::AreEqual(i.Get(), 150);

			i.Get() = 200;
			Assert::AreEqual(org, 200);

			int org_const = 250;
			PropertyGetOnly<const int> ci = org_const;

			Assert::AreEqual(250, ci.Get());

			org_const = 300;
			Assert::AreEqual(300, static_cast<const int>(ci));

			PropertyGetOnly<const int> b = 150;
			Assert::AreEqual(150, b.Get());
		}

		TEST_METHOD(PropertySetOnlyTest)
		{
			using namespace SDL;
			int v = 0;
			PropertySetOnly<int> vp = v;
			vp = 150;

			Assert::AreEqual(150, v);
		}

		TEST_METHOD(PropertyGetSetTest)
		{
			using namespace SDL;
			int p = 150;
			PropertyGetSet<int> vp = p;

			p += 20;
			Assert::AreEqual(150 + 20, static_cast<int>(vp));

			vp = 50;
			Assert::AreEqual(50, static_cast<int>(vp));
			Assert::AreEqual(p, 50);


			PropertyGetSet<int> codeTest(
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