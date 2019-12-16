#include "elly_svg.h"

#include "elly_results.h"

std::vector<std::string> elly::to_svg(const results&)
{
  //STUB
  return {
    "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
    "<svg width=\"200\" height=\"10\" viewBox=\"-10 0 10 1\" xmlns=\"http://www.w3.org/2000/svg\">",
    "<line x1=\"-1.2\" y1=\"1\" x2=\"3.4\" y2=\"1\" stroke=\"black\" />",
    "</svg>"
  };
}
