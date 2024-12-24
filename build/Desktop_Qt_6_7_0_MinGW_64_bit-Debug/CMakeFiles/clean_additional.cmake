# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\fistfight_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\fistfight_autogen.dir\\ParseCache.txt"
  "fistfight_autogen"
  )
endif()
