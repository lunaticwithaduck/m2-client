#pragma once

#include <string>
#include <set>

#include "FileProvider.h"

class Folder : public FileProvider
{
protected:
	std::string folderPath;
	std::set<std::string> fileList = {};

public:
	Folder(const std::string& folderPath);
	std::vector<std::string> listFiles();
	bool fileExists(const std::string& fileName);
	bool getFile(const std::string& fileName, std::shared_ptr<std::vector<char>>& fileData);

private:
	void ListFiles(const std::string& directory, const std::string& relativePath);
};

