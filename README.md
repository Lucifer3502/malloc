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

# LICENSE
  本网络库开放源码并遵循 [The MIT License](LICENSE) 开源协议。
