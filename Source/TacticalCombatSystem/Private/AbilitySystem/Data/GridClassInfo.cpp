// Copyright  CtrlShiftSpace


#include "AbilitySystem/Data/GridClassInfo.h"

FGridClassAssetInfo UGridClassInfo::GetGridClassAssetInfo(EGridShape GridShape) const
{
	return GridClassAssetInfoMap.FindChecked(GridShape);
}
