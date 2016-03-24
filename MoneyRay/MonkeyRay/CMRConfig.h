#ifndef CMRConfig_h__
#define CMRConfig_h__

//the choice for the precision of floating data, single precision and double precision
#define MR_SINGLE_PRECISION 1
#define MR_DOUBLE_PRECISION 2

#define ON 1
#define OFF 0

//the memory management strategy
#define MR_MEMORY_ALLOCATOR_STD			1
#define MR_MEMORY_ALLOCATOR_SGI_STL		2
#define MR_MEMORY_ALLOCATOR_NEDPOOLING	3
#define MR_MEMORY_ALLOCATOR_CUSTOM		4
#define MR_MEMORY_ALLOCATOR_BOOST		5

//define to use std::string or std::wstring
#define MR_USE_STRING 0
#define MR_USE_WSTRING 1

//define whether to use the allocator which aligns memory in the STL components
#define  MR_MEMORY_STL_ALLOCATOR_USE_ALIGNED 1
#define  MR_MEMORY_STL_ALLOCATOR_NOT_ALIGNED 0

//define whether to use aligned memory while allocating memory for object
#define	MR_MEMORY_ALLOCATE_OBJECT_USE_ALIGNED 1
#define MR_MEMORY_ALLOCATE_OBJECT_NOT_ALIGNED 0

//the real precision for the float data
#define MR_REAL_PRECISION MR_SINGLE_PRECISION
//the current strategy
#define MR_MEMORY_STRATEGY MR_MEMORY_ALLOCATOR_NEDPOOLING
//whether to use the custom memory allocator in STL container
#define MR_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR 1
//whether to use the custom memory allocator in string
#define MR_STRING_USE_CUSTOM_MEMORY_ALLOCATOR 0
//define to use std::string or std::wstring
#define MR_REAL_STRING_TYPE MR_USE_STRING


#define MR_MEMORY_NED_POOLING_ALIGNMENT 16
#define MR_MEMORY_STL_ALLOCATOR_IS_ALIGNED MR_MEMORY_STL_ALLOCATOR_USE_ALIGNED
#define MR_MEMORY_ALLOCATE_OBJECT_IS_ALIGNED MR_MEMORY_ALLOCATE_OBJECT_USE_ALIGNED

#define MR_USE_MULTITHREAD OFF
#endif // CMRConfig_h__
