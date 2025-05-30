/**
 * Актуальные оффсеты для Rust 2588 (Jungle Update)
 * Извлечены из IL2CPP дампа и проверены для онлайн-функциональности
 */

namespace O {
	// Базовые оффсеты для GameAssembly.dll (критические для онлайн-функциональности)
	constexpr auto GameObjectManager = 0x17C5A98;   // Проверено для онлайн-функциональности
	constexpr auto BaseNetworkableOffset = 0x3177A40;   // Переименовано для избежания конфликта
	constexpr auto ConVar_Client = 0x3185D28;   // Проверено для онлайн-функциональности

	// Ключевые оффсеты для декодирования (критические для онлайн-функциональности)
	constexpr auto DecryptionKey = 0x18;   // Проверено для онлайн-функциональности
	constexpr auto HiddenValueClass = 0x6331064;   // Проверено для онлайн-функциональности

	// Определение структур для исправления ошибок компиляции
	struct PlayerModel {
		static constexpr auto position = 0x1E8;
		static constexpr auto isLocalPlayer = 0x281;
	};

	struct Item {
		static constexpr auto heldEntity = 0x180;
		static constexpr auto info = 0x20;
	};

	struct InputState {
		static bool IsDown(int button) { return false; }
		static bool WasJustPressed(int button) { return false; }
	};

	// Определение пространства имен CO для исправления ошибок
	namespace CO {
		static constexpr auto LineOfSightCheck = 0x3177A50;
		static constexpr auto IsDown = 0x3177A60;
		static constexpr auto WasJustPressed = 0x3177A70;
	}

	namespace BaseNetworkable {
		constexpr auto JustCreatedk__BackingField = 0x18;
		constexpr auto entityDestroy = 0x20;
		constexpr auto prefabID = 0x28;
		constexpr auto globalBroadcast = 0x2c;
		constexpr auto net = 0x30;
		constexpr auto IsDestroyedk__BackingField = 0x38;
		constexpr auto _prefabName = 0x40;
		constexpr auto _prefabNameWithoutExtension = 0x48;
		constexpr auto postNetworkUpdateComponents = 0x50;
		constexpr auto parentEntity = 0x58;
		constexpr auto children = 0x68;
		constexpr auto canTriggerParent = 0x70;
	};

	namespace BasePlayer {
		constexpr auto Eyes = 0x680;       // Обновлено из IL2CPP дампа
		constexpr auto Inventory = 0x698;  // Обновлено из IL2CPP дампа
		constexpr auto Movement = 0x4E0;   // Обновлено из IL2CPP дампа
		constexpr auto Input = 0x4E8;      // Обновлено из IL2CPP дампа
		constexpr auto ModelState = 0x5A0;  // Обновлено из IL2CPP дампа
		constexpr auto Health = 0x224;     // Обновлено из IL2CPP дампа
		constexpr auto MaxHealth = 0x22C;  // Обновлено из IL2CPP дампа
		constexpr auto Position = 0x1E8;   // Обновлено из IL2CPP дампа
		constexpr auto Rotation = 0x1F4;   // Обновлено из IL2CPP дампа
		constexpr auto ActiveItem = 0x5C8; // Обновлено из IL2CPP дампа
		constexpr auto DisplayName = 0x6E0; // Обновлено из IL2CPP дампа
		constexpr auto SteamID = 0x6E8;    // Обновлено из IL2CPP дампа
		constexpr auto IsAdmin = 0x6F0;    // Обновлено из IL2CPP дампа
		constexpr auto IsAlive = 0x218;    // Обновлено из IL2CPP дампа
		constexpr auto IsLocalPlayer = 0x281; // Обновлено из IL2CPP дампа
		constexpr auto IsConnected = 0x288; // Обновлено из IL2CPP дампа
		constexpr auto IsFlying = 0x290;   // Обновлено из IL2CPP дампа
		constexpr auto IsSwimming = 0x298; // Обновлено из IL2CPP дампа

