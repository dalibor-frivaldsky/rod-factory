#pragma once


#include <functional>
#include <tuple>

#include <rod/TypeList.hpp>
#include <rod/annotation/Resolver.hpp>

#include <rod/factory/GetFactoryDeps.hpp>
#include <rod/factory/FactorySelector.hpp>




namespace rod
{

	namespace factory
	{

		class FactoryResolver;


		namespace detail
		{

			template< typename FactoryType >
			struct GetDependencies;

			template< typename Type, typename... ToBeProvided >
			struct GetDependencies< Factory< Type, ToBeProvided... > >
			{
				using r = typename GetFactoryDeps< Type, ToBeProvided... >::r;
			};


			template< typename Dependency >
			struct CreateResolveClosure
			{
				template< typename Context >
				static
				std::function< Dependency() >
				create( Context& context )
				{
					return [&] () -> decltype( resolve< Dependency >( context ) ) { return resolve< Dependency >( context ); };
				}
			};


			template< typename FactoryType, typename Dependencies >
			struct CreateFactory;

			template< typename FactoryType >
			struct CreateFactory< FactoryType, TypeList<> >
			{
				template< typename Context >
				static
				FactoryType
				create( Context& context )
				{
					return FactoryType();
				}
			};

			template< typename FactoryType, typename... Dependency >
			struct CreateFactory< FactoryType, TypeList< Dependency... > >
			{
				template< typename Context >
				static
				FactoryType
				create( Context& context )
				{
					return FactoryType( CreateResolveClosure< Dependency >::create( context )... );
				}
			};
			
		}


		class FactoryResolver
		{
		public:

			using Resolver = annotation::Resolver<
								FactorySelector >;

			template< typename FactoryType, typename Context >
			static
			FactoryType
			resolve( Context& context )
			{
				return detail::CreateFactory<
						FactoryType,
						typename detail::GetDependencies< FactoryType >::r >::create( context );
			}
		};
		
	}
	
}