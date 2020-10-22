#pragma once

typedef pair<bool, int> selectData;

class MultiTeamSelector {
protected:
	vector<selectData> selectedList;
public:
	MultiTeamSelector();
	virtual ~MultiTeamSelector();
	void select(int team); // selects input team
	void unselect(int team); // unselects input team
	bool isSelected(int team); // returns true if input command is selected or false when not adn false if team not found
private:
	selectData* searchTeam(int team); // returns pointer to element with selection data in selectedList or NULL when team not found
	selectData* addNewTeamSelectData(int team); // adds new selectData to selectedList with false selected value and returns pointer to this selectData element or NULL if input team exist
};

