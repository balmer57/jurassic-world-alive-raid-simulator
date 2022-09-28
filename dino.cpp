#include "dino.h"
#include "modifiers.h"
#include "actions.h"

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
            action_groups.emplace(group_it, new ActionGroup(TARGET_TEAM, {new RemoveTaunt()}));
            group_it = action_groups.end();
            break;
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

void Dino::Impose(const Modifier *mod)
{
    mod->Impose(*this);
    mods.emplace_back(mod);
}

int Dino::Dispose(int type_flags)
{
    int count = 0;
    for(auto mod_it = mods.begin(); mod_it != mods.end(); ) {
        if (mod_it->modifier->Type() & type_flags) {
            mod_it->modifier->Dispose(*this);
            mods.erase(mod_it++);
            ++count;
        } else
            ++mod_it;
    }
    return count;
}
