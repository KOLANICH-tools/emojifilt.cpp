#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include <emojifilt/emojifilt.hpp>

#include "searchPathsConfig.hpp"

const std::string usage {" < original > converted"};
const std::string programName {"emojifilt"};
const std::string description {"converts :markers: in text files into actual emoji."};

#if defined(WITH_DB_PATH_RELATIVE_TO_BINARY)
#include <whereami.h>
#include <stdexcept>

std::filesystem::path currentExecutablePath(){
	auto len = wai_getExecutablePath(nullptr, 0, nullptr);
	if(len == -1){
		throw std::system_error(std::make_error_code(std::io_errc::stream));
	}
	size_t lenS = static_cast<size_t>(len);
	std::string res;
	res.reserve(lenS);
	res.resize(lenS);
	size_t dirnameSize = static_cast<size_t>(len);
	wai_getExecutablePath(res.data(), len, reinterpret_cast<int*>(&dirnameSize));
	res.resize(dirnameSize);
	return res;
}

std::filesystem::path discoverDbPathRelativeToBinary(){
	std::filesystem::path pathCandidate = currentExecutablePath() / dbFileName;
	if(std::filesystem::exists(pathCandidate)){
		return pathCandidate;
	}
	return "";
}
#endif

#if defined(WITH_DB_PATH_ACCORDING_TO_FHS)
std::filesystem::path dbRelatibePath = std::filesystem::path{resourcesSubdirName} / dbFileName;
constexpr std::string_view currentWorkingDir{"."};

std::array<std::filesystem::path, 3> emojiDatabasePaths{
	std::filesystem::path{dataRootDir} / dbRelatibePath,
	std::filesystem::path{sysConfDir} / dbRelatibePath,
	std::filesystem::path{currentWorkingDir} / dbFileName
};

std::filesystem::path discoverDbPathHardcoded(){
	std::filesystem::path dbPath;
	for(auto &pathCandidate: emojiDatabasePaths){
		if(std::filesystem::exists(pathCandidate)){
			return pathCandidate;
		}
	}
	return "";
}

std::filesystem::path discoverDbPath(){
	#if defined(WITH_DB_PATH_RELATIVE_TO_BINARY)
	auto res = discoverDbPathRelativeToBinary();
	if(!res.empty()){
		return res;
	}
	#endif
	return discoverDbPathHardcoded();
}
#else
std::filesystem::path discoverDbPath(){
#if defined(WITH_DB_PATH_RELATIVE_TO_BINARY)
	return discoverDbPathRelativeToBinary();
#else
	#error "On OSes not following FHS we have to discover path relative to binary"
	return "";
#endif
}
#endif


int main(int argc, const char **argv) {
	std::ios::sync_with_stdio(false);

	auto printHelp = [&]() -> int {
		if(argc == 1) {
			std::cout << argv[0];
		} else {
			std::cout << programName;
		}
		std::cout << usage << std::endl;
		std::cout << description << std::endl;
		return 1;
	};

	if(argc > 1) {
		return printHelp();
	}

	auto dbPath = discoverDbPath();
	
	if(dbPath.empty()){
		std::cerr << "No emoji database found" << std::endl;
		return 1;
	}
	
	std::ifstream dbStream(dbPath, std::ifstream::binary);
	auto emojiDB = libmo::open(dbStream);

	emojifilt::convert(*emojiDB, std::cin, std::cout);
	
	return 0;
}
