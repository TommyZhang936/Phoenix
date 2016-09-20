#include "DVR/DVRStatement.h"
#include "DVR/DVRSession.h"

namespace DVR {

DVRStatement::DVRStatement(DVRStatementImpl::Ptr pImpl):
_pImpl(pImpl)
{
	poco_check_ptr(pImpl);
}


DVRStatement::~DVRStatement()
{
}


DVRStatement::DVRStatement(DVRSession& rSession)
{
	reset(rSession);
}

DVRStatement::DVRStatement(const DVRStatement& stmt):
_pImpl(stmt._pImpl)
{

}

DVRStatement& DVRStatement::operator = (const DVRStatement& stmt)
{
	DVRStatement tmp(stmt);
	swap(tmp);
	return *this;
}

void DVRStatement::swap(DVRStatement& other)
{
	using std::swap;
	swap(_pImpl, other._pImpl);
}

DVRStatement& DVRStatement::reset(DVRSession& rSession)
{
	DVRStatement stmt(rSession.createStatementImpl());
	swap(stmt);
	return *this;
}


void DVRStatement::DownloadByName(const std::string& name)
{
	_pImpl->donwloadByName(name);
}
void DVRStatement::DownloadByTime(const Poco::DateTime stime, const Poco::DateTime etime)
{

}

void DVRStatement::Searchfile(const Poco::DateTime stime, const Poco::DateTime etime, const std::vector<int>& Channels)
{
	_pImpl->list(stime, etime);
}

void DVRStatement::playByName(const std::string& filename)
{
	_pImpl->playByName(filename);
}

void DVRStatement::playByTime(const Poco::DateTime& stime, const  Poco::DateTime etime)
{

}

}