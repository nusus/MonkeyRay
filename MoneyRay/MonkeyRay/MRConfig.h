#ifndef MRConfig_h__
#define MRConfig_h__

//the choice for the precision of floating data, single precision and double precision
#define MR_SINGLE_PRECISION 1
#define MR_DOUBLE_PRECISION 2

//the real precision for the float data
#define MR_REAL_PRECISION 1

//the memory management strategy
#define MR_MEMORY_ALLOCATOR_STD			1
#define MR_MEMORY_ALLOCATOR_SGI_STL		2
#define MR_MEMORY_ALLOCATOR_NEDPOOLING	3
#define MR_MEMORY_ALLOCATOR_CUSTOM		4
#define MR_MEMORY_ALLOCATOR_BOOST		5

//the current strategy
#define MR_MEMORY_STRATEGY 3

#endif // MRConfig_h__
