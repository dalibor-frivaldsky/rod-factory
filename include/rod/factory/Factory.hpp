#pragma once


#include <functional>
#include <tuple>
#include <utility>

#include <rod/TypeList.hpp>
#include <rod/common/Sequence.hpp>

#include <rod/factory/GetFactoryDeps.hpp>




namespace rod
{

	namespace factory
	{

		namespace factory
		{

			template< typename Type, typename... ToBeProvided >
			struct DepsTuple
			{
			private:
				using deps = typename GetFactoryDeps< Type, ToBeProvided... >::r;


				template< typename T >
				struct MakeFunction
				{
					using r = std::function< T() >;
				};


			public:
				using r = typename deps::template Apply< MakeFunction >::r::AsTuple::r;
			};


			template< typename ToCreate, typename... Provided >
			struct Creator
			{
				template< typename ArgsTuple, int... Seq >
				static
				ToCreate
				create( ArgsTuple& argsTuple, rod::common::Sequence< Seq... >&&, Provided&&... provided )
				{
					return ToCreate( std::get< Seq >( argsTuple )()..., std::forward< Provided >( provided )... );
				}
			};
			
		}

		template< typename Type, typename... ToBeProvided >
		class Factory
		{
		private:
			using This = Factory< Type, ToBeProvided... >;
			using depsTuple = typename factory::DepsTuple< Type, ToBeProvided... >::r;

			depsTuple	deps;


		public:

			template< typename... Dependency >
			Factory( std::function< Dependency >&&... dependency ):
			  deps( std::make_tuple( std::move( dependency )... ) )
			{}

			Factory( const This& other ):
			  deps( other.deps )
			{}

			Factory( This&& other ):
			  deps( std::move( other.deps ) )
			{}


			Type
			create( ToBeProvided&&... provided )
			{
				return factory::Creator< Type, ToBeProvided... >::create(
							deps,
							typename rod::common::GenerateSequence< std::tuple_size< depsTuple >::value >::r(),
							std::forward< ToBeProvided >( provided )... );
			}
		};
		
	}
	
}