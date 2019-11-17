November 12, 2019 22:46:52 Library.fmp12 - newTag -1-
tagMenu: probablyNotInUse: newTag
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#
#Not sure where this script is used? Can
#probably be replaced with newTagMenuTag
#script, and then deleted. Testing required.
#
#
Set Variable [ $rule; Value:tagTable::kGroupOrTest ]
New Record/Request
Set Field [ tagTable::kGroupOrTest; $rule ]
Go to Field [ tagTable::tag ]
#
