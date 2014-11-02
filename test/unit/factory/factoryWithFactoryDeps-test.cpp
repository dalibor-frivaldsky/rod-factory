#include <cassert>

#include <rod/Extend.hpp>
#include <rod/Rod.hpp>
#include <rod/Singleton.hpp>
#include <rod/annotation/Requires.hpp>

#include <rod/factory/FactoryResolver.hpp>

#include <rod/factory/FactoryResolver.hpp>




bool called = false;


struct Component
{
	void
	method()
	{
		called = true;
	}
};


struct InnerType
{
	private:

	Component&	component;


public:
	using Requires = rod::annotation::Requires< Component& >;

	InnerType( Component& component ):
	  component( component )
	{}

	void
	method()
	{
		component.method();
	}
};


struct Type
{
private:

	using InnerTypeFactory = rod::factory::Factory< InnerType >;

	InnerTypeFactory	innerTypeFactory;


public:
	using Requires = rod::annotation::Requires< InnerTypeFactory >;

	Type( InnerTypeFactory innerTypeFactory ):
	  innerTypeFactory( innerTypeFactory )
	{}

	void
	method()
	{
		innerTypeFactory.create().method();
	}
};


void
test()
{
	rod::enter(
	[] ( rod::Root& root )
	{
		auto context = rod::extend( root )
						.with<
							rod::factory::FactoryResolver,
							rod::Singleton< Component > >()();

		auto typeFactory = rod::resolve< rod::factory::Factory< Type > >( context );
		auto type = typeFactory.create();

		type.method();
	});

	assert( called );
}