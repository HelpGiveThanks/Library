August 30, 2018 12:33:34 Library.fmp12 - enterShortOrLongTagField -1-
reference: enterShortOrLongTagField
#
#
#Exit script if it was started after the
#loadTagRecord script finished, which
#will be less than a second ago.
If [ Get ( CurrentTime ) - $$ifScriptRunsHalfSecondAfterThisOneHaltIt < 1 ]
Exit Script [ ]
End If
#
#
#Stops script when user is going to the Learn
#or Reference section, except for exit script
#when user has navigated to a key tag menu
#record by clicking on the order-number
#popup menu.
If [ $$stopGoToKeyTag ≠ "" ]
Set Variable [ $$stopGoToKeyTag ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
If [ $$keyOrderNumberPossibleChanged ≠ "" ]
#Disable this variable as the exit script needs
#to know if the order field triggered this script.
// Set Variable [ $$keyOrderNumberPossibleChanged ]
Perform Script [ “exit” ]
End If
Exit Script [ ]
End If
#
#
#Allow empty picture fields to be hidden, and
#the tag's text box to appear longer, basically
#covering up the unused picture field on
#reference table Tag Menus.
If [ reference::referenceHidePicture = "" and Get (LayoutTableName) = "reference" ]
#
#If in inventory mode where the empty picture
#and title and description fields are hidden do
#the following to reveal these hidden fields, and
#if currently showing to go the field the user is
#currently not in, thus allowing the user to
#switch between these temporarily unhidden
#fields.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
Refresh Window
If [ Get ( ActiveFieldName ) ≠ "Title" ]
Set Variable [ $$editLocation ]
Go to Object [ Object Name: "tag 1" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
Refresh Window
Else
Set Variable [ $$editLocation ]
Go to Object [ Object Name: "tag 2" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
Refresh Window
End If
#
Else
#
#Open reference in a new window.
Perform Script [ “viewReference (update) ” ]
Exit Script [ ]
End If
#
#
Else If [ reference::referenceHidePicture ≠ "" and Get (LayoutTableName) = "reference" ]
#
#If in inventory mode where the empty picture
#and title and description fields are hidden do
#the following to reveal these hidden fields and
#if currently showing to go the field the user is
#currently not in, thus allowing the user to
#switch between these temporarily unhidden
#fields.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
Refresh Window
If [ Get ( ActiveFieldName ) ≠ "Title" ]
Set Variable [ $$editLocation ]
Go to Object [ Object Name: "tag 1" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
Refresh Window
Else
Set Variable [ $$editLocation ]
Go to Object [ Object Name: "tag 2" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
Refresh Window
End If
Exit Script [ ]
#
Else
#
#Open reference in a new window.
Perform Script [ “viewReference (update) ” ]
Exit Script [ ]
End If
End If
#
#
#Allow empty picture fields to be hidden, and
#the tag's text box to appear longer, basically
#covering up the unused picture field on tag
#table Tag Menus layouts.
If [ Get (LayoutTableName) = "tagMenus" and tagMenus::tagTestTextItemOrLongTagField ≠ "" ]
Go to Object [ Object Name: "tag 1" ]
Else If [ Get (LayoutTableName) = "tagMenus" and tagMenus::tagTestTextItemOrLongTagField = "" ]
Go to Object [ Object Name: "tag 2" ]
End If
#
#
