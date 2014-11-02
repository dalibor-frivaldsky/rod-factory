#pragma once


#include <rod/TypeList.hpp>
#include <rod/annotation/Requires.hpp>




namespace rod
{

	namespace factory
	{

		template< typename Type, typename... ToBeProvided >
		struct GetFactoryDeps
		{
		private:
			using TypeDeps = typename rod::annotation::GetRequirements< Type >::r;

		public:
			using r = typename TypeDeps::template RemoveList< TypeList< ToBeProvided... > >::r;
		};
		
	}
	
}