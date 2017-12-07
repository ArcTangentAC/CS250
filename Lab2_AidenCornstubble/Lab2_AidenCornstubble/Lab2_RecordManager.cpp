#include "stdafx.h"
#include "Lab2_RecordManager.h"
#include "stdexcept"

RecordManager::~RecordManager()
{
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (m_outputs[i].is_open())
		{
			m_outputs[i].close();
		}
	}
}

void RecordManager::OpenOutputFile(string filename)
{
	int index = FindAvailableFile(); noexcept(true);
	if (index == -1)
	{
		throw runtime_error("No available files ");
	}
	m_outputs[index].open(filename);
	m_filenames[index] = filename;
}

void RecordManager::CloseOutputFile(string filename)
{
	int index = FindFilenameIndex(filename); noexcept(true);
	if (index == -1)
	{
		throw runtime_error("No available files ");
	}
	m_outputs[index].close();
	m_filenames[index] = "";
}

void RecordManager::WriteToFile(string filename, string	text)
{
	int index = FindFilenameIndex(filename);
	if (index == -1)
	{
		throw runtime_error("No available files ");
	}
	m_outputs[index] << text << endl;
}

void RecordManager::DisplayAllOpenFiles() noexcept
{
	cout << "Open files : " << endl;
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (m_outputs[i].is_open())
		{
			cout << i << ". " << m_filenames[i] << endl;
		}
	}
}

int RecordManager::FindAvailableFile() noexcept
{
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (m_outputs[i].is_open() == false)
		{
			return i;
		}
	}
	return -1;
}

int RecordManager::FindFilenameIndex(string filename) noexcept
{
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (m_filenames[i] == filename)
		{
			return i;
		}
	}
	return -1;
}