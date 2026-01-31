#pragma once

#include <windows.h>
#include <unordered_map>
#include "../eterBase/Singleton.h"
#include "../eterBase/Stl.h"

#include "FileProvider.h"

class CEterPackManager : public CSingleton<CEterPackManager>
{
	public:
		enum ESearchModes
		{
			SEARCH_FILE_FIRST,
			SEARCH_PACK_FIRST
		};

		typedef std::list<std::shared_ptr<FileProvider>> TEterPackList;
		typedef std::unordered_map<std::string, std::shared_ptr<FileProvider>> TEterPackMap;
		typedef std::unordered_map<std::string, std::shared_ptr<FileProvider>> TFileMap;
		typedef std::shared_ptr<std::vector<char>> TPackDataPtr;

	public:
		CEterPackManager();
		virtual ~CEterPackManager();
		
		void SetSearchMode(bool bPackFirst);
		int GetSearchMode();

		bool Get(const std::string& fileName, TPackDataPtr& dataPtr);
		bool Get(const std::string& fileName, std::stringstream& dataStream);

		bool isExist(const char * c_szFileName);
		bool isExistInPack(const char * c_szFileName);

		bool PackExists(const std::string& name, const std::string& container);
		bool RegisterPack(const std::string& name, const std::string& container);
		std::string ConvertFileName(std::string fileName);

		const TFileMap& GetFileMap();

	protected:
		bool CompareName(const char * c_szDirectoryName, DWORD iLength, const char * c_szFileName);
		bool GetFromPack(const std::string& fileName, TPackDataPtr& dataPtr);
		bool GetFromFile(const std::string& fileName, TPackDataPtr& dataPtr);

	protected:
		int						m_iSearchMode;

		TFileMap				m_FileMap;
		TEterPackMap			m_PackMap;

		CRITICAL_SECTION		m_csFinder;
};
