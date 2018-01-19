January 18, 2018 15:50:57 Library.fmp12 - enterShortOrLongTagField -1-
reference: enterShortOrLongTagField
#
#Stops script when user is going to the Learn
#or Reference section.
If [ $$stopGoToKeyTag ≠ "" ]
Set Variable [ $$stopGoToKeyTag ]
Exit Script [ ]
End If
#
#Allow empty picture fields to be hidden, and
#the tag's text box to appear longer, basically
#covering up the unused picture field on the
#Reference Cite Tag Menu.
If [ reference::referenceShortLong = "" and Get (LayoutTableName) = "reference" ]
Go to Object [ Object Name: "tag 2" ]
Else If [ reference::referenceShortLong ≠ "" and Get (LayoutTableName) = "reference" ]
Go to Object [ Object Name: "tag 1" ]
End If
#
#Allow empty picture fields to be hidden, and
#the tag's text box to appear longer, basically
#covering up the unused picture field on the
#Learn Key, Node, and Reference Tag Menus.
If [ Get (LayoutTableName) = "tagMenus" and tagMenus::tagTestTextItemOrLongTagField ≠ "" ]
Go to Object [ Object Name: "tag 1" ]
Else If [ Get (LayoutTableName) = "tagMenus" and tagMenus::tagTestTextItemOrLongTagField = "" ]
Go to Object [ Object Name: "tag 2" ]
End If
#
