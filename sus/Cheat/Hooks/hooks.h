#include "defs.h"
Vector3 last_head_pos = Vector3::Zero();
Vector3 last_neck_pos = Vector3::Zero();
Vector3 last_spine4_pos = Vector3::Zero();
Vector3 last_spine3_pos = Vector3::Zero();
Vector3 last_spine2_pos = Vector3::Zero();
Vector3 last_spine1_pos = Vector3::Zero();
Vector3 last_l_upperarm_pos = Vector3::Zero();
Vector3 last_l_forearm_pos = Vector3::Zero();
Vector3 last_l_hand_pos = Vector3::Zero();
Vector3 last_r_upperarm_pos = Vector3::Zero();
Vector3 last_r_forearm_pos = Vector3::Zero();
Vector3 last_r_hand_pos = Vector3::Zero();
Vector3 last_pelvis_pos = Vector3::Zero();
Vector3 last_l_knee_pos = Vector3::Zero();
Vector3 last_l_foot_pos = Vector3::Zero();
Vector3 last_r_knee_pos = Vector3::Zero();
Vector3 last_r_foot_pos = Vector3::Zero();

bool magic_projectile_test = false;
float insta_travel_check_time = -1.f;
bool is_noclipping = false;

int flick = 0;
int yaw = 100;

bool targeted = false;
float target_time = 0.f;

Vector3 GetTrajectoryPoint(Vector3& startingPosition, Vector3 initialVelocity, float timestep, float gravity)
{
	float physicsTimestep = Time::fixedDeltaTime();
	Vector3 stepVelocity = initialVelocity * physicsTimestep;

	//Gravity is already in meters per second, so we need meters per second per second
	Vector3 stepGravity(0, physicsTimestep * physicsTimestep * gravity, 0);

	return startingPosition + (stepVelocity * timestep) + ((stepGravity * (timestep * timestep + timestep)) / 2.0f);;
}

using namespace hk_defs;

auto gameAssembly = GetModuleHandleA(xorstr_("GameAssembly.dll"));

#define ProcAddr(func) GetProcAddress(gameAssembly, func)

template<typename T, typename... Args>
inline T call(const char* func, Args... args) {
	return reinterpret_cast<T(__fastcall*)(Args...)>(ProcAddr(func))(args...);
}
namespace System {
	class Object_ {
	public:

	};
	template<typename T = void*>
	class Array {
	public:
		uint32_t size() {
			if (!this) return 0;
			return *reinterpret_cast<uint32_t*>(this + 0x18);
		}
		T get(int idx) {
			if (!this) return T{};
			return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
		}
		void add(int idx, T value) {
			if (!this) return;
			*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
		}
	};
	class String : public Object_ {
	public:
		char pad_0000[0x10];
		int len;
		wchar_t buffer[0];

