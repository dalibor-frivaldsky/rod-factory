#pragma once




namespace rod
{

	namespace factory
	{

		template< typename Type, typename... ToBeProvided >
		class Factory
		{
		public:

			Type
			create()
			{
				return Type();
			}
		};
		
	}
	
}