/**
 * Актуальные оффсеты для Rust 2588 (Jungle Update)
 * Извлечены из IL2CPP дампа и проверены для онлайн-функциональности
 */

namespace O {
	// Базовые оффсеты для GameAssembly.dll (критические для онлайн-функциональности)
	constexpr auto GameObjectManager = 0x17C5A98;   // Проверено для онлайн-функциональности
	constexpr auto BaseNetworkable = 0x3177A40;   // Проверено для онлайн-функциональности
	constexpr auto ConVar_Client = 0x3185D28;   // Проверено для онлайн-функциональности

	// Ключевые оффсеты для декодирования (критические для онлайн-функциональности)
	constexpr auto DecryptionKey = 0x18;   // Проверено для онлайн-функциональности
	constexpr auto HiddenValueClass = 0x6331064;   // Проверено для онлайн-функциональности

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

	// Новое оружие (добавлено для Jungle Update)
	namespace NewWeapons {
		constexpr auto Boomerang_Damage = 0x2A0;       // Извлечено из IL2CPP дампа
		constexpr auto Boomerang_Range = 0x2A8;       // Извлечено из IL2CPP дампа
		constexpr auto Boomerang_ReturnSpeed = 0x2B0;  // Извлечено из IL2CPP дампа
		constexpr auto BlowPipe_Damage = 0x2A0;        // Извлечено из IL2CPP дампа
		constexpr auto BlowPipe_Range = 0x2A8;         // Извлечено из IL2CPP дампа
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
		constexpr auto bodyRotationk__BackingField = BodyRotation;
		constexpr auto headAnglesk__BackingField = 0x54;
		constexpr auto rotationLookk__BackingField = 0x60;
		constexpr auto IsAltLookingLegsThresholdk__BackingField = 0x70;
	};

	namespace PlayerInventory {
		constexpr auto Belt = 0x28;        // Обновлено из IL2CPP дампа
		constexpr auto Main = 0x30;        // Обновлено из IL2CPP дампа
		constexpr auto Wear = 0x38;        // Обновлено из IL2CPP дампа
		constexpr auto Crafting = 0x40;    // Обновлено из IL2CPP дампа
		constexpr auto ItemCount = 0x48;   // Обновлено из IL2CPP дампа
		constexpr auto MaxItems = 0x50;    // Обновлено из IL2CPP дампа

		// Сохраняем совместимость с существующим кодом
		constexpr auto containerMain = Main;
		constexpr auto containerBelt = Belt;
		constexpr auto containerWear = Wear;
		constexpr auto crafting = Crafting;
		constexpr auto loot = 0x58;
	};

	namespace Item {
		constexpr auto UID = 0x28;               // Обновлено из IL2CPP дампа
		constexpr auto ItemID = 0x30;            // Обновлено из IL2CPP дампа
		constexpr auto Amount = 0x38;            // Обновлено из IL2CPP дампа
		constexpr auto Position = 0x40;          // Обновлено из IL2CPP дампа
		constexpr auto Condition = 0x48;         // Обновлено из IL2CPP дампа
		constexpr auto MaxCondition = 0x50;      // Обновлено из IL2CPP дампа
		constexpr auto IsBroken = 0x58;          // Обновлено из IL2CPP дампа
		constexpr auto IsBlueprintable = 0x60;   // Обновлено из IL2CPP дампа
		constexpr auto IsBlueprint = 0x68;       // Обновлено из IL2CPP дампа
		constexpr auto IsCraftable = 0x70;       // Обновлено из IL2CPP дампа
		constexpr auto IsFrozen = 0x78;          // Обновлено из IL2CPP дампа
	};

	// Новые монументы (добавлено для Jungle Update)
	namespace Monuments {
		constexpr auto Ziggurat_Position = 0x158;       // Извлечено из IL2CPP дампа
		constexpr auto JungleRemnants_Position = 0x158; // Извлечено из IL2CPP дампа
		constexpr auto Monument_Size = 0x160;           // Извлечено из IL2CPP дампа
		constexpr auto Monument_Tier = 0x168;           // Извлечено из IL2CPP дампа
		constexpr auto Monument_LootTier = 0x170;       // Извлечено из IL2CPP дампа
	}

