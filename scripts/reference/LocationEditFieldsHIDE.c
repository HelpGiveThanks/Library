July 20, 2018 21:51:53 Library.fmp12 - LocationEditFieldsHIDE -1-
reference: LocationEditFieldsHIDE
#
#Stop this script when first navigating to a
#record. User most likely just wanted to
#go this record; not edit it.
If [ $$editLocation = "" ]
Exit Script [ ]
End If
#
#If the user decided not continue editing this
#Hide the edit fields (which are hidden once
#this variable is blank and the window
#is refreshed).
Set Variable [ $$editLocation ]
Refresh Window
#
#Once the field is hidden, re-load this variable
#so the next time the user clicks on the picture
#field (if there is no picture) they will be taken
#to the edit fields. If this variable remains
#blank, then the next time they click on an
#empty picture field, nothing will happen, which
#can be frustrating if you're trying to edit.
Set Variable [ $$editLocation; Value:reference::_Lreference ]
#
#
