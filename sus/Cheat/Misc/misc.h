void weapon_set( ) {
	Item* weapon = LocalPlayer::Entity( )->GetActiveWeapon( );
	if (weapon == nullptr) return;

	//-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
	Weapon target = weapon->Info( );
	if (!target.id) return;
	if (!target.category) return;
	if (target.category == -2) {
		weapon->NoSway( );
		weapon->FastBow( );
		return;
	}
	if (target.category == 3) {
		weapon->NoSway( );
		weapon->RapidFire( );
		weapon->instakill_button();
		return;
	}
	if (target.category == 2) {
		weapon->NoSway( );
		weapon->instakill_button( );
		weapon->SetAutomatic( );
		return;
	}
	if (target.category == -1) {
		weapon->NoSway( );
		weapon->EokaTap( );
		return;
	}
}
float w_last_syringe = 0.f;
void misc_set( ) {
	if (w_last_syringe == 0.f) {
		w_last_syringe = LocalPlayer::Entity( )->lastSentTickTime( );
	}
	Item* weapon = LocalPlayer::Entity( )->GetActiveWeapon( );
	if ((weapon->GetID( ) == 1079279582 || weapon->GetID( ) == -2072273936) && vars::misc::faster_healing && LocalPlayer::Entity()->health() < 99) {
		DWORD64 Held = weapon->entity( );
		bool deployed = read(Held + O::HeldEntity::isDeployed, bool); // protected bool isDeployed;
		float curtime = LocalPlayer::Entity( )->lastSentTickTime( );
		if (deployed && curtime > w_last_syringe + 0.7f) {
			reinterpret_cast<void(_stdcall*)(DWORD64, Str)>(vars::stor::gBase + CO::ServerRPC)(Held, Str(xorstr_(L"UseSelf")));
			w_last_syringe = curtime;
		}
	}
	auto klass = read(vars::stor::gBase + CO::ConvarGraphics, DWORD64);
	auto static_fields = read(klass + 0xB8, DWORD64);
	if (vars::visuals::zoom && GetAsyncKeyState(vars::keys::zoom)) {
		write(static_fields + 0x18, 10.f, float);
	}
	else {
		write(static_fields + 0x18, vars::misc::fov, float);
	}
	if (vars::misc::spiderman) {
		uintptr_t Movement = read(LocalPlayer::Entity( ) + O::BasePlayer::movement, uintptr_t);
		write(Movement + O::PlayerWalkMovement::groundAngle, 0.f, float);
		write(Movement + O::PlayerWalkMovement::groundAngleNew, 0.f, float);
	}
	if (vars::misc::fakeadmin)
		LocalPlayer::Entity( )->FakeAdmin( );
	if (vars::misc::custom_time)
		LocalPlayer::Entity()->Admintime();
	if (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck))
		LocalPlayer::Entity()->LongNeck();
}

