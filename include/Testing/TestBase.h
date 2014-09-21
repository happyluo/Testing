#ifndef TEST_BASE_H
#define TEST_BASE_H

#include <Testing/Config.h>
#include <Util/Shared.h>
#include <Util/SharedPtr.h>

TESTING_BEGIN

class TESTING_API TestFailed
{
public:

    TestFailed(const std::string&);

    const std::string m_name;
};

class TESTING_API TestBase : public Util::Shared
{
public:
	TestBase(const std::string& name);
	virtual ~TestBase();

	const std::string& Name() const;

	void Start();

	virtual void SetUp() {};
	virtual void TearDown() {};

protected:

	virtual void Run() = 0;

	const std::string m_name;
};

typedef Util::SharedPtr<TestBase>  TestBasePtr;

TESTING_END

#endif