#include "player_movement.h"
#include "kalokairi.h"
#include "camera.h"

PlayerMovement::PlayerMovement(void)
	: transform_(new Transform)
	, renderer_(nullptr)
	, r_arm1_(new Transform)
	, r_arm1_id_(-1)
	, r_hand_(nullptr)
	, pistol_(nullptr)
	, model_list_(nullptr)
	, fade_(0.f)
{
}

PlayerMovement::~PlayerMovement(void)
{
	delete this->transform_;
	delete this->r_arm1_;
}

void PlayerMovement::Initialize(void)
{
	this->renderer_ = this->owner()->Component<Renderer>();

	this->renderer_->animation()->SetAnimation("idle", 1);
	this->renderer_->animation()->SetIntercept(0, this->transform_);

	this->camera_ = this->owner()->scene()->System<Camera>();
	this->camera_->set_target(this->transform_);

	auto r_hand_id = this->renderer_->Find("r_hand");
	auto r_hand_model = this->renderer_->model_list(r_hand_id);
	this->r_hand_ = r_hand_model->transform();

	this->r_arm1_id_ = this->renderer_->Find("r_arm1");

	*this->r_arm1_ = *this->renderer_->model_list(this->r_arm1_id_)->transform();

	this->model_list_ = this->renderer_->model_list();

	for (auto & model : *this->model_list_)
	{
		model.second.set_diffuse(DirectX::Vector4(1.f, 1.f, 1.f, 0.f));
	}
}

void PlayerMovement::Update(void)
{
	if (this->fade_ < 1.f)
	{
		for (auto & model : *this->model_list_)
		{
			model.second.set_diffuse(DirectX::Vector4(1.f, 1.f, 1.f, this->fade_));
		}

		this->fade_ += 0.03f;
	}

	auto walk_index = static_cast<int>(this->renderer_->animation()->animations("walk")->progress_);
	auto run_index = static_cast<int>(this->renderer_->animation()->animations("run")->progress_);

	float move_forward = static_cast<float>(Input::Press(Qt::Key_W)) - static_cast<float>(Input::Press(Qt::Key_S)) * 0.5f;
	
	float move_side = static_cast<float>(Input::Press(Qt::Key_D)) - static_cast<float>(Input::Press(Qt::Key_A)) * 0.5f;

	float rot_side = static_cast<float>(Input::Press(Qt::Key_E)) - static_cast<float>(Input::Press(Qt::Key_Q));

	float move_speed = 0.012f;

	static bool run = false;

	if (move_forward || move_side)
	{
		if (run)
		{
			this->renderer_->animation()->SetAnimation("run", 1);
			move_speed *= 4.f;
			move_speed *= 1 + (run_index % 2 == 0) * 0.4f;
		}
		else
		{
			this->renderer_->animation()->SetAnimation("walk", 1);
			move_speed *= 1 + (walk_index % 2 == 0) * 0.4f;
		}
	}
	else
	{
		this->renderer_->animation()->SetAnimation("idle", 1);
		run = false;
	}

	if (Input::Repeat(Qt::Key_W) || Input::Repeat(Qt::Key_A) || Input::Repeat(Qt::Key_S) || Input::Repeat(Qt::Key_D))
		run = true;

	static int pistol_state = 0;

	if (this->pistol_)
	{
		if (Input::Trigger(Qt::Key_J))
		{
			if (pistol_state == 0)
			{
				*this->r_arm1_ = *this->renderer_->model_list(this->r_arm1_id_)->transform();
				this->renderer_->animation()->SetIntercept(this->r_arm1_id_, this->r_arm1_);

				pistol_state = 1;
			}
			else if (pistol_state == 1)
				pistol_state = 2;
		}

		bool can_shot = false;

		if (pistol_state == 1)
		{
			auto rotation = this->r_arm1_->rotation();
			auto next = DirectX::Vector3(0.f, -90.f, 0.f);
			if (run)
				next.z = -20.f;

			if (DirectX::Vector3::Distance(rotation, next) > 0.01f)
			{
				this->r_arm1_->set_rotation(next, 0.7f);
			}
			else
			{
				can_shot = true;
			}
		}

		if (pistol_state == 2)
		{
			auto rotation = this->r_arm1_->rotation();
			auto next = DirectX::Vector3(0.f, 0.f, 60.f);
			if (DirectX::Vector3::Distance(rotation, next) > 0.01f)
			{
				this->r_arm1_->set_rotation(next, 0.7f);
			}
			else
			{
				this->renderer_->animation()->RemoveIntercept(this->r_arm1_id_);
				pistol_state = 0;
			}
		}

		if (can_shot && Input::Trigger(Qt::Key_I))
		{
			this->pistol_->Component<PistolMovement>()->Shot();
		}
	} // eŽ‚Á‚Ä‚é‚Æ‚«

	if (Input::Trigger(Qt::Key_U))
	{
		if (this->pistol_ == nullptr)
		{
			this->pistol_ = this->owner()->scene()->CreateEntity<Pistol>();
			this->pistol_->transform()->set_parent(this->r_hand_);
			this->renderer_->animation()->SetAnimation("equip_pistol", 0);
		}
		else if(pistol_state == 0)
		{
			this->pistol_->Disappear();
			this->pistol_ = nullptr;
			this->renderer_->animation()->RemoveAnimation("equip_pistol");
		}
	}

	auto rot = this->transform_->rotation();
	auto v3 = this->transform_->position();
	
	rot.y = DirectX::XMConvertToDegrees(atan2f(-move_side, -move_forward) /*+ atan2f(v3.x, v3.z)*/);

	if (move_forward || move_side)
	{
		this->transform_->set_rotation(rot, 0.1f);
		move_speed *= (1 + (pistol_state != 1) * 0.2f);
		move_speed *= (1 + (!this->pistol_) * 0.2f);
		this->transform_->MoveForward(move_speed);
	}
}

void PlayerMovement::Always(void)
{
}

void PlayerMovement::Finalize(void)
{
}

Transform * const PlayerMovement::transform(void)
{
	return this->transform_;
}

Pistol * const PlayerMovement::pistol(void)
{
	return this->pistol_;
}