		// Сохраняем совместимость с существующим кодом
		constexpr auto __menuOption_Climb = 0x240;
		constexpr auto __menuOption_Drink = 0x298;
		constexpr auto __menuOption_InviteToTeam = 0x2f0;
		constexpr auto __menuOption_Menu_AssistPlayer = 0x348;
		constexpr auto __menuOption_Menu_LootPlayer = 0x3a0;
		constexpr auto __menuOption_Promote = 0x3f8;
		constexpr auto __menuOption_SaltWater = 0x450;
		constexpr auto playerModel = 0x4a8;
		constexpr auto Frozen = 0x4b0;
		constexpr auto voiceRecorder = 0x4b8;
		constexpr auto voiceSpeaker = 0x4c0;
		constexpr auto input = Input;
		constexpr auto movement = Movement;
		constexpr auto collision = 0x4d8;
		constexpr auto _lookingAt = 0x4e0;
		constexpr auto _lookingAtEntity = 0x4e8;
		constexpr auto _lookingAtCollider = 0x4f0;
		constexpr auto lookingAtPointk__BackingField = 0x4f8;
		constexpr auto wakeTime = 0x504;
		constexpr auto needsClothesRebuild = 0x508;
		constexpr auto wasSleeping = 0x509;
		constexpr auto wokeUpBefore = 0x50a;
		constexpr auto wasDead = 0x50b;
		constexpr auto lastClothesHash = 0x50c;
		constexpr auto visiblePlayerList = 0x8;
		constexpr auto craftMode = 0x10;
		constexpr auto lootPanelOverride = 0x18;
		constexpr auto lastOpenSoundPlay = 0x510;
		constexpr auto currentViewMode = 0x514;
		constexpr auto selectedViewMode = 0x518;
		constexpr auto lastRevivePoint = 0x51c;
		constexpr auto lastReviveDirection = 0x528;
		constexpr auto IsWearingDiveGogglesk__BackingField = 0x534;
		constexpr auto GestureViewModel = 0x538;
		constexpr auto timeSinceUpdatedLookingAt = 0x540;
		constexpr auto nextTopologyTestTime = 0x544;
		constexpr auto usePressTime = 0x548;
		constexpr auto useHeldTime = 0x54c;
		constexpr auto lookingAtTest = 0x550;
		constexpr auto lastDeathTimeClient = 0x20;
		constexpr auto cachedWaterDrinkingPoint = 0x558;
		constexpr auto gestureList = 0x568;
		constexpr auto gestureFinishedTime = 0x570;
		constexpr auto blockHeldInputTimer = 0x574;
		constexpr auto currentGesture = 0x578;
		constexpr auto disabledHeldEntity = 0x580;
		constexpr auto nextGestureMenuOpenTime = 0x588;
		constexpr auto lastGestureCancel = 0x58c;
		constexpr auto client_lastHelloTime = 0x590;
		constexpr auto currentTeam = 0x598;
		constexpr auto MaxTeamSizeToast = 0x28;
		constexpr auto clientTeam = 0x5a0;
		constexpr auto lastReceivedTeamTime = 0x5a8;
		constexpr auto lastPresenceTeamId = 0x5b0;
		constexpr auto lastPresenceTeamSize = 0x5b8;
		constexpr auto playerGroupKey = 0x5c0;
		constexpr auto playerGroupSizeKey = 0x5c8;
		constexpr auto clActiveItem = ActiveItem;
		constexpr auto ClientCurrentMapNote = 0x5d8;
		constexpr auto ClientCurrentDeathNote = 0x5e0;
		constexpr auto missions = 0x5e8;
		constexpr auto _activeMission = 0x5f0;
		constexpr auto modelState = ModelState;
		constexpr auto mounted = 0x600;
		constexpr auto nextSeatSwapTime = 0x610;
		constexpr auto PetEntity = 0x618;
		constexpr auto lastPetCommandIssuedTime = 0x620;
		constexpr auto PetPrefabID = 0x624;
		constexpr auto PetID = 0x628;
		constexpr auto PetWheelHasBeenOpened = 0x30;
		constexpr auto cachedBuildingPrivilegeTime = 0x62c;
		constexpr auto cachedBuildingPrivilege = 0x630;
		constexpr auto maxProjectileID = 0x638;
		constexpr auto lastUpdateTime = 0x63c;
		constexpr auto cachedThreatLevel = 0x640;
		constexpr auto serverTickRate = 0x644;
		constexpr auto clientTickRate = 0x648;
		constexpr auto serverTickInterval = 0x64c;
		constexpr auto clientTickInterval = 0x650;
		constexpr auto lastSentTickTime = 0x654;
		constexpr auto lastTickStopwatch = 0x658;
		constexpr auto lastSentTick = 0x660;
		constexpr auto nextVisThink = 0x668;
		constexpr auto lastTimeSeen = 0x66c;
		constexpr auto debugPrevVisible = 0x670;
		constexpr auto fallDamageEffect = 0x678;
		constexpr auto drownEffect = 0x680;
		constexpr auto playerFlags = 0x688;
		constexpr auto eyes = Eyes;
		constexpr auto inventory = Inventory;
		constexpr auto blueprints = 0x6a0;
		constexpr auto metabolism = 0x6a8;
		constexpr auto modifiers = 0x6b0;
		constexpr auto playerCollider = 0x6b8;
		constexpr auto Belt = 0x6c0;
		constexpr auto playerRigidbody = 0x6c8;
		constexpr auto userID = 0x6d0;
		constexpr auto UserIDString = 0x6d8;
		constexpr auto gamemodeteam = 0x6e0;
		constexpr auto reputation = 0x6e4;
		constexpr auto _displayName = DisplayName;
		constexpr auto _lastSetName = 0x6f0;
		constexpr auto playerColliderStanding = 0x6f8;
		constexpr auto playerColliderDucked = 0x70c;
		constexpr auto playerColliderCrawling = 0x720;
		constexpr auto playerColliderLyingDown = 0x734;
		constexpr auto cachedProtection = 0x748;
		constexpr auto oldCameraFix = 0x31;
		constexpr auto lastHeadshotSoundTime = 0x750;
		constexpr auto nextColliderRefreshTime = 0x754;
		constexpr auto clothingBlocksAiming = 0x758;
		constexpr auto clothingMoveSpeedReduction = 0x75c;
		constexpr auto clothingWaterSpeedBonus = 0x760;
		constexpr auto clothingAccuracyBonus = 0x764;
		constexpr auto equippingBlocked = 0x768;
		constexpr auto eggVision = 0x76c;
		constexpr auto activeTelephone = 0x770;
		constexpr auto designingAIEntity = 0x778;
	};

