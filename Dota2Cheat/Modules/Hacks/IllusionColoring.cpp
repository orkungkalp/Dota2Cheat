#include "IllusionColoring.h"

bool Hacks::IllusionColoring::ColorIfIllusion(CBaseEntity* ent) {
	if (!Config::IllusionColoring::Enabled)
		return false;

	const char* className = ent->SchemaBinding()->binaryName;
	auto hero = (CDOTABaseNPC_Hero*)ent;
	if (ctx.assignedHero &&
		ctx.assignedHero->GetTeam() != hero->GetTeam() &&
		hero->IsIllusion()
		) {
		auto c = Config::IllusionColoring::Color;
		hero->SetColor(Color(c.x * 255, c.y * 255, c.z * 255));
		return true;
	}

	return false;
}
