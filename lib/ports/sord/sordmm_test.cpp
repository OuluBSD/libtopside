// Copyright 2011 David Robillard <d@drobilla.net>
// SPDX-License-Identifier: ISC

#include <ports/sord/sordmm.hpp>

#ifdef flagMAIN
int
main()
{
  Sord::World world;
  Sord::Model model(world, "http://example.org/");
  return 0;
}
#endif
