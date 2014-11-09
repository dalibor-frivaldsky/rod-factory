#include <cassert>

#include <rod/Extend.hpp>
#include <rod/Rod.hpp>
#include <rod/Singleton.hpp>
#include <rod/annotation/Requires.hpp>

#include <rod/factory/Create.hpp>




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
							rod::Singleton< Component > >()();

		auto type = rod::factory::create< Type >( context, 10 );

		type.method();
	});

	assert( value == 10 );
}