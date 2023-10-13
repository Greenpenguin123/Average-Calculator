#include "pch.h"
#include "MyClass.h"
#include <fstream>
using namespace std;

DWORD CCalcAvg::Calc(IInput* pInput, IOutput* pOut, int& iResult)
{
	DWORD err = ERROR_SUCCESS;

	if (pInput == nullptr || pOut == nullptr)
	{
		return ERROR_INVALID_PARAMETER;
	}

	if (pInput->Open() != ERROR_SUCCESS || pOut->Open() != ERROR_SUCCESS)
	{
		return ERROR_APP_INIT_FAILURE;
	}

	int iVal = 0;
	int iCount = 0;
	int iSum = 0;

	while ((err = pInput->ReadNext(iVal)) == ERROR_SUCCESS)
	{
		iSum += iVal;
		iCount++;
	}

	if (err != ERROR_SUCCESS && err != ERROR_HANDLE_EOF)
	{
		return err;
	}

	if (iCount == 0)
	{
		return ERROR_INVALID_PARAMETER;
	}

	iResult = iSum / iCount;

	pOut->PrintOut(iResult);

	return ERROR_SUCCESS;
}

DWORD CKbInput::Open()
{
	return ERROR_SUCCESS;
}

DWORD CKbInput::ReadNext(int& iResult)
{
	std::cout << "Input an integer\n";
	std::cin >> iResult;

	if (iResult == 0)
	{
		return ERROR_HANDLE_EOF;
	}
	return ERROR_SUCCESS;
}

DWORD CReadFile::Open() 
{
	
	m_StreamFile.open(m_file);
	if (!m_StreamFile.is_open())
	{
		return ERROR_OPEN_FAILED;
	}
	if (m_StreamFile.bad())
	{
		return ERROR_OPEN_FAILED;
	}
	return ERROR_SUCCESS;
	
}

DWORD CReadFile::ReadNext(int& iResult)
{
	if (m_StreamFile.eof())
	{
		return ERROR_HANDLE_EOF;
	}
	m_StreamFile >> iResult;
	if (m_StreamFile.bad())
	{
		return ERROR_READ_FAULT;
	}
	return ERROR_SUCCESS;
}
