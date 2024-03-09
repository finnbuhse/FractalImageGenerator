# CMakeList.txt : CMake project for Fractal, include source and define
# project specific logic here.
#

# Add source to this project's executable.
include_directories(
	"F:/Projects/opencv/include" "F:/Projects/opencv/modules/core/include" "F:/Projects/opencv/out"
	"F:/Projects/opencv/modules/imgcodecs/include"
#[[
# OpenCV modules
	"F:/Projects/opencv/modules/calib3d/include" 
	"F:/Projects/opencv/modules/dnn/include"
	"F:/Projects/opencv/modules/features2d/include"
	"F:/Projects/opencv/modules/flann/include"
	"F:/Projects/opencv/modules/highgui/include"
	
	"F:/Projects/opencv/modules/imgproc/include"
	"F:/Projects/opencv/modules/ml/include"
	"F:/Projects/opencv/modules/objdetect/include"
	"F:/Projects/opencv/modules/photo/include"
	"F:/Projects/opencv/modules/stitching"
	"F:/Projects/opencv/modules/video/include"
	"F:/Projects/opencv/modules/videoio/include"
]]
)


add_executable (FractalImageGenerator  "Main.cpp" "FractalImageGenerator.cpp" "ColourSet.cpp" "Complex.cpp" "FractalImageGenerator.h" "ColourSet.h" "Bounds.h" "Complex.h")

target_link_directories(FractalImageGenerator PRIVATE 
	F:/Projects/opencv/out/lib/Debug
)

target_link_libraries(FractalImageGenerator PRIVATE
	opencv_core490d
	opencv_imgcodecs490d
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FractalImageGenerator PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
