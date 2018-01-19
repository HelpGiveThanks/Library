January 18, 2018 14:53:32 Library.fmp12 - showTagsReferenceForLink3 -1-
reference: showTagsReferenceForLink3
#
#If user is not in add mode then inform user they
#must be before the database will show them reference
#data. The reason for this is because the layout
#in the reference or learn window changes to the
#add tag from these windows to the Tag Menu
#item selected. So instead of having the system
#automatically go into add mode, the user must
#decide they want to do this and thus be expecting
#a change in the layouts. Otherwise this change
#could confuse a user. So at the cost of minor
#inconvience I have choose not to have the system
#guess the user wants to go into add mode and is
#expecting the system to do that when they click
#one of these numbered buttons on the showEvenMore
#layouts.
If [ $$add = "" ]
Show Custom Dialog [ Message: "Click the 'add' button above and then click this button to see citation for this item. "; Default
Button: “OK”, Commit: “No” ]
Exit Script [ ]
End If
#
#If the field is blank then stop the script.
#No poin in looking for a record where there isn't one.
If [ tagMenus::Ktitle3 = "" ]
Exit Script [ ]
End If
#
#Capture the key to unlock the record it belongs to.
Set Variable [ $key; Value:tagMenus::Ktitle3 ]
#
#Select the reference window.
Select Window [ Name: "References"; Current file ]
#
#Loop to selected reference if not selected.
If [ reference::_Lreference ≠ $key ]
#
#Prevent record loading script during loops to
#find wanted record, which would slow down system.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Now loop thru all the records until the record
#that fits the key is found.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ reference::_Lreference = $key ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Allow the record load script to run and run it.
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord (update name change loadCitation)” ]
End If
#
#Select Tag Menus window and conditionally
#format any items that may be linked to record
#in the other window.
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Show user reference record selected.
Select Window [ Name: "References"; Current file ]
#
