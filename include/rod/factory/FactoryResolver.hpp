#pragma once


#include <tuple>

#include <rod/annotation/Resolver.hpp>

#include <rod/factory/GetFactoryDeps.hpp>
#include <rod/factory/FactorySelector.hpp>




namespace rod
{

	namespace factory
	{

		class FactoryResolver;


		namespace factoryResolver
		{

			template< typename FactoryType >
			struct GetDependencies;

			template< typename Type, typename... ToBeProvided >
			struct GetDependencies< Factory< Type, ToBeProvided... > >
			{
				using r = typename GetFactoryDeps< Type, ToBeProvided... >::r;
			};
			
		}


		class FactoryResolver
		{
		public:

			using Resolver = annotation::Resolver<
								FactorySelector >;

			template< typename FactoryType >
			using GetDependencies = factoryResolver::GetDependencies< FactoryType >;


			template< typename FactoryType, typename... Dep >
			static
			FactoryType
			resolve( Dep&&... dep )
			{
				return FactoryType( std::make_tuple( dep... ) );
			}
		};
		
	}
	
}