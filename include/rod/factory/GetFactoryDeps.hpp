#pragma once


#include <rod/TypeList.hpp>
#include <rod/annotation/ConstructWith.hpp>




namespace rod
{

	namespace factory
	{

		template< typename Type, typename... ToBeProvided >
		struct GetFactoryDeps
		{
		private:
			using typeDeps = typename rod::annotation::GetConstructionArguments< Type >::r;

		public:
			using r = typename typeDeps::template RemoveList< TypeList< ToBeProvided... > >::r;
		};
		
	}
	
}