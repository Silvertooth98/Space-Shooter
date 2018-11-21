#include "Universe.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <math.h>
#include "AudioManager.h"

Universe::Universe()
{
	//Load model for the universe
	m_model.LoadModel("Assets\\Models\\Skydome.obj", "SKYDOME");
	m_model.LoadTexture("Assets\\Textures\\Skydome_Diffuse.png", "SKYDOME");

	TheAudio::Instance()->LoadFromFile("Assets\\Audio\\Music.ogg", AudioManager::MUSIC_AUDIO, "MUSIC");

	m_music.SetAudioData("MUSIC", AudioManager::MUSIC_AUDIO);

	m_music.Play();
	m_music.Volume() = 0.2f;
	m_music.SetLoopCount(Audio::ENDLESS_LOOP);
}

Universe::~Universe()
{
}

void Universe::Draw()
{
	//reset the transformation
	m_transform = glm::mat4(1.0f);

	//set the scale of the model
	m_transform = glm::scale(m_transform, glm::vec3(100.0f, 100.0f, 100.0f));
	
	//render universe and reset transformation
	GameObject::setMatrix(m_transform);
	GameObject::SendToShader(false, true);

	//draw the model
	m_model.Draw();
}
