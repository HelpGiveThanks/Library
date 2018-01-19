January 15, 2018 17:43:44 Library.fmp12 - clearpicture1 -1-
pictures: clearpicture1
#
#
#Prevent open reference window from being
#closed and the Tag Menus window from being
#resized during this process.
Set Variable [ $$stopClosingResizingWindows; Value:1 ]
#
#Capture field name where the action of
#the next script needs to focus, and then
#perform this script.
Go to Field [ report::kTag1 ]
Perform Script [ “removeTestResultOrInfoRecordFromReport (update name change reportClearDiscoveryLink)” ]
Go to Field [ ]
