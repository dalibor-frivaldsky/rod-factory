#pragma once


#include <functional>




namespace rod
{

	namespace factory
	{

		template< typename Dependency >
		struct DependencyResolver
		{
		private:

			template< typename Context >
			DependencyResolver( Context& context )
		};
		
	}
	
}