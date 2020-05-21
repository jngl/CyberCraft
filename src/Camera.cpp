//
// Created by jngl on 21/05/2020.
//

#include "Camera.h"

#include "Math.h"

Camera::Camera() {
	m_view.setSize(400,300);
	m_view.setCenter(sf::Vector2f());
}

void Camera::set(sf::RenderTarget& renderTarget){
	renderTarget.setView(m_view);
}

void Camera::moveTo(sf::Vector2f target, float speed){
	const sf::Vector2f& center = m_view.getCenter();

	sf::Vector2f diff = target - center;
	float length = math::length(diff);

	sf::Vector2f move;

	if(length>3.f){
		move = diff / length * 3.f;
	}

	m_view.setCenter(center + move);
}