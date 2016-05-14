#include "CMRMemoryNedPooling.h"

#include <algorithm>
#include <thread>


#include <nedmalloc/nedmalloc.c>
namespace MR
{
	namespace NedPoolingImpl_OGRE
	{
		const size_t g_kPoolCount = 14;
		void* g_pPoolFootprint = reinterpret_cast<void*>(0xBB1AA45A);
		nedalloc::nedpool* g_pPools[g_kPoolCount + 1] = { 0 };
		nedalloc::nedpool* g_pAlignedPools[g_kPoolCount + 1] = { 0 };

		size_t GetPoolIDFromSize(size_t nSize)
		{
			size_t poolID = 0;
			if (nSize > 0)
			{
				if (nSize <= 16)
				{
					poolID = (nSize - 1) >> 2;
				}
				else
				{
					poolID = std::min<size_t>(((nSize - 1) >> 4) + 3, g_kPoolCount);
				}
			}
			return poolID;
		}

		void* AllocateImpl(size_t nSize)
		{
			size_t nPoolID = GetPoolIDFromSize(nSize);
			nedalloc::nedpool* pool(0);

			if (nPoolID < g_kPoolCount)
			{
				if (g_pPools[nPoolID] == 0)
				{
					size_t nThreads = std::thread::hardware_concurrency();
					if (nThreads == 0)
					{
						nThreads = 4;
					}
					g_pPools[nPoolID] = nedalloc::nedcreatepool(0, nThreads);
					nedalloc::nedpsetvalue(g_pPools[nPoolID], g_pPoolFootprint);
				}
				pool = g_pPools[nPoolID];
			}
			return nedalloc::nedpmalloc(pool, nSize);
		}

		void* AllocateAlignedImpl(size_t nSize, size_t nAlignment)
		{
			size_t nPoolID = GetPoolIDFromSize(nSize);
			nedalloc::nedpool* pool(0);

			if (nPoolID < g_kPoolCount)
			{
				if (g_pAlignedPools[nPoolID] == 0)
				{
					size_t nThreads = std::thread::hardware_concurrency();
					if (nThreads == 0)
					{
						nThreads = 4;
					}
					g_pAlignedPools[nPoolID] = nedalloc::nedcreatepool(0, 4);
					nedalloc::nedpsetvalue(g_pAlignedPools[nPoolID], g_pPoolFootprint);
				}
				pool = g_pAlignedPools[nPoolID];
			}
			return nedalloc::nedpmemalign(pool, nAlignment, nSize);
		}

		void FreeImpl(void* ptr)
		{
			if (ptr)
			{
				nedalloc::nedpool* pool(0);
				void* pFootprint = nedalloc::nedgetvalue(&pool, ptr);

				if (pFootprint == g_pPoolFootprint)
				{
					nedalloc::nedpfree(pool, ptr);
				}
				else
				{
					nedalloc::nedfree(ptr);
				}
			}
		}
	}

	void* CMRMemoryNedPoolingAux::Allocate(size_t count)
	{
		return NedPoolingImpl_OGRE::AllocateImpl(count);
	}

	void CMRMemoryNedPoolingAux::Deallocate(void* ptr)
	{
		if (!ptr)
		{
			return;
		}
		NedPoolingImpl_OGRE::FreeImpl(ptr);
	}

	void* CMRMemoryNedPoolingAux::AllocateAligned(size_t count, size_t alignment)
	{
		const size_t kSIMDAlignment = 16;
		return alignment ? (NedPoolingImpl_OGRE::AllocateAlignedImpl(count, alignment)) 
		: (NedPoolingImpl_OGRE::AllocateAlignedImpl(count, kSIMDAlignment));
	}

	void CMRMemoryNedPoolingAux::DeallocateAligned(void* ptr, size_t alignment)
	{
		if (!ptr)
		{
			return;
		}
		NedPoolingImpl_OGRE::FreeImpl(ptr);
	}


}
