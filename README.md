## PubSub
Simple implementation of the Publish/subscribe pattern


## Usage
You can use this module in the following ways:

'''

	#include <iostream>
	
	struct Foo {
		int value;
		Foo(int value) : value(value) {};
	};

	int main(int artc, char** argv) {
		// 1
		utils::PubSub<int, int> pubSub;
		pubSub.on(1, [](int e, int arg) {
			std::cout << e << " " << arg << std::endl;
		});
		pubSub.emit(1, 1);

		// 2 
		utils::PubSub<int, Foo> pubsub2;
		pubsub2.on(1, [](int e, Foo arg) {
			std::cout << e << " " << arg.value << std::endl;
		});

		pubsub2.emit(1, std::forward<Foo>(Foo(2)));

		// 3
		utils::PubSub<int, Foo*> pubsub3;
		pubsub3.on(1, [](int e, Foo* arg) {
			std::cout << e << " " << arg->value << std::endl;
		});

		Foo* foo = new Foo(3);
		pubsub3.emit(1, std::forward<Foo*>(foo));
		delete foo;

		std::getchar();
		return 0;
	}
'''

## License

This project is licensed under the MIT License - see the LICENSE.md file for details
