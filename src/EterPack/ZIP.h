#include <string>
#include <map>
#include <zip.h>

#include "FileProvider.h"

class ZIP : public FileProvider
{
protected:
	zip_t* zipFile = nullptr;
	std::map<std::string, zip_uint64_t> fileList;

public:
	ZIP(const std::string& archivePath);
	~ZIP();

	std::vector<std::string> listFiles();
	bool fileExists(const std::string& fileName);
	bool getFile(const std::string& fileName, std::shared_ptr<std::vector<char>>& fileData);
};
