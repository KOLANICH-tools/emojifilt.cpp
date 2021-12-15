#pragma once
#include <istream>
#include <ostream>

#include <libmo/mo.hpp>

namespace emojifilt {

void convert(libmo::TranslationDatabase &emojiDB, std::istream &i, std::ostream &o);

};