//box_bounds get_bounds(BasePlayer* player, float expand = 0) {
//	box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };
//
//	for (auto j : valid_bones) {
//		auto arr = player->model()->boneTransforms();
//		if (arr) {
//			auto transform = player->model()->boneTransforms()->get(j);
//			if (transform) {
//				Vector2 sc;
//				auto world_pos = transform->position();
//
//				if (j == 48)
//					world_pos.y += 0.2f;
//
//				if (il2cpp::unity::world_to_screen(world_pos, sc)) {
//					Vector2 bone_screen = sc;
//
//					if (bone_screen.x < ret.left)
//						ret.left = bone_screen.x;
//					if (bone_screen.x > ret.right)
//						ret.right = bone_screen.x;
//					if (bone_screen.y < ret.top)
//						ret.top = bone_screen.y;
//					if (bone_screen.y > ret.bottom)
//						ret.bottom = bone_screen.y;
//				}
//			}
//		}
//	}
//
//	if (ret.left == FLT_MAX)
//		return box_bounds::nulls();
//	if (ret.right == FLT_MIN)
//		return box_bounds::nulls();
//	if (ret.top == FLT_MAX)
//		return box_bounds::nulls();
//	if (ret.bottom == FLT_MIN)
//		return box_bounds::nulls();
//
//	ret.left -= expand;
//	ret.right += expand;
//	ret.top -= expand;
//	ret.bottom += expand;
//
//	return ret;
//};
namespace lol {
	void do_attack(f_object target, uintptr_t Held, bool transform) {
		if (!target.valid || !Held) return;

		if (read(Held + O::AttackEntity::nextAttackTime, float) >= Time::time( )) { return; }
		if (read(Held + O::AttackEntity::timeSinceDeploy, float) < read(Held + O::AttackEntity::deployDelay, float)) { return; }

		uintptr_t staticHitTest = read(vars::stor::gBase + CO::HitTest, DWORD64); if (!staticHitTest) return;
		uintptr_t newHitTest = il2cpp::il2cpp_object_new(staticHitTest); if (!newHitTest) return;

		uintptr_t trans; Ray ray = Ray(LocalPlayer::Entity( )->get_bone_pos(neck), (target.position - LocalPlayer::Entity( )->get_bone_pos(neck)).Normalized( ));
		if (!target.entity) return;
		if (transform) {
			trans = reinterpret_cast<BasePlayer*>(target.entity)->mono_transform(head);
		}
		else {
			trans = (DWORD64)reinterpret_cast<Object*>(target.entity)->transform( );
		} if (!trans) {
		//	LogSystem::Log(xorstr_(L"Transform no found in Infinity product, go to update mono_transform pls. dm oxunem#1337 to get help."), 1.f);
			return;
		}

		write(newHitTest + O::HitTest::MaxDistance, 1000.f, float);
		write(newHitTest + O::HitTest::HitTransform, trans, uintptr_t);
		write(newHitTest + O::HitTest::AttackRay, ray, Ray);
		write(newHitTest + O::HitTest::DidHit, true, bool);
		write(newHitTest + O::HitTest::HitEntity, reinterpret_cast<BasePlayer*>(target.entity), BasePlayer*);
		write(newHitTest + O::HitTest::HitPoint, reinterpret_cast<Transform*>(trans)->InverseTransformPoint(target.position), Vector3);
		write(newHitTest + O::HitTest::HitNormal, reinterpret_cast<Transform*>(trans)->InverseTransformPoint(target.position), Vector3);
		write(newHitTest + O::HitTest::damageProperties, read(Held + O::BaseMelee::damageProperties, uintptr_t), uintptr_t);
		reinterpret_cast<void(*)(uintptr_t, float)>(vars::stor::gBase + CO::StartAttackCooldown)(Held, read(Held + O::AttackEntity::repeatDelay, float));
		return reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(vars::stor::gBase + CO::ProcessAttack)(Held, newHitTest);
	}
	// 0, -9.1 * gravityModifier, 0
	TraceResult traceProjectile(Vector3 position, Vector3 velocity, float drag, Vector3 gravity, Vector3 targetPoint) {
		constexpr float num = 0.03125f;
		Vector3 prevPosition = position;
		float prevDist = FLT_MAX;
		Line resultLine = Line(position, position);
		float travelTime = 0.f;
		TraceResult result;

		for (; travelTime < 8.f; ) {
			prevPosition = position;
			position += velocity * num;

			Line line = Line(prevPosition, position);
			Vector3 nearest = line.ClosestPoint(targetPoint);

			float dst = (nearest - targetPoint).Length( );

			if (dst > prevDist) {
				break;
			}
			prevDist = dst;
			resultLine = line;

			velocity += gravity * num;
			velocity -= velocity * drag * num;
			travelTime += num;
		}

		Vector3 hitPos = resultLine.ClosestPoint(targetPoint);

		result.hitDist = (hitPos - targetPoint).Length( );
		result.hitPosition = hitPos;
		result.outVelocity = velocity;
		result.hitTime = travelTime - num;
		return result;
	};
	//uintptr_t shader;
	//int property;
	//void chams(uintptr_t target, Color col, bool npc = false) {
	//	if (!vars::players::chams) return;
	//	if (target) {
	//		if (!property) {
	//			property = reinterpret_cast<int(*)(Str)>(vars::stor::gBase + CO::PropertyToId)(Str(xorstr_(L"_Color")));
	//		}
	//		auto mainRendList = reinterpret_cast<List<uintptr_t>*(*)(uintptr_t)>(vars::stor::gBase + CO::get_Renderers)(target);
	//		for (int idx = 0; idx < mainRendList->get_size(); idx++) {
	//			uintptr_t renderer = mainRendList->get_value(idx);
	//			if (renderer) {
	//				uintptr_t material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(vars::stor::gBase + CO::get_material)(renderer);
	//				if (shader != reinterpret_cast<uintptr_t(*)(uintptr_t)>(vars::stor::gBase + CO::get_shader)(material)) {
	//					if (!shader)
	//						shader = utils::ShaderFind(Str(xorstr_(L"Hidden/Internal-Colored")));
	//					reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(vars::stor::gBase + CO::set_shader)(material, shader);
	//					reinterpret_cast<void(*)(uintptr_t, int, Color)>(vars::stor::gBase + CO::SetColor)(material, property, col);
	//					if (!npc) {
	//						if (vars::players::chams_xqz) {
	//							reinterpret_cast<void(*)(uintptr_t, Str, int)>(vars::stor::gBase + CO::SetInt)(material, Str(xorstr_(L"_ZTest")), 8);
	//						}
	//					}
	//					else {
	//						if (vars::npc::chams_xqz) {
	//							reinterpret_cast<void(*)(uintptr_t, Str, int)>(vars::stor::gBase + CO::SetInt)(material, Str(xorstr_(L"_ZTest")), 8);
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	float LastUpdate = 0.f;
	void update_chams() {
		if (Time::realtimeSinceStartup() > LastUpdate + vars::players::uptime) {
			reinterpret_cast<void(*)()>(vars::stor::gBase + CO::RebuildAll)();
			LastUpdate = Time::realtimeSinceStartup();
		}
	}
	float LastGrade = 0.f;
	void auto_grade(uintptr_t buildingblocc) {
		BuildingBlock* block = reinterpret_cast<BuildingBlock*>(buildingblocc);
		//LogSystem::Log(xorstr_(L"xd"), 5.f);
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastGrade + 0.35f
			&& block->CanAffordUpgrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity( ))
			&& block->CanChangeToGrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity( ))
			&& !block->IsUpgradeBlocked( )) {
			block->UpgradeToGrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity( ));
			LastGrade = LocalPlayer::Entity( )->lastSentTickTime( );
		}
	}
	float LastKnock = 0.f; float LastOpen = 0.f; float LastHatch = 0.f;
	void knocker(uintptr_t Door) {
		typedef void(__stdcall* DoorFunction)(uintptr_t, BasePlayer*);
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastKnock + 0.5f) {
			((DoorFunction)(vars::stor::gBase + CO::KnockDoor))(Door, LocalPlayer::Entity( ));
			LastKnock = LocalPlayer::Entity( )->lastSentTickTime( );
		}
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastOpen + 0.1f) {
			((DoorFunction)(vars::stor::gBase + CO::OpenDoor))(Door, LocalPlayer::Entity( ));
			LastOpen = LocalPlayer::Entity( )->lastSentTickTime( );
		}
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastHatch + 0.1f) {
			((DoorFunction)(vars::stor::gBase + CO::OpenHatch))(Door, LocalPlayer::Entity( ));
			LastHatch = LocalPlayer::Entity( )->lastSentTickTime( );
		}
	}
	float LastPickup = 0.f;
	void pickup_player(BasePlayer* ent) {
		typedef void(__stdcall* AssistPlayer)(BasePlayer*, BasePlayer*);
		if (!LocalPlayer::Entity( )->is_teammate(ent->userID( )) && vars::misc::revive_team_only) return;
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastPickup + 0.5f) {
			((AssistPlayer)(vars::stor::gBase + CO::AssistPlayer))(ent, LocalPlayer::Entity( ));
			LastPickup = LocalPlayer::Entity( )->lastSentTickTime( );
		}
	}
	void cachePlayer(BasePlayer* player) {
		static auto bundle = AssetBundle::LoadFromFile(xorstr_("C:\\Bebrinity.solution\\circuit.bundle"));
		chamsShader = bundle->LoadAsset<Shader>(xorstr_("nebnel"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
		static auto chamz = AssetBundle::LoadFromFile(xorstr_("C:\\Bebrinity.solution\\rust.assets"));
		GalaxyMaterial = chamz->LoadAsset<Shader>(xorstr_("SeethroughShader"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
		
		auto model = player->model();
		if (model) {
			auto cache = new BoneCache();

			cache->head = model->resolve(STATIC_CRC32("head"));
			cache->neck = model->resolve(STATIC_CRC32("neck"));
			cache->root = model->resolve(STATIC_CRC32("root"));
			cache->spine4 = model->resolve(STATIC_CRC32("spine4"));
			cache->spine1 = model->resolve(STATIC_CRC32("spine1"));
			cache->l_clavicle = model->resolve(STATIC_CRC32("l_clavicle"));
			cache->l_upperarm = model->resolve(STATIC_CRC32("l_upperarm"));
			cache->l_forearm = model->resolve(STATIC_CRC32("l_forearm"));
			cache->l_hand = model->resolve(STATIC_CRC32("l_hand"));
			cache->r_clavicle = model->resolve(STATIC_CRC32("r_clavicle"));
			cache->r_upperarm = model->resolve(STATIC_CRC32("r_upperarm"));
			cache->r_forearm = model->resolve(STATIC_CRC32("r_forearm"));
			cache->r_hand = model->resolve(STATIC_CRC32("r_hand"));
			cache->pelvis = model->resolve(STATIC_CRC32("pelvis"));
			cache->l_hip = model->resolve(STATIC_CRC32("l_hip"));
			cache->l_knee = model->resolve(STATIC_CRC32("l_knee"));
			cache->l_ankle_scale = model->resolve(STATIC_CRC32("l_ankle_scale"));
			cache->l_foot = model->resolve(STATIC_CRC32("l_foot"));
			cache->r_hip = model->resolve(STATIC_CRC32("r_hip"));
			cache->r_knee = model->resolve(STATIC_CRC32("r_knee"));
			cache->r_ankle_scale = model->resolve(STATIC_CRC32("r_ankle_scale"));
			cache->r_foot = model->resolve(STATIC_CRC32("r_foot"));

			if (!map_contains_key(cachedBones, player->userID()))
				cachedBones.insert(std::make_pair(player->userID(), cache));
			else
				cachedBones[player->userID()] = cache;
		}
	}
	void auto_farm_loop(bool weaponmelee, uintptr_t active) {
		if (vars::misc::auto_pickup) {
			f_object entity = f_object::get_closest_object(LocalPlayer::Entity( )->get_bone_pos(head),
				xorstr_("/collectable/"),
				Vector3::Zero( ),
				Vector3::Zero( ),
				Vector3::Zero( ),
				false
			);
			if (entity.valid) {
				Vector3 local = utils::ClosestPoint(LocalPlayer::Entity( ), entity.position);
				if (Math::Distance_3D(local, entity.position) < 3.f) {
					if (reinterpret_cast<BaseEntity*>(entity.entity)->IsValid( )) {
						utils::ServerRPC(entity.entity, Str(xorstr_(L"Pickup")));
					}
				}
			}
		}
		if (vars::misc::auto_grade) {
			f_object building_block = f_object::get_closest_object(LocalPlayer::Entity( )->get_bone_pos(head),
				xorstr_(""),
				Vector3::Zero( ),
				Vector3::Zero( ),
				Vector3::Zero( ),
				true,
				xorstr_("BuildingBlock"));
			if (building_block.valid) {
				Vector3 local = utils::ClosestPoint(LocalPlayer::Entity( ), building_block.position);
				if (Math::Distance_3D(local, building_block.position) <= 2.f) {
					if (reinterpret_cast<BaseEntity*>(building_block.entity)->IsValid( )) {
						lol::auto_grade(building_block.entity);
					}
				}
			}
		}
		if (vars::misc::auto_farm) {
			if (vars::misc::auto_farm_barrel || vars::misc::farmbot_barrels) {
				if (weaponmelee) {
					f_object ore_hot_spot = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
						xorstr_("barrel"),
						Vector3::Zero(),
						Vector3::Zero(),
						Vector3::Zero(),
						false,
						xorstr_(""));
					if (ore_hot_spot.valid) {
						Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), ore_hot_spot.position);
						if (Math::Distance_3D(local, ore_hot_spot.position) <= 2.f) {
							if (reinterpret_cast<BaseEntity*>(ore_hot_spot.entity)->IsValid()) {
								lol::do_attack(ore_hot_spot, active, false);
							}
						}
					}
				}
			}
			if (vars::misc::auto_farm_ore || vars::misc::farmbot_ore) {
				if (weaponmelee) {
					f_object ore_hot_spot = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
						xorstr_(""),
						Vector3::Zero(),
						Vector3::Zero(),
						Vector3::Zero(),
						true,
						xorstr_("OreHotSpot"));
					if (ore_hot_spot.valid) {
						Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), ore_hot_spot.position);
						if (Math::Distance_3D(local, ore_hot_spot.position) <= 2.f) {
							if (reinterpret_cast<BaseEntity*>(ore_hot_spot.entity)->IsValid()) {
								lol::do_attack(ore_hot_spot, active, false);
							}
						}
					}
				}
			}
			if (vars::misc::auto_farm_tree) {
				if (weaponmelee) {
					f_object tree_entity = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
						xorstr_(""),
						Vector3::Zero(),
						Vector3::Zero(),
						Vector3::Zero(),
						true,
						xorstr_("TreeEntity"));
					if (tree_entity.valid) {
						tree_entity.position = Vector3::Zero();
						f_object tree_marker = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
							xorstr_(""),
							Vector3::Zero(),
							Vector3::Zero(),
							Vector3::Zero(),
							true,
							xorstr_("TreeMarker"));
						if (tree_marker.valid) {
							Vector3 locala = utils::ClosestPoint(LocalPlayer::Entity(), tree_marker.position);
							if (Math::Distance_3D(locala, tree_marker.position) <= 2.f) {
								tree_entity.position = tree_marker.position;
								Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), tree_entity.position);
								if (Math::Distance_3D(local, tree_entity.position) <= 2.f) {
									if (reinterpret_cast<BaseEntity*>(tree_entity.entity)->IsValid()) {
										lol::do_attack(tree_entity, active, false);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void TestFlying() {
	if (!LocalPlayer::Entity()->OnLadder()) {
		flyhackPauseTime = Mathf::Max(0.f, flyhackPauseTime - Time::deltaTime());
		bool inAir = false;
		float radius = reinterpret_cast<float(*)(BasePlayer*)>(vars::stor::gBase + CO::GetRadius)(LocalPlayer::Entity());
		float height = reinterpret_cast<float(*)(BasePlayer*, bool)>(vars::stor::gBase + CO::GetHeight)(LocalPlayer::Entity(), false);
		Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->tick_position() + read(read(LocalPlayer::Entity() + O::BasePlayer::playerModel, uintptr_t) + 0x218, Vector3)) * 0.5f; //internal Vector3 position; || public class PlayerModel : ListComponent<PlayerModel>, IOnParentDestroying 
		Vector3 vector2 = vector + Vector3(0.f, radius - 2.f, 0.f);
		Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
		float radius2 = radius - 0.05f;
		bool a = Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, QueryTriggerInteraction::Ignore);
		inAir = !a;

		if (inAir) {
			bool flag = false;

			Vector3 vector4 = read(read(LocalPlayer::Entity() + O::BasePlayer::playerModel, uintptr_t) + 0x218, Vector3) - LocalPlayer::Entity()->lastSentTick()->tick_position(); //internal Vector3 position; || public class PlayerModel : ListComponent<PlayerModel>, IOnParentDestroying 
			float num3 = Mathf::Abs(vector4.y);
			float num4 = reinterpret_cast<float(*)(Vector3)>(vars::stor::gBase + CO::Magnitude2D)(vector4);
			if (vector4.y >= 0.f) {
				flyhackDistanceVertical += vector4.y;
				flag = true;
			}
			if (num3 < num4) {
				flyhackDistanceHorizontal += num4;
				flag = true;
			}
			if (flag) {
				float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
				if (flyhackDistanceVertical > num6) {
				}
				float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num8 = 5.f + num7;
				if (flyhackDistanceHorizontal > num8) {
				}
			}
		}
		else {
			flyhackDistanceHorizontal = 0.f;
			flyhackDistanceVertical = 0.f;
		}
		float flyhack_forgiveness_interia = 10.0f;
		float flyhack_forgiveness = 1.5f;
		float flyhack_extrusion = 1.85f;
		float num5 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
		float num6 = ((LocalPlayer::Entity()->GetJumpHeight() + num5) * 3);

		VMaxFlyhack = num6;
		if (flyhackDistanceVertical <= (num6)) {
			VFlyhack = flyhackDistanceVertical;
		}
		if (VFlyhack >= VMaxFlyhack)
			VFlyhack = VMaxFlyhack;
		float num7 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
		float num8 = ((5.f + num7) * 3);

		HMaxFlyhack = num8;
		if (flyhackDistanceHorizontal <= (num8)) {
			HFlyhack = flyhackDistanceHorizontal;
		}
		if (HFlyhack >= HMaxFlyhack)
			HFlyhack = HMaxFlyhack;
	}
}
void CheckFlyhack( ) {
	TestFlying();
	float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num6 = LocalPlayer::Entity( )->GetJumpHeight( ) + num5;
	vars::stuff::max_flyhack = num6;
	if (flyhackDistanceVertical <= num6) {
		vars::stuff::flyhack = flyhackDistanceVertical;
	}

	float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num8 = 5.f + num7;
	vars::stuff::max_hor_flyhack = num8;
	if (flyhackDistanceHorizontal <= num8) {
		vars::stuff::hor_flyhack = flyhackDistanceHorizontal;
	}
}
void warningg() {
	float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
	float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
	vars::stuff::max_flyhack = num6;
	if (flyhackDistanceVertical <= num6) {
		vars::stuff::flyhack = flyhackDistanceVertical;
	}

	float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num8 = 5.f + num7;
	vars::stuff::max_hor_flyhack = num8;
	if (flyhackDistanceHorizontal <= num8) {
		vars::stuff::hor_flyhack = flyhackDistanceHorizontal;
	}
	if (vars::misc::flyhack_indicator && (flyhackDistanceVertical > num6)) {
		g_Render->DrawString(xs, ys - 656, ImColor(255, 0, 0), render2::outline | render2::centered_x, pixel_s, 11, xorstr_("WARNING"));

		//Beep(1, 1);

	}
	if (vars::misc::flyhack_indicator && (flyhackDistanceHorizontal > num6)) {
		g_Render->DrawString(xs, ys - 643, ImColor(255,0,0), render2::outline | render2::centered_x, pixel_s, 11, xorstr_("WARNING"));

		//Beep(1, 1);

	}
}

auto* TargetPlayerA = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);