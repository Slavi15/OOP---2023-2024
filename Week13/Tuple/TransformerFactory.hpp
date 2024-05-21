#include "Transformer.hpp"

#include "AllTransformer.hpp"
#include "ChangeAt.hpp"

template<typename T, size_t N>
Transformer<T, N>* transformerFactory(TransformerType type)
{
	if (type == TransformerType::ALL)
		return new AllTransformer<T, N>();
	else if (type == TransformerType::CHANGE_AT)
		return new ChangeAtTransformer<T, N>();

	return nullptr;
}