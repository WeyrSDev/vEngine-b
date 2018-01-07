#include "vUtility.h"
#include <algorithm>
#include <exception>
#include <Shlwapi.h>
#include <fstream>

namespace vEngine {
	std::string Utility::CurrentDirectory()
	{
		WCHAR buffer[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, buffer);
		std::wstring currentDirectoryW(buffer);

		return std::string(currentDirectoryW.begin(), currentDirectoryW.end());
	}

	std::wstring Utility::ExecutableDirectory()
	{
		WCHAR buffer[MAX_PATH];
		GetModuleFileName(nullptr, buffer, MAX_PATH);
		PathRemoveFileSpec(buffer);

		return std::wstring(buffer);
	}

	void Utility::GetFileName(const std::string& p_InputPath, std::string& p_Filename)
	{
		std::string fullPath(p_InputPath);
		std::replace(fullPath.begin(), fullPath.end(), '\\', '/');
		std::string::size_type lastSlashIndex = fullPath.find_last_of('/');

		if (lastSlashIndex == std::string::npos)
		{
			p_Filename = fullPath;
		}
		else
		{
			p_Filename = fullPath.substr(lastSlashIndex + 1, fullPath.size() - lastSlashIndex - 1);
		}
	}

	void Utility::GetDirectory(const std::string& p_InputPath, std::string& p_Directory)
	{
		std::string fullPath(p_InputPath);
		std::replace(fullPath.begin(), fullPath.end(), '\\', '/');
		std::string::size_type lastSlashIndex = fullPath.find_last_of('/');

		if (lastSlashIndex == std::string::npos)
		{
			p_Directory = "";
		}
		else
		{
			p_Directory = fullPath.substr(0, lastSlashIndex);
		}
	}

	void Utility::GetFileNameAndDirectory(const std::string& p_InputPath, std::string& p_Directory, std::string& p_Filename)
	{
		std::string fullPath(p_InputPath);
		std::replace(fullPath.begin(), fullPath.end(), '\\', '/');
		std::string::size_type lastSlashIndex = fullPath.find_last_of('/');

		if (lastSlashIndex == std::string::npos)
		{
			p_Directory = "";
			p_Filename = fullPath;
		}
		else
		{
			p_Directory = fullPath.substr(0, lastSlashIndex);
			p_Filename = fullPath.substr(lastSlashIndex + 1, fullPath.size() - lastSlashIndex - 1);
		}
	}

	void Utility::LoadBinaryFile(const std::wstring& p_Filename, std::vector<char>& p_Data)
	{
		std::ifstream file(p_Filename.c_str(), std::ios::binary);
		if (file.bad())
		{
			throw std::exception("Could not open file.");
		}

		file.seekg(0, std::ios::end);
		UINT size = (UINT)file.tellg();

		if (size > 0)
		{
			p_Data.resize(size);
			file.seekg(0, std::ios::beg);
			file.read(&p_Data.front(), size);
		}
		file.close();
	}

	void Utility::ToWideString(const std::string& p_Source, std::wstring& p_Dest)
	{
		p_Dest.assign(p_Source.begin(), p_Source.end());
	}

	std::wstring Utility::ToWideString(const std::string& p_Source)
	{
		std::wstring dest;
		dest.assign(p_Source.begin(), p_Source.end());

		return dest;
	}

	void Utility::PathJoin(std::wstring& p_Dest, const std::wstring& p_SourceDirectory, const std::wstring& p_SourceFile)
	{
		WCHAR buffer[MAX_PATH];
		PathCombine(buffer, p_SourceDirectory.c_str(), p_SourceFile.c_str());
		p_Dest = buffer;
	}

	void Utility::GetPathExtension(const std::wstring& p_Source, std::wstring& p_Dest)
	{
		p_Dest = PathFindExtension(p_Source.c_str());
	}
}