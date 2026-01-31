#include "Folder.h"
#include "EterPackManager.h"

#include <iostream>
#include <fstream>
#include <Windows.h>
#include "../eterBase/Stl.h"

void Folder::ListFiles(const std::string& directory, const std::string& relativePath = "") {
    WIN32_FIND_DATA findData;
    HANDLE hFind;

    std::string searchPath = directory + "\\*";

    // Start searching for files and directories
    hFind = FindFirstFile(searchPath.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Failed to open directory: " + directory);

    do {
        const std::string fileOrDirName = findData.cFileName;

        // Skip the "." and ".." directories
        if (fileOrDirName == "." || fileOrDirName == "..") {
            continue;
        }

        // Construct the full and relative paths
        std::string fullPath = directory + "\\" + fileOrDirName;
        std::string currentRelativePath = relativePath + fileOrDirName;

        // Check if the current entry is a directory
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // Recurse into the subdirectory
            ListFiles(fullPath, currentRelativePath + "\\");
        }
        else {
            if (currentRelativePath.rfind("ymir work\\", 0) == 0) {
                currentRelativePath = "d:\\" + currentRelativePath;
            }
            
            currentRelativePath = CEterPackManager::Instance().ConvertFileName(currentRelativePath);

            // Print the file's relative path
            this->fileList.insert(currentRelativePath);
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
}


Folder::Folder(const std::string& folderPath)
{
	this->folderPath = folderPath;
    ListFiles(folderPath);
}

std::vector<std::string> Folder::listFiles()
{
    std::vector<std::string> result;
    std::copy(fileList.begin(), fileList.end(), std::back_inserter(result));
    return result;
}

bool Folder::fileExists(const std::string& fileName)
{
    auto it = fileList.find(fileName);

    if (it == fileList.end())
        return false;

    return true;
}


bool Folder::getFile(const std::string& fileName, std::shared_ptr<std::vector<char>>& fileData)
{
    std::string realFileName = fileName;
    std::string ymirPrefix = "d:/";

    if (fileName.find(ymirPrefix) == 0)
        realFileName = realFileName.substr(ymirPrefix.length());

    realFileName = this->folderPath + "/" + realFileName;

    // Try to open the file
    std::ifstream file(realFileName, std::ios::binary);
    if (!file.is_open())
        return false;

    // Read the file's contents
    fileData = std::make_shared<std::vector<char>>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
    return true;
}