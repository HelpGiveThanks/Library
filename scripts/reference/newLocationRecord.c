July 20, 2018 21:50:41 Library.fmp12 - newLocationRecord -1-
reference: newLocationRecord
#
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode (update)” ]
#
#Copy primary key word/subject of current
#record so it can be given to then new record.
#The user will expect that clicking the new
#button will result in new record in the current
#subject area.
If [ reference::kkeywordPrimary = "" ]
Set Variable [ $P; Value:31120182009273386 ]
Else
Set Variable [ $P; Value:reference::kkeywordPrimary ]
End If
#Copy the current order number.
Set Variable [ $pubYear; Value:reference::publicationYearOrStuffOrderNumber ]
#
#Now create a new record and give it the
#copied information.
Go to Field [ ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Record/Request
Set Field [ reference::kkeywordPrimary; $P ]
Set Field [ reference::publicationYearOrStuffOrderNumber; $pubYear ]
#
#Load new record as the record being
#focused on.
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
Perform Script [ “loadTagRecord (update)” ]
#
#Now go the new record's title field.
Set Variable [ $$editLocation; Value:reference::_Lreference ]
Refresh Window
Set Variable [ $$editLocation ]
Go to Object [ Object Name: "tag 1" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
Refresh Window
Set Variable [ $$doNotHaltOtherScripts ]
#
#