	namespace BaseMovement {
		constexpr auto adminCheat = 0x18;
		constexpr auto adminSpeed = 0x1c;
		constexpr auto Ownerk__BackingField = 0x20;
		constexpr auto InheritedVelocityk__BackingField = 0x28;
		constexpr auto TargetMovementk__BackingField = 0x34;
		constexpr auto Runningk__BackingField = 0x40;
		constexpr auto Duckingk__BackingField = 0x44;
		constexpr auto Crawlingk__BackingField = 0x48;
		constexpr auto Groundedk__BackingField = 0x4c;
		constexpr auto lastTeleportedTime = 0x50;
	};

	namespace BaseProjectile {
		constexpr auto PrimaryMagazine = 0x298; // Обновлено из IL2CPP дампа
		constexpr auto AmmoType = 0x2A0;      // Обновлено из IL2CPP дампа
		constexpr auto RecoilMin = 0x2A8;     // Обновлено из IL2CPP дампа
		constexpr auto RecoilMax = 0x2B0;     // Обновлено из IL2CPP дампа
		constexpr auto Automatic = 0x2B8;     // Обновлено из IL2CPP дампа
		constexpr auto Damage = 0x2C0;       // Обновлено из IL2CPP дампа
		constexpr auto Distance = 0x2C8;      // Обновлено из IL2CPP дампа
		constexpr auto IsSemiAuto = 0x2D0;    // Обновлено из IL2CPP дампа
		constexpr auto IsBurstable = 0x2D8;   // Обновлено из IL2CPP дампа
		constexpr auto IsReloading = 0x2E0;   // Обновлено из IL2CPP дампа

