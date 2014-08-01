#include <cassert>

#include <rod/AsSingleton.hpp>
#include <rod/Contextual.hpp>
#include <rod/Rod.hpp>
#include <rod/annotation/ConstructWith.hpp>

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


struct Type
{
private:

	Component&	component;


public:
	using ConstructWith = rod::annotation::ConstructWith< Component& >;

	Type( Component& component ):
	  component( component )
	{}

	void
	method()
	{
		component.method();
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
		auto typeFactory = rod::resolve< rod::factory::Factory< Type > >( this );
		auto type = typeFactory.create();

		type.method();
	}
};


void
test()
{
	rod::enterPlain< Domain >();

	assert( called );
}