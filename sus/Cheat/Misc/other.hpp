#include <array>

namespace other {
	Vector3 m_manipulate = Vector3::Zero();
	void find_manipulate_angle() {
		Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);

		Vector3 choice = Vector3::Zero();

		if (utils::LineOfSight(re_p, reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head))) {
			m_manipulate = Vector3::Zero();
			return;
		}

		float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
		float mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * LocalPlayer::Entity()->MaxVelocity()) - 0.05f;
		float max_v_multicplier = 4.5f;
		float v_mm_max_eye = mm_max_eye / max_v_multicplier;

		auto right = LocalPlayer::Entity()->eyes()->MovementRight();
		auto forward = LocalPlayer::Entity()->eyes()->MovementForward();

		std::array<Vector3, 41> arr = {
			Vector3(0.f, (v_mm_max_eye / 5), 0.f), // small up

			Vector3(0.f, v_mm_max_eye / 2, 0.f), // medium up

			Vector3(0.f, v_mm_max_eye, 0.f), // big up

			Vector3(0.f, -(1.4f / 2), 0.f), // small down

			Vector3(0.f, -1.4f, 0.f), // big down

			Vector3(right.x * (mm_max_eye / 2), 0.f, right.z * (mm_max_eye / 2)), // small right

			Vector3(right.x * mm_max_eye, 0.f, right.z * mm_max_eye), // big right

			Vector3(right.x * (mm_max_eye / 2), (1.4f / 2), right.z * (mm_max_eye / 2)), // small right up

			Vector3(right.x * mm_max_eye, 1.4f, right.z * mm_max_eye), // big right up

			Vector3(right.x * (mm_max_eye / 2), -(1.4f / 2), right.z * (4.f / 2)), // small right down

			Vector3(right.x * mm_max_eye, -1.4f, right.z * mm_max_eye), // big right down

			Vector3(-(right.x * (mm_max_eye / 2)), 0.f, -(right.z * (mm_max_eye / 2))), // small left

			Vector3(-(right.x * mm_max_eye), 0.f, -(right.z * mm_max_eye)), // big left

			Vector3(-(right.x * (mm_max_eye / 2)), (1.4f / 2), -(right.z * (mm_max_eye / 2))), // small left up

			Vector3(-(right.x * mm_max_eye), 1.4f, -(right.z * mm_max_eye)), // big left up

			Vector3(-(right.x * (mm_max_eye / 2)), -(1.4f / 2), -(right.z * (mm_max_eye / 2))), // small left down

			Vector3(-(right.x * mm_max_eye), -1.4f, -(right.z * mm_max_eye)), // big left down 

			Vector3(forward.x * (mm_max_eye / 2), 0.f, forward.z * (mm_max_eye / 2)),// small forward

			Vector3(forward.x * mm_max_eye, 0.f, forward.z * mm_max_eye), // big forward

			Vector3(-(forward.x * (mm_max_eye / 2)), 0.f, -(forward.z * (mm_max_eye / 2))), // small backward

			Vector3(-(forward.x * mm_max_eye), 0.f, -(forward.z * mm_max_eye)), // big backward

			Vector3(forward.x * (mm_max_eye / 2), (1.4f / 2), forward.z * (mm_max_eye / 2)),// small forward up

			Vector3(forward.x * mm_max_eye, 1.4f, forward.z * mm_max_eye), // big forward up

			Vector3(forward.x * (mm_max_eye / 2), -(1.4f / 2), forward.z * (mm_max_eye / 2)),// small forward down

			Vector3(forward.x * mm_max_eye, -1.4f, forward.z * mm_max_eye), // big forward down

			Vector3(-(forward.x * (mm_max_eye / 2)), 0.f, -(forward.z * (mm_max_eye / 2))),// small reverse

			Vector3(-(forward.x * mm_max_eye), 0.f, -(forward.z * mm_max_eye)), // big reverse 

			Vector3(-(forward.x * (mm_max_eye / 2)), (1.4f / 2), -(forward.z * (mm_max_eye / 2))),// small reverse up

			Vector3(-(forward.x * 4.f), 1.4f, -(forward.z * 4.f)), // big reverse up

			Vector3(-(forward.x * (mm_max_eye / 2)), -(1.4f / 2), -(forward.z * (mm_max_eye / 2))),// small reverse down

			Vector3(-(forward.x * mm_max_eye), -1.4f, -(forward.z * mm_max_eye)), // big reverse down

			Vector3(right.x * mm_max_eye, v_mm_max_eye, right.z * (mm_max_eye)) * 0.9f, // big diag-up-right

			Vector3(-right.x * (mm_max_eye), (v_mm_max_eye), -right.z * (mm_max_eye)) * 0.9f, // big diag-up-left

			Vector3(right.x * mm_max_eye, -v_mm_max_eye, right.z * (mm_max_eye)) * 0.9f, // big diag-down-right

			Vector3(-right.x * (mm_max_eye), (-v_mm_max_eye), -right.z * (mm_max_eye)) * 0.9f, // big diag-up-left

			Vector3((right.x / 2) * mm_max_eye, v_mm_max_eye, (right.z / 2) * (mm_max_eye)), // big diag-up-right

			Vector3(-(right.x / 2) * (mm_max_eye), (v_mm_max_eye), -(right.z / 2) * (mm_max_eye)), // big diag-up-left

			Vector3((right.x / 2) * mm_max_eye, -v_mm_max_eye, (right.z / 2) * (mm_max_eye)), // big diag-down-right

			Vector3(-(right.x / 2) * (mm_max_eye), (-v_mm_max_eye), -(right.z / 2) * (mm_max_eye)), // big diag-up-left

			Vector3((forward.x / 2) * (mm_max_eye / 2), (v_mm_max_eye / 1), (forward.z / 2) * (mm_max_eye / 2)), // big diag-up-forward

			Vector3(-((forward.x / 2) * (mm_max_eye / 2)), (v_mm_max_eye / 1), -((forward.z / 2) * mm_max_eye / 2)), // big diag-up-backward
		};

		for (auto s : arr) {
			Vector3 point = re_p + s;

			if (!utils::LineOfSight(point, re_p))
				continue;

			if (vars::combat::manipulate_angle) {
				DDraw::Sphere(point, 0.05f, Color(vars::colors::angle.x, vars::colors::angle.y, vars::colors::angle.z, 1.f), 0.05f, 10);
			}
			if (vars::combat::manipulate_angle_arrow) {
				DDraw::Arrow(re_p, LocalPlayer::Entity()->eyes()->position(), 0.3f, Color(vars::colors::angle_arrow.x, vars::colors::angle_arrow.y, vars::colors::angle_arrow.z, 1.f), 0.01f);
			}

			if (!utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), point))
				continue;

			choice = s;
			break;
		}
		if (choice.empty()) {
			m_manipulate = Vector3::Zero();
			return;
		}

		m_manipulate = choice;
	}
}