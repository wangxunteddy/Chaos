#ifndef _CHS_MACRO_H
#define _CHS_MACRO_H

#define _DEFINE_PROPERTY( type, property )				\
		private: type _##property;

#define _DEFINE_PROPERTY_GETTER( type, property )		\
		public: type property( void );

#define _DEFINE_PROPERTY_GETTER_CONST( type, property ) \
		public: const type property( void ) const;

#define _DEFINE_PROPERTY_SETTER( type, property ) 		\
		public: void property(type _##property);

#define PROPERTY( type, property )						\
		_DEFINE_PROPERTY( type, property )				\
		_DEFINE_PROPERTY_GETTER( type, property )		\
		_DEFINE_PROPERTY_SETTER( type, property )

#define PROPERTY_CONST( type, property )				\
		_DEFINE_PROPERTY( type, property )				\
		_DEFINE_PROPERTY_GETTER_CONST( type, property )	\
		_DEFINE_PROPERTY_SETTER( type, property )


#define PROPERTY_READONLY( type, property )				\
		_DEFINE_PROPERTY( type, property )				\
		_DEFINE_PROPERTY_GETTER( type, property )

#define PROPERTY_READONLY_CONST( type, property )		\
		_DEFINE_PROPERTY( type, property )				\
		_DEFINE_PROPERTY_GETTER_CONST( type, property )

#define PROPERTY_WRITEONLY( type, property )			\
		_DEFINE_PROPERTY( type, property )				\
		_DEFINE_PROPERTY_SETTER( type, property )


#define SYNTHESIZE_GETTER( class, type, property )		\
		inline type class::property( void ){ return this->_##property; }

#define SYNTHESIZE_GETTER_CONST( class, type, property )\
		inline const type class::property( void ) const { return this->_##property; }

#define SYNTHESIZE_SETTER( class, type, property )		\
		inline void class::property( type _##property ){ this->_##property = _##property; }


#define SYNTHESIZE_READONLY				SYNTHESIZE_GETTER
#define SYNTHESIZE_READONLY_CONST		SYNTHESIZE_GETTER_CONST
#define SYNTHESIZE_WRITEONLY			SYNTHESIZE_SETTER


#define SYNTHESIZE( class, type, property)				\
		SYNTHESIZE_GETTER( class, type, property)		\
		SYNTHESIZE_SETTER( class, type, property)


#define SYNTHESIZE_CONST( class, type, property)		\
		SYNTHESIZE_GETTER_CONST( class, type, property)	\
		SYNTHESIZE_SETTER( class, type, property)

#endif//_CHS_MACRO_H
