#include "ZIP.h"
#include "EterPackManager.h"

#include <iostream>
#include <fstream>
#include <Windows.h>
#include "../eterBase/Stl.h"

ZIP::ZIP(const std::string& archivePath)
{
    int err;

    if ((zipFile = zip_open(archivePath.c_str(), 0, &err)) == NULL) {
        zip_error_t error;

        zip_error_init_with_code(&error, err);
        std::string errorMessage = zip_error_strerror(&error);
        zip_error_fini(&error);

        throw std::runtime_error("Cannot open ZIP archive '" + archivePath + "': " + errorMessage);
    }

    // Read the list of files in the archive
    zip_int64_t numEntries = zip_get_num_entries(zipFile, 0);
    for (int index = 0; index < numEntries; index++)
    {
        zip_stat_t fileData;
        zip_stat_index(zipFile, index, 0, &fileData);

        std::string fileName(fileData.name);

        if (fileData.size == 0) {
            // This is a folder, skip it
            continue;
        }

        if (fileName.rfind("ymir work/", 0) == 0) {
            fileName = "d:/" + fileName;
        }

        fileName = CEterPackManager::Instance().ConvertFileName(fileName);

        fileList.insert({ fileName, fileData.index });
    }
}

ZIP::~ZIP()
{
    zip_close(zipFile);
    zipFile = nullptr;
}

std::vector<std::string> ZIP::listFiles()
{
    std::vector<std::string> result;
    for (auto const& file : fileList)
        result.push_back(file.first);
    return result;
}

bool ZIP::fileExists(const std::string& fileName)
{
    auto it = fileList.find(fileName);
    if (it == fileList.end())
        return false;

    return true;
}


bool ZIP::getFile(const std::string& fileName, std::shared_ptr<std::vector<char>>& fileData)
{
    auto it = fileList.find(fileName);
    if (it == fileList.end())
        return false;

    auto file = zip_fopen_index(zipFile, it->second, 0);
    if (file == NULL)
        return false;

    zip_stat_t fileInfo;
    zip_stat_index(zipFile, it->second, 0, &fileInfo);

    // Initialize the buffer
    fileData = std::make_shared<std::vector<char>>(fileInfo.size);

    // Attempt to read the data into the buffer
    auto retval = zip_fread(file, fileData->data(), fileData->size());

    // Close the file
    zip_fclose(file);

    if (retval == -1)
        return false;

    return true;
}