#include <iostream>
#include "defer.h"

using namespace std;

int deferred_function() {
	cout << "deferred function." << endl;
}

int main() {
	auto deferred_named_lambda = [](){ cout << "deferred named lambda." << endl;};
	defer(deferred_named_lambda);
	defer([](){ cout << "deferred anonymous lambda." << endl;});
	defer(deferred_function);

	auto name_the_defer = defer(deferred_function);
	{
		auto inner_name_the_defer = std::move(name_the_defer);
		defer(deferred_named_lambda);
	}
	cout << "Exited the inner scope okay!\n";
	//name_the_defer.cancel();
	return 0;
}
