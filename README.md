## PubSub
Simple implementation of the Publish/subscribe pattern


## Usage
You can use this module in the following ways:

'''

	#include <iostream>
	#include "PubSub.h"

	struct Foo {
		Foo() {};

		/// object functor style
		void operator() (int e, int arg) {
			this->callback(e, arg);
		}

		/// simple function
		void callback(int e, int arg) {
			printf("The argument %d\n", arg);
		}
	};
			
	int main(int argc, char** argv) {
		// 1  - used lyambda function
		utils::PubSub<int, int> pubsub1;
		pubsub1.on(1, [](int e, int arg) {
			printf("The argument %d\n", arg);
		});
		pubsub1.emit(1, 1);
			
		// 2 - used lyambda with a class argument
		utils::PubSub<int, Foo> pubsub2;
		pubsub2.on(2, [](int e, Foo& arg) {arg(e, 2);});
		pubsub2.emit(2, Foo());
		
		// 3 - capture object for pass it to the lyambda function
		Foo foo;
		utils::PubSub<int, int> pubsub3;
		pubsub3.on(3, [&foo](int e, int arg) { foo(e, arg);	});
		pubsub3.emit(3, 3);

		// 4 - used std::bind for binding class object function
		utils::PubSub<int, int> pubsub4;
		pubsub4.on(4,std::bind(&Foo::callback, &foo, std::placeholders::_1, std::placeholders::_2));
		pubsub4.emit(4, 4);

		// 5 - pass pointer to the object
		Foo* foo5 = new Foo();
		utils::PubSub<int, Foo> pubsub5;
		pubsub5.on(5, [](int e, Foo& arg) { arg(e, 5); });
		pubsub5.emit(5, std::move(*foo5));
		delete foo5;
			
		// 6 - used object functor
		utils::PubSub<int, int> pubsub6;
		pubsub6.on(6, Foo());
		pubsub6.emit(6, 6);

		std::getchar();
		return 0;
	}
'''

## License

This project is licensed under the MIT License - see the LICENSE.md file for details