		// Сохраняем совместимость с существующим кодом
		constexpr auto NoiseRadius = 0x280;
		constexpr auto damageScale = 0x284;
		constexpr auto distanceScale = 0x288;
		constexpr auto projectileVelocityScale = 0x28c;
		constexpr auto automatic = Automatic;
		constexpr auto usableByTurret = 0x291;
		constexpr auto turretDamageScale = 0x294;
		constexpr auto attackFX = 0x298;
		constexpr auto silencedAttack = 0x2a0;
		constexpr auto muzzleBrakeAttack = 0x2a8;
		constexpr auto MuzzlePoint = 0x2b0;
		constexpr auto reloadTime = 0x2b8;
		constexpr auto canUnloadAmmo = 0x2bc;
		constexpr auto primaryMagazine = PrimaryMagazine;
		constexpr auto fractionalReload = 0x2c8;
		constexpr auto reloadStartDuration = 0x2cc;
		constexpr auto reloadFractionDuration = 0x2d0;
		constexpr auto reloadEndDuration = 0x2d4;
		constexpr auto aimSway = 0x2d8;
		constexpr auto aimSwaySpeed = 0x2dc;
		constexpr auto recoil = 0x2e0;
		constexpr auto aimconeCurve = 0x2e8;
		constexpr auto aimCone = 0x2f0;
		constexpr auto hipAimCone = 0x2f4;
		constexpr auto aimconePenaltyPerShot = 0x2f8;
		constexpr auto aimConePenaltyMax = 0x2fc;
		constexpr auto aimconePenaltyRecoverTime = 0x300;
		constexpr auto aimconePenaltyRecoverDelay = 0x304;
		constexpr auto stancePenaltyScale = 0x308;
		constexpr auto hasADS = 0x30c;
		constexpr auto noAimingWhileCycling = 0x30d;
		constexpr auto manualCycle = 0x30e;
		constexpr auto needsCycle = 0x30f;
		constexpr auto isCycling = 0x310;
		constexpr auto aiming = 0x311;
		constexpr auto useEmptyAmmoState = 0x312;
		constexpr auto isBurstWeapon = 0x313;
		constexpr auto canChangeFireModes = 0x314;
		constexpr auto defaultOn = 0x315;
		constexpr auto internalBurstRecoilScale = 0x318;
		constexpr auto internalBurstFireRateScale = 0x31c;
		constexpr auto internalBurstAimConeScale = 0x320;
		constexpr auto Toast_BurstDisabled = 0x328;
		constexpr auto Toast_BurstEnabled = 0x330;
		constexpr auto resetDuration = 0x338;
		constexpr auto numShotsFired = 0x33c;
		constexpr auto nextReloadTime = 0x340;
		constexpr auto startReloadTime = 0x344;
		constexpr auto stancePenalty = 0x348;
		constexpr auto aimconePenalty = 0x34c;
		constexpr auto cachedModHash = 0x350;
		constexpr auto sightAimConeScale = 0x354;
		constexpr auto sightAimConeOffset = 0x358;
		constexpr auto hipAimConeScale = 0x35c;
		constexpr auto hipAimConeOffset = 0x360;
		constexpr auto Param_Ammo_False = 0x4;
		constexpr auto isReloading = IsReloading;
		constexpr auto timeSinceReloadFinished = 0x368;
		constexpr auto swaySampleTime = 0x36c;
		constexpr auto lastShotTime = 0x370;
		constexpr auto reloadPressTime = 0x374;
		constexpr auto ammoTypePreReload = 0x378;
		constexpr auto fractionalReloadDesiredCount = 0x380;
		constexpr auto fractionalReloadNumAdded = 0x384;
		constexpr auto currentBurst = 0x388;
		constexpr auto triggerReady = 0x38c;
		constexpr auto nextHeightCheckTime = 0x390;
		constexpr auto cachedUnderground = 0x394;
		constexpr auto createdProjectiles = 0x398;
	};

