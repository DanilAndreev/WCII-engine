#include "pch.h"
#include "MultiTeamSelector.h"


MultiTeamSelector::MultiTeamSelector()
{
}


MultiTeamSelector::~MultiTeamSelector()
{
}

void MultiTeamSelector::select(int team) {
	selectData* target = searchTeam(team);
	if (target) {
		target->first = true;
	}
	else {
		addNewTeamSelectData(team)->first = true;
	}
}

void MultiTeamSelector::unselect(int team) {
	selectData* target = searchTeam(team);
	if (target) {
		target->first = false;
	}
}

bool MultiTeamSelector::isSelected(int team) {
	selectData* target = searchTeam(team);
	if (target) {
		return target->first;
	}
	return false;
}

selectData* MultiTeamSelector::searchTeam(int team) {
	for (int i = 0; i < selectedList.size(); i++) {
		if (selectedList[i].second == team) {
			return &selectedList[i];
		}
	}
	return NULL;
}

selectData* MultiTeamSelector::addNewTeamSelectData(int team) {
	if (!searchTeam(team)) {
		selectData temp(false, team);
		selectedList.push_back(temp);
		selectData* ptr = searchTeam(team);
		return ptr;
	}
	return NULL;
}
