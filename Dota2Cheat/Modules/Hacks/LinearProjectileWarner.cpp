#include "LinearProjectileWarner.h"


// Draws a dashed red line from begin to end
// Returns the wrapper for the created particle

ParticleWrapper Hacks::LinearProjectileWarner::DrawTrajectory(Vector begin, Vector end) {
	auto pw = GameSystems::ParticleManager->CreateParticle(
		"particles/ui_mouseactions/range_finder_tower_line.vpcf",
		PATTACH_WORLDORIGIN,
		nullptr
	);
	Vector boolCp{ 1, 0, 0 };
	pw.particle
		->SetControlPoint(2, &begin)
		->SetControlPoint(6, &boolCp)
		->SetControlPoint(7, &end);
	return pw;
}

void Hacks::LinearProjectileWarner::DrawIfTrajectoryModifier(CDOTAModifier* modifier) {
	if (!Config::WarnLinearProjectiles)
		return;

	auto owner = modifier->GetOwner();
	if (AbilityTrajectories.count(modifier->GetName()) &&
		!EntityTrajectories.count(modifier)) {
		auto trajectoryInfo = AbilityTrajectories[modifier->GetName()];
		int offset = 0;
		offset = trajectoryInfo.isAbilitySlot
			? offset = owner->GetAbilities()[trajectoryInfo.value]->GetEffectiveCastRange()
			: offset = trajectoryInfo.value;

		EntityTrajectories[modifier] = EntTrajectoryInfo{
			.offset = offset,
			.particleWrap = DrawTrajectory(
				owner->GetPos(),
				owner->GetForwardVector(offset))
		};
	}
}

void Hacks::LinearProjectileWarner::RemoveParticleIfTrajectoryModifier(CDOTAModifier* modifier) {
	if (EntityTrajectories.count(modifier)) {
		GameSystems::ParticleManager->DestroyParticle(EntityTrajectories[modifier].particleWrap);
		EntityTrajectories.erase(modifier);
	}
}

void Hacks::LinearProjectileWarner::FrameBasedLogic() {
	for (auto& [modifier, info] : EntityTrajectories) {
		auto owner = modifier->GetOwner();
		auto forwardVec = modifier->GetOwner()->GetForwardVector(info.offset);
		info.particleWrap.particle->SetControlPoint(7, &forwardVec);
	}
}

void Hacks::LinearProjectileWarner::ProcessLinearProjectileMsg(NetMessageHandle_t* msgHandle, google::protobuf::Message* msg) {
	if (msgHandle->messageID == 471) {
		auto linProjMsg = reinterpret_cast<CDOTAUserMsg_CreateLinearProjectile*>(msg);
		auto& newProj =
			linearProjectiles[linProjMsg->handle()] =
			LinearProjectile{
			.source = Interfaces::EntitySystem->GetEntity(linProjMsg->entindex()),
			.handle = linProjMsg->handle(),
			.distance = linProjMsg->distance(),
			.velocity = Vector2D(linProjMsg->velocity().x(), linProjMsg->velocity().y()),
			.acceleration = Vector2D(linProjMsg->acceleration().x(), linProjMsg->acceleration().y()),
			.origin = Vector(linProjMsg->origin().x(), linProjMsg->origin().y(), linProjMsg->origin().z())
		};

		if (
			Config::WarnLinearProjectiles &&
			(!newProj.source || newProj.source->GetTeam() != ctx.assignedHero->GetTeam())
			) {

			auto ratio = newProj.distance / newProj.velocity.Length();
			auto endPoint = newProj.origin;
			endPoint.x += (newProj.velocity * ratio).x;
			endPoint.y += (newProj.velocity * ratio).y;
			TrackedProjectiles[newProj.handle] = DrawTrajectory(newProj.origin, endPoint);
		}
	}
	else if (msgHandle->messageID == 472) {
		auto linProjMsg = reinterpret_cast<CDOTAUserMsg_DestroyLinearProjectile*>(msg);
		auto handle = linProjMsg->handle();
		linearProjectiles.erase(handle);
		if (TrackedProjectiles.count(handle)) {
			GameSystems::ParticleManager->DestroyParticle(TrackedProjectiles[handle]);
			TrackedProjectiles.erase(handle);
		}
	}
}
