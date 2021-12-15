#include <emojifilt/emojifilt.hpp>

#include <cstddef>
#include <string>
#include <string_view>

#if defined(WITH_CTRE)
	#include <ctre.hpp>
#else
	#include <regex>
#endif

namespace emojifilt {

#if defined(WITH_CTRE)
static constexpr auto elRx = ctll::fixed_string{ "([^:]*):(\\w+):(.*)" };
#else
std::regex elRx(":(\\w+):", std::regex_constants::ECMAScript | std::regex_constants::icase);
#endif


void convert(libmo::TranslationDatabase &emojiDB, std::istream &i, std::ostream &o){
	std::string line;
	while(std::getline(i, line)) {
		#if defined(WITH_CTRE)
		std::string_view tail = line;
		while(true){
			if(auto match = ctre::match<elRx>(tail)){  // matched
				o << match.get<1>();
				auto name = match.get<2>().to_view();
				auto found = emojiDB.lookup(name);
				if(found.empty()) {// not found
					o << ":" << name << ":";
				} else {
					o << found;
				}
				tail = match.get<3>().to_view();
			} else { // not matched
				o << tail;
				break;
			}
		}
		#else
		std::sregex_iterator it {line.begin(), line.end(), elRx};
		const std::sregex_iterator stop;
		size_t endPos = 0;

		for(; it != stop; ++it) {
			const std::smatch &match = *it;
			o << match.prefix();
			const std::string_view fullMatch {line.data() + match.position(), static_cast<size_t>(match.length())};
			auto name = fullMatch.substr(1, fullMatch.size() - 2);
			auto found = emojiDB.lookup(name);
			if(found.empty()) {// not found
				o << fullMatch;
			} else {
				o << found;
			}
			o << match[3];
			
			endPos = static_cast<size_t>(match.position() + match.length());
		}

		o << std::string_view {line.data() + endPos, line.size() - endPos};
		#endif
		o << std::endl;
	}
}
};
