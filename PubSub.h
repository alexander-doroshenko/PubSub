#pragma once

/// <summary> 
///		Simple implementation of the Publish/Subscribe pattern.
/// </summary>
/// <author> Doroshenko Alexander </author>
/// <example>
/// <code>
/// 
/// #include <iostream>
/// #include "PubSub.h"
///	
///	struct Foo {
///		Foo() {};
///	
///		void operator() (int e, int arg) {
///			this->callback(e, arg);
///		}
///	
///		void callback(int e, int arg) {
///			printf("The argument %d\n", arg);
///		}
///	};
///			
///	int main(int argc, char** argv) {
///		// The lambda-function with a simple type
///		// argument is used like callback
///		awkward::PubSub<int, int> pubsub1;
///		pubsub1.on(1, [](int e, int arg) {
///			printf("The argument %d\n", arg);
///		});
///		pubsub1.emit(1, 1);
///			
///		// The lambda-function with a class type 
///		// argument is used like a callback 
///		awkward::PubSub<int, Foo> pubsub2;
///		pubsub2.on(2, [](int e, Foo& arg) {arg(e, 2);});
///		pubsub2.emit(2, Foo());
///		
///		// The object is passed to the lambda-function
///		Foo foo;
///		awkward::PubSub<int, int> pubsub3;
///		pubsub3.on(3, [&foo](int e, int arg) { foo(e, arg);	});
///		pubsub3.emit(3, 3);
///	
///		// std::bind
///		awkward::PubSub<int, int> pubsub4;
///		pubsub4.on(4,std::bind(&Foo::callback, &foo, std::placeholders::_1, std::placeholders::_2));
///		pubsub4.emit(4, 4);
///	
///		// passed pointer to the object
///		Foo* foo5 = new Foo();
///		awkward::PubSub<int, Foo> pubsub5;
///		pubsub5.on(5, [](int e, Foo& arg) { arg(e, 5); });
///		pubsub5.emit(5, std::move(*foo5));
///		delete foo5;
///			
///		// object functor (override round brackets operator )
///		awkward::PubSub<int, int> pubsub6;
///		pubsub6.on(6, Foo());
///		pubsub6.on(6, Foo());
///		pubsub6.on(6, Foo());
///		pubsub6.on(7, Foo());
///		pubsub6.emit(6, 6);
///		pubsub6.emit(7, 7);
///		
///		// test the "off" function
///		pubsub6.off(6);
///		pubsub6.emit(6, 6);
///	
///		std::getchar();
///		return 0;
///	}
/// </code>
/// </example>

#include <functional>
#include <unordered_map>

namespace awkward {


	template <typename EventName, typename ... EventArgs>
	class PubSub 
	{
		// type of the callback-function
		using Callback = std::function<void(EventName, EventArgs...)>;
		
		// holds all pairs EventName -> Callback
		std::unordered_multimap<EventName, Callback> callbacks;
		

	public:

		///
		PubSub() {};


		/// <summary>
		///		run all callbacks associated with 
		///		specified event name and pass given 
		///		arguments into it
		/// </summary>
		///	<param name="eventName"> emited event </param>
		/// <param name="arg"> passed argument </param>
		template <typename... Args>
		void emit(const EventName& eventName, Args&&... arg)
		{
			auto callbacks = this->callbacks.equal_range(eventName);
			for (auto it = callbacks.first; it != callbacks.second; it++) 
			{
				auto &[_, callback] = *it;
				callback(std::move(eventName), std::forward<Args>(arg)...);
			}
		}


		/// <summary>
		///		associates callback with an event
		/// </summary>
		///	<param name="eventName"> 
		///		event with which the 
		///		function is associated 
		///	</param>
		/// <param name="callback"> 
		///		function to be called when 
		///		the specified event happens 
		///	</param>
		void on(EventName&& eventName, Callback&& callback)
		{
			this->callbacks.emplace(std::move(eventName), std::move(callback));
		}


		/// <summary>
		///		remove all callbacks associated 
		///		with the specified event
		/// </summary>
		/// <param name="event> removing event </param>
		void off(const EventName& eventName)
		{
			if (this->callbacks.count(eventName)) {
				this->callbacks.erase(eventName);
			}
		}
	};
}