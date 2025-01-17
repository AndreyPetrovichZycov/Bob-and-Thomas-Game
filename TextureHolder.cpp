#include "TextureHolder.h"
#include <assert.h>

using namespace std;
using namespace sf;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}


Texture& TextureHolder::GetTexture(std::string const& filename) {

	auto& m = m_s_Instance->m_Texutre;

	auto keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
		auto& texture = m[filename];
		texture.loadFromFile(filename);

		return texture;
	}

}
