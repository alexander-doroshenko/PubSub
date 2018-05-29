#pragma once

/// <summary> Publish/Subscribe pattern:
/// <example>
/// <code>
///	struct Foo {
///		int value;
///		Foo(int value) : value(value) {};
///	};
///
///
///	int main(int artc, char** argv) {
///		// 1
///		utils::PubSub<int, int> pubSub;
///		pubSub.on(1, [](int e, int arg) {
///			std::cout << e << " " << arg << std::endl;
///		});
///		pubSub.emit(1, 1);
///
///		// 2 
///		utils::PubSub<int, Foo> pubsub2;
///		pubsub2.on(1, [](int e, Foo arg) {
///			std::cout << e << " " << arg.value << std::endl;
///		});
///
///		pubsub2.emit(1, std::forward<Foo>(Foo(2)));
///
///		// 3
///		utils::PubSub<int, Foo*> pubsub3;
///		pubsub3.on(1, [](int e, Foo* arg) {
///			std::cout << e << " " << arg->value << std::endl;
///		});
///
///		Foo* foo = new Foo(3);
///		pubsub3.emit(1, std::forward<Foo*>(foo));
///		delete foo;
///
///		std::getchar();
///		return 0;
///	}
/// </code>
/// </example>
/// </summary>

#include <functional>
#include <map>

namespace utils {

	template <typename Key, typename Arg>
	class PubSub {
	private:
		std::map< Key, std::function<void(Key, Arg)>> callbacks;
	public:

		///
		PubSub() {};

		///
		void emit(Key&& eventName, Arg&& arg) {
			if (this->callbacks.count(eventName)) {
				this->callbacks[eventName] (eventName, arg);
			}
		}

		///
		void on(const Key&& eventName, std::function<void(Key, Arg)>&& fn) {
			this->callbacks.emplace(eventName, fn);
		}

		///
		void off(const Key&& eventName) {
			if (this->callbacks.count(eventName)) {
				this->callbacks.erase(eventName);
			}
		}
	};
}