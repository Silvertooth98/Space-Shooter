#include "ExplosionAnim.h"
#include "AudioManager.h"

int ExplosionAnim::s_totalEXP = 0;

ExplosionAnim::ExplosionAnim()
{
	if (s_totalEXP == 0)
	{
		m_animation.Create("EXP");
		m_animation.LoadTexture("Assets\\Sprites\\Explosion.png", "EXP");
		TheAudio::Instance()->LoadFromFile("Assets\\Audio\\Explosion.wav", AudioManager::SFX_AUDIO, "SFXEXP");
	}
	else
	{
		m_animation.SetBuffer("EXP");
		m_animation.SetTexture("EXP");
	}

	s_totalEXP++;

	m_animation.IsAnimationLooping() = false;
	m_animation.SetAnimationVelocity(50.0f);
	m_animation.SetTextureDimension(8.0f, 6.0f);

	m_sfx.SetAudioData("SFXEXP", AudioManager::SFX_AUDIO);
	m_sfx.Play();
	m_sfx.Volume() = 0.1f;
}

void ExplosionAnim::Update()
{
	m_animation.Update();
	m_isAlive = !(m_animation.IsAnimationDead());
}

void ExplosionAnim::Draw()
{
	m_transform = glm::mat4(1.0f);

	m_transform = glm::translate(m_transform, m_position - glm::vec3(2.5f, 2.5f, 0.0f));
	m_transform = glm::scale(m_transform, glm::vec3(5.0f));
	GameObject::setMatrix(m_transform);

	GameObject::SendToShader(false, true);

	m_animation.Draw();
}

void ExplosionAnim::Destroy()
{
}
