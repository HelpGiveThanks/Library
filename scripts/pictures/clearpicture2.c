January 15, 2018 17:44:30 Library.fmp12 - clearpicture2 -1-
pictures: clearpicture2
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
Go to Field [ report::kTag2 ]
Perform Script [ “removeTestResultOrInfoRecordFromReport (update name change reportClearDiscoveryLink)” ]
Go to Field [ ]