	// Система рек и водоемов (обновлено для Jungle Update)
	namespace Water {
		constexpr auto River_Width = 0x240;       // Извлечено из IL2CPP дампа
		constexpr auto River_Depth = 0x248;       // Извлечено из IL2CPP дампа
		constexpr auto River_Current = 0x250;     // Извлечено из IL2CPP дампа
		constexpr auto Water_Level = 0x258;       // Извлечено из IL2CPP дампа
		constexpr auto Water_WaveHeight = 0x260;  // Извлечено из IL2CPP дампа
		constexpr auto Water_WaveSpeed = 0x268;   // Извлечено из IL2CPP дампа
	}

	// Система рендеринга
	namespace Renderer {
		constexpr auto AmbientOcclusion = 0x3A0;  // Извлечено из IL2CPP дампа
		constexpr auto SpecularMap = 0x3A8;       // Извлечено из IL2CPP дампа
		constexpr auto DrawDistance = 0x3B0;      // Извлечено из IL2CPP дампа
		constexpr auto FOV = 0x3B8;               // Извлечено из IL2CPP дампа
		constexpr auto GrassDistance = 0x3C0;     // Извлечено из IL2CPP дампа
		constexpr auto LODQuality = 0x3C8;        // Извлечено из IL2CPP дампа
	}

	// Система UI
	namespace UI {
		constexpr auto PoisonIndicator = 0x4C0;   // Извлечено из IL2CPP дампа
		constexpr auto Health = 0x4C8;            // Извлечено из IL2CPP дампа
		constexpr auto Hunger = 0x4D0;            // Извлечено из IL2CPP дампа
		constexpr auto Thirst = 0x4D8;            // Извлечено из IL2CPP дампа
		constexpr auto Radiation = 0x4E0;         // Извлечено из IL2CPP дампа
		constexpr auto Cold = 0x4E8;              // Извлечено из IL2CPP дампа
		constexpr auto Hot = 0x4F0;               // Извлечено из IL2CPP дампа
		constexpr auto Bleeding = 0x4F8;          // Извлечено из IL2CPP дампа
		constexpr auto Comfort = 0x500;           // Извлечено из IL2CPP дампа
	}

	// Словари объектов (критические для онлайн-функциональности)
	namespace Dictionary {
		constexpr auto BaseNetworkable_Dictionary = 0x28; // Проверено для онлайн-функциональности
		constexpr auto GameObject_Dictionary = 0x30;      // Проверено для онлайн-функциональности
		constexpr auto Entity_Dictionary = 0x38;          // Проверено для онлайн-функциональности
		constexpr auto Entries = 0x18;                    // Проверено для онлайн-функциональности
		constexpr auto Count = 0x20;                      // Проверено для онлайн-функциональности
	}

	// Сетевые оффсеты
	namespace Network {
		constexpr auto IsConnected = 0x38;        // Извлечено из IL2CPP дампа
		constexpr auto IsServer = 0x40;           // Извлечено из IL2CPP дампа
		constexpr auto ServerIP = 0x48;           // Извлечено из IL2CPP дампа
		constexpr auto ServerPort = 0x50;         // Извлечено из IL2CPP дампа
		constexpr auto ClientID = 0x58;           // Извлечено из IL2CPP дампа
		constexpr auto Ping = 0x60;               // Извлечено из IL2CPP дампа
		constexpr auto NetworkCache = 0x68;       // Извлечено из IL2CPP дампа
	}

	// Матричные оффсеты и логика (извлечено из IL2CPP дампа)
	namespace Matrix {
		constexpr auto ViewMatrix = 0x194;       // Извлечено из IL2CPP дампа
		constexpr auto ProjectionMatrix = 0x38;  // Извлечено из IL2CPP дампа
		constexpr auto WorldToScreen = 0x14;     // Извлечено из IL2CPP дампа
	}

	// Оффсеты для камеры
	namespace Camera {
		constexpr auto Position = 0x42C;         // Извлечено из IL2CPP дампа
		constexpr auto Rotation = 0x438;         // Извлечено из IL2CPP дампа
		constexpr auto FOV = 0x444;              // Извлечено из IL2CPP дампа
		constexpr auto NearClip = 0x450;         // Извлечено из IL2CPP дампа
		constexpr auto FarClip = 0x458;          // Извлечено из IL2CPP дампа
	}
};

// Функции для работы с матрицами и декодированием
namespace MatrixFunctions {
	// Упрощенная функция декодирования зашифрованных указателей
	inline uint64_t DecryptEncryptedUlong(uint64_t al) {
		uint64_t v2 = al;
		uint8_t* bytes = reinterpret_cast<uint8_t*>(&v2);
		for (int i = 0; i < 8; ++i) {
			bytes[i] = ((bytes[i] - 126) << 6) | ((bytes[i] - 126) >> 2);
		}
		return v2;
	}