		static String* New(const char* str) {
			return call<String*, const char*>(xorstr_("il2cpp_string_new"), str);
		}
	};
}
class MonoBehaviour {
public:
	static inline System::Object_* (*StartCoroutine_)(MonoBehaviour*, System::Object_*) = nullptr;
	System::Object_* StartCoroutine(System::Object_* routine) {
		return StartCoroutine_(this, routine);
	}
};
uintptr_t shader;
//auto chams(BasePlayer* player, bool draw = true) -> void
//{
//	bool PlayerSleeping = player->get_flag(16);
//	if (vars::players::sleeperignore && PlayerSleeping) return;
//	if (draw) {
//		if (vars::players::chams) {
//			auto _multiMesh = player->get_player_model2()->_multiMesh();
//			if (_multiMesh) {
//				auto render = _multiMesh->get_Renderers();
//				for (int i = 0; i < render->get_size(); i++) {
//					auto renderer = render->get_value(i);
//					if (renderer) {
//						Material* material = renderer->GetMaterial();
//						if (material) {
//							if (vars::players::chams_type == 0)
//							{
//								material->SetShader(chamsShader);
//								material->SetColor(xorstr_(L"_Color"), col(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, 1));
//							}
//							else if (vars::players::chams_type == 1)
//							{
//								material->SetShader(GalaxyMaterial);
//								material->SetColor(xorstr_(L"_Color"), col(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, 1));
//							}
//
//						}
//					}
//				}
//			}
//		}
//	}
//}
//auto chams(BasePlayer* player, bool draw = true) -> void
//{
//	bool PlayerSleeping = player->HasFlags(16);
//	if (PlayerEsp::sleeperignore && PlayerSleeping)
//		return;
//	static int cases = 0;
//	static float r = 1.00f, g = 0.00f, b = 1.00f;
//	switch (cases)
//	{
//	case 0: { r -= 0.05f; if (r <= 0) cases += 1; break; }
//	case 1: { g += 0.05f; b -= 0.05f; if (g >= 1) cases += 1; break; }
//	case 2: { r += 0.05f; if (r >= 1) cases += 1; break; }
//	case 3: { b += 0.05f; g -= 0.05f; if (b >= 1) cases = 0; break; }
//	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
//	}
//	if (draw) {
//		if (Misc::chams1) {
//			const auto multiMesh = *reinterpret_cast<std::uintptr_t*>(player->get_player_model() + O::PlayerModel::_multiMesh);
//
//			if (!multiMesh)
//				return;
//			auto render = get_Renderers(multiMesh);
//			for (size_t idx{ 0 }; idx < render->get_size(); idx++)
//			{
//				auto renderer = render->get_value(idx);
//				if (renderer)
//				{
//					auto material = get_material(renderer);
//					if (material) {
//						if (shader != unity::get_shader(material)) {
//							if (!shader)
//								shader = Find((L"Classic"));//Hidden/Internal-Colored
//							unity::set_shader(material, shader);
//							if (vars::players::OnlyVisible) {
//								SetInt(material, (L"_ZTest"), 8); // through walls
//							}
//							if (vars::players::rainbow_chams) {
//								SetColor(material, (L"_Color"), col(r, g, b, 1));
//							}
//							else if (vars::players::health_chams) {
//								int health = (int)player->GetHealth();
//								float maxheal = 100.f;
//								if ((int)player->GetHealth() <= 33) {
//									SetColor(material, (L"_Color"), col(3, 0, 0, 1));
//								}
//								if ((int)player->GetHealth() >= 34 && (int)player->GetHealth() <= 66) {
//									SetColor(material, (L"_Color"), col(3, 3, 0, 1));
//								}
//								if ((int)player->GetHealth() >= 67) {
//									SetColor(material, (L"_Color"), col(0, 3, 0, 1));
//								}
//							}
//							else {
//								SetColor(material, (L"_Color"), col(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, 1));
//							}
//							//SetColor(material, xorstr(L"_ColorVisible")), Color(Settings::Visuals::Players::Colors::VisibleChams[0], Settings::Visuals::Players::Colors::VisibleChams[1], Settings::Visuals::Players::Colors::VisibleChams[2], Settings::Visuals::Players::Colors::VisibleChams[3]));
//							//SetColor(material, xorstr(L"_ColorBehind")), Color(Settings::Visuals::Players::Colors::InVisibleChams[0], Settings::Visuals::Players::Colors::InVisibleChams[1], Settings::Visuals::Players::Colors::InVisibleChams[2], Settings::Visuals::Players::Colors::InVisibleChams[3]));
//
//
//						}
//					}
//				}
//			}
//		}
//	}
//}
//void HandChams() {
//	if (!LocalPlayer::Entity()->is_alive() || LocalPlayer::Entity()->is_sleeping()) return;
//	if (vars::visuals::hand_chams && LocalPlayer::Entity()->is_local_player()) {
//		auto model = get_activemodel();
//		auto renderers = ((Networkable*)model)->GetComponentsInChildren(GetType(xorstr_("UnityEngine"), xorstr_("Renderer")));
//		if (renderers)
//		{
//			auto sz = *reinterpret_cast<int*>(renderers + 0x18);
//			for (int i = 0; i < sz; i++) {
//				auto renderer = *reinterpret_cast<Renderer_**>(renderers + 0x20 + i * 0x8);
//				if (!renderer) continue;
//				Material* material = renderer->material();
//				if (!material) continue;
//				if (vars::visuals::hand_chams_type == 0)
//				{
//					material->SetShader(chamsShader);
//					material->SetColor(xorstr_(L"_Color"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
//				}
//				else if (vars::visuals::hand_chams_type == 1)
//				{
//					material->SetShader(GalaxyMaterial);
//					material->SetColor(xorstr_(L"_Color"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
//				}
//			}
//		}
//	}
//}
void Watermark()
{
		std::time_t result = std::time(nullptr);
		std::string wintime = std::asctime(std::localtime(&result));
		time_t lt;
		struct tm* t_m;
		lt = time(NULL);
		t_m = localtime(&lt);

		int time_h = t_m->tm_hour;
		int time_m = t_m->tm_min;
		int time_s = t_m->tm_sec;

		std::string time;

		if (time_h < 10)
			time += "0";

		time += std::to_string(time_h) + ":";

		if (time_m < 10)
			time += "0";

		time += std::to_string(time_m) + ":";

		if (time_s < 10)
			time += "0";

		time += std::to_string(time_s);
		float sWidth = vars::stuff::ScreenWidth;
		const char* _text = (u8"SNUS");
		std::string _text1 = " | ";
		const char* _text2("Build : " __DATE__ " | ");
		std::string _text3 = "Time : ";
		std::string waterka = _text + _text1 + _text2 + _text3 + time;
		std::string string;	char buf[256] = { 0 };
		sprintf_s(buf, xorstr_("%ls"), waterka);
		string += buf;
		g_Render->DrawString(200, 50, ImColor(255, 255, 255), render2::outline, calibri_, 14, waterka.c_str());
}
namespace hk {
	namespace exploit {
		void DoMovement(Projectile* projectile, float deltaTime) {
			auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
			BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();

			if (projectile->isAuthoritative() && vars::combat::always_heli_rotor) {
				f_object target = f_object::get_closest_object(projectile->currentPosition(), xorstr_("xdwadawfgaga"),
					Vector3::Zero(), Vector3::Zero(), Vector3::Zero(),
					true, xorstr_("BaseHelicopter"));

				if (target.valid) {
					Vector3 tar = reinterpret_cast<BaseEntity*>(target.entity)->transform()->position();
					if (utils::LineOfSight(tar, projectile->currentPosition()) && Math::Distance_3D(projectile->currentPosition(), tar) < 35.0f) {
						if (projectile->traveledDistance() > 35.0f) {
							Transform* transform = reinterpret_cast<BaseEntity*>(target.entity)->transform();

							HitTest* hitTest = projectile->hitTest();
							hitTest->DidHit() = true;
							hitTest->HitEntityt((BaseEntity*)target.entity);
							hitTest->HitTransform() = transform;
							hitTest->HitPoint() = transform->InverseTransformPoint(projectile->currentPosition());
							hitTest->HitNormal() = transform->InverseTransformDirection(projectile->currentPosition());
							hitTest->AttackRay() = Ray(projectile->currentPosition(), tar - projectile->currentPosition());
							projectile->DoHit(hitTest, hitTest->HitPointWorld(), hitTest->HitNormalWorld());
							return;
						}
					}
				}
			}

			auto mod = projectile->mod();
			auto ammo_type = projectile->ammoType();

			bool fast = false;
			switch (ammo_type)
			{
			case 785728077:
				fast = true;
				break;
			case -1691396643:
				fast = true;
				break;
			case 51984655:
				fast = true;
				break;
			case -1211166256:
				fast = true;
				break;
			case 1712070256:
				fast = true;
				break;
			case 605467368:
				fast = true;
				break;
			case -1321651331:
				fast = true;
				break;
			case -1685290200:
				fast = true;
				break;
			case -727717969:
				fast = true;
				break;
			case -1036635990:
				fast = true;
				break;
			case 588596902:
				fast = true;
				break;
			}

			Vector3 l_current_pos = projectile->currentPosition();

			for (size_t i = 0; i < 50; i++) //Simulate 100 times per bullet? pretty efficient?
			{
				l_current_pos = GetTrajectoryPoint(l_current_pos,
					projectile->initialVelocity(),
					0.1f,
					projectile->gravityModifier());

				float dist = l_current_pos.distance(LocalPlayer::Entity()->bones()->head->position);

				if ((fast ? dist < 50.0f : dist < 25.0f)) {
					//targeted = true;
					target_time = Time::fixedTime();
				}
			}

			return original_domovement(projectile, deltaTime);
		}
		bool Refract(Projectile* prj, uint32_t seed, Vector3 point, Vector3 normal, float resistancePower) {
			if (vars::combat::tree_reflect) {
				float gravity;
				if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) {
					gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
					a::Prediction(prj->currentPosition(), reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->newVelocity(), GetBulletSpeed(), gravity);
					prj->currentVelocity((reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head) - prj->currentPosition()) * (GetBulletSpeed() / 75.f));
					prj->currentPosition(prj->currentPosition() + prj->currentVelocity().Normalized() * 0.001f);
				}
			}
			else {
				return original_refract(prj, seed, point, normal, resistancePower);
			}
		}
	}
	namespace misc {
		void ClientUpdate(BasePlayer* player) {
			lol::cachePlayer(player);

			return original_clientupdate(player);
		}
		void ClientUpdate_Sleeping(BasePlayer* player) {
			if (!vars::players::sleeperignore) {
				lol::cachePlayer(player);
			}

			return original_clientupdate_sleeping(player);
		}
		void VisUpdateUsingCulling(BasePlayer* pl, float dist, bool vis) {
			if (vars::players::chams) {
				return original_UnregisterFromVisibility(pl, 2.f, true);
			}
			else {
				return original_UnregisterFromVisibility(pl, dist, vis);
			}
		}
		float LastUpdate = 0.f;
		GameObject* CreateEffect(pUncStr strPrefab, Effect* effect) {
			auto effectName = strPrefab->str;
			auto position = read(effect + 0x5C, Vector3);
			if (vars::visuals::raid_esp && effect && strPrefab->str && !position.empty()) {
				switch (RUNTIME_CRC32_W(effectName)) {
				case STATIC_CRC32("assets/prefabs/tools/c4/effects/c4_explosion.prefab"):
					LogSystem::LogExplosion(C4, position);
					//LogSystem::Log(StringFormat::format(xorstr_(L"✚ Explosion: %ls, Distsnce: %1.0fm"), wC4.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/satchelcharge/effects/satchel-charge-explosion.prefab"):
					LogSystem::LogExplosion(Satchel, position);
					//		LogSystem::Log(StringFormat::format(xorstr_(L"✚ Explosion: %ls, Distsnce: %1.0fm"), wSatchel.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion_incendiary.prefab"):
					LogSystem::LogExplosion(IncenRocket, position);
					//LogSystem::Log(StringFormat::format(xorstr_(L"✚ Explosion: %ls, Distsnce: %1.0fm"), wIncenRocket.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion.prefab"):
					LogSystem::LogExplosion(Rocket, position);
					//LogSystem::Log(StringFormat::format(xorstr_(L"✚ Explosion: %ls, Distsnce: %1.0fm"), wRocket.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				}
			}
			return original_createeffect(strPrefab, effect);
		}
		void __fastcall SetFlying(ModelState* a1, bool a2) { }
		void SendClientTick(BasePlayer* baseplayer) {
			if (!baseplayer) return original_sendclienttick(baseplayer);
			if (vars::misc::anti_aim) {
				if (Time::fixedTime() > (target_time + 0.1f) && target_time != 0.0f && targeted)
				{
					target_time = 0.0f;
					targeted = false;
				}
				auto input = read(baseplayer + O::BasePlayer::input, uintptr_t);
				auto state = read(input + 0x20, uintptr_t);
				auto current = read(state + 0x10, uintptr_t); if (!current) { return original_sendclienttick(baseplayer); }
				if (!current)
					return original_sendclienttick(baseplayer);
				Vector3 real_angles = safe_read(current + 0x18, Vector3);
				Vector3 spin_angles = Vector3::Zero();
				if (vars::misc::anti_aim_yaw == 0) { //x = yaw (up/down), y = pitch (spin), z = roll?????;
					if (targeted)
						spin_angles = Vector3(-999.f, (rand() % 999 + -999), (rand() % 999 + -999));
				}
				if (vars::misc::anti_aim_yaw == 1) { //backwards
					spin_angles.y = real_angles.y + (targeted ? (rand() % -180 + 1) : 180.f);
				}
				if (vars::misc::anti_aim_yaw == 2) { //backwards (down)
					spin_angles.x = (targeted ? 999.f : -999.f);
					spin_angles.z = 0.f;
					spin_angles.y = real_angles.y + 180.f;
				}
				if (vars::misc::anti_aim_yaw == 3) { //backwards (up)
					spin_angles.x = (targeted ? -999.f : 999.f);
					spin_angles.z = (targeted ? -999.f : 999.f);
					spin_angles.y = real_angles.y + 180.f;
				}
				if (vars::misc::anti_aim_yaw == 4) { //left
					spin_angles.y = real_angles.y + (targeted ? (rand() % -90 + 1) : 90.f);
				}
				if (vars::misc::anti_aim_yaw == 5) { //left (down)
					spin_angles.x = (targeted ? 999.f : -999.f);
					spin_angles.z = 0.f;
					spin_angles.y = real_angles.y + (targeted ? (rand() % -90 + 1) : 90.f);
				}
				if (vars::misc::anti_aim_yaw == 6) { //left (up)
					spin_angles.x = (targeted ? -999.f : 999.f);
					spin_angles.z = (targeted ? -999.f : 999.f);
					spin_angles.y = real_angles.y + (targeted ? (rand() % -90 + 1) : 90.f);
				}
				if (vars::misc::anti_aim_yaw == 7) { //right
					spin_angles.y = real_angles.y + (targeted ? (rand() % 90 + 1) : -90.f);
				}
				if (vars::misc::anti_aim_yaw == 8) { //right (down)
					spin_angles.x = (targeted ? 999.f : -999.f);
					spin_angles.z = 0.f;
					spin_angles.y = real_angles.y + (targeted ? (rand() % 90 + 1) : -90.f);
				}
				if (vars::misc::anti_aim_yaw == 9) { //right (up)
					spin_angles.x = (targeted ? -999.f : 999.f);
					spin_angles.z = (targeted ? -999.f : 999.f);
					spin_angles.y = real_angles.y + (targeted ? (rand() % 90 + 1) : -90.f);
				}
				if (vars::misc::anti_aim_yaw == 10) { //jitter
					if (jitter <= jitter_speed * 1)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % 45 + 1) : -45.f);
					}
					else if (jitter <= jitter_speed * 2)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % 45 + 1) : 45.f);
					}
					else if (jitter <= jitter_speed * 3)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % 180 + 1) : -180.f);
						jitter = 1;
					}
					jitter = jitter + 1;
					spin_angles.y = real_angles.y;
				}
				if (vars::misc::anti_aim_yaw == 11) { //jitter (down)
					if (jitter <= jitter_speed * 1)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % 45 + 1) : -45.f);
					}
					else if (jitter <= jitter_speed * 2)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % -45 + 1) : 45.f);
					}
					else if (jitter <= jitter_speed * 3)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % -180 + 1) : 180.f);
						jitter = 1;
					}
					jitter = jitter + 1;
					spin_angles.x = (targeted ? (rand() % 999 + 1) : -999.f);
					spin_angles.z = 0.f;
					spin_angles.y = real_angles.y;
				}
				if (vars::misc::anti_aim_yaw == 12) { //jitter (up)
					if (jitter <= jitter_speed * 1)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % -45 + 1) : 45.f);
					}
					else if (jitter <= jitter_speed * 2)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % 45 + 1) : -45.f);
					}
					else if (jitter <= jitter_speed * 3)
					{
						spin_angles.y = real_angles.y + (targeted ? (rand() % 180 + 1) : -180.f);
						jitter = 1;
					}
					jitter = jitter + 1;
					spin_angles.x = (targeted ? -999.f : 999.f);
					spin_angles.z = (targeted ? -999.f : 999.f);
					spin_angles.y = real_angles.y;
				}
				if (vars::misc::anti_aim_yaw == 13) { //spin
					spin_angles.y = targeted ? -(real_angles.y + (spin_speed * spin++)) : real_angles.y + (spin_speed * spin++);
					if (spin > (360 / spin_speed))
						spin = 1;
				}
				if (vars::misc::anti_aim_yaw == 14) { //spin (down)
					spin_angles.x = (targeted ? 999.f : -999.f);
					spin_angles.z = 0.f;
					spin_angles.y = targeted ? -(real_angles.y + (spin_speed * spin++)) : real_angles.y + (spin_speed * spin++);
					if (spin > (360 / spin_speed))
						spin = 1;
				}
				if (vars::misc::anti_aim_yaw == 15) { //spin (up)
					spin_angles.x = (targeted ? -999.f : 999.f);
					spin_angles.y = targeted ? -(real_angles.y + (spin_speed * spin++)) : real_angles.y + (spin_speed * spin++);
					spin_angles.z = (targeted ? -999.f : 999.f);
					if (spin > (360 / spin_speed))
						spin = 1;
				}
				if (vars::misc::anti_aim_yaw == 16) { //random
					spin_angles = Vector3((rand() % 999 + -999), (rand() % 999 + -999), (rand() % 999 + -999));
				}

				if (spin_angles != Vector3::Zero())
					write(current + 0x18, spin_angles, Vector3);
			}
			if (vars::misc::local_bones)
			{
				last_head_pos = baseplayer->bones()->head->position;
				last_neck_pos = baseplayer->bones()->neck->position;
				last_spine4_pos = baseplayer->bones()->spine4->position;
				last_spine1_pos = baseplayer->bones()->spine1->position;
				last_l_upperarm_pos = baseplayer->bones()->l_upperarm->position;
				last_l_forearm_pos = baseplayer->bones()->l_forearm->position;
				last_l_hand_pos = baseplayer->bones()->l_hand->position;
				last_r_upperarm_pos = baseplayer->bones()->r_upperarm->position;
				last_r_forearm_pos = baseplayer->bones()->r_forearm->position;
				last_r_hand_pos = baseplayer->bones()->r_hand->position;
				last_pelvis_pos = baseplayer->bones()->pelvis->position;
				last_l_knee_pos = baseplayer->bones()->l_knee->position;
				last_l_foot_pos = baseplayer->bones()->l_foot->position;
				last_r_knee_pos = baseplayer->bones()->r_knee->position;
				last_r_foot_pos = baseplayer->bones()->r_foot->position;
			}
			if (baseplayer->userID() == LocalPlayer::Entity()->userID()) {
				Vector3 current = baseplayer->transform()->position();
				Vector3 old = baseplayer->lastSentTick()->tick_position();
				Vector3 vector4 = (baseplayer->transform()->position() - baseplayer->lastSentTick()->tick_position());
				Vector3 overrided = Vector3(current.x, current.y, current.z);
				if (vars::misc::fly_auto_stopper && VFlyhack >= (VMaxFlyhack - 2.5f) && !GetAsyncKeyState(vars::keys::ignore_stopper)) {
					overrided = Vector3(overrided.x, current.y < old.y ? (current.y - 0.3f) : old.y, overrided.z);
				}
				if (vars::misc::fly_auto_stopper && HFlyhack >= (HMaxFlyhack - 2.5f) && !GetAsyncKeyState(vars::keys::ignore_stopper)) {
					overrided = Vector3(old.x, overrided.y, old.z);
				}
				if (vars::misc::fly_auto_stopper && !GetAsyncKeyState(vars::keys::ignore_stopper) && HFlyhack >= (HMaxFlyhack - 2.5f) || vars::misc::fly_auto_stopper && !GetAsyncKeyState(vars::keys::ignore_stopper) && VFlyhack >= (VMaxFlyhack - 2.5f)) {
					if (overrided != current);
					baseplayer->movement()->TeleportTo(overrided);
				}
				if (vars::misc::bhop && GetAsyncKeyState(vars::keys::bhop) || vars::misc::bhop && vars::keys::bhop == 0) {
					static float b = 4.0f;
					if (b >= 4.0f) {
						float radius = baseplayer->GetRadius();
						float height = baseplayer->GetHeight(false);
						Vector3 vector = (baseplayer->lastSentTick()->tick_position() + baseplayer->transform()->position()) * 0.5f;
						float flyhack_extrusion = 0.25f;
						Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
						Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
						float radius2 = radius - 0.05f;
						bool isgrounded = GamePhysics::CheckCapsule(vector2, vector3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);
						if (isgrounded) {
							baseplayer->movement()->Jump(baseplayer->modelState());
							b = 0.0f;
						}
					}
					b++;
				}
				if (vars::misc::farmbot && vars::misc::jumpfarm) {
					static float b = 4.0f;
					if (b >= 4.0f) {
						float radius = baseplayer->GetRadius();
						float height = baseplayer->GetHeight(false);
						Vector3 vector = (baseplayer->lastSentTick()->tick_position() + baseplayer->transform()->position()) * 0.5f;
						float flyhack_extrusion = 0.25f;
						Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
						Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
						float radius2 = radius - 0.05f;
						bool isgrounded = GamePhysics::CheckCapsule(vector2, vector3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);
						if (isgrounded) {
							baseplayer->movement()->Jump(baseplayer->modelState());
							b = 0.0f;
						}
					}
					b++;
				}
			}
			return original_sendclienttick(baseplayer);
		}
		void DoFixedUpdate(PlayerWalkMovement* movement, ModelState* modelstate) {
			float speed = (read(movement + 0x143, bool) /*swimming*/ || read(movement + 0x50, float) /* ducked */ > 0.5f) ? 1.7f : (read(movement + 0x145, bool) /*jumping*/ ? 8.f : 5.5f);
			if (vars::misc::farmbot) {
				if (vars::misc::farmbot_trees) {
					Vector3 vel = read(movement + 0x34, Vector3);
					f_object closest = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head), xorstr_("tree"));
					if (closest.valid) {
						Vector3 direction = (closest.position - LocalPlayer::Entity()->get_bone_pos(head)).Normalized() * speed;
						write(movement + 0x34, Vector3(direction.x, vel.y, direction.z), Vector3);
					}
				}
				if (vars::misc::farmbot_ore) {
					Vector3 vel = read(movement + 0x34, Vector3);
					f_object closest = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head), xorstr_("ore.prefab"));
					if (closest.valid) {
						Vector3 direction = (closest.position - LocalPlayer::Entity()->get_bone_pos(head)).Normalized() * speed;
						write(movement + 0x34, Vector3(direction.x, vel.y, direction.z), Vector3);
					}
				}
				if (vars::misc::farmbot_barrels) {
					Vector3 vel = read(movement + 0x34, Vector3);
					f_object closest = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head), xorstr_("barrel"));
					if (closest.valid) {
						Vector3 direction = (closest.position - LocalPlayer::Entity()->get_bone_pos(head)).Normalized() * speed;
						write(movement + 0x34, Vector3(direction.x, vel.y, direction.z), Vector3);
					}
				}
			}


			//if (!movement->flying()) {
			//	Vector3 vel = movement->TargetMovement();
			//	if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
			//		float max_speed = (movement->swimming() || movement->Ducking() > 0.5) ? 1.7f : 5.5f;
			//		if (vel.length() > 0.f) {
			//			movement->TargetMovement() = Vector3::Zero();
			//		}
			//	}
			//}

			original_dofixedupdate(movement, modelstate);
		}

		void ClientInput(BasePlayer* baseplayah, ModelState* ModelState) {
			if (!baseplayah) return original_clientinput(baseplayah, ModelState);
			if (!baseplayah->IsValid()) return original_clientinput(baseplayah, ModelState);

			auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
			Vector3 startPos = LocalPlayer::Entity()->get_bone_pos(head);
			Vector3 endPos = ((BasePlayer*)TargetPlayer)->get_bone_pos(head);
			//if (true) {
			//	DWORD64 BaseNetworkable;
			//	BaseNetworkable = read(vars::stor::gBase + CO::BaseNetworkable, DWORD64); //BaseNetworkable_c 
			//	DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
			//	DWORD64 ClientEntities = read(EntityRealm, DWORD64);
			//	DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
			//	DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
			//	if (!ClientEntities_values) return;
			//	int EntityCount = read(ClientEntities_values + 0x10, int);
			//	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);
			//	for (int i = 0; i <= EntityCount; i++)
			//	{
			//		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);
			//		if (Entity <= 100000) continue;
			//		DWORD64 Object = read(Entity + 0x10, DWORD64);
			//		if (Object <= 100000) continue;
			//		DWORD64 ObjectClass = read(Object + 0x30, DWORD64);
			//		if (ObjectClass <= 100000) continue;
			//		pUncStr name = read(ObjectClass + 0x60, pUncStr);
			//		if (!name) continue;
			//		char* buff = name->stub;
			//		BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			//		if (strstr(buff, xorstr_("Local"))) {
			//			BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			//			BasePlayer* Local = (BasePlayer*)read(Object + 0x28, DWORD64);
			//			if (!read(Player + O::BasePlayer::playerModel, DWORD64)) continue;

			//			HandChams();
			//		}

			//		if (strstr(buff, xorstr_("player.prefab")))
			//		{
			//			BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			//			BasePlayer* Local = (BasePlayer*)read(Object + 0x28, DWORD64);
			//			if (!read(Player + O::BasePlayer::playerModel, DWORD64)) continue;
			//			lol::update_chams();
			//			/*chams(Player);*/
			//		}
			//	}
			//}
			if (vars::visuals::hand_chams) {
				auto oxunem = il2cpp::_init_class(xorstr_("Graphics"), xorstr_("ConVar"));
				auto static_fields = safe_read(oxunem + 0xb8, uintptr_t);
				safe_write(static_fields + 0x75, false, bool);
			}

			if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key))
				baseplayah->clientTickInterval() = 0.99f;
			else {
				baseplayah->clientTickInterval() = 0.05f;
			}
			if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
				other::find_manipulate_angle();
			}
			else if (!other::m_manipulate.empty()) {
				other::m_manipulate = Vector3::Zero();
			}

			if (vars::misc::rayleigh_changer) {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_rayleigh)(vars::misc::rayleigh);
			}
			else {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_rayleigh)(vars::misc::rayleigh);
			}
			if (vars::misc::mie_changer) {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_mie)(vars::misc::mie);
			}
			else {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_mie)(vars::misc::mie);
			}
			if (vars::misc::brightness_changer) {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_brightness)(vars::misc::brightness);
			}
			else {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_brightness)(vars::misc::brightness);
			}

			typedef void(__stdcall* oxunem)(float);
			if (vars::misc::speedhack && GetAsyncKeyState(vars::keys::speedkey)) {
				oxunem Infinity = (oxunem)(vars::stor::gBase + CO::set_timeScale);
				Infinity(2);
			}
			else {
				oxunem Infinity = (oxunem)(vars::stor::gBase + CO::set_timeScale);
				Infinity(1);
			}

			if (vars::misc::mass_suicide) {
				LocalPlayer::Entity()->OnLand(-108.0001f);
			}

			if (vars::misc::movement_line) {
				if (baseplayah->get_flag(PlayerFlags::Connected)) {
					DDraw::Line(baseplayah->_playerModel()->position(), baseplayah->lastSentTick()->tick_position(), Color(vars::colors::mov_line.x, vars::colors::mov_line.y, vars::colors::mov_line.z, 255), 1.f, true, true);
				}
				else {}
			}

			if (vars::misc::flyhack_indicator) {
				CheckFlyhack();
			}

			auto held = baseplayah->GetHeldEntity<BaseProjectile>();
			BaseProjectile* _held = held = baseplayah->GetHeldEntity<BaseProjectile>();

			float lastShotTime = _held->lastShotTime() - GLOBAL_TIME;
			float reloadTime = _held->nextReloadTime() - GLOBAL_TIME;

			float desyncpercentage;
			float desyncTime = (Time::realtimeSinceStartup() - baseplayah->lastSentTickTime()) - 0.03125 * 3;
			desyncpercentage = ((desyncTime / 0.99f) * 100.0f) + 1.f;
			variables::manipulator::desync = (0.1f + (((desyncTime)+2.f / 60.f + 0.125f) * 1.5f) * baseplayah->GetMaxSpeed()) - 0.05f;

			if (_held && _held != nullptr && _held->class_name_hash() == STATIC_CRC32("BaseProjectile") ||
				_held && _held != nullptr && _held->class_name_hash() == STATIC_CRC32("BowWeapon") ||
				_held && _held != nullptr && _held->class_name_hash() == STATIC_CRC32("CrossBowWeapon")) {
				if (vars::combat::autoreload && _held)
				{
					BaseProjectile* ent = baseplayah->GetHeldEntity<BaseProjectile>();

					if (!did_reload)
						time_since_last_shot = (Time::fixedTime() - fixed_time_last_shot);

					if (just_shot && (time_since_last_shot > 0.2f))
					{
						ent->_ServerRPC(xorstr_("StartReload"));
						ent->SendSignalBroadcast(BaseEntity::Signal::Reload);
						just_shot = false;
					}
					if (time_since_last_shot > (_held->reloadTime() - (_held->reloadTime() / 10))
						&& !did_reload)
					{
						ent->_ServerRPC(xorstr_("Reload"));
						did_reload = true;
						time_since_last_shot = 0;
					}
				}
			}
			else {
				did_reload = false;
				just_shot = true;
				fixed_time_last_shot = Time::fixedTime();
			}

			if (baseplayah->userID() == LocalPlayer::Entity()->userID()) {
				if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1588298435 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -778367295 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1367281941 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -765183617 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -41440462 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 795371088 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -75944661 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 884424049 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1318558775 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1796682209 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 649912614 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 818877484 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -852563019 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1373971859 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1758372725 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1812555177 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -904863145 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1545779598 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1335497659 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -2069578888 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1214542497 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 28201841 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1953903201) {
					if (vars::combat::desync_autoshoot_type == 0) {
						if (vars::combat::autoshoot) {
							if (vars::combat::autoshoot_type == 0) {
								if (!held->Empty()) {
									if (_held && reloadTime < 1.f) {
										if (lastShotTime < -0.1f) {
											if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->userID()) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
												if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), baseplayah->eyes()->position())) {
													_held->LaunchProjectile();
													_held->primaryMagazine()->contents()--;
													_held->UpdateAmmoDisplay();
													_held->ShotFired();
													_held->DidAttackClientside();
													_held->BeginCycle();
												}
											}
										}
									}
								}
							}
						}

						if (vars::combat::autoshoot) {
							if (vars::combat::autoshoot_type == 1) {
								if (!held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
									if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->isCached()) {
										auto mpv = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->find_mpv_bone();
										Vector3 target;
										if (mpv != nullptr)
											target = mpv->position;
										else
											target = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->bones()->head->position;

										if (utils::LineOfSight(target, baseplayah->eyes()->position()))
											held->DoAttack();
									}
								}
							}
						}
					}

					if (vars::combat::desync_autoshoot_type == 1) {
						if (vars::combat::autoshoot && vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
							if (vars::combat::autoshoot_type == 0) {
								if (!held->Empty()) {
									if (_held && reloadTime < 1.f) {
										if (lastShotTime < -0.1f) {
											if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->userID()) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
												if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), baseplayah->eyes()->position())) {
													_held->LaunchProjectile();
													_held->primaryMagazine()->contents()--;
													_held->UpdateAmmoDisplay();
													_held->ShotFired();
													_held->DidAttackClientside();
													_held->BeginCycle();
												}
											}
										}
									}
								}
							}
						}

						if (vars::combat::autoshoot && vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
							if (vars::combat::autoshoot_type == 1) {
								if (!held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
									if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->isCached()) {
										auto mpv = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->find_mpv_bone();
										Vector3 target;
										if (mpv != nullptr)
											target = mpv->position;
										else
											target = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->bones()->head->position;

										if (utils::LineOfSight(target, baseplayah->eyes()->position()))
											held->DoAttack();
									}
								}
							}
						}
					}

					if (vars::combat::instakill && GetAsyncKeyState(vars::keys::instakill)) {
						if (vars::combat::instakill_type == 0) {
							if (!held->Empty()) {
								if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->userID()) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
									if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), baseplayah->eyes()->position())) {
										baseplayah->clientTickInterval() = 0.99f;
										if (desyncTime > 0.80f) {
											_held->LaunchProjectile();
											_held->primaryMagazine()->contents()--;
											_held->UpdateAmmoDisplay();
											_held->ShotFired();
											_held->DidAttackClientside();
											_held->BeginCycle();
										}
									}
								}
							}
						}
					}

					if (vars::combat::instakill && GetAsyncKeyState(vars::keys::instakill)) {
						if (vars::combat::instakill_type == 1) {
							if (!held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
								if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->userID()) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
									if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), baseplayah->eyes()->position())) {
										baseplayah->clientTickInterval() = 0.99f;
										if (desyncTime > 0.80f) {
											held->DoAttack();
										}
									}
								}
							}
						}
					}
				}

				if (vars::misc::local_bones)
				{
					//DDraw::Line(localPlayer->eyes( )->get_position( ), ret->hitPositionWorld( ), Color(1, 0, 0, 1), 0.05f, false, true);
					DDraw::Sphere(last_head_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //head
					DDraw::Line(last_head_pos, last_neck_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Line(last_neck_pos, last_spine4_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_spine4_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.05f, false); //
					DDraw::Line(last_spine4_pos, last_spine1_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_spine4_pos, last_l_upperarm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_spine4_pos, last_r_upperarm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_spine1_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_spine1_pos, last_pelvis_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_spine1_pos, last_l_upperarm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_spine1_pos, last_r_upperarm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_upperarm_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_l_upperarm_pos, last_l_forearm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_forearm_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_l_forearm_pos, last_l_hand_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_hand_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //

					DDraw::Sphere(last_r_upperarm_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_r_upperarm_pos, last_r_forearm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_r_forearm_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_r_forearm_pos, last_r_hand_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_r_hand_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //

					DDraw::Sphere(last_pelvis_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_pelvis_pos, last_l_knee_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_pelvis_pos, last_r_knee_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_knee_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_l_knee_pos, last_l_foot_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_foot_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //

					DDraw::Sphere(last_r_knee_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_r_knee_pos, last_r_foot_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_r_foot_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
				}

				static bool alreadystartedReload = false;

				static bool alreadyReset = false;
				if (vars::combat::desync)
				{
					alreadyReset = false;
					static int updownleft = 0;
					static bool waspressed = false;
					if (vars::keys::PressedKeys[VK_DELETE])
					{
						waspressed = true;
					}

					if (!vars::keys::PressedKeys[VK_DELETE] && waspressed)
					{
						waspressed = false;
						updownleft += 1;
						if (updownleft > 3)
						{
							updownleft = 0;
						}
					}
				}
				if (vars::combat::desync && GetAsyncKeyState(vars::keys::desync)) {
					static int updownleft = 0;
					float desyncTime = (Time::realtimeSinceStartup() - baseplayah->lastSentTickTime()) - 0.03125 * 3;
					float max_eye_value = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * baseplayah->MaxVelocity()) - 0.05f;
					baseplayah->clientTickInterval() = 1.f;

					if (updownleft == 0)
					{
						baseplayah->eyes()->viewOffset().y = max_eye_value;
					}
				}

				if (vars::weapons::compound && held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon")) {
					reinterpret_cast<CompoundBowWeapon*>(held)->currentHoldProgress() = 1.5f;
				}

				GLOBAL_TIME = Time::time();
			}

			Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
			DWORD64 active = weapon->entity();
			char* classname = weapon->ClassName();
			bool weaponmelee = weapon && classname && (strcmp(classname, xorstr_("BaseMelee")) || strcmp(classname, xorstr_("Jackhammer")));
			if (active && vars::misc::weapon_spam) {
				if (GetAsyncKeyState(vars::keys::weaponspam)) {
					reinterpret_cast<void(*)(uintptr_t, Signal, Str)>(vars::stor::gBase + CO::SendSignalBroadcast)(active, Signal::Attack, Str(xorstr_(L"")));
				}
			}
			if (vars::stor::meme_target != NULL) {
				if (!reinterpret_cast<BasePlayer*>(vars::stor::meme_target)->IsValid()) {
					vars::stor::meme_target = NULL;
				}
				if (LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::meme_target)->userID())) {
					vars::stor::meme_target = NULL;
				}
				if (reinterpret_cast<BasePlayer*>(vars::stor::meme_target)->health() <= 0.f) {
					vars::stor::meme_target = NULL;
				}
			}

			lol::auto_farm_loop(weaponmelee, active);
			game_thread_loop();

			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::Water, !vars::misc::walker);
			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::Tree, vars::misc::walker);
			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::AI, vars::misc::walker);

			weapon_set();
			misc_set();

			original_clientinput(baseplayah, ModelState);

			if (vars::misc::farmbot || vars::misc::egg_bot) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sprinting);
			}

			if (vars::misc::modelstate == 0) {
			}
			if (vars::misc::modelstate == 1) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::OnLadder);
			}
			if (vars::misc::modelstate == 2) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::OnGround);
			}
			if (vars::misc::modelstate == 3) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Ducked);
			}
			if (vars::misc::modelstate == 4) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sleeping);
			}

			if (vars::misc::omnidirectional_sprinting) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sprinting);
			}

			if (vars::misc::interactive_debug && GetAsyncKeyState(vars::keys::debugging)) {
				BaseProjectile* ent = baseplayah->GetHeldEntity<BaseProjectile>();
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Mounted);
				ent->_ServerRPC(xorstr_("RPC_LootPlayer"));
			}
		}
		void UpdateAmbient(TOD_Sky* TOD_Sky) {
			uintptr_t cycle = read(TOD_Sky + 0x38, uintptr_t);
			uintptr_t ambient = read(TOD_Sky + 0x90, uintptr_t);
			if (vars::misc::night_stars) {
				uintptr_t stars = read(TOD_Sky + 0x70, uintptr_t);
				*(float*)(stars + 0x14) = vars::misc::stars;
			}

			if (!vars::misc::bright_ambient) {
				return original_updateambient(TOD_Sky);
			}
			RenderSettings::set_ambientMode(RenderSettings::AmbientMode::Flat);
			RenderSettings::set_ambientIntensity(6.f);
			RenderSettings::set_ambientLight(Color({ vars::colors::ambient_color.x, vars::colors::ambient_color.y, vars::colors::ambient_color.z, 1 }));
		}
		pUncStr Run(ConsoleOptions* options, pUncStr strCommand, DWORD64 args) {
			if (options->IsFromServer()) {
				std::wstring cmd = std::wstring(strCommand->str);
				if (cmd.find(xorstr_(L"noclip")) != std::wstring::npos || cmd.find(xorstr_(L"debugcamera")) != std::wstring::npos || cmd.find(xorstr_(L"camspeed")) != std::wstring::npos || cmd.find(xorstr_(L"admintime")) != std::wstring::npos) {
					strCommand = nullptr;
				}
			}
			return original_consolerun(options, strCommand, args);
		}
		void DoHitNotify(BaseCombatEntity* entity, HitInfo* info, Projectile* prj) {
			if (entity->IsPlayer()) {
				if (vars::misc::hit_logs) {
			/*		std::stringstream ss;*/
					std::string _name(CStringA(reinterpret_cast<BasePlayer*>(entity)->_displayName()));
					std::string string;
					float damage = info->damageTypes()->Total();
					char buf[256] = { 0 }; sprintf_s(buf, xorstr_("Hit for %.2f damage"), damage);
					string += buf;
					notify::add_log("Logs", string.c_str(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
				}
				if (vars::misc::hitmaterial == 0) {
				}
				if (vars::misc::hitmaterial == 1) {
					uint32_t material = utils::StringPool::Get(xorstr_("glass"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 2) {
					uint32_t material = utils::StringPool::Get(xorstr_("water"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 3) {
					uint32_t material = utils::StringPool::Get(xorstr_("wood"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 4) {
					uint32_t material = utils::StringPool::Get(xorstr_("metal"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 5) {
					uint32_t material = utils::StringPool::Get(xorstr_("sand"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 6) {
					uint32_t material = utils::StringPool::Get(xorstr_("grass"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 7) {
					uint32_t material = utils::StringPool::Get(xorstr_("rock"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 8) {
					uint32_t material = utils::StringPool::Get(xorstr_("concrete"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 9) {
					uint32_t material = utils::StringPool::Get(xorstr_("forest"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 10) {
					uint32_t material = utils::StringPool::Get(xorstr_("cloth"));
					info->HitMaterial() = material;
				}
				if (vars::misc::hitmaterial == 11) {
					uint32_t material = utils::StringPool::Get(xorstr_("null"));
					info->HitMaterial() = material;
				}
				if (vars::misc::custom_hitsound) {

					if (vars::misc::hitsound_rejim == 0) {
						PlaySoundA((LPCSTR)NL, NULL, SND_MEMORY | SND_ASYNC);
					}

					return;
				}
				if (vars::combat::always_headshot) {
					reinterpret_cast<void(*)(Str, GameObject*)>(vars::stor::gBase + CO::EffectRun)(
						Str(xorstr_(L"assets/bundled/prefabs/fx/headshot_2d.prefab")),
						LocalPlayer::Entity()->eyes()->gameObject());
					return;
				}
			}

			return original_dohitnotify(entity, info, prj);
		}
		bool get_isHeadshot(HitInfo* hitinfo) {
			if (vars::misc::custom_hitsound) {
				return false;
			}
			if (vars::combat::always_headshot) {
				return false;
			}
			return original_getisheadshot(hitinfo);
		}
		void Play(ViewModel* viewmodel, pUncStr name, int layer = 0) {
			if (vars::weapons::remove_attack_anim) {
				static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::DoAttack(): Void");
				if (!CALLED_BY(ptr, 0x296) || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -75944661) {
					return original_viewmodelplay(viewmodel, name, layer);
				}
			}
			else {
				return original_viewmodelplay(viewmodel, name, layer);
			}
		}
	}
	namespace combat {
		float GetRandomVelocity(ItemModProjectile* mod) {
			return vars::weapons::fast_bullets ? original_getrandomvelocity(mod) * 1.499 : original_getrandomvelocity(mod);
		}
		void AddPunch(HeldEntity* a1, Vector3 a2, float duration) {
			if (vars::weapons::no_recoil) {
				a2 *= vars::weapons::recoil_control / 100.f;
			}
			return original_addpunch(a1, a2, duration);
		}
		Vector3 MoveTowards(Vector3 a1, Vector3 a2, float maxDelta) {
			static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::SimulateAimcone(): Void");
			if (CALLED_BY(ptr, 0x800)) {
				if (vars::weapons::no_recoil) {
					a2 *= vars::weapons::recoil_control / 100.f;
					maxDelta *= vars::weapons::recoil_control / 100.f;
				}
			}
			return original_movetowards(a1, a2, maxDelta);
		}
		bool DoHit(Projectile* prj, HitTest* test, Vector3 point, Vector3 normal) {
			auto localPlayer = LocalPlayer::Entity();
			auto held = localPlayer->GetHeldEntity<BaseProjectile>();
			if (prj->isAuthoritative()) {
				if (vars::combat::ignore_team) {
					if (test->HitEntity() != null) {
						if (test->HitEntity()->IsValid()) {
							if (LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(test->HitEntity())->userID())) {
								if (reinterpret_cast<BaseCombatEntity*>(test->HitEntity())->IsPlayer()) {
									return false;
								}
							}
						}
					}
				}

				if (vars::misc::hitmarker) {
					if (test->HitEntity() != nullptr) {
						if (test->HitEntity()->IsValid()) {
							if (reinterpret_cast<BasePlayer*>(test->HitEntity())->IsPlayer()) {
								DDraw::Text(il2cpp::String::New("x"), prj->currentPosition(), Color(vars::colors::marker.x, vars::colors::marker.y, vars::colors::marker.z, 255), 1.5f);
							}
						}
					}
				}
				if (vars::misc::bullet_tracers) {
					//	DDraw::Sphere(prj->previousPosition(), 0.05f, Color(1, 0, 0, 1), 1.5f, 10);
				//		DDraw::Sphere(prj->sentPosition(), 0.05f, Color(1, 0, 0, 1), 1.5f, 10);
					//DDraw::Line(localPlayer->eyes()->position(), prj->currentPosition(), Color(89, 227, 255, 89), 5.5f, false, true);
					DDraw::Line(localPlayer->eyes()->position(), prj->currentPosition(), Color(89, 227, 89, 89), 1.5f, false, true);
				}
				if (vars::combat::tree_reflect) {
					if (test->HitEntity() != null) {
						if (!reinterpret_cast<BaseCombatEntity*>(test->HitEntity())->IsPlayer()) {
							prj->penetrationPower(35.f);
						}
					}
				}
				if (vars::weapons::penetrate) {
					if (test->HitEntity() != null) {
						if (test->HitEntity()->IsValid()) {
							BaseCombatEntity* lol = reinterpret_cast<BaseCombatEntity*>(test->HitEntity());
							if (vars::stuff::testInt == 2) {
								printf(xorstr_("%s \n"), lol->ClassName());
							}
							if (lol->ClassNameHash() == STATIC_CRC32("CargoShip") || lol->ClassNameHash() == STATIC_CRC32("BaseOven")
								|| lol->ClassNameHash() == STATIC_CRC32("TreeEntity") || lol->ClassNameHash() == STATIC_CRC32("OreResourceEntity")
								|| lol->ClassNameHash() == STATIC_CRC32("CH47HelicopterAIController") || lol->ClassNameHash() == STATIC_CRC32("MiniCopter")
								|| lol->ClassNameHash() == STATIC_CRC32("BoxStorage") || lol->ClassNameHash() == STATIC_CRC32("Workbench")
								|| lol->ClassNameHash() == STATIC_CRC32("VendingMachine") || lol->ClassNameHash() == STATIC_CRC32("Barricade")
								|| lol->ClassNameHash() == STATIC_CRC32("BuildingPrivlidge") || lol->ClassNameHash() == STATIC_CRC32("LootContainer")
								|| lol->ClassNameHash() == STATIC_CRC32("HackableLockedCrate") || lol->ClassNameHash() == STATIC_CRC32("ResourceEntity")
								|| lol->ClassNameHash() == STATIC_CRC32("RidableHorse") || lol->ClassNameHash() == STATIC_CRC32("MotorRowboat")
								|| lol->ClassNameHash() == STATIC_CRC32("ScrapTransportHelicopter") || lol->ClassNameHash() == STATIC_CRC32("JunkPile")
								|| lol->ClassNameHash() == STATIC_CRC32("MiningQuarry") || lol->ClassNameHash() == STATIC_CRC32("WaterCatcher")) {
								return false;
							}
						}
					}
				}
			}
			return original_dohit(prj, test, point, normal);
		}
		void Launch(Projectile* prdoj) {
			if (vars::weapons::no_spread) {
				write(prdoj->mod() + 0x38, 0.f, float);
			}
			return original_launch(prdoj);
		}
		bool CanHoldItems(BaseMountable* a1) {
			if (vars::weapons::minicopter_aim) return true;
			return original_canholditems(a1);
		}
		void SendProjectileAttack(BasePlayer* a1, PlayerProjectileAttack* a2) {
			uintptr_t PlayerAttack = read(a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
			uintptr_t Attack = read(PlayerAttack + 0x18, uintptr_t); // public Attack attack;
			uint32_t hitID = read(Attack + 0x2C, uint32_t);
			if (vars::weapons::spoof_hitdistance) {
				write(a2 + 0x2C, vars::weapons::hitdistance, float);
			}
			if (vars::combat::always_headshot || vars::combat::always_heli_rotor) {
				BaseCombatEntity* entity = BaseNetworkable::clientEntities()->Find<BaseCombatEntity*>(hitID);
				if (vars::combat::always_headshot) {
					if (entity->IsPlayer()) {
						uint32_t bone = utils::StringPool::Get(xorstr_("head"));
						write(Attack + 0x30, bone, uint32_t);
					}
				}
				if (vars::combat::always_heli_rotor) {
					if (entity->ClassNameHash() == STATIC_CRC32("BaseHelicopter")) {
						int health = (int)reinterpret_cast<BaseCombatEntity*>(vars::stor::closestHeli)->health();
						if (health <= 5000) {
							write(Attack + 0x30, utils::StringPool::Get(xorstr_("tail_rotor_col")), uint32_t);
						}
						else {
							write(Attack + 0x30, utils::StringPool::Get(xorstr_("engine_col")), uint32_t);
						}
					}
				}
			}
			return original_sendprojectileattack(a1, a2);
		}
		bool CanAttack(BasePlayer* a1) {
			if (vars::misc::can_attack)
				return true;
			return original_canattack(a1);
		}
		Projectile* CreateProjectile(BaseProjectile* BaseProjectileA, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) {
			Projectile* projectile = original_create_projectile(BaseProjectileA, prefab_pathptr, pos, forward, velocity);
			BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
			projectile->transform()->set_scale({ 8, 8 ,8 });

			if (vars::weapons::thick_bullet) {
				projectile->thickness(vars::weapons::thickness);
			}
			else {
				projectile->thickness(0.1f);
			}

			float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
			if (vars::combat::bullet_tp)
			{
				auto pos = Vector3_::MoveTowards(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), BaseProjectileA->transform()->position(), 2.0f);
				auto d2t = LocalPlayer::Entity()->eyes()->get_position().distance(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head));

				projectile->initialDistance(d2t - 2.f); //1m then 2m?
				projectile->integrity(10.f);
				projectile->ricochetChance(1.f);
				DDraw::Sphere(pos, 0.05f, Color::Color(1, 0, 0, 50), 5.f, false);
				magic_projectile_test = false;
			}
			else projectile->initialDistance(1.f);

			if (vars::combat::bullet_tp && desyncTime > 0.f && !magic_projectile_test) {

				if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), LocalPlayer::Entity()->eyes()->position())
					&& desyncTime > insta_travel_check_time)
				{
					projectile->initialDistance(4.f);
					projectile->integrity(10.f);
				}
			}
			else projectile->initialDistance(1.f);

			return projectile;
		}
		Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
			BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
			Vector3 Local = LocalPlayer::Entity()->eyes()->get_position();
			Vector3 heli_target = reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->transform()->position() + Vector3(0, 1.5, 0);
			Vector3 target = vars::combat::bodyaim ? TargetPlayer->get_bone_pos(spine1) : TargetPlayer->get_bone_pos(head);
			float gravity;
			if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
				gravity = 1.9f;
			}
			else {
				gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
			}
			a::Prediction(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), GetBulletSpeed(), gravity);
			a::Prediction(Local, target, TargetPlayer->newVelocity(), GetBulletSpeed(), gravity);
			Vector3 heliDir = (heli_target - Local).Normalized();
			Vector3 playerDir = (target - Local).Normalized();
			if (vars::combat::psilent) {
				if (!vars::combat::psilentonkey) {
					if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
						inputVec = playerDir;
					}
					if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
						inputVec = heliDir;
					}
				}
				else {
					if (GetAsyncKeyState(vars::keys::psilent)) {
						if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
							inputVec = playerDir;
						}
						if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
							inputVec = heliDir;
						}
					}
				}
			}
			if (vars::weapons::no_spread) {
				aimCone = 0.f;
			}
			did_reload = false;
			just_shot = true;
			fixed_time_last_shot = Time::fixedTime();
			auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
			return original_aimconedirection(aimCone, inputVec, anywhereInside);
		}
		Vector3 hk_BodyLeanOffset(PlayerEyes* a1) {
			if (vars::combat::manipulator && !other::m_manipulate.empty()) {
				return other::m_manipulate;
			}
			return Original_BodyLeanOffset(a1);
		}
		Vector3 hk_EyePositionForPlayer(BaseMountable* arg1, BasePlayer* arg2, Quaternion* arg3) {
			BasePlayer* player = arg2;
			if (player->userID()) {
				if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
					return Original_EyePositionForPlayer(arg1, arg2, arg3) + other::m_manipulate;
				}
			}
			return Original_EyePositionForPlayer(arg1, arg2, arg3);
		}
		void hk_DoFirstPersonCamera(PlayerEyes* a1, Component* cam) {
			if (!a1 || !cam) return;
			Original_DoFirstPersonCamera_hk(a1, cam);
			if (vars::combat::manipulator) {
				Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
				cam->transform()->set_position(re_p);
			}
		}
	}
	System::Object_* StartCoroutine_hk(MonoBehaviour* a1, System::Object_* un2) {
		if (vars::misc::fast_loot) {
			static auto v = METHOD("Assembly-CSharp::ItemIcon::SetTimedLootAction(UInt32,Action): Void");
			if (CALLED_BY(v, 0x656)) {
				*reinterpret_cast<float*>(un2 + 0x28) = -0.2f;
			}
		}
		return a1->StartCoroutine(un2);
	}
}

void UpdateVelocity_hk(PlayerWalkMovement* self) {
	if (!self->flying()) {
		Vector3 vel = self->TargetMovement();
		if (vars::misc::omnidirectional_sprinting) {
			float max_speed = (self->swimming() || self->Ducking() > 0.5) ? 1.7f : 5.5f;
			if (vel.length() > 0.f) {

				Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
				self->TargetMovement() = target_vel;
			}
		}
	}

	return original_updatevelos(self);
}

void HandleJumping_hk(PlayerWalkMovement* a1, ModelState* state, bool wantsJump, bool jumpInDirection = false) {
	if (vars::misc::inf_jump) {
		if (!wantsJump)
			return;

		a1->grounded() = (a1->climbing() = (a1->sliding() = false));
		state->set_ducked(false);
		a1->jumping() = true;
		state->set_jumped(true);
		a1->jumpTime() = Time::time();
		a1->ladder() = nullptr;

		Vector3 curVel = a1->body()->velocity();
		a1->body()->set_velocity({ curVel.x, 10, curVel.z });
		return;
	}

	return original_jumpup(a1, state, wantsJump, jumpInDirection);
}

inline float __fastcall Fake_GetSpeed(float* a1, float* a2)
{
	if (vars::misc::speedhack && GetAsyncKeyState(vars::keys::speedkey));
	return true;
	return  Orig_GetSpeed(a1, a2);
}

void OnLand_hk(BasePlayer* ply, float vel) {
	if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return ply->OnLand(vel);
	if (!vars::misc::no_fall)
		ply->OnLand(vel);
}

bool IsDown_hk(InputState* self, Button btn) {
	if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return original_isdown(self, btn);
	if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1588298435 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -778367295 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1367281941 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -765183617 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -41440462 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 795371088 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -75944661 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 884424049 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1318558775 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1796682209 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 649912614 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 818877484 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -852563019 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1373971859 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1758372725 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1812555177 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -904863145 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1545779598 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1335497659 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -2069578888 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1214542497 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 28201841 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1953903201) {
		if (vars::combat::autoshoot) {
			if (vars::combat::desync_autoshoot_type == 0) {
				if (vars::combat::autoshoot_type == 1) {
					if (btn == Button::FIRE_PRIMARY) {
						auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
						if (held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
							if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->isCached()) {
								auto mpv = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->find_mpv_bone();
								Vector3 target;
								if (mpv != nullptr)
									target = mpv->position;
								else
									target = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->bones()->head->position;

								if (utils::LineOfSight(target, LocalPlayer::Entity()->eyes()->position()) && vars::combat::autoshoot)
									return true;
							}
						}
					}
				}
			}
		}
		if (vars::combat::desync_autoshoot_type == 1) {
			if (vars::combat::autoshoot && vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
				if (vars::combat::autoshoot_type == 1) {
					if (btn == Button::FIRE_PRIMARY) {
						auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
						if (held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
							if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->isCached()) {
								auto mpv = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->find_mpv_bone();
								Vector3 target;
								if (mpv != nullptr)
									target = mpv->position;
								else
									target = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->bones()->head->position;

								if (utils::LineOfSight(target, LocalPlayer::Entity()->eyes()->position()) && vars::combat::autoshoot)
									return true;
							}
						}
					}
				}
			}
		}
		float desyncpercentage;
		float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
		desyncpercentage = ((desyncTime / 0.99f) * 100.0f) + 1.f;
		if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return original_isdown(self, btn);
		if (vars::combat::instakill && GetAsyncKeyState(vars::keys::instakill)) {
			if (vars::combat::instakill_type == 1) {
				if (btn == Button::FIRE_PRIMARY) {
					auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
					if (held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
						if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->userID()) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
							if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), LocalPlayer::Entity()->eyes()->position())) {
								LocalPlayer::Entity()->clientTickInterval() = 0.99f;
								if (desyncTime > 0.80f) {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	return original_isdown(self, btn);
}

void hk_(void* Function, void** Original, void* Detour) {
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED) {
		MessageBox(0, xorstr_(L"Initialization hook error in product, go to 2iq fix pls. dm  to get help."), 0, 0);
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	MH_EnableHook(Function);
}

void hk__() {

	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::set_flying), (void**)&original_setflying, hk::misc::SetFlying);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::SendProjectileAttack), (void**)&original_sendprojectileattack, hk::combat::SendProjectileAttack);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CanAttack), (void**)&original_canattack, hk::combat::CanAttack);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::SendClientTick), (void**)&original_sendclienttick, hk::misc::SendClientTick);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::GetModifiedAimConeDirection), (void**)&original_aimconedirection, hk::combat::GetModifiedAimConeDirection);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CanHoldItems), (void**)&original_canholditems, hk::combat::CanHoldItems);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Run), (void**)&original_consolerun, hk::misc::Run);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CreateProjectile), (void**)&original_create_projectile, hk::combat::CreateProjectile);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CreateEffect), (void**)&original_createeffect, hk::misc::CreateEffect);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Play), (void**)&original_viewmodelplay, hk::misc::Play);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::VisUpdateUsingCulling), (void**)&original_UnregisterFromVisibility, hk::misc::VisUpdateUsingCulling);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::GetRandomVelocity), (void**)&original_getrandomvelocity, hk::combat::GetRandomVelocity);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::AddPunch), (void**)&original_addpunch, hk::combat::AddPunch);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::MoveTowards), (void**)&original_movetowards, hk::combat::MoveTowards);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Refract), (void**)&original_refract, hk::exploit::Refract);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoMovement), (void**)&original_domovement, hk::exploit::DoMovement);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Launch), (void**)&original_launch, hk::combat::Launch);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoFixedUpdate), (void**)&original_dofixedupdate, hk::misc::DoFixedUpdate);
	//hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientUpdate), (void**)&original_clientupdate, hk::misc::ClientUpdate);
	//hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientUpdate_Sleeping), (void**)&original_clientupdate_sleeping, hk::misc::ClientUpdate_Sleeping);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoHit), (void**)&original_dohit, hk::combat::DoHit);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::UpdateAmbient), (void**)&original_updateambient, hk::misc::UpdateAmbient);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientInput), (void**)&original_clientinput, hk::misc::ClientInput);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoHitNotify), (void**)&original_dohitnotify, hk::misc::DoHitNotify);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::get_isHeadshot), (void**)&original_getisheadshot, hk::misc::get_isHeadshot);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::StartCoroutine), (void**)&MonoBehaviour::StartCoroutine_, hk::StartCoroutine_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::UpdateVelocity), (void**)&original_updatevelos, UpdateVelocity_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::HandleJumping), (void**)&original_jumpup, HandleJumping_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::OnLand), (void**)&BasePlayer::OnLand_, OnLand_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::IsDown), (void**)&original_isdown, IsDown_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::get_BodyLeanOffset), (void**)&Original_BodyLeanOffset, hk::combat::hk_BodyLeanOffset);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::EyePositionForPlayer), (void**)&Original_EyePositionForPlayer, hk::combat::hk_EyePositionForPlayer);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoFirstPersonCamera), (void**)&Original_DoFirstPersonCamera_hk, hk::combat::hk_DoFirstPersonCamera);
}