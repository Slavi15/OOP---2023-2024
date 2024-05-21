#include "Tuple.hpp"

#define TT template<typename T, size_t N>

enum class TransformerType { ALL, CHANGE_AT };

TT
class Transformer
{
private:
	TransformerType type;

public:
	Transformer(TransformerType type) : type(type) {}

	virtual Tuple<T, N>& transform(Tuple<T, N>& tuple) const = 0;
	virtual Transformer* clone() const = 0;

	virtual ~Transformer() noexcept = default;
};