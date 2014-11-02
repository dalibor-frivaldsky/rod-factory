#include <cassert>

#include <rod/Extend.hpp>
#include <rod/Rod.hpp>
#include <rod/Singleton.hpp>
#include <rod/annotation/Requires.hpp>

#include <rod/factory/FactoryResolver.hpp>




int value = 0;


struct Component
{
	void
	method( int v )
	{
		value = v;
	}
};


struct Type
{
private:

	Component&	component;
	int			v;


public:
	using Requires = rod::annotation::Requires< Component&, int >;

	Type( Component& component, int v ):
	  component( component ),
	  v( v )
	{}

	void
	method()
	{
		component.method( v );
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

		auto typeFactory = rod::resolve< rod::factory::Factory< Type, int > >( context );
		auto type = typeFactory.create( 10 );

		type.method();
	});

	assert( value == 10 );
}