#pragma once
#include <map>
#include "Globals.h"
#include "Wrappers.h"
#include "Protobuf Messages/usermessages.pb.h"

namespace Hacks {
	class ParticleAbilityWarner {
		// Draws a dashed red line from begin to end
		// Returns the wrapper for the created particle
		auto DrawTrajectory(Vector3 begin, Vector3 end) {
			auto pw = Globals::ParticleManager->CreateParticle(
				"particles/ui_mouseactions/range_finder_tower_line.vpcf",
				PATTACH_WORLDORIGIN,
				ctx.assignedHero
			);
			Vector3 boolCp{ 1, 0, 0 };
			pw.particle
				->SetControlPoint(2, &begin)
				->SetControlPoint(6, &boolCp)
				->SetControlPoint(7, &end);
			return pw;
		}

		enum AbilityParticles : uint64_t {
			AP_PUDGE_MEAT_HOOK = 16517413739925325824,
			AP_KOTL_ILLUMINATE = 2498180139172148061
		};

		struct AbilityParticleInfo {
			AbilityParticles nameIndex;
			Vector3 begin{}, end{};
			BaseNpc* owner;
		};

		std::map<uint32_t, AbilityParticleInfo> queuedParticleIndexes{};
		std::map<uint32_t, CDOTAParticleManager::ParticleWrapper> TrackedAbilityParticles{};
	public:
		// Meat hook:
		// On create: begin = fallback_position 
		// Update: end = control point 1

		// Illuminate:
		// 
		// Update: velocity = control point 1

		void ProcessParticleMsg(NetMessageHandle_t* msgHandle, google::protobuf::Message* msg) {
			if (msgHandle->messageID == 145) {

				auto pmMsg = reinterpret_cast<CUserMsg_ParticleManager*>(msg);
				auto msgIndex = pmMsg->index();
				switch (pmMsg->type()) {
					// Catches any net-created particles to see if they represent an ability
					// Places them into queuedParticleIndexes until further messages are processed
				case GAME_PARTICLE_MANAGER_EVENT_CREATE: {

					auto particle = pmMsg->create_particle();
					switch (particle.particle_name_index()) {

					case AbilityParticles::AP_KOTL_ILLUMINATE:
					case AbilityParticles::AP_PUDGE_MEAT_HOOK:
						auto& qParticle = queuedParticleIndexes[msgIndex] = AbilityParticleInfo{
							.nameIndex = (AbilityParticles)particle.particle_name_index()
						};

						if (qParticle.nameIndex == AbilityParticles::AP_KOTL_ILLUMINATE) {
							for (auto& hero : ctx.heroes)
								if (!strcmp(hero->GetUnitName(), "npc_dota_hero_keeper_of_the_light")) {
									qParticle.owner = hero;
									break;
								}
							break;
						}
						break;
					}

					break;
				}
													   // Gets the ability owner and determines if the ability trajectory will be drawn
				case GAME_PARTICLE_MANAGER_EVENT_UPDATE_ENT:
				{
					if (!queuedParticleIndexes.count(msgIndex))
						break;

					auto updParticleEnt = pmMsg->update_particle_ent();
					auto owner = Interfaces::EntitySystem->GetEntity(NH2IDX(updParticleEnt.entity_handle()));
					// If they're not an enemy we dequeue the particle's index
					if (!owner || owner->GetTeam() == ctx.assignedHero->GetTeam()) {
						queuedParticleIndexes.erase(msgIndex);
						break;
					}
					auto& info = queuedParticleIndexes[msgIndex];

					switch (info.nameIndex) {
					case AbilityParticles::AP_PUDGE_MEAT_HOOK: {
						info.begin = Vector3{
							updParticleEnt.fallback_position().x(),
							updParticleEnt.fallback_position().y(),
							updParticleEnt.fallback_position().z()
						};
						info.owner = (BaseNpc*)owner;
						break;
					}
					}
				}
				case GAME_PARTICLE_MANAGER_EVENT_UPDATE:
				{
					if (!queuedParticleIndexes.count(msgIndex))
						break;


					auto& info = queuedParticleIndexes[msgIndex];
					auto cpIdx = pmMsg->update_particle().control_point();
					auto cpVal = Vector3{
							pmMsg->update_particle().position().x(),
							pmMsg->update_particle().position().y(),
							pmMsg->update_particle().position().z()
					};

					switch (info.nameIndex) {
					case AP_PUDGE_MEAT_HOOK:
						// Hook's destination
						if (cpIdx == 1) {
							info.end = cpVal;
							TrackedAbilityParticles[msgIndex] = DrawTrajectory(info.begin, info.end);
						}
						break;
					case AP_KOTL_ILLUMINATE:
						if (cpIdx == 0)
							info.begin = cpVal;
						// Illuminate's velocity
						// Same calculations as in LinearProjectileWarner
						else if (cpIdx == 1) {
							auto castRange =
								info.owner->GetAbilities()[7] // illuminate is moved to index 7 when End Illuminate takes its place
								.GetAs<BaseAbility>()->GetEffectiveCastRange();
							auto ratio = castRange / cpVal.AsVec2().Length();
							auto enlargedVec = cpVal.AsVec2() * ratio;
							info.end = info.begin + enlargedVec;
							TrackedAbilityParticles[msgIndex] = DrawTrajectory(info.begin, info.end);
						}
						break;
					}
					break;
				}
				case GAME_PARTICLE_MANAGER_EVENT_DESTROY: {
					queuedParticleIndexes.erase(msgIndex);
					if (TrackedAbilityParticles.count(msgIndex)) {
						Globals::ParticleManager->DestroyParticle(TrackedAbilityParticles[msgIndex]);
						TrackedAbilityParticles.erase(msgIndex);
					}
					break;
				}
				};
			}
		}
	};
}
namespace Modules {
	Hacks::ParticleAbilityWarner ParticleAbilityWarner{};
}