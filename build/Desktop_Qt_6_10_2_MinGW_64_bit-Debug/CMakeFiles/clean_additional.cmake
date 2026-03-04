# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FinancialDashboard_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FinancialDashboard_autogen.dir\\ParseCache.txt"
  "FinancialDashboard_autogen"
  )
endif()
