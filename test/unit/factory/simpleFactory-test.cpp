#include <cassert>

#include <rod/Extend.hpp>
#include <rod/Rod.hpp>

#include <rod/factory/FactoryResolver.hpp>




bool called = false;


struct Type
{
	void
	method()
	{
		called = true;
	}
};


void
test()
{
	rod::enter(
	[] ( rod::Root& root )
	{
		auto	canResolve = rod::extend( root ).with< rod::factory::FactoryResolver >()();

		auto	typeFactory = rod::resolve< rod::factory::Factory< Type > >( canResolve );
		auto	type = typeFactory.create();

		type.method();
	});

	assert( called );
}