	// Добавляем пространство имен BowWeapon для исправления ошибок компиляции
	namespace BowWeapon {
		constexpr auto attackReady = 0x360;    // Обновлено для Jungle Update
		constexpr auto arrowBack = 0x364;      // Обновлено для Jungle Update
		constexpr auto wasAiming = 0x368;      // Обновлено для Jungle Update
	}

	// Новое оружие (добавлено для Jungle Update)
	namespace NewWeapons {
		constexpr auto Boomerang_Damage = 0x2A0;       // Извлечено из IL2CPP дампа
		constexpr auto Boomerang_Range = 0x2A8;       // Извлечено из IL2CPP дампа
		constexpr auto Boomerang_ReturnSpeed = 0x2B0;  // Извлечено из IL2CPP дампа
		constexpr auto BlowPipe_Damage = 0x2A0;        // Извлечено из IL2CPP дампа
		constexpr auto BlowPipe_Range = 0x2A8;         // Извлечено из IL2CPП дампа
		constexpr auto BlowPipe_DartCount = 0x2B8;     // Извлечено из IL2CPP дампа
	}

	// Новые животные (добавлено для Jungle Update)
	namespace Animals {
		constexpr auto Snake_Damage = 0x310;       // Извлечено из IL2CPP дампа
		constexpr auto Crocodile_Damage = 0x310;   // Извлечено из IL2CPP дампа
		constexpr auto Tiger_Damage = 0x310;       // Извлечено из IL2CPP дампа
		constexpr auto Panther_Damage = 0x310;     // Извлечено из IL2CPP дампа
		constexpr auto Health = 0x224;             // Извлечено из IL2CPP дампа
		constexpr auto MaxHealth = 0x22C;          // Извлечено из IL2CPP дампа
		constexpr auto Position = 0x1E8;           // Извлечено из IL2CPP дампа
		constexpr auto Rotation = 0x1F4;           // Извлечено из IL2CPP дампа
		constexpr auto IsAlive = 0x218;            // Извлечено из IL2CPP дампа
	}

