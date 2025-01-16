# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\projetSE_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\projetSE_autogen.dir\\ParseCache.txt"
  "projetSE_autogen"
  )
endif()
