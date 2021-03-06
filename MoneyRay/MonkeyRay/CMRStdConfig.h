#ifndef CMRStdConfig_h__
#define CMRStdConfig_h__

//C library
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

//STL Container
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <set>
#include <unordered_set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <stack>
#include <forward_list>

//STL thread
#include <thread>
#if MR_USE_MULTITHREAD
#include <mutex>
#endif
#include <atomic>
#include <condition_variable>
#include <future>

//STL algorithms and functions and regex
#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>

//STL stream
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#endif // CMRStdConfig_h__
