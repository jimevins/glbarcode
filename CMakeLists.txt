cmake_minimum_required (VERSION 2.8)

project (GLBARCODE_PP)

set (Package_Name "glbarcode++")

set (API_Version     "0")
set (Feature_Version "0")
set (Bugfix_Version  "0")

set (Package_Version "${API_Version}.${Feature_Version}.${Bugfix_Version}")
set (Package_URL "https://github.com/jimevins/glbarcode")

set (Lib_Name ${Package_Name}-${API_Version})
set (CAPI_Lib_Name ${Package_Name}-capi-${API_Version})

add_definitions (-g)

add_subdirectory (glbarcode)
add_subdirectory (glbarcode/capi)
add_subdirectory (examples)
add_subdirectory (app)
add_subdirectory (doc)
add_subdirectory (test)
add_subdirectory (test/capi)

