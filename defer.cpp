#include <iostream>
#include <functional>

using namespace std;

template<class R, class... args>
class DeferImpl {
	public:
		DeferImpl() {};
		DeferImpl(std::function<R(args...)> &&callee) {
			m_callee = callee;
		}
		~DeferImpl() {
			m_callee();
		}
	private:
		std::function<R(args...)> m_callee;
};

int deferred_function() {
	cout << "function deferred." << endl;
}

#define CONCATENATE_IMPL(s1,s2) s1##s2
#define CONCATENATE(s1,s2) CONCATENATE_IMPL(s1,s2)
#define defer_impl(fn, c) \
	auto CONCATENATE(f,c) = fn; \
	auto CONCATENATE(df,c) = DeferImpl<std::invoke_result<decltype(CONCATENATE(f,c))>::type>(CONCATENATE(f,c))

#define defer(fn) defer_impl(fn, __COUNTER__)

int main() {
	auto deferred_named_lambda = [](){ cout << "named lambda deferred." << endl;};
	defer(deferred_named_lambda);
	defer([](){ cout << "anonymous lambda deferred." << endl;});
	defer(deferred_function);
	return 0;
}
