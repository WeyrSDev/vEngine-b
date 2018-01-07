#pragma once
#include "vInclude.h"

namespace vEngine {
	class Utility
	{
	private:
		Utility();
		Utility(const Utility& p_Rhs);
		Utility& operator=(const Utility& p_Rhs);
	public:
		static std::string CurrentDirectory();
		static std::wstring ExecutableDirectory();
		static void GetFileName(const std::string& p_InputPath, std::string& p_Filename);
		static void GetDirectory(const std::string& p_InputPath, std::string& p_Directory);
		static void GetFileNameAndDirectory(const std::string& p_InputPath, std::string& p_Directory, std::string& p_Filename);
		static void LoadBinaryFile(const std::wstring& p_Filename, std::vector<char>& p_Data);
		static void ToWideString(const std::string& p_Source, std::wstring& p_Dest);
		static std::wstring ToWideString(const std::string& p_Source);
		static void PathJoin(std::wstring& p_Dest, const std::wstring& p_SourceDirectory, const std::wstring& p_SourceFile);
		static void GetPathExtension(const std::wstring& p_Source, std::wstring& p_Dest);
	};
}