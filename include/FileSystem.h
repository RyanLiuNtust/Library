#ifndef FileSystem_H
#define FileSystem_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <boost\lexical_cast.hpp>
#include <boost\filesystem.hpp>

namespace fs = boost::filesystem;
// using getFileList() to parse all filename in specific directory
// and then can use the resizeDime() with respect sample and numRegister 
// to assign the number of second and first dimension of vector
// and it will sort by the default comparasion equation cmpNum
// add automatically create file and provide customization cmp
enum imgExt {
	JPG = 1,
	BMP,
	GIF,
	PNG
};

struct extMap:std::map<unsigned int, std::string> {
	extMap() {
		this->operator[](JPG) = ".jpg";
		this->operator[](BMP) = ".bmp";
		this->operator[](GIF) = ".gif";
		this->operator[](PNG) = ".png";
	};
};

class FileSystem {
	public:
		std::vector<std::string> getFileList(std::string dirName, imgExt ext,bool showList = false);
		// with specific output format
		std::vector<std::vector<std::string>> getFilelist(std::string dirName, int sample, int numRegister, bool showList = false);
		std::vector<std::string> getfilename();
		std::vector<std::vector<std::string>> appendPath();
		void showFileList(); //only for the mResizeFileList

	private:
		//bool sortBySecondNum(const std::string &p1, const std::string &p2);
		std::vector<std::vector<std::string>> resizeDim(int sample, int numRegister);
	private:
		std::vector<std::string> mFileList;
		std::vector<std::string> mDirFileList;
		std::vector<std::vector<std::string>> mResizeFileList;
		std::string mDirPath;
		int mSample;
		int mRegister;
};
#endif