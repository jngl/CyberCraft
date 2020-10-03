#pragma once

#include <string>
#include <iostream>

namespace debug
{
	namespace
	{
		template <typename T>
		void log2(T t) 
		{
			std::cout << t;
		}
		
		template<typename T, typename... Args>
		void log2(T t, Args... args) // recursive variadic function
		{
			std::cout << t;

			log2(args...) ;
		}
	}

	template<typename... Args>
	void log(std::string module, Args... args) // recursive variadic function
	{
		std::cout << module << " : " ;

		log2(args...) ;
		
		std::cout  <<std::endl ;
	}
	
	template<typename... Args>
	void assert(std::string module, bool cond, Args... args) // recursive variadic function
	{
		if(cond)return;
		
		std::cout <<"assert error in "<< module << " : " ;

		log2(args...) ;
		
		std::cout  <<std::endl ;
		
		exit(1);
	}
}

#define IM_ASSERT(cond) debug::assert("ImGUI", cond, "")
