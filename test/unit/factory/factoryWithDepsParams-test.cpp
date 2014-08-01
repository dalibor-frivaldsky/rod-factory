#include <cassert>

#include <rod/AsSingleton.hpp>
#include <rod/Contextual.hpp>
#include <rod/Rod.hpp>
#include <rod/annotation/ConstructWith.hpp>

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
	using ConstructWith = rod::annotation::ConstructWith< Component&, int >;

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


template< typename Context >
class Domain:
  public rod::Contextual< Context,
  						  rod::factory::FactoryResolver,
  						  rod::AsSingleton< Component > >
{
public:

	ROD_Contextual_Constructor( Domain )

	void
	enter()
	{
		auto typeFactory = rod::resolve< rod::factory::Factory< Type, int > >( this );
		auto type = typeFactory.create( 10 );

		type.method();
	}
};


void
test()
{
	rod::enterPlain< Domain >();

	assert( value == 10 );
}