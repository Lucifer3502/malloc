# note
  - 这是一个简易的内存管理库，使用方式同标准的`malloc`，`free`函数。
  - 原理是使用一个全局的内存块，对外提供动态的内存分配与释放。内存块的大小可以自定义。
  - 除了`malloc`，`free`函数外，另外提供了查询剩余内存`get_free_heap_size`和显示内存映射图`show_mem_map`两个api接口。
  - 支持32位和64位系统。已经在`Ubuntu16.04.5 X86_64`系统上验证通过。
  - 可以使用在类似嵌入式系统等没有内存管理库的平台之上。比如`stm32`平台等。

# quick start
  我们以linux系统为例，介绍一下使用和测试方法。

	sudo apt-get install cmake
	cd malloc
	mkdir build 
	cd build
	cmake ..
	make
	./bin/memdemo

# principle 
 - 使用一个巧妙的技巧，来标记每个申请或者释放的内存块，并且能够双向查找内存块。
 - 在释放内存的时候，双向查找能够很方便的合并内存块，比如前向合并，后向合并。
 - 数据结构简单，只用到了一个4字节的头结点来标识内存块的状态和大小，这四个字节不仅能标识自身内存块的状态和大小，而且能标识前向内存块的状态和大小。
 - 双向查找的核心原理是：在已经释放内存的内存块的末尾，保存当前内存块的头地址。如果该内存块没有被释放，则没有必要保存。因为如果当前内存块的下一个内存块处于释放状态时，当前内存块如果没有被释放，则不需要查找当前内存块的地址。
 - 具体可以参考这个图，灰色标识正在使用的内存，绿色标识空闲内存。[示意图]()

# defect 
 - 内存申请时，没有对内存大小做最优化处理。
 - 因此，如果内存申请不够平均，时间久了，如果有内存未释放，可能会有碎片。但是针对一般的应用，少量的内存分配请求是足够的。
 
# LICENSE
  本网络库开放源码并遵循 [The MIT License](LICENSE) 开源协议。
