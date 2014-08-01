#include <cassert>

#include <rod/Contextual.hpp>
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


template< typename Context >
class Domain:
  public rod::Contextual< Context,
  						  rod::factory::FactoryResolver >
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