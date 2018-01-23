January 15, 2018 17:45:59 Library.fmp12 - clearpicture4 -1-
pictures: clearpicture4
#
#Prevent open reference window from being
#closed and the Tag Menus window from being
#resized during this process.
Set Variable [ $$stopClosingResizingWindows; Value:1 ]
#
#Capture field name where the action of
#the next script needs to focus, and then
#perform this script.
Go to Field [ report::kTag4 ]
Perform Script [ “removeTestResultOrInfoRecordFromReport” ]
Go to Field [ ]
