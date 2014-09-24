#include <Util/Exception.h>
#include <Testing/ColorStream.h>
#include <Testing/TestBase.h>

using namespace std;

TESTING_BEGIN

TestFailed::TestFailed(const std::string& name) : m_name(name) 
{
}


TestBase::TestBase(const std::string& name) : m_name(name) 
{
    SetUp();
}

TestBase::~TestBase()
{
    TearDown();
}

const std::string& TestBase::Name() const
{
    return m_name;
}

void TestBase::Start()
{
    colorostream out(cout);
    out << "running " << m_name << " test... " << flush;
    try
    {
        Run();
        out << fggreen << "OK" << endl;
    }
    catch(const Util::FatalException& )
    {
        colorostream eout(cerr);
        eout << fgred << "FAILED" << endl;
    }
    catch(const Util::Exception& e)
    {
        colorostream eout(cerr);
        eout << e << " FAILED" << endl;
        throw TestFailed(m_name);
    }
}

TESTING_END