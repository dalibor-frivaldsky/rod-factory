#pragma once


#include <functional>
#include <tuple>

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


			template< typename ToCreate >
			struct Creator
			{
				template< typename ArgsTuple, int... Seq >
				static
				ToCreate
				create( ArgsTuple& argsTuple, rod::common::Sequence< Seq... >&& )
				{
					return ToCreate( std::get< Seq >( argsTuple )()... );
				}
			};
			
		}

		template< typename Type, typename... ToBeProvided >
		class Factory
		{
		private:
			using depsTuple = typename factory::DepsTuple< Type, ToBeProvided... >::r;

			depsTuple	deps;


		public:

			Factory( depsTuple&& deps ):
			  deps( std::forward< depsTuple >( deps ) )
			{}


			Type
			create()
			{
				return factory::Creator< Type >::create(
							deps,
							typename rod::common::GenerateSequence< std::tuple_size< depsTuple >::value >::r() );
			}
		};
		
	}
	
}