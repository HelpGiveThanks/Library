January 15, 2018 17:45:18 Library.fmp12 - clearpicture3 -1-
pictures: clearpicture3
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
Go to Field [ report::kTag3 ]
Perform Script [ “removeTestResultOrInfoRecordFromReport (update name change reportClearDiscoveryLink)” ]
Go to Field [ ]
