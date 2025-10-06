#include "Renderer.h"
#include "Walnut/Random.h"

void Renderer::Render() {
	// render every pixel
	// Set Random pixel value ABGR - (8 bits each for RGBA - uint32)
	//for (uint32_t i = 0; i < m_FinalImage->GetWidth() * m_FinalImage->GetHeight(); i++) {
	//	m_ImageData[i] = Walnut::Random::UInt();
	//	// To make the A value 100%
	//	m_ImageData[i] |= 0xff000000;
	//}

	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++) {
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++) {
			glm::vec2 coord = { (float)x / (float)m_FinalImage->GetWidth(), (float)y / (float)m_FinalImage->GetHeight()};
			coord = coord * 2.0f - 1.0f; // -1 -> 1
			m_ImageData[x + y * m_FinalImage->GetWidth()] = PerPixel(coord);
		}
	}

	// Link image data to m_Image
	m_FinalImage->SetData(m_ImageData);
}

void Renderer::OnResize(uint32_t width, uint32_t height) {
	
	if (m_FinalImage) {
		// No resize necessary
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height) return;
		m_FinalImage->Resize(width, height);
	}
	else {
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}
	
	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}

uint32_t Renderer::PerPixel(glm::vec2 coord) {

	uint8_t r = (uint8_t)(coord.x * 255.0f);
	uint8_t g = (uint8_t)(coord.y * 255.0f);

	glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
	glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
	float radius = 0.5f;
	// (bx^2 + by^2 + bz^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0 

	// a -> ray orign
	// b -> ray direction
	// t -> hit distance
	// r -> radius

	//float a = rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z;
	float a = glm::dot(rayDirection, rayDirection);
	float b = 2 * glm::dot(rayOrigin, rayDirection);	
	float c = glm::dot(rayOrigin, rayOrigin) - radius*radius;

	float discriminant = b * b - 4.0f * a * c;
	
	if (discriminant >= 0) return 0xff0000ff;
	return 0xff000000;
}