﻿#pragma once

#ifdef WIN32
	#include <windows.h>
#elif POSIX
	#include <dlfcn.h>
#else
	#error "Undefine platform"
#endif

#include <string>

namespace HttpServer
{
	class Module
	{
	protected:
	#ifdef WIN32
		::HMODULE lib_handle;
	#elif POSIX
		void *lib_handle;
	#else
		#error "Undefine platform"
	#endif

	public:
		Module();
		Module(const std::string &libPath);
		Module(const Module &module);
		Module(Module &&module);

		~Module() = default;

		inline bool is_open() const
		{
			return nullptr != lib_handle;
		}

		bool open(const std::string &libPath);
		void close();

		bool find(const std::string &symbolName, void *(**addr)(void *) ) const;
		bool find(const char *symbolName, void *(**addr)(void *) ) const;

		inline bool operator ==(const Module &module) const
		{
			return lib_handle == module.lib_handle;
		}

		inline bool operator !=(const Module &module) const
		{
			return lib_handle != module.lib_handle;
		}

		Module &operator =(const Module &);
		Module &operator =(Module &&);
	};
};