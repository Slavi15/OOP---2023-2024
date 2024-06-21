#include "Tuple.hpp"

#define TT template<typename T, size_t N>

TT
class Transformer
{
public:
	Transformer() = default;

	virtual Tuple<T, N>& transform(Tuple<T, N>& tuple) const = 0;
	virtual Transformer* clone() const = 0;

	virtual ~Transformer() noexcept = default;
};