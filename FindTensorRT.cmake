find_package(CUDA REQUIRED)

set(TensorRT_ROOT /usr/src/tensorrt)


# find all include directories
find_path(TensorRT_INCLUDE_DIRS NvInfer.h
        HINTS ${TensorRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
        PATH_SUFFIXES include)
set(TensorRT_INCLUDE_DIRS
        ${TensorRT_INCLUDE_DIRS} ${TensorRT_ROOT}/samples/common ${CUDA_INCLUDE_DIRS})
# find all libraries
find_library(TensorRT_LIBRARY_NVINFER nvinfer
        HINTS ${TensorRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
        PATH_SUFFIXES lib lib64 lib/x64)
find_library(TensorRT_LIBRARY_NVINFER_PLUGIN nvinfer_plugin
        HINTS ${TensorRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
        PATH_SUFFIXES lib lib64 lib/x64)
#find_library(TensorRT_LIBRARY_NVCAFFE_PARSER nvcaffe_parser
#        HINTS ${TensorRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
#        PATH_SUFFIXES lib lib64 lib/x64)
find_library(TensorRT_LIBRARY_NVONNXPARSER nvonnxparser
        HINTS ${TensorRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
        PATH_SUFFIXES lib lib64 lib/x64)
#find_library(TensorRT_LIBRARY_NVPARSERS nvparsers
#        HINTS ${TensorRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
#        PATH_SUFFIXES lib lib64 lib/x64)
#find_library(TensorRT_LIBRARY_CUDART cudart
#        HINTS ${TensorRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
#        PATH_SUFFIXES lib lib64 lib/x64)

set(TensorRT_LIBS
        ${TensorRT_LIBRARY_NVINFER}
        ${TensorRT_LIBRARY_NVINFER_PLUGIN}
#        ${TensorRT_LIBRARY_NVCAFFE_PARSER}
        ${TensorRT_LIBRARY_NVONNXPARSER}
#        ${TensorRT_LIBRARY_NVPARSERS}
#        ${TensorRT_LIBRARY_CUDART}
        ${CUDA_LIBRARIES}
        )
# find all source files
#aux_source_directory(${TensorRT_ROOT}/samples/common TensorRT_SOURCE)
set(TensorRT_SOURCE ${TensorRT_ROOT}/samples/common/logger.cpp)

find_package_handle_standard_args(
        TensorRT DEFAULT_MSG TensorRT_INCLUDE_DIRS TensorRT_LIBS TensorRT_SOURCE)