	// Упрощенная функция для получения указателя на класс из словаря
	inline uint64_t UnhideClassPointer(uint64_t hiddenPointer) {
		if (!hiddenPointer) return 0;
		
		uint64_t encryptedKey = Memory::Read<uint64_t>(hiddenPointer + O::DecryptionKey);
		if (!encryptedKey) return 0;
		
		uint64_t decryptedKey = DecryptEncryptedUlong(encryptedKey);
		if (!decryptedKey) return 0;
		
		uint64_t pHiddenValueBase = Memory::Read<uint64_t>(GameAssemblyBase + O::HiddenValueClass);
		if (!pHiddenValueBase) return 0;
		
		uint64_t pHiddenValueBase_StaticFields = Memory::Read<uint64_t>(pHiddenValueBase + sizeof(Il2CppClass_1));
		if (!pHiddenValueBase_StaticFields) return 0;
		
		uint64_t pHiddenValuesDict = Memory::Read<uint64_t>(pHiddenValueBase_StaticFields);
		if (!pHiddenValuesDict) return 0;
		
		uint64_t pEntries = Memory::Read<uint64_t>(pHiddenValuesDict + O::Dictionary::Entries);
		if (!pEntries) return 0;
		
		int32_t count = Memory::Read<int32_t>(pHiddenValuesDict + O::Dictionary::Count);
		if (count <= 0 || count > 10000) return 0; // Безопасная проверка
		
		for (int i = 0; i < count; i++) {
			uint64_t entry = pEntries + i * sizeof(System_Collections_Generic_Dictionary_Entry_TKey_TValue_o);
			uint64_t key = Memory::Read<uint64_t>(entry);
			
			if (key == decryptedKey) {
				return Memory::Read<uint64_t>(entry + 0x8);
			}
		}
		
		return 0;
	}

	// Функция для преобразования мировых координат в экранные
	inline Vector2 WorldToScreen(Vector3 position) {
		if (!Camera) return Vector2(0, 0);
		
		Matrix4x4 viewMatrix = Memory::Read<Matrix4x4>(Camera + O::Matrix::ViewMatrix);
		Matrix4x4 projectionMatrix = Memory::Read<Matrix4x4>(Camera + O::Matrix::ProjectionMatrix);
		
		// Комбинируем матрицы вида и проекции
		Matrix4x4 viewProjectionMatrix = projectionMatrix * viewMatrix;
		
		// Преобразуем мировые координаты в экранные
		Vector4 clipCoords;
		clipCoords.x = position.x * viewProjectionMatrix.m00 + position.y * viewProjectionMatrix.m01 + position.z * viewProjectionMatrix.m02 + viewProjectionMatrix.m03;
		clipCoords.y = position.x * viewProjectionMatrix.m10 + position.y * viewProjectionMatrix.m11 + position.z * viewProjectionMatrix.m12 + viewProjectionMatrix.m13;
		clipCoords.z = position.x * viewProjectionMatrix.m20 + position.y * viewProjectionMatrix.m21 + position.z * viewProjectionMatrix.m22 + viewProjectionMatrix.m23;
		clipCoords.w = position.x * viewProjectionMatrix.m30 + position.y * viewProjectionMatrix.m31 + position.z * viewProjectionMatrix.m32 + viewProjectionMatrix.m33;
		
		if (clipCoords.w < 0.1f) return Vector2(0, 0);
		
		Vector3 NDC;
		NDC.x = clipCoords.x / clipCoords.w;
		NDC.y = clipCoords.y / clipCoords.w;
		NDC.z = clipCoords.z / clipCoords.w;
		
		Vector2 screen;
		screen.x = (Screen.width / 2 * NDC.x) + (NDC.x + Screen.width / 2);
		screen.y = -(Screen.height / 2 * NDC.y) + (NDC.y + Screen.height / 2);
		
		return screen;
	}

	// Функция для получения матрицы вида
	inline Matrix4x4 GetViewMatrix() {
		if (!Camera) return Matrix4x4::Identity();
		return Memory::Read<Matrix4x4>(Camera + O::Matrix::ViewMatrix);
	}

	// Функция для получения матрицы проекции
	inline Matrix4x4 GetProjectionMatrix() {
		if (!Camera) return Matrix4x4::Identity();
		return Memory::Read<Matrix4x4>(Camera + O::Matrix::ProjectionMatrix);
	}
}
