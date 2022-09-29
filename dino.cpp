#include "dino.h"
#include "modifiers.h"
#include "actions.h"
#include "logger.h"
#include <memory>

using namespace std;

Ability::Ability(int _delay, int _cooldown, bool _priority, std::initializer_list<ActionGroup *> _action_groups)
    : delay(_delay)
    , cooldown(_cooldown)
    , priority(_priority)
    , action_groups(_action_groups.begin(), _action_groups.end())
{
    for (auto group_it = action_groups.begin(); group_it != action_groups.end(); ++group_it) {
        for (auto action_it = (*group_it)->actions.begin(); action_it != (*group_it)->actions.end(); ++action_it) {
            if (!dynamic_cast<ImposeTaunt *>(action_it->get()))
                continue;
            action_groups.emplace(group_it, new ActionGroup(TARGET_TEAM, {new Remove(TAUNT)}));
            return;
        }
    }
}

void Ability::Do(Dino &self, Dino *team[], int size) const
{
    for (int i = 0; i < (int)action_groups.size(); ++i) {
        action_groups[i]->Do(self, team, size);
    }
}

void Dino::Prepare(int _ability_id)
{
    ability_id = _ability_id;
    threatened = kind->ability[ability_id]->Threatened(*this);
    priority = kind->ability[ability_id]->Priority(*this);
}

void Dino::Attack(Dino *team[], int size)
{
    kind->ability[ability_id]->Do(*this, team, size);
}

void Dino::CounterAttack(Dino &target)
{
    //kind->counter_attack->Do(*this, target);
}

void Dino::Impose(const Modifier *mod, Dino &author)
{
    mod->Impose(*this);
    mods.emplace_back(mod);
    Logger::Log("%s imposes %s to %s for %d turns%s\n", author.name.c_str(), mod->name.c_str(), name.c_str(), mod->duration, mod->number ? strprintf(" %d attack(s)", mod->number).c_str() : "");
}

int Dino::Dispose(int type_flags, Dino &author)
{
    int count = 0;
    for(auto mod_it = mods.begin(); mod_it != mods.end(); ) {
        if (mod_it->modifier->Type() & type_flags) {
            Logger::Log("%s disposes %s from %s\n", author.name.c_str(), mod_it->modifier->name.c_str(), name.c_str());
            mod_it->modifier->Dispose(*this);
            mods.erase(mod_it++);
            ++count;
        } else
            ++mod_it;
    }
    return count;
}

void Dino::PassTurn()
{
    for (auto mod_it = mods.begin(); mod_it != mods.end(); ) {
        if (mod_it->duration == 0) {
            mods.erase(mod_it++);
            Logger::Log("%s loses %s\n", name.c_str(), mod_it->modifier->name.c_str());
        } else
            --mod_it++->duration;
    }
}
