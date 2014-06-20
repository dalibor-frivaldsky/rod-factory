#pragma once


#include <rod/factory/Factory.hpp>




namespace rod
{

	namespace factory
	{

		template< typename FactoryType >
		struct FactorySelector;

		template< typename Type, typename... ToBeProvided >
		struct FactorySelector< Factory< Type, ToBeProvided... > >
		{
			enum { r = true };
		};

		template< typename OtherType >
		struct FactorySelector
		{
			enum { r = false };
		};
		
	}
	
}