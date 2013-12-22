#include "FileSystem.h"

bool FileSystem::sortBySecondNum(const std::string &p1, const std::string &p2) {
//e.g. 10_123.bmp p1_sNum = 123
//	   23_32.bmp  p2_sNum =32
	std::size_t p1_underline = p1.find("_");
	std::size_t p1_fullstop  = p1.find(".");
	std::size_t p2_underline = p2.find("_");
	std::size_t p2_fullstop  = p2.find(".");

	char p1_sNum[3];
	char p2_sNum[3];
	p1_sNum[p1.copy(p1_sNum, p1_fullstop - p1_underline-1, p1_underline + 1)] = '\0';
	p2_sNum[p2.copy(p2_sNum, p2_fullstop - p2_underline-1, p2_underline + 1)] = '\0';

	return boost::lexical_cast<int>(p1_sNum) < boost::lexical_cast<int>(p2_sNum);
}

std::vector<std::string> FileSystem::getFileList(std::string dirName, imgExt ext, bool showList) {
	extMap map;
	mDirPath = dirName;
	fs::path mDirName(mDirPath);
	//if(!fs::exists(mDirName)) return NULL;

	if(fs::is_directory(mDirName)) {
		fs::recursive_directory_iterator it(mDirName);
		fs::recursive_directory_iterator end;
		while(it != end) {
			if(fs::is_regular_file(*it) && it->path().extension() == map[ext]) {
				mFileList.push_back(it->path().filename().string());
			}
			++it;
		}
	}
	if(showList) showFileList();
	return mFileList;
}
// resizeDim() is to make it straightforward
// the result array will be the two dimesion array
// and organized as result[sample][numRegister]
// only for following named image
// e.g. sample_numRegister.bmp
std::vector<std::vector<std::string>> FileSystem::resizeDim(int sample, int numRegister) {
	mResizeFileList = std::vector<std::vector<std::string>> (sample, numRegister);
	mSample = sample;
	mRegister = numRegister;

	for(int s = 0; s < sample; s++) {
		std::vector<std::string> colFileList(numRegister);
		for(int n = 0; n < numRegister; n++) {
			colFileList[n] = mFileList[s*numRegister + n];
		}
		std::sort(colFileList.begin(), colFileList.end(), sortBySecondNum);
		for(int n = 0; n < numRegister; n++){
			mResizeFileList[s][n] = colFileList[n];
		}
	}
	
	return mResizeFileList;
}

std::vector<std::vector<std::string>> FileSystem::appendPath() {
	for(int s = 0; s < mSample; s++) {
		for(int n = 0; n < mRegister; n++) {
			mResizeFileList[s][n] = mDirPath + mResizeFileList[s][n];
		}
	}
	return mResizeFileList;
}

void FileSystem::showFileList() {
	/*int i = 0;
	for(std::vector<std::string>::iterator it = mFileList.begin(); it!= mFileList.end(); it++, i++) {
		std::cout << "<" << i << ">\t" << *it << std::endl;
	}*/
	int i = 0;
	for(std::vector<std::vector<std::string>>::iterator it = mResizeFileList.begin(); it != mResizeFileList.end(); it++) {
		for(std::vector<std::string>::iterator inner = it->begin(); inner != it->end(); inner++, i++) {
			std::cout << "<" << i << ">\t" << *inner << std::endl;
		}
	}
}

std::vector<std::vector<std::string>> FileSystem::getImageName(std::string dirName, int sample, int numRegister,bool showList) {
	std::vector<std::vector<std::string>> filePath;
	getFileList(dirName, BMP);
	resizeDim(sample, numRegister);
	filePath = appendPath();

	if(showList) showFileList();
	return filePath;
}