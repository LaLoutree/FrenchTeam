/*
** File description:
** uVector.hpp
*/

#ifndef UVECTOR_HPP_
#define UVECTOR_HPP_

#include <memory>

template<class A>
using uVector = std::vector<std::unique_ptr<A>>;

#endif /* !UVECTOR_HPP_ */