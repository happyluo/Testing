// **********************************************************************
//
// Copyright (c) 2010-2014 Bernard Luo. All rights reserved.
//
// <Email: luo (dot) xiaowei (at) hotmail (dot) com>
//
// **********************************************************************

#ifndef UTIL_EXCEPTION_H
#define UTIL_EXCEPTION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <exception>
#include <sstream>
#include <Util/Config.h>
#include <Util/Exception.h>

namespace Util
{

/// 异常类基类
class UTIL_API Exception : public std::exception
{
public:
	Exception();

	///构造函数
	///@param[in]		file		异常所发生的文件
	///@param[in]		line	异常所发生的行
	Exception(const char* file, int line);

	///析构函数
	virtual ~Exception() throw();

	///获取异常的名称
	///return 异常的名称
	virtual std::string Name() const;

	///输出异常信息
	///@param[out]	out	输出流
	virtual void Print(std::ostream& out) const;

	// return pointer to message string
	///获取异常信息
	///return 异常发生的原因
	virtual const char* what() const throw();

	///从内存中创建当前对象的新的副本
	///return		新创建的副本所对应的指针，注意：调用者负责释放内存
	virtual Exception* Clone() const;

	///将异常抛出
	virtual void Throw() const;

	///获取异常所发生的文件
	const char* File() const;

	///获取异常所发生的行
	int Line() const;

	const std::string& StackTrace() const;

private:

	///异常所发生的文件
	const char			*m_fileName;

	///异常所发生的行
	int					m_line;

	///异常的名称
	static const char	*ms_pcName;

	const std::string	m_stackTrace;

	///异常信息
	mutable std::string	m_strWhat;		// Initialized lazily in what().
};

///重载输出操作符，用于将异常信息输出
UTIL_API std::ostream& operator << (std::ostream &out, const Util::Exception &ex);

/// 空共享指针异常类
class UTIL_API NullSharedPtrException : public Exception
{
public:
	NullSharedPtrException(const char* file, int line);

	virtual ~NullSharedPtrException() throw();

	virtual std::string Name() const;

	virtual Exception* Clone() const;

	virtual void Throw() const;
	
private:
	
	static const char *ms_pcName;
};
	
class UTIL_API IllegalArgumentException : public Exception
{
public:
	IllegalArgumentException(const char* file, int line);

	IllegalArgumentException(const char* file, int line, const std::string& reason);

	virtual ~IllegalArgumentException() throw();

	virtual std::string Name() const;

	virtual void Print(std::ostream& out) const;

	virtual Exception* Clone() const;

	virtual void Throw() const;

	const std::string& Reason() const;

private:

	std::string			m_reason;

	static const char	*ms_pcName;
};

/// 系统调用异常类
class UTIL_API SyscallException : public Exception
{
public:
	SyscallException(const char* file, int line, int syscallError);

	virtual ~SyscallException() throw();

	virtual std::string Name() const;

	virtual void Print(std::ostream& out) const;

	virtual Exception* Clone() const;

	virtual void Throw() const;

	int Error() const;

private:

	const int			m_errorCode;
	static const char	*ms_pcName;
};

//////////////////////////////////////////////////////////////////////////
/// FatalException
class UTIL_API FatalException : public Exception
{
public:
	FatalException(const char* file, int line, const std::string& message);
	virtual ~FatalException() throw();

	virtual std::string Name() const;
	virtual void Print(std::ostream& out) const;
	virtual FatalException* Clone() const;
	virtual void Throw() const;

	const std::string& Reason() const;

private:
	std::string m_reason;

	static const char* ms_pcName;    
};

}

#endif
