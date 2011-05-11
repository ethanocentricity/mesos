#ifndef FOREACH_HPP
#define FOREACH_HPP

#include <boost/foreach.hpp>

#include <boost/tuple/tuple.hpp>


#define BOOST_FOREACH_PAIR(VARFIRST, VARSECOND, COL)                                            \
    BOOST_FOREACH_PREAMBLE()                                                                    \
    if (boost::foreach_detail_::auto_any_t _foreach_col = BOOST_FOREACH_CONTAIN(COL)) {} else   \
    if (boost::foreach_detail_::auto_any_t _foreach_cur = BOOST_FOREACH_BEGIN(COL)) {} else     \
    if (boost::foreach_detail_::auto_any_t _foreach_end = BOOST_FOREACH_END(COL)) {} else       \
    for (bool _foreach_continue = true, _foreach_onetime = true;                                \
              _foreach_continue && !BOOST_FOREACH_DONE(COL);                                    \
              _foreach_continue ? BOOST_FOREACH_NEXT(COL) : (void)0)                            \
        if  (boost::foreach_detail_::set_false(_foreach_onetime)) {} else                       \
        for (VARFIRST = BOOST_FOREACH_DEREF(COL).first;                                         \
	     !_foreach_onetime;                                                                 \
	     _foreach_onetime = true)                                                           \
            if  (boost::foreach_detail_::set_false(_foreach_continue)) {} else                  \
            for (VARSECOND = BOOST_FOREACH_DEREF(COL).second;                                   \
		 !_foreach_continue;                                                            \
		 _foreach_continue = true)

#define foreach BOOST_FOREACH
#define foreachpair BOOST_FOREACH_PAIR

namespace foreach {

const boost::tuples::detail::swallow_assign _ = boost::tuples::ignore;

template <typename T> T copy(const T& t) { return t; }

}

#define foreachkey(VAR, COL)                    \
  foreachpair (VAR, foreach::_, COL)

#define foreachvalue(VAR, COL)                  \
  foreachpair (foreach::_, VAR, COL)

#define foreachcopy(VAR, COL)                   \
  foreach (VAR, foreach::copy(COL))

#define foreachpaircopy(VARFIRST, VARSECOND, COL)       \
  foreachpair (VARFIRST, VARSECOND, foreach::copy(COL))

#define foreachkeycopy(VAR, COL)                        \
  foreachpair (VAR, foreach::_, foreach::copy(COL))

#define foreachvaluecopy(VAR, COL)                      \
  foreachpair (foreach::_, VAR, foreach::copy(COL))

#endif // __FOREACH_HPP__
