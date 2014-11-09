#pragma once


#include <utility>

#include <rod/Resolve.hpp>
#include <rod/TypeList.hpp>

#include <rod/factory/GetFactoryDeps.hpp>




namespace rod {
namespace factory
{

	namespace detail
	{

		template< typename ToCreate, typename Deps >
		struct Create;

		template< typename ToCreate >
		struct Create< ToCreate, TypeList<> >
		{
			template< typename Context, typename... ToForward >
			static
			ToCreate
			create( Context&, ToForward&&... toForward )
			{
				return ToCreate(
					std::forward< ToForward >( toForward )... );
			}
		};

		template< typename ToCreate, typename... Dep >
		struct Create< ToCreate, TypeList< Dep... > >
		{
			template< typename Context, typename... ToForward >
			static
			ToCreate
			create( Context& context, ToForward&&... toForward )
			{
				return ToCreate(
					rod::resolve< Dep >( context )...,
					std::forward< ToForward >( toForward )... );
			}
		};
		
	}


	template< typename ToCreate, typename Context, typename... ToForward >
	ToCreate
	create( Context& context, ToForward&&... toForward )
	{
		using Deps = typename GetFactoryDeps< ToCreate, ToForward... >::r;

		return detail::Create< ToCreate, Deps >::create(
					context,
					std::forward< ToForward >( toForward )... );
	}
	
}}