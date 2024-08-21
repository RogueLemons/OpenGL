#include "Model.h"

namespace Charis {

	Model::Model(const float* vertices, unsigned int size, unsigned int stride, const std::vector<unsigned int>& attributeFloatSizes)
	{
	}
	Model::Model(const std::vector<float>& vertices, unsigned int stride, const std::vector<unsigned int>& attributeFloatSizes) 
	{
	}

	Model::~Model()
	{
	}

	template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& attributeFloatSizes) 
	{

	}

}