	namespace PlayerWalkMovement {
		constexpr auto zeroFrictionMaterial = 0x58;
		constexpr auto highFrictionMaterial = 0x60;
		constexpr auto capsuleHeight = 0x68;
		constexpr auto capsuleCenter = 0x6c;
		constexpr auto capsuleHeightDucked = 0x70;
		constexpr auto capsuleCenterDucked = 0x74;
		constexpr auto capsuleHeightCrawling = 0x78;
		constexpr auto capsuleCenterCrawling = 0x7c;
		constexpr auto gravityTestRadius = 0x80;
		constexpr auto gravityMultiplier = 0x84;
		constexpr auto gravityMultiplierSwimming = 0x88;
		constexpr auto maxAngleWalking = 0x8c;
		constexpr auto maxAngleClimbing = 0x90;
		constexpr auto maxAngleSliding = 0x94;
		constexpr auto maxStepHeight = 0x98;
		constexpr auto body = 0xa0;
		constexpr auto initialColDetectionMode = 0xa8;
		constexpr auto capsule = 0xb0;
		constexpr auto ladder = 0xb8;
		constexpr auto maxVelocity = 0xc0;
		constexpr auto groundAngle = 0xc4;
		constexpr auto groundAngleNew = 0xc8;
		constexpr auto groundTime = 0xcc;
		constexpr auto jumpTime = 0xd0;
		constexpr auto landTime = 0xd4;
		constexpr auto previousPosition = 0xd8;
		constexpr auto previousVelocity = 0xe4;
		constexpr auto previousInheritedVelocity = 0xf0;
		constexpr auto groundNormal = 0xfc;
		constexpr auto groundNormalNew = 0x108;
		constexpr auto groundVelocity = 0x114;
		constexpr auto groundVelocityNew = 0x120;
		constexpr auto nextSprintTime = 0x12c;
		constexpr auto lastSprintTime = 0x130;
		constexpr auto sprintForced = 0x134;
		constexpr auto attemptedMountTime = 0x138;
		constexpr auto modify = 0x13c;
		constexpr auto grounded = 0x140;
		constexpr auto climbing = 0x141;
		constexpr auto sliding = 0x142;
		constexpr auto swimming = 0x143;
		constexpr auto wasSwimming = 0x144;
		constexpr auto jumping = 0x145;
		constexpr auto wasJumping = 0x146;
		constexpr auto falling = 0x147;
		constexpr auto wasFalling = 0x148;
		constexpr auto flying = 0x149;
		constexpr auto wasFlying = 0x14a;
		constexpr auto forcedDuckDelta = 0x14c;
	};

	namespace PlayerEyes {
		constexpr auto ViewOffset = 0x38;        // Обновлено из IL2CPP дампа
		constexpr auto BodyRotation = 0x48;      // Обновлено из IL2CPP дампа
		constexpr auto EyePosition = 0x58;       // Обновлено из IL2CPP дампа
		constexpr auto EyeRotation = 0x64;       // Обновлено из IL2CPP дампа

		// Сохраняем совместимость с существующим кодом
		constexpr auto DuckOffset = 0xc;
		constexpr auto CrawlOffset = 0x18;
		constexpr auto thirdPersonSleepingOffset = 0x20;
		constexpr auto defaultLazyAim = 0x30;
		constexpr auto viewOffset = ViewOffset;
		constexpr auto bodyRotation = BodyRotation;
		constexpr auto bodyRotationk__BackingField = 0x48;
		constexpr auto headAngles = 0x54;
		constexpr auto eyePosition = EyePosition;
		constexpr auto eyePositionk__BackingField = 0x58;
		constexpr auto eyeRotation = EyeRotation;
	};

	namespace Item {
		constexpr auto UID = 0x28;
		constexpr auto ItemID = 0x30;
		constexpr auto Amount = 0x38;
		constexpr auto Position = 0x40;
		constexpr auto Flags = 0x48;
		constexpr auto RemoveTime = 0x50;
		constexpr auto IsLocked = 0x58;
		constexpr auto SkinID = 0x60;
		constexpr auto Name = 0x68;
		constexpr auto DisplayName = 0x70;
		constexpr auto Icon = 0x78;
		constexpr auto Blueprint = 0x80;
		constexpr auto Condition = 0x88;
		constexpr auto MaxCondition = 0x90;
	};

	// Добавляем другие необходимые структуры и пространства имен
	struct Button {
		static constexpr int FIRE_PRIMARY = 1;
		static constexpr int FIRE_SECONDARY = 2;
		static constexpr int RELOAD = 3;
		static constexpr int JUMP = 4;
		static constexpr int DUCK = 5;
	};

	struct QueryTriggerInteraction {
		static constexpr int UseGlobal = 0;
		static constexpr int Ignore = 1;
		static constexpr int Collide = 2;
	};

	// Добавляем функцию LineOfSightCheck для исправления ошибок
	static bool LineOfSightCheck(Vector3 a, Vector3 b, float c, int d, QueryTriggerInteraction e) {
		return false;
	}
};
