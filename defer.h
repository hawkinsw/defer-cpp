#ifndef __DEFER_H
#define __DEFER_H

#include <functional>

template<class R, class... args>
class DeferImpl {
	public:
		DeferImpl() = delete;
		DeferImpl(const DeferImpl &) = delete;

		DeferImpl(DeferImpl &&orig) {
			m_callee = std::move(orig.m_callee);
			m_canceled = m_canceled;
			orig.m_canceled = true;
		}

		DeferImpl(std::function<R(args...)> &&callee) :
		  m_callee(callee),
			m_canceled(false) {}

		~DeferImpl() {
			if (!m_canceled)
				m_callee();
		}

		void cancel() {
			m_canceled = true;
		}

	private:
		std::function<R(args...)> m_callee;
		bool m_canceled;
};

#define CONCATENATE_IMPL(s1,s2) s1##s2
#define CONCATENATE(s1,s2) CONCATENATE_IMPL(s1,s2)
#define defer_impl(fn, c) \
  [&]() { \
	auto CONCATENATE(f,c) = fn; \
	auto CONCATENATE(df,c) = DeferImpl<std::invoke_result<decltype(CONCATENATE(f,c))>::type>(CONCATENATE(f,c)); \
	return std::move(CONCATENATE(df,c)); \
	}()

#define defer(fn) defer_impl(fn, __COUNTER__)

#endif
