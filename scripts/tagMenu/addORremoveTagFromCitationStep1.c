tagMenu: addORremoveTagFromCitationStep1
#
#Stop script if user is looking at item/detail tags
#in add mode, as these tags cannot be applied
#to reference records.
If [ $$add = 1 and $$citationMatch = "testItem" ]
Show Custom Dialog [ Message: "You cannot tag reference records with item tags. So why then are there buttons? The buttons show up because I have not made time to create a separate layout just for item tags. This issue has been logged as a minor irritation."; Buttons: “OK” ]
Exit Script [ ]
End If
#
// #Due to the fact that users click the add tag button
// #when they want to find records tagged with a tag,
// #I'm making it so that users can only add tags in edit mode.
// If [ Left (Get (LayoutName) ; 3 ) = "ref" and $$stopAdd = "" ]
// Show Custom Dialog [ Message: "Click the edit button in the References window (but not in Learn window) to add/change tags. This inconvience was put in place because users kept forgetting to click find before click the P or O buttons."; Buttons: “OK” ]
// Exit Script [ ]
// End If
#
#Remove focus from field so can see
#conditional formatting.
Go to Field [ ]
#
#Determine if user is looking at nodes or keywords.
If [ $$citationMatch = "key" ]
Perform Script [ “addORremoveTagFromCitationStep2keyword” ]
Else If [ $$citationMatch = "node" ]
Perform Script [ “addORremoveTagFromCitationStep2node” ]
Close Window [ Name: "reorder"; Current file ]
Set Variable [ $$stopLoadTagRecord ]
#
#Get the keys currently unlocking who is a
#copyright holder.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#Remove key from keychain if it is on
#the copyright holder keychain.
If [ reference::knodeOther = "" and reference::knodePrimary = "" ]
Set Field [ reference::kcopyrightHolder; Substitute ( $keyChain ; "node738fds8ef" & "¶" ; "" ) ]
End If
#
Select Window [ Name: "Tag Menus Change Back When Done"; Current file ]
If [ Get ( WindowName ) = "Tag Menus Change Back When Done" ]
Close Window [ Name: "Tag Menus"; Current file ]
Set Window Title [ Of Window: "Tag Menus Change Back When Done"; Current file; New Title: "Tag Menus" ]
End If
Refresh Window
End If
January 7, 平成26 16:23:44 Imagination Quality Management.fp7 - addORremoveTagFromCitationStep1 -1-
