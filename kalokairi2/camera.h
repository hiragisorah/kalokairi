#pragma once

#include "..\frame-work\engine.h"

#include "..\frame-work\SimpleMath.h"

#include "transform.h"

#undef near
#undef far

class Camera : public Seed::System
{
public:
	Camera(void);

public:
	void Initialize(void) override;
	void Update(void) override;
	void Always(void) override;
	void Finalize(void) override;
	void Begin(Seed::Graphics & graphics) override;
	void End(Seed::Graphics & graphics) override;

private:
	DirectX::Vector3 dir_light_;

private:
	DirectX::Vector3 eye_;
	DirectX::Vector3 at_;
	DirectX::Vector3 up_;

	float fov_;
	float aspect_;
	float near_;
	float far_;

public:
	const DirectX::Vector3 & eye(void);
	const DirectX::Vector3 & at(void);
	const DirectX::Vector3 & up(void);

	void set_eye(const DirectX::Vector3 & eye);
	void set_at(const DirectX::Vector3 & at);
	void set_up(const DirectX::Vector3 & up);

	void set_fov(const float & fov);
	void set_aspect(const float & aspect);
	void set_near(const float & near);
	void set_far(const float & far);

public:
	DirectX::Matrix View(void);
	DirectX::Matrix Projection(void);

private:
	Transform * target_;

public:
	void set_target(Transform * const target);
};