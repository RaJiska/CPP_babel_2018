/*
** EPITECH PROJECT, 2018
** Server
** File description:
** INetworkMessage
*/

#ifndef INETWORKMESSAGE_HPP_
	#define INETWORKMESSAGE_HPP_

#include <boost/serialization/serialization.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/variant.hpp>
#include <boost/serialization/export.hpp>

using PolyArchive = boost::variant<
	boost::archive::polymorphic_oarchive &,
	boost::archive::polymorphic_iarchive &>;

class INetworkMessage {
	public:
	INetworkMessage() = default;
	virtual ~INetworkMessage() = default;

	virtual void serialize(PolyArchive ar, unsigned int version) = 0;
};

namespace visitor {
	template <typename F> struct wrap_visitor : boost::static_visitor<>
	{
		wrap_visitor(F const& f) : f_(f) { }
		wrap_visitor(F&& f)      : f_(std::move(f)) { }

		template<typename... T> void operator()(T&&... t) const
		{
			f_(std::forward<T>(t)...);
		}

	private:
		F f_;
	};

	template <typename F>
	wrap_visitor<F> make_visitor(F&& f)
	{
		return std::forward<F>(f);
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(INetworkMessage)

#endif /* !INETWORKMESSAGE_HPP_ */
