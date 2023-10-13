#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fstream>
//#pragma once
class IOutput;

class IInput
{
public:
	virtual DWORD Open() = 0;
	virtual DWORD ReadNext(int& iResult) = 0;
};


class ICalc
{
public:
	virtual DWORD Calc(IInput* pInput, IOutput* pOut, int& iResult) = 0;
};


class IOutput
{
public:
	virtual DWORD Open() = 0;
	virtual DWORD PrintOut(int iVal) = 0;
};


/******************************************************************************/
class CCalcAvg : public  ICalc
{
public:
	virtual DWORD Calc(IInput* pInput, IOutput* pOut, int& iResult);
};


class CKbInput : public IInput
{
public:
	CKbInput(const char* pDevPath)
	{
	};

	virtual DWORD Open();
	virtual DWORD ReadNext(int& iResult);
};

class CScrnOut : public IOutput
{
public:
	virtual DWORD Open()
	{
		return ERROR_SUCCESS;
	};

	virtual DWORD PrintOut(int iVal)
	{
		std::cout << "Result is :" << iVal << std::endl;
		return ERROR_SUCCESS;
	}
};

class CReadFile : public IInput
{
public:
	virtual DWORD Open();
	virtual DWORD ReadNext(int& iResult);
	CReadFile(std::string file) 
	{
		m_file = file;
	}
	~CReadFile()
	{
		m_StreamFile.close();
	}
private:
	std::string m_file;
	std::ifstream m_StreamFile;
	
};
