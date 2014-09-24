#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <Testing/Config.h>
#include <Testing/TestBase.h>
#include <string>
#include <list>

TESTING_BEGIN

extern std::list<TestBasePtr> gAllTests;

void InitializeTestSuite();

class TestSuite : public Util::Shared
{
public:
    typedef Util::SharedPtr<TestSuite> TestSuitePtr;
    typedef void (*RegisterFunction)();


    static TestSuitePtr GetInstance()
    {
        static TestSuitePtr instance;
        if (!instance)
        {
            instance = new TestSuite();
        }
        
        return instance;
    }

    void RunAllTest()
    {
        for (std::list<TestBasePtr>::const_iterator iter = m_AllTests.begin(); 
            iter != m_AllTests.end(); ++iter)
        {
            (*iter)->Start();
        }
        m_AllTests.clear();
    }

    TestBasePtr RegistTestInstance(TestBasePtr testInstance) 
    {
        m_AllTests.push_back(testInstance);                                            
        return testInstance;
    }

private:
    std::list<TestBasePtr> m_AllTests;
};


#define TEST_CLASS_NAME(TestCaseName, TestName) TestCaseName##_##TestName##_##Test

#define TEST_IMPL(TestCaseName, TestName, ParentClass)                                    \
    class TEST_CLASS_NAME(TestCaseName, TestName) : public ParentClass {                \
        public:                                                                            \
            TEST_CLASS_NAME(TestCaseName, TestName)() :                                    \
                ParentClass(#TestCaseName##"."###TestName) {}                            \
                                                                                        \
            static TESTING TestBasePtr Register() {                                        \
                return TESTING TestSuite::GetInstance()->RegistTestInstance(            \
                    new TEST_CLASS_NAME(TestCaseName, TestName)()); }                    \
        private:                                                                        \
        static TESTING TestBasePtr const ms_testInstancePtr;                            \
            virtual void Run();                                                            \
    };                                                                                    \
    TESTING TestBasePtr const TEST_CLASS_NAME(TestCaseName, TestName)                    \
        ::ms_testInstancePtr = TEST_CLASS_NAME(TestCaseName, TestName)::Register();        \
    void TEST_CLASS_NAME(TestCaseName, TestName)::Run()
    

#define TEST(TestCaseName, TestName) \
    TEST_IMPL(TestCaseName, TestName, TESTING TestBase)

#define TEST_F(TestCaseName, TestName) \
    TEST_IMPL(TestCaseName, TestName, TestCaseName)
    

#define RUN_ALL_TESTS()        \
    (TESTING TestSuite::GetInstance()->RunAllTest())

TESTING_END

#endif