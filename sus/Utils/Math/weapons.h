struct Ammo {
	int id[2];
	float speed;
};
struct Weapon {
	int id;
	const char* name;
	Ammo ammo[4];
	int category; //-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
};
Weapon info[]{
Weapon{1588298435, xorstr_("Bolt Action Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375.f}, Ammo{{1712070256} /*HV 5.56*/, 788 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 394}}, 2 },
Weapon{-778367295, xorstr_("L96 Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 625.f}, Ammo{{1712070256} /*HV 5.56*/, 1350 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 675}}, 2 },

Weapon{-1367281941, xorstr_("Waterpipe Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, 2 },
Weapon{-765183617, xorstr_("Double Barrel Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, 2 },
Weapon{-41440462, xorstr_("Spas-12 Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, 2 },
Weapon{795371088, xorstr_("Pump Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, 2 },
Weapon{-75944661, xorstr_("Eoka Pistol"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, -1 },

Weapon{1965232394, xorstr_("Crossbow"), { Ammo{{-1234735557}/*normal arrow*/, 78.f}, Ammo{{14241751} /*fire arrow*/, 61.f}, Ammo{{215754713} /*bone arrow*/, 66.f}, Ammo{{-1023065463} /*HV arrow*/, 120.f}}, 2 },
Weapon{884424049, xorstr_("Compound Bow"), { Ammo{{-1234735557}/*normal arrow*/, 50.f}, Ammo{{14241751} /*fire arrow*/, 40}, Ammo{{215754713} /*bone arrow*/, 45}, Ammo{{-1023065463} /*HV arrow*/, 78.8f}}, 2 }, //TODO on zoom velocity x2
Weapon{1443579727, xorstr_("Hunting Bow"), { Ammo{{-1234735557}/*normal arrow*/, 50.f}, Ammo{{14241751} /*fire arrow*/, 40}, Ammo{{215754713} /*bone arrow*/, 45}, Ammo{{-1023065463} /*HV arrow*/, 80} }, -2 },

Weapon{1318558775, xorstr_("MP5A4"), { Ammo{{785728077}/*normal pistol*/, 190.f}, Ammo{{-1691396643} /*HV pistol*/, 290.f}, Ammo{{51984655} /*inc pistol*/, 145.f}}, 3 },
Weapon{1796682209, xorstr_("Custom SMG"), { Ammo{{785728077}/*normal pistol*/, 205.f}, Ammo{{-1691396643} /*HV pistol*/, 300.f}, Ammo{{51984655} /*inc pistol*/, 145.f}}, 3 },
Weapon{649912614, xorstr_("Revolver"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{818877484, xorstr_("Semi-Automatic Pistol"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{-852563019, xorstr_("M92 Pistol"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{1373971859, xorstr_("Python Revolver"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol 225*/, 225}}, 2 },
Weapon{-1758372725, xorstr_("Thompson"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 3 },

Weapon{-1812555177, xorstr_("LR-300 Assault Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 3 },
Weapon{-904863145, xorstr_("Semi-Automatic Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 2 },
Weapon{1545779598, xorstr_("Assault Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 3 },
Weapon{-1335497659, xorstr_("Assault Rifle Ice"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 3 },
Weapon{-2069578888, xorstr_("M249"), { Ammo{{-1211166256}/*normal 5.56*/, 375.f}, Ammo{{1712070256} /*HV 5.56*/, 585 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 293}}, 3 },
Weapon{-1214542497, xorstr_("HMLMG"), { Ammo{{-1211166256}/*normal 5.56*/, 375.f}, Ammo{{1712070256} /*HV 5.56*/, 585 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 293}}, 3 },
Weapon{28201841, xorstr_("M39 Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 469}, Ammo{{1712070256} /*HV 5.56*/, 563 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 281}}, 2 },

Weapon{1090916276, xorstr_("Pitchfork"), {Ammo{{0}, 25}}, 1 },
Weapon{1540934679, xorstr_("Wooden Spear"), {Ammo{{0}, 25}}, 1 },
Weapon{1814288539, xorstr_("Bone Knife"), {Ammo{{0}, 20}}, 1 },
Weapon{-363689972, xorstr_("Snowball"), {Ammo{{0}, 20}}, 1 },
Weapon{1789825282, xorstr_("Candy Cane Club"), {Ammo{{0}, 20}}, 1 },
Weapon{-1137865085, xorstr_("Machete"), {Ammo{{0}, 20}}, 1 },
Weapon{1711033574, xorstr_("Bone Club"), {Ammo{{0}, 20}}, 1 },
Weapon{-1966748496, xorstr_("Mace"), {Ammo{{0}, 18}}, 1 },
Weapon{-194509282, xorstr_("Butcher Knife"), {Ammo{{0}, 20}}, 1 },
Weapon{1326180354, xorstr_("Salvaged Sword"), {Ammo{{0}, 20}}, 1 },
Weapon{-1469578201, xorstr_("Longsword"), {Ammo{{0}, 18}}, 1 },
Weapon{-1978999529, xorstr_("Salvaged Cleaver"), {Ammo{{0}, 18}}, 1 },
Weapon{1602646136, xorstr_("Stone Spear"), {Ammo{{0}, 30}}, 1 },
Weapon{2040726127, xorstr_("Combat Knife"), {Ammo{{0}, 30}}, 1 },
Weapon{963906841, xorstr_("Rock"), {Ammo{{0}, 18}}, 1 },

Weapon{1953903201, xorstr_("Nailgun"), { Ammo{{-2097376851}/*nails*/, 50}}, 2 },
Weapon{-1123473824, xorstr_("Multiple Grenade Launcher"), { Ammo{{915408809, 349762871}/*smoke, exp*/, 100}, Ammo{{1055319033}, 225}/*shotgun*/}, 2 },
Weapon{442886268, xorstr_("Rocket Launcher"), 0, 69 },
Weapon{-1215753368, xorstr_("Flame Thrower"), 0, 0 },
Weapon{200773292, xorstr_("Hammer"), {0}, -3 }
};