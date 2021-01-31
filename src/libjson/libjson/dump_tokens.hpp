#pragma once

#include <iosfwd>

namespace json {

void dump_tokens(std::istream& in, std::ostream& out);

}  // namespace json
