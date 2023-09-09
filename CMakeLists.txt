cmake_minimum_required(VERSION 3.11 )
project(RM_RPS_Radar2023)

find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)
#find_package(TensorRT REQUIRED)
#find_package(fmt REQUIRED)

option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

set(CMAKE_BUILD_TYPE "Debug")
set(set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_FLAGS "-std=c++11"))
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O0  -Wall -fopenmp")
set(CUDA_GEN_CODE "-gencode=arch=compute_86,code=sm_86")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS}  -std=c++17 -O0 -Xcompiler -fPIC -g -w ${CUDA_GEN_CODE}")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Ofast -Wfatal-errors -D_MWAITXINTRIN_H_INCLUDED")

include_directories(
        ${PROJECT_SOURCE_DIR}/Net/TRTInfer/include
        ${EIGEN3_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS}
        ${TensorRT_INCLUDE_DIRS}
)


cuda_add_executable(
        ${PROJECT_NAME}
        main.cpp
        general/general.cpp
        Image/src/Image.cpp
        Net/Net.cpp
        Net/TRTInfer/src/Inference.cpp
        Net/TRTInfer/CUDA/preprocess.cu
        Place/src/getLocate3D_cls.cpp
        Place/src/place_post_cfg.cpp
        Place/Mouse/Mouse.cpp
        Port/scr/CRC_Check.cpp
        Port/scr/Port.cpp
        Port/scr/serialport.cpp

        Camera/HikCamera/HikCamera.cpp


)


#target_include_directories(${PROJECT_NAME} PUBLIC ./ ./net_onnx/include)

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}  ${OpenCV_LIBS})

## GalaxyCamera
#add_subdirectory(GalaxyCameraReader)
#target_include_directories(${PROJECT_NAME} PUBLIC  GalaxyCameraReader)
#target_link_libraries(${PROJECT_NAME} PUBLIC "GalaxyCameraReader")

# HikCamera

target_include_directories(${PROJECT_NAME} PUBLIC ${MVCAM_SDK_PATH}/include )
target_include_directories(${PROJECT_NAME} PUBLIC /opt/MVS/include/)
target_link_libraries(${PROJECT_NAME}  /opt/MVS/lib/64/libMvCameraControl.so )
target_link_libraries(${PROJECT_NAME}  ${LD_LIBRARY_PATH} )
#
set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(${PROJECT_NAME}  nvinfer)
target_link_libraries(${PROJECT_NAME}  cudart)
target_link_libraries(${PROJECT_NAME}  nvonnxparser)
target_link_libraries(${PROJECT_NAME}  cuda)
target_link_libraries(${PROJECT_NAME}  ${TensorRT_LIBS})

#eigen3
include_directories(/usr/include/eigen3)

#fmt
target_link_libraries(${PROJECT_NAME}  fmt)

#yaml-cpp
find_package(yaml-cpp REQUIRED)
include_directories(/usr/local/include/yaml-cpp)
target_link_libraries(${PROJECT_NAME} /usr/local/lib/libyaml-cpp.so)

# 在Linux系统下，多线程模块并非自动链接的，需要额外链接。
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(Threads)
    target_link_libraries(${PROJECT_NAME}  ${CMAKE_THREAD_LIBS_INIT})
endif()

#其他
target_link_libraries(${PROJECT_NAME}  dl pthread m)

