#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "algorithms" ? 0 : 1;
}
